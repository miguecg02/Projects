package Ejercicio_2;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;

public class ServerReplica1 extends UnicastRemoteObject implements Donaciones_I {

    private Map<String, Double> clientesDonaciones;
    private double totalDonado;

    public ServerReplica1() throws RemoteException {
        super();
        clientesDonaciones = new HashMap<>();
        totalDonado = 0.0;
    }

    @Override
    public boolean registrarCliente(String nombreCliente) throws RemoteException {
        if (!clientesDonaciones.containsKey(nombreCliente)) {
            clientesDonaciones.put(nombreCliente, 0.0);
            return true;
        }
        return false;
    }

      @Override
     public Map<String, Double> getclientesDonaciones(){
        return this.clientesDonaciones;
    }

    @Override
    public void realizarDonacion(String nombreCliente, double monto) throws RemoteException {
        if (clientesDonaciones.containsKey(nombreCliente)) {
            // Donación en esta réplica
            clientesDonaciones.put(nombreCliente, clientesDonaciones.get(nombreCliente) + monto);
            totalDonado += monto;
        } else {
            // Si no está registrado en esta réplica, se consulta la otra réplica
            try {
                Registry registry2= LocateRegistry.getRegistry("localhost", 1101);
                Donaciones_I replica2 = (Donaciones_I) registry2.lookup("Replica2");

                if (replica2.consultarListaDonantes().contains(nombreCliente)) {
                    replica2.realizarDonacion(nombreCliente, monto); // Donar en la réplica 2
                }
            } catch (Exception e) {
                System.err.println("Error al realizar la donación en la otra réplica: " + e.getMessage());
            }
        }
    }

    @Override
    public double consultarTotalDonadoReplica()  throws RemoteException{
        return this.totalDonado;
    }

    @Override
    public double consultarTotalDonado() throws RemoteException {
        double totalDonadoReplica2 = 0.0;

        try {
            // Intentar consultar el total donado en la réplica 2
            System.out.println("Consultando el total donado en la réplica 2...");
            Registry registry2 = LocateRegistry.getRegistry("localhost", 1101);
            Donaciones_I replica2 = (Donaciones_I) registry2.lookup("Replica2");
            totalDonadoReplica2 = replica2.consultarTotalDonadoReplica();
        } catch (RemoteException e) {
            // Mostrar información detallada en caso de error de red o comunicación
            System.err.println("Error al consultar el total donado en la réplica 2:");
            e.printStackTrace();
            // Si ocurre un error, retornar el total donado de la réplica local
        } catch (NotBoundException e) {
            System.err.println("La réplica 2 no está registrada o disponible.");
        }

        // Asegurarse de retornar el total donado de ambas réplicas
        return totalDonadoReplica2 + this.totalDonado;
    }

   @Override
    public List<String> consultarListaDonantes() throws RemoteException {
        List<String> listaDonantes = new ArrayList<>(clientesDonaciones.keySet());

        // Consultar la lista de donantes en la réplica 2
        try {
            Registry registry2 = LocateRegistry.getRegistry("localhost", 1101);
            Donaciones_I replica2 = (Donaciones_I) registry2.lookup("Replica2");
              // Obtener los donantes de la réplica2
        Map<String, Double> donantesReplica2 = replica2.getclientesDonaciones();

        // Fusionar las listas de donantes
        for (String donante : donantesReplica2.keySet()) {
            if (!listaDonantes.contains(donante)) {
                listaDonantes.add(donante);
            }
        }

        } catch (Exception e) {
            System.err.println("Error al consultar la lista de donantes en la réplica 2: " + e.getMessage());
        }

        return listaDonantes;
    }

    @Override
    public int consultarNumeroClientes() throws RemoteException {
        return clientesDonaciones.size();
    }

    @Override
    public List<String> consultarTopDonantes() throws RemoteException {
        List<Map.Entry<String, Double>> listaDonantes = new ArrayList<>(clientesDonaciones.entrySet());

        // Consultar la lista de donantes en la réplica 2s
        try {
            Registry registry2 = LocateRegistry.getRegistry("localhost", 1101);
            Donaciones_I replica2 = (Donaciones_I) registry2.lookup("Replica2");
            Map<String, Double> donantesReplica2 = replica2.getclientesDonaciones();

            // Fusionar las listas de donantes de ambas réplicas
            for (Map.Entry<String, Double> donante : donantesReplica2.entrySet()) {
                listaDonantes.add(donante);  // Añadir la entrada (nombre, monto) de la réplica 2
            }

        } catch (Exception e) {
            System.err.println("Error al consultar el top donantes en la réplica 2: " + e.getMessage());
        }

        // Ordenar por monto donado en orden descendente
        listaDonantes.sort((e1, e2) -> Double.compare(e2.getValue(), e1.getValue()));

        // Crear la lista final de donantes
        List<String> topDonantes = new ArrayList<>();
        for (int i = 0; i < Math.min(10, listaDonantes.size()); i++) {
            topDonantes.add(listaDonantes.get(i).getKey() + ": " + listaDonantes.get(i).getValue());
        }

        return topDonantes;
    }

    @Override
    public double consultarTotalDonadoPorCliente(String nombreCliente) throws RemoteException {
        // Primero, consultar si el cliente está registrado en la réplica local (Replica1)
        Double totalReplica1 = clientesDonaciones.getOrDefault(nombreCliente, null);

        // Si está registrado en esta réplica, devolver el total de donaciones de esta réplica
        if (totalReplica1 != null) {
            return totalReplica1;
        }

        // Si no está registrado en esta réplica, consultar en la réplica 2
        try {
            Registry registry2 = LocateRegistry.getRegistry("localhost", 1101);
            Donaciones_I replica2 = (Donaciones_I) registry2.lookup("Replica2");

            // Consultar si el cliente está registrado en la réplica 2
            Double totalReplica2 = replica2.consultarTotalDonadoPorCliente(nombreCliente);
            if (totalReplica2 != 0.0) {
                return totalReplica2;  // Si está registrado en la réplica 2, devolver el total
            }
        } catch (Exception e) {
            System.err.println("Error al consultar las donaciones de " + nombreCliente + " en la réplica 2: " + e.getMessage());
        }

        // Si el cliente no está registrado en ninguna réplica, devolver 0.0
        return 0.0;
    }



    @Override
    public boolean registrarClienteInteligente(String nombreCliente) throws RemoteException {
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 1101);
            Donaciones_I replica2 = (Donaciones_I) registry.lookup("Replica2");

            boolean registradoEnEsta = clientesDonaciones.containsKey(nombreCliente);
            boolean registradoEnOtra = replica2.consultarListaDonantes().contains(nombreCliente);

            if (registradoEnEsta || registradoEnOtra) return false;

            int total1 = this.consultarNumeroClientes();
            int total2 = replica2.consultarNumeroClientes();

            if (total1 <= total2) return this.registrarCliente(nombreCliente);
            else return replica2.registrarCliente(nombreCliente);

        } catch (Exception e) {
            System.err.println("Error en registro inteligente: " + e.getMessage());
            return false;
        }
    }

    public static void main(String[] args) {
        try {
            ServerReplica1 replica1 = new ServerReplica1();
            Registry registry = LocateRegistry.createRegistry(1100);
            registry.rebind("Replica1", replica1);
            System.out.println("Servidor Replica1 en funcionamiento...");
        } catch (RemoteException e) {
            System.err.println("Error en ServerReplica1:");
            e.printStackTrace();
        }
    }
}

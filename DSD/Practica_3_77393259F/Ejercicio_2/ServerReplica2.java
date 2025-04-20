package Ejercicio_2;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;

public class ServerReplica2 extends UnicastRemoteObject implements Donaciones_I {

    private Map<String, Double> clientesDonaciones;
    private double totalDonado;

    public ServerReplica2() throws RemoteException {
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
    public boolean registrarClienteInteligente(String nombreCliente) throws RemoteException {
        try {
            // Consultar si ya está registrado en esta réplica
            if (clientesDonaciones.containsKey(nombreCliente)) {
                return false;
            }

            // Consultar la otra réplica
            Registry registry1 = LocateRegistry.getRegistry("localhost", 1100);
            Donaciones_I replica1 = (Donaciones_I) registry1.lookup("Replica1");

            if (replica1.consultarListaDonantes().contains(nombreCliente)) {
                return false; // Ya está registrado en la otra réplica
            }

            // Consultar número de clientes en ambas réplicas
            int numClientesReplica1 = replica1.consultarNumeroClientes();
            int numClientesReplica2 = this.consultarNumeroClientes();

            if (numClientesReplica1 <= numClientesReplica2) {
                return replica1.registrarCliente(nombreCliente); // Registrar en réplica 1
            } else {
                return this.registrarCliente(nombreCliente); // Registrar en esta réplica
            }

        } catch (Exception e) {
            System.err.println("Error al registrar inteligentemente: " + e.getMessage());
            return false;
        }
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
                Registry registry1 = LocateRegistry.getRegistry("localhost", 1100);
                Donaciones_I replica1 = (Donaciones_I) registry1.lookup("Replica1");

                if (replica1.consultarListaDonantes().contains(nombreCliente)) {
                    replica1.realizarDonacion(nombreCliente, monto); // Donar en la réplica 1
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
            double totalDonadoReplica1 = 0.0;

            try {
                // Intentar consultar el total donado en la réplica 2
                System.out.println("Consultando el total donado en la réplica 1...");
                Registry registry1 = LocateRegistry.getRegistry("localhost", 1100);
                Donaciones_I replica1 = (Donaciones_I) registry1.lookup("Replica1");
                totalDonadoReplica1 = replica1.consultarTotalDonadoReplica();
            } catch (RemoteException e) {
                // Mostrar información detallada en caso de error de red o comunicación
                System.err.println("Error al consultar el total donado en la réplica 1:");
                e.printStackTrace();
                // Si ocurre un error, retornar el total donado de la réplica local
            } catch (NotBoundException e) {
                System.err.println("La réplica 1 no está registrada o disponible.");
            }

            // Asegurarse de retornar el total donado de ambas réplicas
            return totalDonadoReplica1 + this.totalDonado;
        }


   @Override
public List<String> consultarListaDonantes() throws RemoteException {
    List<String> listaDonantes = new ArrayList<>(clientesDonaciones.keySet());

    // Consultar la lista de donantes en la réplica 1
    try {
        Registry registry1 = LocateRegistry.getRegistry("localhost", 1100);
        Donaciones_I replica1 = (Donaciones_I) registry1.lookup("Replica1");

        // Obtener los donantes de la réplica 1
        Map<String, Double> donantesReplica1 = replica1.getclientesDonaciones();

        // Fusionar las listas de donantes
        for (String donante : donantesReplica1.keySet()) {
            if (!listaDonantes.contains(donante)) {
                listaDonantes.add(donante);
            }
        }

    } catch (Exception e) {
        System.err.println("Error al consultar la lista de donantes en la réplica 1: " + e.getMessage());
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

        // Consultar la lista de donantes en la réplica 1
        try {
            Registry registry1 = LocateRegistry.getRegistry("localhost", 1100);
            Donaciones_I replica1 = (Donaciones_I) registry1.lookup("Replica1");
            Map<String, Double> donantesReplica1 = replica1.getclientesDonaciones();

            // Fusionar las listas de donantes de ambas réplicas
            for (Map.Entry<String, Double> donante : donantesReplica1.entrySet()) {
                listaDonantes.add(donante);  // Añadir la entrada (nombre, monto) de la réplica 1
            }

        } catch (Exception e) {
            System.err.println("Error al consultar el top donantes en la réplica 1: " + e.getMessage());
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
        // Primero, consultar si el cliente está registrado en la réplica local (Replica2)
        Double totalReplica2 = clientesDonaciones.getOrDefault(nombreCliente, null);

        // Si está registrado en esta réplica, devolver el total de donaciones de esta réplica
        if (totalReplica2 != null) {
            return totalReplica2;
        }

        // Si no está registrado en esta réplica, consultar en la réplica 1
        try {
            Registry registry1 = LocateRegistry.getRegistry("localhost", 1100);
            Donaciones_I replica1 = (Donaciones_I) registry1.lookup("Replica1");

            // Consultar si el cliente está registrado en la réplica 1
            Double totalReplica1 = replica1.consultarTotalDonadoPorCliente(nombreCliente);
            if (totalReplica1 != 0.0) {
                return totalReplica1;  // Si está registrado en la réplica 1, devolver el total
            }
        } catch (Exception e) {
            System.err.println("Error al consultar las donaciones de " + nombreCliente + " en la réplica 1: " + e.getMessage());
        }

        // Si el cliente no está registrado en ninguna réplica, devolver 0.0
        return 0.0;
    }




    public static void main(String[] args) {
        try {
            ServerReplica2 replica2 = new ServerReplica2();
            Registry registry = LocateRegistry.createRegistry(1101);
            registry.rebind("Replica2", replica2);
            System.out.println("Servidor Replica2 en funcionamiento...");
        } catch (RemoteException e) {
            System.err.println("Error en ServerReplica2:");
            e.printStackTrace();
        }
    }
}

package Ejercicio_2;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.util.*;

public class Cliente {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {

            // Permitir al usuario elegir réplica de conexión
            System.out.println("Seleccione la réplica a la que desea conectarse:");
            System.out.println("1. Replica1");
            System.out.println("2. Replica2");
            int opcionReplica = scanner.nextInt();
            scanner.nextLine();  // Limpiar buffer

            Donaciones_I replica;
            if (opcionReplica == 1) {
                Registry registry1 = LocateRegistry.getRegistry("localhost", 1100);
                replica = (Donaciones_I) registry1.lookup("Replica1");
            } else {
                Registry registry2 = LocateRegistry.getRegistry("localhost", 1101);
                replica = (Donaciones_I) registry2.lookup("Replica2");
            }

            System.out.print("Ingrese su nombre: ");
            String nombreCliente = scanner.nextLine();

            if (!replica.registrarClienteInteligente(nombreCliente)) {
                System.out.println("El cliente ya está registrado en alguna réplica.");
                return;
            }

            System.out.println("Cliente registrado correctamente.");

            while (true) {
                System.out.println("\n--- Menú ---");
                System.out.println("1. Realizar una donación");
                System.out.println("2. Consultar total donado");
                System.out.println("3. Ver lista de donantes");
                System.out.println("4. Top de donantes");
                System.out.println("5. Buscar donaciones de otro cliente");
                System.out.println("6. Salir");
                System.out.print("Opción: ");
                int opcion = scanner.nextInt();

                switch (opcion) {
                    case 1:
                        System.out.print("Monto a donar: ");
                        double monto = scanner.nextDouble();
                        if (monto > 0) {
                            replica.realizarDonacion(nombreCliente, monto);
                            System.out.println("Donación realizada.");
                        } else {
                            System.out.println("Monto inválido.");
                        }
                        break;
                    case 2:
                        double total = replica.consultarTotalDonado();
                        System.out.println("Total donado: " + total);
                        break;
                    case 3:
                        List<String> donantes = replica.consultarListaDonantes();
                        if (donantes.isEmpty()) {
                            System.out.println("No hay donantes.");
                        } else {
                            donantes.forEach(d -> System.out.println("- " + d));
                        }
                        break;
                    case 4:
                        List<String> top = replica.consultarTopDonantes();
                        top.forEach(System.out::println);
                        break;
                    case 5:
                        scanner.nextLine();  // limpiar buffer
                        System.out.print("Nombre del cliente: ");
                        String otro = scanner.nextLine();
                        double totalPorCliente = replica.consultarTotalDonadoPorCliente(otro);
                        System.out.println("Total donado por " + otro + ": " + totalPorCliente);
                        break;
                    case 6:
                        System.out.println("Hasta luego.");
                        return;
                    default:
                        System.out.println("Opción inválida.");
                }
            }

        } catch (RemoteException | NotBoundException e) {
            System.err.println("Error en Cliente:");
            e.printStackTrace();
        }
    }
}

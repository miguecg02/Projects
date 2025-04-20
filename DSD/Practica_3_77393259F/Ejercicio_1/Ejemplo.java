//Implementación de la interfaz remota. Fichero Ejemplo.java deldirectorio //“simple”

package Practica_3;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class Ejemplo implements Ejemplo_I {

    public void escribir_mensaje(String mensaje) throws RemoteException {
        try {
            System.out.println("\nEntra Hebra " + mensaje);
            if (mensaje.endsWith("0")) {
                System.out.println("Empezamos a dormir");
                Thread.sleep(5000);
                System.out.println("Terminamos de dormir");
            }
            System.out.println("Sale Hebra " + mensaje);
        } catch (InterruptedException e) {
            System.err.println("Error en el hilo: " + e.getMessage());
            Thread.currentThread().interrupt();
        }
    }

    public static void main(String[] args) {
        try {
            Ejemplo prueba = new Ejemplo();
            Ejemplo_I stub = (Ejemplo_I) UnicastRemoteObject.exportObject(prueba, 0);
            Registry registry = LocateRegistry.getRegistry();
            String nombre_objeto_remoto = "ServidorMensaje";  // Nombre significativo
            registry.rebind(nombre_objeto_remoto, stub);
            System.out.println("Ejemplo bound");
        } catch (Exception e) {
            System.err.println("Ejemplo exception:");
            e.printStackTrace();
        }
    }
}

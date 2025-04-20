//Implementación del cliente que accede a la interfaz remota Ejemplo_I.
//Fichero Cliente_Ejemplo.java del directorio “simple”
package Practica_3;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Cliente_Ejemplo implements Runnable {

    public String nombre_objeto_remoto = "ServidorMensaje";  // Nombre significativo
    public String server;

    public Cliente_Ejemplo(String server) {
        this.server = server;
    }

    @Override
    public void run() {
        System.out.println("Buscando el objeto remoto");
        try {
            // Conexión con el registro RMI del servidor
            Registry registry = LocateRegistry.getRegistry(server);
            Ejemplo_I instancia_local = (Ejemplo_I) registry.lookup(nombre_objeto_remoto);

            System.out.println("Invocando el objeto remoto desde el hilo: " + Thread.currentThread().getName());
            // Llamada al método remoto
            instancia_local.escribir_mensaje(Thread.currentThread().getName());
        } catch (Exception e) {
            System.err.println("Ejemplo_I exception en el hilo " + Thread.currentThread().getName() + ":");
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Uso: Cliente_Ejemplo <host> <número_de_hilos>");
            return;
        }

        String server = args[0]; // Nombre o dirección IP del servidor
        int n_hebras = Integer.parseInt(args[1]); // Número de hilos a ejecutar

        // Creamos vector de hebras y clientes
        Cliente_Ejemplo[] v_clientes = new Cliente_Ejemplo[n_hebras];
        Thread[] v_hebras = new Thread[n_hebras];

        // Creamos y lanzamos los hilos
        for (int i = 0; i < n_hebras; i++) {
            v_clientes[i] = new Cliente_Ejemplo(server);
            v_hebras[i] = new Thread(v_clientes[i], "Cliente " + i);
            v_hebras[i].start();  // Inicia cada hilo
        }
    }
}

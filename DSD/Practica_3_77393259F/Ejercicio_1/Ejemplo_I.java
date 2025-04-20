//Diseño de la interfaz. Fichero Ejemplo_I.java del directorio “simple”
package Practica_3;
//Diseño de la interfaz. Fichero Ejemplo_I.java del directorio “multi_hebra”
import java.rmi.Remote;
import java.rmi.RemoteException;
public interface Ejemplo_I extends Remote {
public void escribir_mensaje (String mensaje) throws RemoteException;
}

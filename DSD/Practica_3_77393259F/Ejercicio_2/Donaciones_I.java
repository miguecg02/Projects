package Ejercicio_2;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;
import java.util.*;

public interface Donaciones_I extends Remote {

    // Registrar un cliente
    boolean registrarCliente(String nombreCliente) throws RemoteException;

    // Realizar una donación
    void realizarDonacion(String nombreCliente, double monto) throws RemoteException;

    // Consultar el total donado
    double consultarTotalDonado() throws RemoteException;

    // Consultar la lista de donantes
    List<String> consultarListaDonantes() throws RemoteException;

    // Consultar el número total de clientes
    int consultarNumeroClientes() throws RemoteException;

    // Consultar el top de los donantes
    List<String> consultarTopDonantes() throws RemoteException;

    // Consultar las donaciones de un cliente específico
    double consultarTotalDonadoPorCliente(String nombreCliente) throws RemoteException;

     boolean registrarClienteInteligente(String nombreCliente) throws RemoteException;

    double consultarTotalDonadoReplica()  throws RemoteException;

    Map<String, Double> getclientesDonaciones()  throws RemoteException;
}

import sys
import math
from thrift.transport import TSocket, TTransport
from thrift.protocol import TBinaryProtocol
from calculadora import Calculadora

def conectar():
    """Establece la conexión con el servidor Thrift."""
    transport = TSocket.TSocket("127.0.0.1", 9090)  # Conectar al servidor en localhost:9090
    transport = TTransport.TBufferedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = Calculadora.Client(protocol)

    try:
        transport.open()
        print("Conectado al servidor.")
        return client, transport
    except Exception as e:
        print(f"Error al conectar con el servidor: {e}")
        sys.exit(1)

def menu():
    client, transport = conectar()

    while True:
        print("\nMenú de la Calculadora")
        print("1. Suma")
        print("2. Resta")
        print("3. Multiplicación")
        print("4. División")
        print("5. MCM")
        print("6. MCD")
        print("7. Factorial")
        print("8. Evaluar expresión")
        print("9. Seno")
        print("10. Coseno")
        print("11. Tangente")
        print("12. Área Triángulo")
        print("13. Área Círculo")
        print("14. Área Rectángulo")
        print("15. Suma de vectores")
        print("16. Producto de vectores")
        print("17. Suma de matrices")
        print("18. Multiplicación de matrices")
        print("19. Salir")

        opcion = input("Elige una opción: ")

        if opcion == "19":
            print("Cerrando conexión...")
            transport.close()
            break

        elif opcion in ["1", "2", "3", "4"]:
            n1 = int(input("Introduce el primer número: "))
            n2 = int(input("Introduce el segundo número: "))

            operaciones = {
                "1": client.suma,
                "2": client.resta,
                "3": client.multiplicacion,
                "4": client.division
            }
            resultado = operaciones[opcion](n1, n2)
            print(f"➡️ Resultado: {resultado}")

        elif opcion in ["5", "6"]:
            n1 = int(input("Introduce el primer número: "))
            n2 = int(input("Introduce el segundo número: "))
            n3 = int(input("Introduce el tercer número: "))
            n4 = int(input("Introduce el cuarto número: "))

            if opcion == "5":
                resultado = client.mcm(n1, n2, n3, n4)
                print(f"MCM de {n1}, {n2}, {n3}, {n4}: {resultado}")
            else:
                resultado = client.mcd(n1, n2, n3, n4)
                print(f"MCD de {n1}, {n2}, {n3}, {n4}: {resultado}")

        elif opcion == "7":
            n = int(input("Introduce un número: "))
            resultado = client.factorial(n)
            print(f"Factorial de {n}: {resultado}")

        elif opcion == "8":
            expresion = input("Introduce la expresión matemática (ej: 1*1*(2-4)): ")
            resultado = client.evaluar_expresion(expresion)
            print(f"Resultado de '{expresion}': {resultado}")


        elif opcion in ["9", "10", "11"]:
            angulo = float(input("Introduce el ángulo en grados: "))
            radianes = math.radians(angulo)
            funciones_trig = {
                "9": client.seno,
                "10": client.coseno,
                "11": client.tangente
            }
            resultado = funciones_trig[opcion](radianes)
            print(f"Resultado: {resultado}")

        elif opcion in ["12", "13", "14"]:
            if opcion == "12":
                base = float(input("Introduce la base del triángulo: "))
                altura = float(input("Introduce la altura del triángulo: "))
                resultado = client.area_triangulo(base, altura)
            elif opcion == "13":
                radio = float(input("Introduce el radio del círculo: "))
                resultado = client.area_circulo(radio)
            else:
                largo = float(input("Introduce el largo del rectángulo: "))
                ancho = float(input("Introduce el ancho del rectángulo: "))
                resultado = client.area_rectangulo(largo, ancho)
            print(f"Área calculada: {resultado}")

        elif opcion == "15":
            v1 = list(map(int, input("Ingresa el primer vector separado por espacios: ").split()))
            v2 = list(map(int, input("Ingresa el segundo vector separado por espacios: ").split()))
            try:
                print(f"Resultado: {client.suma_vectores(v1, v2)}")
            except Exception as e:
                print(f"Error al sumar vectores: {e}")

        elif opcion == "16":
            v1 = list(map(int, input("Ingresa el primer vector separado por espacios: ").split()))
            v2 = list(map(int, input("Ingresa el segundo vector separado por espacios: ").split()))
            try:
                print(f"Resultado: {client.multiplicacion_vectores(v1, v2)}")
            except Exception as e:
                print(f"Error al multiplicar vectores: {e}")

        elif opcion == "17":
            print("Ingresa la primera matriz fila por fila, separando elementos por espacio. Usa una línea vacía para terminar:")
            matriz1 = []
            while True:
                fila = input()
                if fila == "":
                    break
                matriz1.append(list(map(int, fila.split())))

            print("Ingresa la segunda matriz:")
            matriz2 = []
            for _ in range(len(matriz1)):
                fila = list(map(int, input().split()))
                matriz2.append(fila)

            try:
                resultado = client.suma_matrices(matriz1, matriz2)
                if isinstance(resultado, str):  # Si el servidor devuelve un mensaje de error
                    print(f"Error: {resultado}")
                else:
                    print("Resultado:")
                    for fila in resultado:
                        print(" ".join(map(str, fila)))
            except Exception as e:
                print(f"Error inesperado en la suma de matrices: {e}")


        elif opcion == "18":
            print("Ingresa la primera matriz fila por fila, separando elementos por espacio. Usa una línea vacía para terminar:")
            matriz1 = []
            while True:
                fila = input()
                if fila == "":
                    break
                matriz1.append(list(map(int, fila.split())))

            print("Ingresa la segunda matriz:")
            matriz2 = []
            for _ in range(len(matriz1[0])):  # Asegurar compatibilidad de dimensiones
                fila = list(map(int, input().split()))
                matriz2.append(fila)

            try:
                resultado = client.multiplicacion_matrices(matriz1, matriz2)
                if isinstance(resultado, str):  # Si el servidor devuelve un mensaje de error
                    print(f"Error: {resultado}")
                else:
                    print("Resultado:")
                    for fila in resultado:
                        print(" ".join(map(str, fila)))
            except Exception as e:
                print(f"Error inesperado en la multiplicacion de matrices: {e}")

if __name__ == "__main__":
    print("Cliente iniciado...")
    menu()

import math
import sys
import ast
import operator
from calculadora import Calculadora
from trigonometria import Trigonometria
from thrift.transport import TSocket, TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

class CalculadoraHandler:
    def __init__(self):
        self.log = {}

        # Conexión al servidor de trigonometría y áreas en el puerto 9091
        self.transporte_trig = TSocket.TSocket("127.0.0.1", 9091)
        self.transporte_trig = TTransport.TBufferedTransport(self.transporte_trig)
        protocolo_trig = TBinaryProtocol.TBinaryProtocol(self.transporte_trig)
        self.cliente_trig = Trigonometria.Client(protocolo_trig)
        self.transporte_trig.open()

    # Suma de 2 números enteros
    def suma(self, n1, n2):
        return n1 + n2

    # Resta de 2 números enteros
    def resta(self, n1, n2):
        return n1 - n2

    # Multiplicación de 2 números enteros
    def multiplicacion(self, n1, n2):
        return n1 * n2

    # División de 2 números reales, devuelve inf si se divide por cero
    def division(self, n1, n2):
        return n1 / n2 if n2 != 0 else float("inf")

    # Máximo común divisor (MCD) de cuatro números
    def mcd(self, a, b, c, d):
        return math.gcd(math.gcd(a, b), math.gcd(c, d))

    # Mínimo común múltiplo (MCM) de cuatro números
    def mcm(self, a, b, c, d):
        def lcm(x, y):
            return abs(x * y) // math.gcd(x, y)

        return lcm(lcm(a, b), lcm(c, d))


    # Factorial de un número entero no negativo
    def factorial(self, n):
        if n < 0:
            return "Error: No se puede calcular el factorial de un número negativo."
        return math.factorial(n)


    # Evalúa una expresión matemática pasada como string
    def evaluar_expresion(self, expresion):
        print(f"Evaluando expresión: {expresion}")
        try:
            arbol = ast.parse(expresion, mode="eval")
            return self._evaluar_ast(arbol.body)
        except Exception as e:
            print(f"Error al evaluar: {e}")
            return float("nan")


    # Cada operación del nodo BinOp debe asignarse a una operación real
    def _evaluar_ast(self, node):
        operadores = {
            ast.Add: operator.add,
            ast.Sub: operator.sub,
            ast.Mult: operator.mul,
            ast.Div: operator.truediv,
            ast.Pow: operator.pow,
            ast.USub: operator.neg
        }

        # Evaluar si es una expresión binaria, un número o una operación unaria
        if isinstance(node, ast.BinOp):
            izquierda = self._evaluar_ast(node.left)
            derecha = self._evaluar_ast(node.right)
            operacion = operadores.get(type(node.op))
            if operacion is operator.truediv and derecha == 0:
                return float("inf")  # Manejo de división por cero
            return operacion(izquierda, derecha)
        elif isinstance(node, ast.Constant):
            return node.value
        elif isinstance(node, ast.UnaryOp) and isinstance(node.op, ast.USub):
            return -self._evaluar_ast(node.operand)
        else:
            raise ValueError("Expresión inválida")

    # Suma dos matrices
    def suma_matrices(self, A, B):
        if not A or not B:
            return "Error: Las matrices no pueden estar vacías."

        if len(A) != len(B) or any(len(A[i]) != len(B[i]) for i in range(len(A))):
            return "Error: Las matrices deben tener las mismas dimensiones."

        try:
            return [[A[i][j] + B[i][j] for j in range(len(A[0]))] for i in range(len(A))]
        except Exception as e:
            return f"Error inesperado al sumar matrices: {str(e)}"

    # Multiplicación de dos matrices
    def multiplicacion_matrices(self, A, B):
        if not A or not B:
            return "Error: Las matrices no pueden estar vacías."

        if len(A[0]) != len(B):
            return "Error: El número de columnas de A debe ser igual al número de filas de B."

        try:
            return [[sum(A[i][k] * B[k][j] for k in range(len(B))) for j in range(len(B[0]))] for i in range(len(A))]
        except Exception as e:
            return f"Error inesperado al multiplicar matrices: {str(e)}"

    # Suma dos vectores
    def suma_vectores(self, v1, v2):
        if not v1 or not v2:
            return "Error: Los vectores no pueden estar vacíos."

        if len(v1) != len(v2):
            return "Error: Los vectores deben tener las mismas dimensiones."

        try:
            return [v1[i] + v2[i] for i in range(len(v1))]
        except Exception as e:
            return f"Error inesperado al sumar vectores: {str(e)}"

    # Multiplicación de dos vectores (producto escalar)
    def multiplicacion_vectores(self, v1, v2):
        if not v1 or not v2:
            return "Error: Los vectores no pueden estar vacíos."

        if len(v1) != len(v2):
            return "Error: Los vectores deben tener las mismas dimensiones."

        try:
            return sum(v1[i] * v2[i] for i in range(len(v1)))
        except Exception as e:
            return f"Error inesperado al multiplicar vectores: {str(e)}"

    def seno(self, x):
        return self.cliente_trig.seno(x)

    def coseno(self, x):
        return self.cliente_trig.coseno(x)

    def tangente(self, x):
        return self.cliente_trig.tangente(x)

    def area_triangulo(self, base, altura):
        return self.cliente_trig.area_triangulo(base, altura)

    def area_circulo(self, radio):
        return self.cliente_trig.area_circulo(radio)

    def area_rectangulo(self, base, altura):
        return self.cliente_trig.area_rectangulo(base, altura)

if __name__ == "__main__":
    handler = CalculadoraHandler()
    processor = Calculadora.Processor(handler)
    transport = TSocket.TServerSocket(host="127.0.0.1", port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()
    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print("Servidor de Calculadora iniciado en el puerto 9090...")
    server.serve()
    print("Servidor detenido.")

import math
import sys
from trigonometria import Trigonometria
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

class TrigonometriaHandler:
    def seno(self, x):
        return math.sin(x)

    def coseno(self, x):
        return math.cos(x)

    def tangente(self, x):
        return math.tan(x)

    def area_triangulo(self, base, altura):
        if base <= 0 or altura <= 0:
            print("Error al calcular el área del triángulo.")
            return 0
        return (base * altura) / 2

    def area_circulo(self, radio):
        if radio <= 0:
            print("Error al calcular el área del círculo.")
            return 0
        return math.pi * radio * radio

    def area_rectangulo(self, base, altura):
        if base <= 0 or altura <= 0:
            print("Error al calcular el área del rectángulo.")
            return 0
        return base * altura



if __name__ == "__main__":
    handler = TrigonometriaHandler()
    processor = Trigonometria.Processor(handler)
    transport = TSocket.TServerSocket(host="127.0.0.1", port=9091)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()
    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print("Servidor de Trigonometría y areas iniciado en el puerto 9091...")
    server.serve()
    print("Servidor detenido.")

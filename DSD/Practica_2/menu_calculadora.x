/* Archivo menu_calculadora.x: Protocolo RPC para la calculadora
Miguel Ángel Caballero Gómez
77393259F */


struct intpair {
    int a;
    int b;
};

struct doublepair{
    double a;
    double b;
};

typedef int resultvector<30>;
typedef int resultmatriz<60>;

struct matrizpair {
    resultmatriz m1;
    resultmatriz m2;
};

struct vectorpair {
    resultvector v1;
    resultvector v2;
};

 program CALCPROG {
     version CALCULADORA {
        int SUMA(intpair) = 1;
        int RESTA(intpair) = 2;
        int MULTIPLICA(intpair) = 3;
        double DIVIDE(doublepair) = 4;
        resultvector SUMA_VECTOR(vectorpair) = 5;
        resultvector RESTA_VECTOR(vectorpair) = 6;
        int PRODUCTO_VECTOR(vectorpair) = 7;
        resultmatriz SUMA_MATRIZ(matrizpair) = 8;
        resultmatriz RESTA_MATRIZ(matrizpair) = 9;
        resultmatriz PRODUCTO_MATRIZ(matrizpair) = 10;
        double LOGARITMO(doublepair) = 11;
        double SENO(double)=12;
        double COS(double)=13;
        double AREA_TRIANGULO(doublepair)=14;
        double AREA_RECTANGULO(doublepair)=15;
        double AREA_CIRCULO(doublepair)=16;

     } = 1;
} = 0x20000001;

/* Funciones auxiliares para manejar memoria */

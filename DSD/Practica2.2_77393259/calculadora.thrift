service Calculadora {
    i32 suma(1: i32 n1, 2: i32 n2),
    i32 resta(1: i32 n1, 2: i32 n2),
    i32 multiplicacion(1: i32 n1, 2: i32 n2),
    double division(1: i32 n1, 2: i32 n2),
    i32 mcm(1: i32 n1, 2: i32 n2, 3: i32 n3, 4: i32 n4),
    i32 mcd(1: i32 n1, 2: i32 n2, 3: i32 n3, 4: i32 n4),
    i64 factorial(1: i32 n),
    double evaluar_expresion(1: string expresion),

    list<i32> suma_vectores(1: list<i32> v1, 2: list<i32> v2)
    i32 multiplicacion_vectores(1: list<i32> v1, 2: list<i32> v2)

    list<list<i32>> suma_matrices(1: list<list<i32>> A, 2: list<list<i32>> B)
    list<list<i32>> multiplicacion_matrices(1: list<list<i32>> A, 2: list<list<i32>> B)

    // Operaciones delegadas al segundo servidor
    double seno(1: double x),
    double coseno(1: double x),
    double tangente(1: double x),
    double area_triangulo(1: double base, 2: double altura),
    double area_circulo(1: double radio),
    double area_rectangulo(1: double base, 2: double altura)
}

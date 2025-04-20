#include "menu_calculadora.h"
#include <stdio.h>

/*
 Miguel Ángel Caballero Gómez
77393259F
*/

intpair output() {
    intpair valores;
    printf("Ingrese el primer número: ");
    if (scanf("%d", &valores.a) != 1) {
        printf("Entrada inválida\n");
        while (getchar() != '\n') { continue; }
    }

    printf("Ingrese el segundo número: ");
    if (scanf("%d", &valores.b) != 1) {
        printf("Entrada inválida\n");
        while (getchar() != '\n') { continue; }
    }
    return valores;
}


void imprimir_matriz(resultmatriz *m, int c) {
   for (int i = 0; i < m->resultmatriz_len/c; i++) {
        for (int j = 0; j < m->resultmatriz_len/c; j++) {
             printf("%d ", m->resultmatriz_val[i*(m->resultmatriz_len/c)+j]);
        }
       printf("\n");
     }
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;
    int *result;
    double *r;
    char *server;
    resultvector *vec;
    vectorpair vectores;
     matrizpair matrices;
    resultmatriz *resultmat;
    int f=0;
    int c =0 ;

    char *message;

    if (argc < 2) {
        fprintf(stderr, "Uso: %s <maquina> [<modo> <num1> <num2>]\n", argv[0]);
        exit(1);
    }

    server = argv[1];
    intpair valores;
    doublepair v;

    clnt = clnt_create(server, CALCPROG, CALCULADORA, "visible");
    if (clnt == (CLIENT *)NULL) {
        clnt_pcreateerror(server);
        exit(1);
    }

    if (argc == 5 || argc ==4) {
        int decision = atoi(argv[2]);
        if(decision==4){
           v.a = atof(argv[3]);
           v.b = atof(argv[4]);
        }
        else{
            valores.a = atoi(argv[3]);
            valores.b = atoi(argv[4]);
        }


        switch (decision) {
            case 1:
            result = suma_1(&valores, clnt);
            if (result == NULL) {
            fprintf(stderr, "resultado invalido");
            } else {
            printf("Resultado de la suma: %2d\n", *result);
            }
            break;
            case 2:
            result = resta_1(&valores, clnt);
            if (result == NULL) {
            fprintf(stderr, "resultado invalido");
            } else {
            printf("Resultado de la resta: %2d\n", *result);
            }
            break;
            case 3:
            result = multiplica_1(&valores, clnt);
            if (result == NULL) {
            fprintf(stderr, "resultado invalido");
            } else {
            printf("Resultado de la multiplicacion: %2d\n", *result);
            }
            break;
            case 4:
            r = divide_1(&v, clnt);
            if (result == NULL) {
            fprintf(stderr, "resultado invalido");
            } else {
            printf("Resultado de la división: %.2lf\n", *r);
            }
            break;
            case 11:
            result = logaritmo_1(&valores, clnt);
            if (result == NULL) {
            fprintf(stderr, "resultado invalido");
            } else {
            printf("Resultado del logaritmo: %2d\n", *result);
            }
            break;
            case 12:
            result = seno_1(&valores.a, clnt);
            if (result == NULL) {
            fprintf(stderr, "resultado invalido");
            } else {
            printf("Resultado del seno: %2d\n", *result);
            }
            break;
            case 13:
            result = cos_1(&valores.a, clnt);
            if (result == NULL) {
            fprintf(stderr, "resultado invalido");
            } else {
            printf("Resultado del coseno: %2d\n", *result);
            }
            break;

            default:
             printf("Opción inválida\n");
             break;
        }
        // Llamada remota a la suma

    }

    else if(argc == 2){
        int opcion;

        do {
            printf("\nMENU INTERACTIVO\n");
            printf("1. Sumar dos números\n");
            printf("2. Restar dos números\n");
            printf("3. Multiplicar dos números\n");
            printf("4. Dividir dos números\n");
            printf("5. Sumar dos vectores\n");
            printf("6. Resta dos vectores\n");
            printf("7. Producto dos vectores\n");
            printf("8. Suma de matrices\n");
            printf("9. Resta de matrices\n");
            printf("10. Producto de matrices\n");
            printf("11. Logaritmo \n");
            printf("12. Seno\n");
            printf("13. Coseno\n");
            printf("14. Area triangulo\n");
            printf("15. Area rectangulo\n");
            printf("16. Area circulo\n");
            printf("0. Salir\n");
            printf("Seleccione una opción: ");

            if (scanf("%d", &opcion) != 1) {
                printf("Entrada inválida\n");
                while (getchar() != '\n'); // Limpiar buffer
                continue;
            }

            switch (opcion) {
                case 1:
                    /* Llamada remota al procedimiento en el servidor */
                    valores = output();
                    result = suma_1(&valores, clnt);
                     if(result==NULL){
                        fprintf(stderr, "Error en la operación\n");
                        break;
                    }
                    printf("Resultado de la suma: %.2d\n", *result);

                    break;

                case 2:
                    valores = output();
                    result = resta_1(&valores, clnt);
                     if(result==NULL){
                        fprintf(stderr, "Error en la operación\n");
                        break;
                    }
                    printf("Resultado de la resta: %.2d\n", *result);
                    break;

                case 3:
                    valores = output();
                    result = multiplica_1(&valores, clnt);
                    if(result==NULL){
                        fprintf(stderr, "Error en la operación\n");
                        break;
                    }
                    printf("Resultado de la multiplicación: %.2d\n", *result);

                    break;

                case 4:
                    printf("Ingrese el primer número: ");
                    if (scanf("%lf", &v.a) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                     printf("Ingrese el segundo número: ");
                    if (scanf("%lf", &v.b) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                    r = divide_1(&v, clnt);
                    if(r==NULL){
                        fprintf(stderr, "Error en la operación, no se puede dividir por cero\n");
                        break;
                    }
                    printf("Resultado de la división: %.2lf\n", *r);
                    break;

                case 5:

                    printf("Ingrese el tamaño de los vectores:\n");
                    scanf("%d", &vectores.v1.resultvector_len);


                    vectores.v2.resultvector_len = vectores.v1.resultvector_len;
                    vectores.v1.resultvector_val = (int *)malloc(vectores.v1.resultvector_len * sizeof(int));
                    vectores.v2.resultvector_val = (int *)malloc(vectores.v2.resultvector_len * sizeof(int));

                    printf("Ingrese los valores del primer vector:\n");
                    for (int i = 0; i < vectores.v1.resultvector_len; i++) {
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &vectores.v1.resultvector_val[i]);
                    }

                    printf("Ingrese los valores del segundo vector:\n");
                    for (int i = 0; i < vectores.v2.resultvector_len; i++) {
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &vectores.v2.resultvector_val[i]);
                    }

                    vec= suma_vector_1(&vectores, clnt);
                     if(vec==NULL){
                        fprintf(stderr, "Error en la operación,tamaño insufuciente\n");
                        break;
                    }
                    if (vec->resultvector_val == NULL || vec->resultvector_len == 0) {
                        fprintf(stderr, "Error en la operación\n");
                    } else {
                        printf("Resultado de la suma de vectores: ");
                        for (int i = 0; i < vec->resultvector_len; i++) {
                            printf("%d ", vec->resultvector_val[i]);
                        }
                        printf("\n");
                    }

                        free(vectores.v1.resultvector_val);
                        free(vectores.v2.resultvector_val);

                    break;
                case 6:

                    printf("Ingrese el tamaño de los vectores:\n");
                    scanf("%d", &vectores.v1.resultvector_len);


                    vectores.v2.resultvector_len = vectores.v1.resultvector_len;
                    vectores.v1.resultvector_val = (int *)malloc(vectores.v1.resultvector_len * sizeof(int));
                    vectores.v2.resultvector_val = (int *)malloc(vectores.v2.resultvector_len * sizeof(int));

                    printf("Ingrese los valores del primer vector:\n");
                    for (int i = 0; i < vectores.v1.resultvector_len; i++) {
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &vectores.v1.resultvector_val[i]);
                    }

                    printf("Ingrese los valores del segundo vector:\n");
                    for (int i = 0; i < vectores.v2.resultvector_len; i++) {
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &vectores.v2.resultvector_val[i]);
                    }

                    vec= resta_vector_1(&vectores, clnt);
                    if(vec==NULL){
                        fprintf(stderr, "Error en la operación,tamaño insufuciente\n");
                        break;
                    }
                    if (vec->resultvector_val == NULL || vec->resultvector_len == 0) {
                        fprintf(stderr, "Error en la operación\n");
                    } else {
                        printf("Resultado de la resta de vectores: ");
                        for (int i = 0; i < vec->resultvector_len; i++) {
                            printf("%d ", vec->resultvector_val[i]);
                        }
                        printf("\n");
                    }

                        free(vectores.v1.resultvector_val);
                        free(vectores.v2.resultvector_val);

                    break;

                case 7:

                    printf("Ingrese el tamaño de los vectores:\n");
                    scanf("%d", &vectores.v1.resultvector_len);


                    vectores.v2.resultvector_len = vectores.v1.resultvector_len;
                    vectores.v1.resultvector_val = (int *)malloc(vectores.v1.resultvector_len * sizeof(int));
                    vectores.v2.resultvector_val = (int *)malloc(vectores.v2.resultvector_len * sizeof(int));

                    printf("Ingrese los valores del primer vector:\n");
                    for (int i = 0; i < vectores.v1.resultvector_len; i++) {
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &vectores.v1.resultvector_val[i]);
                    }

                    printf("Ingrese los valores del segundo vector:\n");
                    for (int i = 0; i < vectores.v2.resultvector_len; i++) {
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &vectores.v2.resultvector_val[i]);
                    }

                    result= producto_vector_1(&vectores, clnt);
                    if (result == NULL) {
                        fprintf(stderr, "Error en la operación\n");
                        break;
                    } else {
                        printf("Resultado del producto de vectores: ");
                            printf("%d ", *result);
                    }

                        free(vectores.v1.resultvector_val);
                        free(vectores.v2.resultvector_val);

                    break;

                case 8:
                    printf("Ingrese el tamaño de las matrices cuadradas:\n");

                    scanf("%d", &matrices.m1.resultmatriz_len);
                     f = matrices.m1.resultmatriz_len* matrices.m1.resultmatriz_len;
                     c =matrices.m1.resultmatriz_len;

                      matrices.m2.resultmatriz_len = matrices.m1.resultmatriz_len=f;


                    matrices.m1.resultmatriz_val = (int *)malloc(f * sizeof(int));
                    matrices.m2.resultmatriz_val = (int *)malloc(f * sizeof(int));


                    printf("Ingrese los valores de la primera matriz:\n");
                    for (int i = 0; i < f; i++){
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &matrices.m1.resultmatriz_val[i]);
                    }

                   printf("Ingrese los valores de la segunda matriz:\n");
                    for (int i = 0; i < f; i++){
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &matrices.m2.resultmatriz_val[i]);
                    }

                        // Llamar a la función remota
                        resultmat = suma_matriz_1(&matrices, clnt);

                        if (resultmat == NULL) {
                        fprintf(stderr, "Error en la operación, tamaños insuficientes\n");
                        break;
                         }


                        printf("Matriz A:\n");
                        imprimir_matriz(&matrices.m1,c);

                        printf("Matriz B:\n");
                        imprimir_matriz(&matrices.m2, c);

                        printf("Matriz resultado (A + B):\n");
                        imprimir_matriz(resultmat, c);



                        free(matrices.m1.resultmatriz_val);
                        free(matrices.m2.resultmatriz_val);
                    break;

                case 9:
                    printf("Ingrese el tamaño de las matrices cuadradas:\n");

                    scanf("%d", &matrices.m1.resultmatriz_len);
                     f = matrices.m1.resultmatriz_len* matrices.m1.resultmatriz_len;
                     c =matrices.m1.resultmatriz_len;
                      matrices.m2.resultmatriz_len = matrices.m1.resultmatriz_len=f;


                    matrices.m1.resultmatriz_val = (int *)malloc(f * sizeof(int));
                    matrices.m2.resultmatriz_val = (int *)malloc(f * sizeof(int));


                    printf("Ingrese los valores de la primera matriz:\n");
                    for (int i = 0; i < f; i++){
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &matrices.m1.resultmatriz_val[i]);
                    }

                   printf("Ingrese los valores de la segunda matriz:\n");
                    for (int i = 0; i < f; i++){
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &matrices.m2.resultmatriz_val[i]);
                    }

                     // Llamar a la función remota
                        resultmat = resta_matriz_1(&matrices, clnt);

                        if (resultmat == NULL) {
                        fprintf(stderr, "Error en la operación, tamaños insuficientes\n");
                        break;
                         }

                        printf("Matriz A:\n");
                        imprimir_matriz(&matrices.m1,c

                        );

                        printf("Matriz B:\n");
                        imprimir_matriz(&matrices.m2,c);


                        printf("Matriz resultado (A + B):\n");
                           imprimir_matriz(resultmat, c);



                        free(matrices.m1.resultmatriz_val);
                        free(matrices.m2.resultmatriz_val);
                    break;

                case 10:
                    printf("Ingrese el tamaño de las matrices cuadradas:\n");

                    scanf("%d", &matrices.m1.resultmatriz_len);
                     f = matrices.m1.resultmatriz_len* matrices.m1.resultmatriz_len;
                      c =matrices.m1.resultmatriz_len;
                      matrices.m2.resultmatriz_len = matrices.m1.resultmatriz_len=f;


                    matrices.m1.resultmatriz_val = (int *)malloc(f * sizeof(int));
                    matrices.m2.resultmatriz_val = (int *)malloc(f * sizeof(int));


                    printf("Ingrese los valores de la primera matriz:\n");
                    for (int i = 0; i < f; i++){
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &matrices.m1.resultmatriz_val[i]);
                    }

                   printf("Ingrese los valores de la segunda matriz:\n");
                    for (int i = 0; i < f; i++){
                        printf("Elemento %d: ", i + 1);
                        scanf("%d", &matrices.m2.resultmatriz_val[i]);
                    }

                    // Llamar a la función remota
                        resultmat = producto_matriz_1(&matrices, clnt);

                        if (resultmat == NULL) {
                        fprintf(stderr, "Error en la operación, tamaños insuficientes\n");
                        break;
                         }

                        printf("Matriz A:\n");
                        imprimir_matriz(&matrices.m1,c);

                        printf("Matriz B:\n");
                        imprimir_matriz(&matrices.m2,c);

                        printf("Matriz resultado (A + B):\n");
                        imprimir_matriz(resultmat, c);

                        free(matrices.m1.resultmatriz_val);
                        free(matrices.m2.resultmatriz_val);

                    break;

                    case 11:
                        printf("Ingrese el  número: ");
                    if (scanf("%lf", &v.a) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                     printf("Ingrese el la base del logaritmo : ");
                    if (scanf("%lf", &v.b) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                    r = logaritmo_1(&v, clnt);
                    if(r==NULL){
                        fprintf(stderr, "Error: Los logaritmo deben ser mayores a cero\n");
                        break;
                    }
                    printf("Resultado del logaritmo: %.2lf\n", *r);
                    break;

                    case 12:
                        printf("Ingrese el  número: ");
                    if (scanf("%lf", &v.a) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                    r = seno_1(&v, clnt);
                    if(r==NULL){
                        fprintf(stderr, "Error:Operacion invalida\n");
                        break;
                    }
                    printf("Resultado del seno: %.2lf\n", *r);
                    break;

                    case 13:
                        printf("Ingrese el  número: ");
                    if (scanf("%lf", &v.a) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                    r = cos_1(&v, clnt);
                    if(r==NULL){
                        fprintf(stderr, "Error: Operacion invalida\n");
                        break;
                    }
                    printf("Resultado del coseno: %.2lf\n", *r);
                    break;

                    case 14:
                        printf("Ingrese la base del triangulo: ");
                    if (scanf("%lf", &v.a) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                     printf("Ingrese la altura del triangulo: ");
                    if (scanf("%lf", &v.b) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                    r = area_triangulo_1(&v, clnt);
                    if(r==NULL){
                        fprintf(stderr, "Tanto la altura como la base deben ser > 0\n");
                        break;
                    }
                    printf("Resultado del area: %.2lf\n", *r);
                    break;

                    case 15:
                        printf("Ingrese un lado del rectangulo: ");
                    if (scanf("%lf", &v.a) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                     printf("ngrese un lado del rectangulo: ");
                    if (scanf("%lf", &v.b) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }
                    r = area_rectangulo_1(&v, clnt);
                    if(r==NULL){
                        fprintf(stderr, "Error: Ambos lados deben ser > 0\n");
                        break;
                    }
                    printf("Resultado del area: %.2lf\n", *r);
                    break;

                    case 16:
                        printf("Ingreseel raqdio del circulo: ");
                    if (scanf("%lf", &v.a) != 1) {
                        printf("Entrada inválida\n");
                        while (getchar() != '\n')  continue;
                    }

                    r = area_circulo_1(&v, clnt);
                    if(r==NULL){
                        fprintf(stderr, "El radio debe ser mayor que cero\n");
                        break;
                    }
                    printf("Resultado del area: %.2lf\n", *r);
                    break;

                case 0:
                    printf("Saliendo...\n");
                    exit(0);

                default:
                    printf("Opción inválida\n");
                    continue;
            }

        } while (1);
    }

    if (*result == (int *)NULL) {
        clnt_perror(clnt, server);
        exit(1);
    }
    if (*result == 0) {
        fprintf(stderr, "%s: no pudo imprimir el mensaje\n", argv[0]);
        exit(1);
    }
    printf("Mensaje enviado a %s\n", server);
    exit(0);
}


/* calculadora_server.c : código del servidor
Miguel Ángel Caballero Gómez
77393259F
*/
#include "menu_calculadora.h" /* creado por rpcgen */
#include <errno.h>
#include <stdlib.h>  // Para malloc y free
#include <math.h>

/* Variable global para almacenar el resultado */

static  resultvector res;
static resultvector resultado;
static resultmatriz resultamat;


/* Suma */
 int * suma_1_svc(intpair *argp, struct svc_req *rqstp) {
    static int  result;


    result = argp->a + argp->b;


    return(&result); // Retorna el puntero a la estructura, no solo el campo resultado
}

/* Resta */
 int * resta_1_svc(intpair *argp, struct svc_req *rqstp) {

    static int  result;


    result = argp->a - argp->b;


    return(&result); // Retorna el puntero a la estructura, no solo el campo resultado
}

/* Multiplicacion */
 int * multiplica_1_svc(intpair *argp, struct svc_req *rqstp) {

    static int  result;


    result = argp->a * argp->b;


    return(&result); // Retorna el puntero a la estructura, no solo el campo resultado
}

/* Division */
 double * divide_1_svc(doublepair *argp, struct svc_req *rqstp) {
    static double  resulta;

    if(argp->b==0){
         fprintf(stderr, "Error: No se puede dividir por cero\n");
        return NULL;
    }

    resulta = argp->a / argp->b;


    return(&resulta); // Retorna el puntero a la estructura, no solo el campo resultado
}


resultvector *suma_vector_1_svc(vectorpair *argp, struct svc_req *rqstp) {
    // Verificar que el tamaño sea válido


    free(resultado.resultvector_val);
    resultado.resultvector_len=0;

    if(argp->v1.resultvector_len<=0 || argp->v2.resultvector_len<=0){
         fprintf(stderr, "Error: Tamaño incorrecto\n");
        return NULL;
    }

    resultado.resultvector_val = (int *)malloc(argp->v1.resultvector_len * sizeof(int));
    resultado.resultvector_len = argp->v1.resultvector_len;

    for (int i = 0; i < resultado.resultvector_len; i++) {
        resultado.resultvector_val[i] = argp->v1.resultvector_val[i] + argp->v2.resultvector_val[i];
    }

    return(&resultado);
}

resultvector *resta_vector_1_svc(vectorpair *argp, struct svc_req *rqstp) {

    free(resultado.resultvector_val);
    resultado.resultvector_len=0;

    // Verificar que el tamaño sea válido
    if(argp->v1.resultvector_len<=0 || argp->v2.resultvector_len<=0){
         fprintf(stderr, "Error: Tamaño incorrecto\n");
        return &resultado;
    }

    resultado.resultvector_val = (int *)malloc(argp->v1.resultvector_len * sizeof(int));
    resultado.resultvector_len = argp->v1.resultvector_len;

    for (int i = 0; i < resultado.resultvector_len; i++) {
        resultado.resultvector_val[i] = argp->v1.resultvector_val[i] - argp->v2.resultvector_val[i];
    }

    return(&resultado);
}

int *producto_vector_1_svc(vectorpair *argp, struct svc_req *rqstp) {

    static int  result;

    if(argp->v1.resultvector_len<=0 || argp->v2.resultvector_len<=0){
         fprintf(stderr, "Error: Tamaño incorrecto\n");
        return NULL;
    }
    for (int i = 0; i < argp->v1.resultvector_len; i++) {
        result += argp->v1.resultvector_val[i] * argp->v2.resultvector_val[i];
    }

    return(&result);
}


resultmatriz * suma_matriz_1_svc(matrizpair *m, struct svc_req *rqstp) {

    free(resultamat.resultmatriz_val);
    resultamat.resultmatriz_len=0;


    if(m->m1.resultmatriz_len<=0 || m->m2.resultmatriz_len<=0){
         fprintf(stderr, "Error: Tamaño incorrecto\n");
        return NULL;
    }
    // Verificar que las matrices tienen el mismo tamaño
    if (m->m1.resultmatriz_len != m->m2.resultmatriz_len || m->m1.resultmatriz_len <=0) {
        fprintf(stderr, "Error: Las matrices deben tener el mismo tamaño\n");
        return NULL;
    }


    // Asignar memoria para la matriz resultamat
    resultamat.resultmatriz_val = (int *)malloc( m->m1.resultmatriz_len * sizeof(int));
    resultamat.resultmatriz_len = m->m1.resultmatriz_len;
    if (resultamat.resultmatriz_val == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        return NULL;
    }


    // Sumar matrices
   for (int i = 0; i <  resultamat.resultmatriz_len; i++) {
            resultamat.resultmatriz_val[i] = m->m1.resultmatriz_val[i] + m->m2.resultmatriz_val[i];
    }

    return(&resultamat);
}

resultmatriz * resta_matriz_1_svc(matrizpair *m, struct svc_req *rqstp) {

    free(resultamat.resultmatriz_val);
    resultamat.resultmatriz_len=0;

    // Verificar que las matrices tienen el mismo tamaño
    if (m->m1.resultmatriz_len != m->m2.resultmatriz_len || m->m1.resultmatriz_len <=0) {
        fprintf(stderr, "Error: Las matrices deben tener el mismo tamaño\n");
        return NULL;
    }


    // Asignar memoria para la matriz resultamat
    resultamat.resultmatriz_val = (int *)malloc( m->m1.resultmatriz_len * sizeof(int));
    resultamat.resultmatriz_len = m->m1.resultmatriz_len;
    if (resultamat.resultmatriz_val == NULL) {
        fprintf(stderr, "Error al asignar memoria\n");
        return NULL;
    }


    // Sumar matrices
   for (int i = 0; i <  resultamat.resultmatriz_len; i++) {
            resultamat.resultmatriz_val[i] = m->m1.resultmatriz_val[i] - m->m2.resultmatriz_val[i];
    }

    return(&resultamat);
}

resultmatriz *producto_matriz_1_svc(matrizpair *m, struct svc_req *rqstp) {

    free(resultamat.resultmatriz_val);
    resultamat.resultmatriz_len=0;;


    // Verificar que las matrices tienen el mismo tamaño
    if (m->m1.resultmatriz_len != m->m2.resultmatriz_len || m->m1.resultmatriz_len <=0) {
        fprintf(stderr, "Error: Las matrices deben tener el mismo tamaño\n");
        return NULL;
    }


    // Asignar memoria para la matriz resultamat
    resultamat.resultmatriz_val = (int *)malloc( m->m1.resultmatriz_len * sizeof(int));
    resultamat.resultmatriz_len = m->m1.resultmatriz_len;
    int tam =   resultamat.resultmatriz_len;
    int c = sqrt(tam);

    // Inicializamos la matriz resultamat
    for (int i = 0; i < tam/c; i++) {
        for (int j = 0; j < tam/c; j++) {
            resultamat.resultmatriz_val[i * tam/c + j] = 0;
            for (int k = 0; k < tam/c; k++) {
                resultamat.resultmatriz_val[i * tam/c + j] += m->m1.resultmatriz_val[i * tam/c + k] * m->m2.resultmatriz_val[k * tam/c + j];
            }
        }
    }

    return (&resultamat);
}

double * logaritmo_1_svc(doublepair *agrp,struct svc_req *rqstp ){

    if(agrp->a <=0 || agrp->b <=0){
        fprintf(stderr, "Error: Los logaritmo deben ser mayores a cero\n");
        return NULL;
    }
     static double  result;
     result = log(agrp->a)/log(agrp->b);
     return (&result);

}

double * seno_1_svc(double *d,struct svc_req *rqstp ){
     static double  result;
     result = sin(*d);
     return (&result);

}

double * cos_1_svc(double *d,struct svc_req *rqstp ){
     static double  result;
     result = cos(*d);
     return (&result);

}

double * area_triangulo_1_svc(doublepair *agrp,struct svc_req *rqstp ){
     static double  result;
     if(agrp->a <=0 || agrp->b <=0){
         fprintf(stderr, "Error: Tanto la altura como la base deben ser > 0\n");
        return NULL;
    }
     result = result = (agrp->a*agrp->b)/2;
     return (&result);

}

double * area_rectangulo_1_svc(doublepair *agrp,struct svc_req *rqstp ){
     static double  result;
     if(agrp->a <=0 || agrp->b <=0){
         fprintf(stderr, "Error: Ambos lados deben ser > 0\n");
        return NULL;
    }
     result = agrp->a*agrp->b;
     return (&result);

}

double * area_circulo_1_svc(doublepair *agrp,struct svc_req *rqstp ){
     static double  result;
     if(agrp->a <=0){
         fprintf(stderr, "Error: El radio debe ser > 0\n");
        return NULL;
    }
     result = result = 3.14*agrp->a*agrp->a;
     return (&result);

}




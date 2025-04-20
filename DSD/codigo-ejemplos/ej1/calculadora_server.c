 /* calculadora_server.c : código del servidor */
#include "calculadora.h" /* creado por rpcgen */
#include <stdio.h>
#include <errno.h>

typedef struct calcnode *calclist;
struct calcnode {
    int resultado;
    calclist next;
};

/* Aquí result es estático porque la función debe devolver un puntero a un valor que sigue existiendo después de que la función termina.*/
static struct {
    int errnum;
    calcnode list;
} result;


// Manejo de memoria para evitar fugas
void liberar_memoria() {
    xdr_free((xdrproc_t)xdr_int, &result);
}



/* Suma */
struct calcnode *suma_1_svc(intpair *argp, struct svc_req *rqstp) {
    liberar_memoria();

    calcnode nl = (calcnode) malloc(sizeof(struct calcnode));
    if (nl == NULL) {
        result.errnum = 1;
        return &result.list;
    }
    nl->result = argp->a + argp->b;
    nl->next = NULL;
    result.list = nl;
    result.errnum = 0;
    return &result.list;
}




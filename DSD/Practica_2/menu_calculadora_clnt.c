/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "menu_calculadora.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

int *
suma_1(intpair *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SUMA,
		(xdrproc_t) xdr_intpair, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
resta_1(intpair *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RESTA,
		(xdrproc_t) xdr_intpair, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
multiplica_1(intpair *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MULTIPLICA,
		(xdrproc_t) xdr_intpair, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

double *
divide_1(doublepair *argp, CLIENT *clnt)
{
	static double clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, DIVIDE,
		(xdrproc_t) xdr_doublepair, (caddr_t) argp,
		(xdrproc_t) xdr_double, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

resultvector *
suma_vector_1(vectorpair *argp, CLIENT *clnt)
{
	static resultvector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SUMA_VECTOR,
		(xdrproc_t) xdr_vectorpair, (caddr_t) argp,
		(xdrproc_t) xdr_resultvector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

resultvector *
resta_vector_1(vectorpair *argp, CLIENT *clnt)
{
	static resultvector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RESTA_VECTOR,
		(xdrproc_t) xdr_vectorpair, (caddr_t) argp,
		(xdrproc_t) xdr_resultvector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
producto_vector_1(vectorpair *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, PRODUCTO_VECTOR,
		(xdrproc_t) xdr_vectorpair, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

resultmatriz *
suma_matriz_1(matrizpair *argp, CLIENT *clnt)
{
	static resultmatriz clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SUMA_MATRIZ,
		(xdrproc_t) xdr_matrizpair, (caddr_t) argp,
		(xdrproc_t) xdr_resultmatriz, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

resultmatriz *
resta_matriz_1(matrizpair *argp, CLIENT *clnt)
{
	static resultmatriz clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, RESTA_MATRIZ,
		(xdrproc_t) xdr_matrizpair, (caddr_t) argp,
		(xdrproc_t) xdr_resultmatriz, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

resultmatriz *
producto_matriz_1(matrizpair *argp, CLIENT *clnt)
{
	static resultmatriz clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, PRODUCTO_MATRIZ,
		(xdrproc_t) xdr_matrizpair, (caddr_t) argp,
		(xdrproc_t) xdr_resultmatriz, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

double *
logaritmo_1(doublepair *argp, CLIENT *clnt)
{
	static double clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, LOGARITMO,
		(xdrproc_t) xdr_doublepair, (caddr_t) argp,
		(xdrproc_t) xdr_double, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

double *
seno_1(double *argp, CLIENT *clnt)
{
	static double clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SENO,
		(xdrproc_t) xdr_double, (caddr_t) argp,
		(xdrproc_t) xdr_double, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

double *
cos_1(double *argp, CLIENT *clnt)
{
	static double clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, COS,
		(xdrproc_t) xdr_double, (caddr_t) argp,
		(xdrproc_t) xdr_double, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

double *
area_triangulo_1(doublepair *argp, CLIENT *clnt)
{
	static double clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, AREA_TRIANGULO,
		(xdrproc_t) xdr_doublepair, (caddr_t) argp,
		(xdrproc_t) xdr_double, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

double *
area_rectangulo_1(doublepair *argp, CLIENT *clnt)
{
	static double clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, AREA_RECTANGULO,
		(xdrproc_t) xdr_doublepair, (caddr_t) argp,
		(xdrproc_t) xdr_double, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

double *
area_circulo_1(doublepair *argp, CLIENT *clnt)
{
	static double clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, AREA_CIRCULO,
		(xdrproc_t) xdr_doublepair, (caddr_t) argp,
		(xdrproc_t) xdr_double, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

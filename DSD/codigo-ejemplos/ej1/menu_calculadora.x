/* Archivo menu_calculadora.x: Protocolo RPC para la calculadora */


/* La siguiente unión se utiliza para discriminar entre llamadas
* con éxito y llamadas con errores */
union readdir_res switch (int errnum) {
case 0:
namelist list; /* sin error: listado del directorio */
default:
void; /* con error: nada */
};




   program CALCPROG {
     version CALCULADORA {
        float SUMA(intpair) = 1;
        float RESTA(intpair) = 2;
        float MULT(intpair) = 3;
        float DIV(intpair) = 4;
     } = 1;
   } = 0x20000001;


    struct intpair {
        float a;
        float b;
    };

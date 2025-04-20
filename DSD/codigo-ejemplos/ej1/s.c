#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

void mostrar_menu(CLIENT *clnt) {
    int opcion;
    char **result;

    do {
        printf("\nMENU INTERACTIVO\n");
        printf("1. Opción 1\n");
        printf("2. Opción 2\n");
        printf("3. Opción 3\n");
        printf("4. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                result = opcion1_1(clnt);
                break;
            case 2:
                result = opcion2_1(clnt);
                break;
            case 3:
                result = opcion3_1(clnt);
                break;
            case 4:
                printf("Saliendo...\n");
                return;
            default:
                printf("Opción inválida\n");
                continue;
        }

        if (result == NULL) {
            printf("Error en la llamada RPC\n");
        } else {
            printf("Respuesta del servidor: %s\n", *result);
        }
    } while (1);
}

int main(int argc, char *argv[]) {
    CLIENT *clnt;

    if (argc != 2) {
        printf("Uso: %s servidor\n", argv[0]);
        exit(1);
    }

    clnt = clnt_create(argv[1], MENUPROG, MENUVER, "udp");
    if (clnt == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }

    mostrar_menu(clnt);
    clnt_destroy(clnt);
    return 0;
}

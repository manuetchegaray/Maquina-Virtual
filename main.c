#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "memoria.h"


MV mv;

/* Lo que se recibe por linea de comandos */
typedef struct {
    const char *rutaVmx;      /* NULL si no se indico */
    const char *rutaVmi;      /* NULL si no se indico */
    uint32_t    memKiB;       /* m=M, o MEM_SIZE_KIB por defecto */
    int         disassembler; /* -d */
    int         cantParams;   /* cantidad de parametros despues de -p */
    char      **params;       /* parametros despues de -p (apuntan a argv) */
} Argumentos;

/* Devuelve 1 si el texto 's' termina con 'ext' (por ejemplo ".vmx"). */
static int terminaCon(const char *s, const char *ext){
    size_t ls = strlen(s), le = strlen(ext);
    return ls > le && strcmp(s + ls - le, ext) == 0;
}

/* Lee los argumentos: vmx [archivo.vmx] [archivo.vmi] [m=M] [-d] [-p p1 p2 ... pN]
 * Devuelve 0 si hay algun argumento invalido o si no hay ni .vmx ni .vmi. */
static int leerArgumentos(int argc, char *argv[], Argumentos *a){
    memset(a, 0, sizeof(*a));
    a->memKiB = MEM_SIZE_KIB;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {          /* todo lo que sigue son parametros */
            a->params     = &argv[i + 1];
            a->cantParams = argc - (i + 1);
            break;
        }
        else if (strcmp(argv[i], "-d") == 0)
            a->disassembler = 1;
        else if (strncmp(argv[i], "m=", 2) == 0) {
            int kib = atoi(argv[i] + 2);
            if (kib <= 0 || kib > 0xFFFF)          /* en el .vmi se guarda en 2 bytes */
                return 0;
            a->memKiB = (uint32_t)kib;
        }
        else if (terminaCon(argv[i], ".vmx"))
            a->rutaVmx = argv[i];
        else if (terminaCon(argv[i], ".vmi"))
            a->rutaVmi = argv[i];
        else
            return 0;                                /* argumento desconocido */
    }

    if (a->rutaVmx == NULL) {                        /* sin .vmx se ignora -p */
        a->cantParams = 0;
        a->params     = NULL;
    }
    return a->rutaVmx != NULL || a->rutaVmi != NULL;
}

int main(int argc, char *argv[]) {
    Argumentos args;
    vm_error_t res;

    if (!leerArgumentos(argc, argv, &args)) {
        mostrarUso();
        return 1;
    }

    srand((unsigned int)time(NULL));   /* semilla para RND, una sola vez */

    if (args.rutaVmx != NULL) {
        // 1. Crear la memoria principal del tamaño pedido
        res = crearMemoria(&mv, args.memKiB);
        if (res != OK) {
            informarError(res);
            return res;
        }

        // 2. Cargar ejecutable desde disco
        res = cargarPrograma(&mv, args.rutaVmx);
        if (res != OK) {
            informarError(res);
            liberarMemoria(&mv);
            return res;
        }
    }
    else {
        /* solo .vmi: continuar una imagen (se implementa en la parte 3c) */
        printf("Todavia no se puede continuar una imagen.\n");
        return 1;
    }

    // 3. Cargar la tabla de instrucciones
    init_funciones(&mv);

    // 4. Flujo principal: Disassembler o Ejecución
    if (args.disassembler) {
        disassembler(&mv);
    }
    res = ejecutarPrograma(&mv);
    if (res != OK) {
        informarError(res);
    }

    liberarMemoria(&mv);
    return res;
}
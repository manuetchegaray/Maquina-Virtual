#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "memoria.h"


MV mv;
uint16_t tamCodigo = 0;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        mostrarUso();
        return 1;
    }

    const char *rutaArchivo = NULL;
    int modoDisassembler = 0;

    // Parser de argumentos (soporta 'vmx archivo.vmx -d' o 'vmx -d archivo.vmx')
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            modoDisassembler = 1;
        } else {
            rutaArchivo = argv[i];
        }
    }

    if (rutaArchivo == NULL) {
        mostrarUso();
        return 1;
    }

    srand((unsigned int)time(NULL));   /* semilla para RND, una sola vez */


    // 1. Cargar ejecutable desde disco
    vm_error_t res = cargarPrograma(&mv, rutaArchivo, &tamCodigo);
    if (res != OK) {
        informarError(res);
        return res;
    }

    // 2. Inicializar MV con el tamaño de código detectado
    inicializarMV(&mv, tamCodigo);
    init_funciones(&mv);

    // 3. Flujo principal: Disassembler o Ejecución
    if (modoDisassembler) {
        disassembler(&mv);
    } else {
        // Proximamente: Ciclo Fetch-Decode-Execute
        res = ejecutarPrograma(&mv);
        if (res != OK) {
            informarError(res);
        }
    }

    return 0;
}
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


    // 1. Crear la memoria principal (por ahora, siempre el tamaño por defecto)
    vm_error_t res = crearMemoria(&mv, MEM_SIZE_KIB);
    if (res != OK) {
        informarError(res);
        return res;
    }

    // 2. Cargar ejecutable desde disco
    res = cargarPrograma(&mv, rutaArchivo, &tamCodigo);
    if (res != OK) {
        informarError(res);
        liberarMemoria(&mv);
        return res;
    }

    // 3. Inicializar MV con el tamaño de código detectado
    inicializarMV(&mv, tamCodigo);
    init_funciones(&mv);

    // 4. Flujo principal: Disassembler o Ejecución
    if (modoDisassembler) {
        disassembler(&mv);
    } 
    res = ejecutarPrograma(&mv);
        if (res != OK) {
            informarError(res);
        }
    
    liberarMemoria(&mv);
    return res;
}
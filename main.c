#include <stdio.h>
#include <string.h>
#include "memoria.h"


MV mv;
uint16_t tamCodigo = 0;

static void imprimirEstado(const MV *mv) {
    printf("=== Tabla de Segmentos ===\n");
    for (unsigned i = 0; i < SEG_TABLE; i++) {
        printf("  [%u] Base: 0x%04X | Tamanio: 0x%04X\n",
               i, mv->tabla[i].base, mv->tabla[i].tamanio);
    }

    printf("\n=== Registros Iniciales ===\n");
    printf("  CS = 0x%08X\n", mv->reg[CS]);
    printf("  DS = 0x%08X\n", mv->reg[DS]);
    printf("  IP = 0x%08X\n", mv->reg[IP]);
    printf("---------------------------\n");
}

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


    // 1. Cargar ejecutable desde disco
    vm_error_t res = cargarPrograma(&mv, rutaArchivo, &tamCodigo);
    if (res != OK) {
        informarError(res);
        return res;
    }

    // 2. Inicializar MV con el tamaño de código detectado
    inicializarMV(&mv, tamCodigo);
    init_funciones(&mv);

    printf("Programa '%s' cargado exitosamente (%u bytes de codigo).\n\n", 
           rutaArchivo, tamCodigo);

    imprimirEstado(&mv);

    // 3. Flujo principal: Disassembler o Ejecución
    if (modoDisassembler) {
        printf("Modo Desensamblador activo:\n");
        disassembler(&mv);
    } else {
        printf("Iniciando ejecucion...\n");
        // Proximamente: Ciclo Fetch-Decode-Execute
        res = ejecutarPrograma(&mv);
        if (res != OK) {
            informarError(res);
        }
    }

    return 0;
}
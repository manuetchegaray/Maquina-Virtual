#include <stdio.h>
#include <stdint.h> //Te da tipos de tamaño exacto: uint8_t (1 byte), uint16_t (2) y uint32_t (4).
#include <string.h>


int main(int cantidad, char *palabras[]){
    if (cantidad<2){
        printf("Uso: vmx archivo.vmx [-d]\n");
        return 1;
    }

    char *archivoNombre=palabras[1];

    FILE *arch=fopen(archivoNombre, "rb");
    if (!arch){
        printf("Error: No se pudo abrir el archivo %s\n", archivoNombre);
        return 1;
    }
    

}
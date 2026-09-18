#pragma once

#include "mv.h"

/* Inicializa los registros, asigna los segmentos de Código y Datos en la tabla,
 * invalida el resto de la tabla y deja los punteros CS, DS e IP listos. */
void inicializarMV(MV *mv, uint16_t tamCodigo);

/* Lee un archivo .vmx, valida la cabecera ("VMX26", versión actual), 
 * carga el código binario en memoria y devuelve el tamaño del código cargado. */
vm_error_t cargarPrograma(MV *mv, const char *ruta, uint16_t *tamCodigo);

/* Verifica si el registro IP apunta dentro de los límites del Segmento de Código. */
int ipEnSegmentoDeCodigo(MV *mv);

/* Imprime en pantalla el mensaje asociado al código de error. */
void informarError(int codigo);

/* Muestra las instrucciones de uso del ejecutable por línea de comandos. */
void mostrarUso(void);


#pragma once

#include "mv.h"
#include <stdio.h>

/* Arma la tabla de segmentos (Param, Const, Code, Data, Extra, Stack; solo los de
 * tamaño > 0) y carga los registros de segmento. Si no entran, ERR_MEMORIA. */
vm_error_t armarSegmentos(MV *mv, const Cabecera *cab, uint16_t tamParam);

/* Guarda el estado de la MV (registros, tabla de segmentos y memoria) en un .vmi. */
vm_error_t guardarImagen(MV *mv, const char *ruta);

/* Lee un .vmx (version 1 o 2), arma los segmentos, carga el codigo y las
 * constantes y deja listos IP y SP. */
vm_error_t cargarPrograma(MV *mv, const char *ruta);

/* Verifica si el registro IP apunta dentro de los límites del Segmento de Código. */
int ipEnSegmentoDeCodigo(MV *mv);

/* Imprime en pantalla el mensaje asociado al código de error. */
void informarError(int codigo);

/* Muestra las instrucciones de uso del ejecutable por línea de comandos. */
void mostrarUso(void);

/* Traduce una dirección lógica a física validando los límites del segmento. */
int traducirDireccion(MV *mv, uint32_t dirLogica, int cantBytes, uint16_t *dirFisica);

/* Lee/escribe 'cantBytes' de memoria desde una dirección lógica,
 * cargando LAR, MAR y MBR. */
int leerMemoria(MV *mv, uint32_t dirLogica, int cantBytes, int32_t *valor);
int escribirMemoria(MV *mv, uint32_t dirLogica, int cantBytes, int32_t valor);

/* Crea la memoria principal de 'kib' KiB (en cero) y guarda su tamaño en tamMem. */
vm_error_t crearMemoria(MV *mv, uint32_t kib);

/* Libera la memoria principal. */
void liberarMemoria(MV *mv);

/* Lee y valida la cabecera del .vmx (version 1 o 2). */
vm_error_t leerCabecera(FILE *arch, Cabecera *cab);
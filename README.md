# Maquina-Virtual 2026

Sistema Operativo
    Desarrollada y compilada para windows.


Requerimintos Previos
    Ninguno. vmx.exe es un ejecutable nativo de windows.

Ejecucion
    vmx.exe filename.vmx [-d]
    '-d' (opcional): muestra el código desensamblado antes de ejecutarlo.

Archivos
- main.c: argumentos de consola y arranque.
- memoria.c/memoria.h: carga del .vmx, tabla de segmentos, acceso a memoria.
- mv.c/mv.h:decodificación, disassembler, ciclo de ejecución e instrucciones.
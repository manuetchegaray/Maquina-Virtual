# Maquina-Virtual 2026

Sistema Operativo
    Desarrollada y compilada para windows.


Requerimintos Previos
    Ninguno. vmx.exe es un ejecutable nativo de windows.

Compilacion
    gcc -Wall -o vmx.exe main.c mv.c memoria.c

Ejecucion
    vmx.exe [filename.vmx] [filename.vmi] [m=M] [-d] [-p param1 ... paramN]

 filename.vmx  programa en lenguaje maquina (version 1 o 2).
    filename.vmi  archivo de imagen. Si se indica junto al .vmx, se genera en cada breakpoint (SYS F). Si se indica solo, se retoma la
    ejecucion desde esa imagen.
    m=M          tamaño de la memoria principal en KiB (por defecto 16).
    -d            muestra el codigo desensamblado antes de ejecutarlo.
    -p            parametros para la subrutina principal (siempre al final).

    Es obligatorio indicar al menos un .vmx o un .vmi.

Breakpoints (SYS F, solo si se indico un .vmi)
    g      continua hasta el proximo breakpoint
    q      aborta la ejecucion (el .vmi queda guardado para retomarla)
    Enter  ejecuta la siguiente instruccion y vuelve a pausar

Herramientas de la catedra
    vmt.exe  traductor:  vmt.exe programa.asm programa.vmx v=2
    vmg.exe  debugger:   vmg.exe imagen.vmi [-r] [-s] [w=W]

Archivos
- main.c: lectura de argumentos y arranque (programa o imagen).
- memoria.c/memoria.h: carga del .vmx, segmentos, Param Segment, pila inicial,
  imagen .vmi y acceso a memoria.
- mv.c/mv.h: decodificacion, operandos (sectores y modificadores), instrucciones,
  pila, llamadas al sistema, breakpoints y disassembler.
- docs/: enunciados y guias de assembler de la catedra.

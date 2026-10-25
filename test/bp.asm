\\DATA 10
\\STACK 30
TXT EQU "Hola"
main: MOV EAX, 5
      SYS 0xF
      ADD EAX, 1
      MOV [DS+0], EAX
      SYS 0xF
      MOV EBX, 9
      STOP
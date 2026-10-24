\\DATA 10
\\EXTRA 20
\\STACK 30
TXT  EQU "Hola"
TXT2 EQU "Chau"
otra: MOV EAX, 1
main: MOV EDX, KS
      ADD EDX, TXT2
      STOP
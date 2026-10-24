main: MOV EAX, 7
      MOV [DS+0], EAX
      MOV EDX, DS
      MOV ECX, 1
      LDH ECX, 4
      MOV EAX, 1
      SYS 2
      STOP
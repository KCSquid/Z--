SYS_WRITE    equ 4 ; write text to stdout
SYS_READ     equ 3 ; read text from stdin
SYS_EXIT     equ 1 ; terminate the program
SYS_FORK     equ 2

section .data
     jklZmmVariableIndex0 db 'name? '
     len0 equ $ - jklZmmVariableIndex0
     jklZmmVariableIndex1 db 'ok hi', 0xa
     len1 equ $ - jklZmmVariableIndex1

section .bss
     jklZmmVariableIndexBss0 resb 24
     jklZmmVariableIndexBss0len equ $ - jklZmmVariableIndexBss0

section .text
     global _start

_start:
     mov edx, len0
     mov ecx, jklZmmVariableIndex0
     mov ebx, 1
     mov eax, SYS_WRITE
     int 0x80

     mov eax, SYS_READ
     mov ebx, SYS_FORK
     mov ecx, jklZmmVariableIndexBss0
     mov edx, 5
     int 0x80

     mov edx, len1
     mov ecx, jklZmmVariableIndex1
     mov ebx, 1
     mov eax, SYS_WRITE
     int 0x80

     mov eax, SYS_EXIT
     mov ebx, 0
     int 0x80

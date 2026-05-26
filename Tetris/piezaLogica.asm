.386
.model flat, stdcall
.stack 4096


public inicializarPiezaASM

.data
.code



inicializarPiezaASM PROC pPieza:DWORD, tipo:DWORD
    mov ebx, tipo
    mov esi, pPieza

    cmp ebx,0
    je PIEZA_I

    cmp ebx,1
    je PIEZA_O

    cmp ebx,2
    je PIEZA_T

    cmp ebx,3
    je PIEZA_S

    cmp ebx,4
    je PIEZA_Z

    cmp ebx,5
    je PIEZA_J

    cmp ebx,6
    je PIEZA_L

    PIEZA_I:
        mov dword ptr [esi], 0
        mov dword ptr [esi + 4], 0
        mov dword ptr [esi + 8], 0
        mov dword ptr [esi + 12], 0
        ;
        mov dword ptr [esi + 16], 1
        mov dword ptr [esi + 20], 1
        mov dword ptr [esi + 24], 1
        mov dword ptr [esi + 28], 1
        ;
        mov dword ptr [esi + 32], 0
        mov dword ptr [esi + 36], 0
        mov dword ptr [esi + 40], 0
        mov dword ptr [esi + 44], 0
        ;
        mov dword ptr [esi + 48], 0
        mov dword ptr [esi + 52], 0
        mov dword ptr [esi + 56], 0
        mov dword ptr [esi + 60], 0
        jmp FIN_INICIALIZAR

   PIEZA_O:
         mov dword ptr [esi], 0
        mov dword ptr [esi + 4], 0
        mov dword ptr [esi + 8], 0
        mov dword ptr [esi + 12], 0
        ;
        mov dword ptr [esi + 16], 0
        mov dword ptr [esi + 20], 1
        mov dword ptr [esi + 24], 1
        mov dword ptr [esi + 28], 0
        ;
        mov dword ptr [esi + 32], 0
        mov dword ptr [esi + 36], 1
        mov dword ptr [esi + 40], 1
        mov dword ptr [esi + 44], 0
        ;
        mov dword ptr [esi + 48], 0
        mov dword ptr [esi + 52], 0
        mov dword ptr [esi + 56], 0
        mov dword ptr [esi + 60], 0
        jmp FIN_INICIALIZAR

    PIEZA_T:
         mov dword ptr [esi], 0
        mov dword ptr [esi + 4], 1
        mov dword ptr [esi + 8], 0
        mov dword ptr [esi + 12], 0
        ;
        mov dword ptr [esi + 16], 1
        mov dword ptr [esi + 20], 1
        mov dword ptr [esi + 24], 1
        mov dword ptr [esi + 28], 0
        ;
        mov dword ptr [esi + 32], 0
        mov dword ptr [esi + 36], 0
        mov dword ptr [esi + 40], 0
        mov dword ptr [esi + 44], 0
        ;
        mov dword ptr [esi + 48], 0
        mov dword ptr [esi + 52], 0
        mov dword ptr [esi + 56], 0
        mov dword ptr [esi + 60], 0
        jmp FIN_INICIALIZAR

    PIEZA_S:
         mov dword ptr [esi], 0
        mov dword ptr [esi + 4], 1
        mov dword ptr [esi + 8], 0
        mov dword ptr [esi + 12], 0
        ;
        mov dword ptr [esi + 16], 0
        mov dword ptr [esi + 20], 1
        mov dword ptr [esi + 24], 1
        mov dword ptr [esi + 28], 0
        ;
        mov dword ptr [esi + 32], 0
        mov dword ptr [esi + 36], 0
        mov dword ptr [esi + 40], 1
        mov dword ptr [esi + 44], 0
        ;
        mov dword ptr [esi + 48], 0
        mov dword ptr [esi + 52], 0
        mov dword ptr [esi + 56], 0
        mov dword ptr [esi + 60], 0
        jmp FIN_INICIALIZAR

    PIEZA_J:
        mov dword ptr [esi], 0
        mov dword ptr [esi + 4], 0
        mov dword ptr [esi + 8], 1
        mov dword ptr [esi + 12], 0
        ;
        mov dword ptr [esi + 16], 0
        mov dword ptr [esi + 20], 0
        mov dword ptr [esi + 24], 1
        mov dword ptr [esi + 28], 0
        ;
        mov dword ptr [esi + 32], 0
        mov dword ptr [esi + 36], 1
        mov dword ptr [esi + 40], 1
        mov dword ptr [esi + 44], 0
        ;
        mov dword ptr [esi + 48], 0
        mov dword ptr [esi + 52], 0
        mov dword ptr [esi + 56], 0
        mov dword ptr [esi + 60], 0
        jmp FIN_INICIALIZAR

    PIEZA_Z:
        mov dword ptr [esi], 0
        mov dword ptr [esi + 4], 0
        mov dword ptr [esi + 8], 0
        mov dword ptr [esi + 12], 0
        ;
        mov dword ptr [esi + 16], 0
        mov dword ptr [esi + 20], 1
        mov dword ptr [esi + 24], 1
        mov dword ptr [esi + 28], 0
        ;
        mov dword ptr [esi + 32], 0
        mov dword ptr [esi + 36], 0
        mov dword ptr [esi + 40], 1
        mov dword ptr [esi + 44], 1
        ;
        mov dword ptr [esi + 48], 0
        mov dword ptr [esi + 52], 0
        mov dword ptr [esi + 56], 0
        mov dword ptr [esi + 60], 0
       jmp FIN_INICIALIZAR

    PIEZA_L:
        mov dword ptr [esi], 0
        mov dword ptr [esi + 4], 1
        mov dword ptr [esi + 8], 0
        mov dword ptr [esi + 12], 0
        ;
        mov dword ptr [esi + 16], 0
        mov dword ptr [esi + 20], 1
        mov dword ptr [esi + 24], 0
        mov dword ptr [esi + 28], 0
        ;
        mov dword ptr [esi + 32], 0
        mov dword ptr [esi + 36], 1
        mov dword ptr [esi + 40], 1
        mov dword ptr [esi + 44], 0
        ;
        mov dword ptr [esi + 48], 0
        mov dword ptr [esi + 52], 0
        mov dword ptr [esi + 56], 0
        mov dword ptr [esi + 60], 0
         jmp FIN_INICIALIZAR


    FIN_INICIALIZAR:
    ret
inicializarPiezaASM ENDP

END
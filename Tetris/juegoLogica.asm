.386
.model flat, stdcall
.stack 4096

public getPuntajeASM
public aumentarPuntajeASM
public rotarPiezaASM
public limpiarLineasASM
public verificarColisionASM
public colocarPiezaASM
public llenarTableroASM
public hayColumnaLlenaASM

.data
.code


llenarTableroASM PROC pTablero:DWORD
    mov ebx, 0      
    FILA_L:
        cmp ebx, 4
        je FIN_LLENAR
        mov ecx, 0  ; columna
        COLUMNA_L:
            cmp ecx, 4
            je SIGUIENTE_FILA_L
            mov eax, ebx
            imul eax, 4
            add eax, ecx
            imul eax, 4
            mov edi, pTablero
            add edi, eax
            mov dword ptr [edi], 0
            inc ecx
            jmp COLUMNA_L
        SIGUIENTE_FILA_L:
        inc ebx
        jmp FILA_L
    FIN_LLENAR:
    ret
    llenarTableroASM ENDP


hayColumnaLlenaASM PROC pTablero:DWORD
    
    local temp:DWORD
    mov esi, pTablero
    lea edi, temp

    mov ecx, 200
    COPIAR:
    mov eax, [esi]
    mov [edi], eax
    add esi, 4
    add edi, 4
    loop COPIAR

    mov edx,0
    mov ebx,0
    mov edi, temp
    REVISAR_COLUMNAS:
        mov ecx, 9
        push ecx
        REVISAR_COL_INDV:
        mov eax, [edi]
        cmp eax,0
        je SIGUIENTE_COL
        inc ebx
        add edi,40
        loop REVISAR_COL_INDV

        cmp ebx,10
        je HAY_COLUMNA_LLENA

        SIGUIENTE_COL:
        inc edx
        mov edi, temp
        add edx,4
        add edi, edx
        pop ecx
    loop REVISAR_COLUMNAS

    mov eax, 0
    jmp FIN

    HAY_COLUMNA_LLENA: 
    mov eax, 1


    FIN:
  
    ret
hayColumnaLlenaASM ENDP

getPuntajeASM PROC punteroPuntaje:DWORD
    mov eax, punteroPuntaje
    mov eax, [eax]
    ret
getPuntajeASM ENDP


aumentarPuntajeASM PROC punteroPuntaje:DWORD, aumento:DWORD
    mov eax, punteroPuntaje
    mov ecx, [eax]
    add ecx, aumento
    mov [eax], ecx
    ret
aumentarPuntajeASM ENDP


rotarPiezaASM PROC pMatriz:DWORD
    local temp[16]:DWORD
    mov esi, pMatriz
    lea edi, temp

    mov ecx, 16
    COPIAR:
        mov eax, [esi]
        mov [edi], eax
        add esi, 4
        add edi, 4
        loop COPIAR

   
    mov edi, pMatriz
    mov ebx, 0         
    FILA:
        mov ecx, 0      
        COLUMNA:
            mov eax, ebx
            imul eax, 4
            add eax, ecx
            imul eax, 4         
            lea esi, temp
            add esi, eax
            mov eax, [esi]      

            mov edx, ecx
            imul edx, 4
            mov esi, 3
            sub esi, ebx
            add edx, esi
            imul edx, 4         
            mov esi, pMatriz
            add esi, edx
            mov [esi], eax

            inc ecx
            cmp ecx, 4
            jl COLUMNA
        inc ebx
        cmp ebx, 4
        jl FILA
    ret
rotarPiezaASM ENDP

limpiarLineasASM PROC pMatriz:DWORD
    local lineas:DWORD
    mov lineas, 0
    mov ebx, 19       

    REVISAR_FILA:
        cmp ebx, 0
        jl FIN_LIMPIAR

        mov ecx, 0     ; columna
        mov esi, pMatriz
        mov eax, ebx
        imul eax, 10
        imul eax, 4
        add esi, eax   

        VERIFICAR_COLUMNA:
            cmp ecx, 10
            je FILA_COMPLETA
            mov eax, [esi + ecx*4]
            cmp eax, 0
            je FILA_INCOMPLETA
            inc ecx
            jmp VERIFICAR_COLUMNA

        FILA_COMPLETA:
            inc lineas
            mov edx, ebx   
            BAJAR:
                cmp edx, 0
                je LIMPIAR_TOP
                mov eax, edx
                imul eax, 10
                imul eax, 4
                mov edi, pMatriz
                add edi, eax        

                mov eax, edx
                dec eax
                imul eax, 10
                imul eax, 4
                mov esi, pMatriz
                add esi, eax        

                mov ecx, 10
                COPIAR_FILA:
                    mov eax, [esi + ecx*4 - 4]
                    mov [edi + ecx*4 - 4], eax
                    loop COPIAR_FILA

                dec edx
                jmp BAJAR

            LIMPIAR_TOP:
                mov edi, pMatriz
                mov ecx, 10
                LIMPIAR:
                    mov dword ptr [edi + ecx*4 - 4], 0
                    loop LIMPIAR
            jmp REVISAR_FILA   

        FILA_INCOMPLETA:
            dec ebx
            jmp REVISAR_FILA

    FIN_LIMPIAR:
    mov eax, lineas
    ret
limpiarLineasASM ENDP

verificarColisionASM PROC pTablero:DWORD, pPieza:DWORD, xPos:DWORD, yPos:DWORD
    mov ebx, 0    
    FILA_P:
        cmp ebx, 4
        je SIN_COLISION
        mov ecx, 0  
        COLUMNA_P:
            cmp ecx, 4
            je SIGUIENTE_FILA_P

            mov eax, ebx
            imul eax, 4
            add eax, ecx
            imul eax, 4
            mov esi, pPieza
            add esi, eax
            mov eax, [esi]
            cmp eax, 0
            je SIGUIENTE_COL_P  

            ; posicion en tablero
            mov eax, ebx
            add eax, yPos      
            cmp eax, 20
            jge HAY_COLISION    

            mov edx, ecx
            add edx, xPos       
            cmp edx, 0
            jl HAY_COLISION     
            cmp edx, 10
            jge HAY_COLISION    

            mov esi, eax
            imul esi, 10
            add esi, edx
            imul esi, 4
            add esi, pTablero
            mov eax, [esi]
            cmp eax, 0
            jne HAY_COLISION

            SIGUIENTE_COL_P:
            inc ecx
            jmp COLUMNA_P

        SIGUIENTE_FILA_P:
        inc ebx
        jmp FILA_P

    HAY_COLISION:
    mov eax, 1
    ret

    SIN_COLISION:
    mov eax, 0
    ret
verificarColisionASM ENDP



colocarPiezaASM PROC pTablero:DWORD, pPieza:DWORD, xPos:DWORD, yPos:DWORD, color:DWORD
    mov ebx, 0      ; fila
    FILA_C:
        cmp ebx, 4
        je FIN_COLOCAR
        mov ecx, 0  ; columna
        COLUMNA_C:
            cmp ecx, 4
            je SIGUIENTE_FILA_C

            mov eax, ebx
            imul eax, 4
            add eax, ecx
            imul eax, 4
            mov esi, pPieza
            add esi, eax
            mov eax, [esi]
            cmp eax, 0
            je SIGUIENTE_COL_C

            ; posicion en tablero
            mov eax, ebx
            add eax, yPos
            imul eax, 10
            mov edx, ecx
            add edx, xPos
            add eax, edx
            imul eax, 4
            mov edi, pTablero
            add edi, eax
            mov eax, color
            mov [edi], eax

            SIGUIENTE_COL_C:
            inc ecx
            jmp COLUMNA_C

        SIGUIENTE_FILA_C:
        inc ebx
        jmp FILA_C

    FIN_COLOCAR:
    ret
colocarPiezaASM ENDP

END
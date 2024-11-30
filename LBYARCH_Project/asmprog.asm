section .data
    factor dq 255.0                ; Constant for scaling (1.0 * 255)

section .text
bits 64
default rel
global imgCvtGrayDoubleToInt

imgCvtGrayDoubleToInt:
    ; Function arguments:
    ; rdi = input (pointer to double array)
    ; rsi = output (pointer to uint8_t array)
    ; rdx = width
    ; rcx = height

    push rbp
    mov rbp, rsp
    sub rsp, 32                     ; Reserve stack space

    ; Check input and output pointers
    test rdi, rdi                   ; Check if input pointer is null
    jz null_pointer_error
    test rsi, rsi                   ; Check if output pointer is null
    jz null_pointer_error

    ; Compute total pixels
    imul rdx, rcx                   ; rdx = width * height

    ; Initialize loop counter
    xor r8, r8                      ; r8 = 0 (loop counter)

convert_loop:
    ; Check if we've processed all pixels
    cmp r8, rdx
    jge end_loop

    ; Load the current double value
    mov rax, rdi                    ; Load input array pointer into rax
    movsd xmm0, qword [rax + r8 * 8]  ; xmm0 = input[r8]

    ; Scale the value by 255
    lea rax, [rel factor]           ; Load address of 'factor'
    movsd xmm1, qword [rax]         ; xmm1 = 255.0
    mulsd xmm0, xmm1                ; xmm0 *= 255.0

    ; Convert to integer
    cvttsd2si eax, xmm0             ; eax = (int)xmm0

    ; Clamp the value to 0-255
    cmp eax, 255
    jle not_overflow
    mov eax, 255                    ; Cap to 255
not_overflow:
    cmp eax, 0
    jge not_underflow
    mov eax, 0                      ; Cap to 0
not_underflow:

    ; Store the result
    mov rax, rsi                    ; Load output array pointer into rax
    mov byte [rax + r8], al         ; output[r8] = (uint8_t)eax

    ; Increment loop counter
    inc r8
    jmp convert_loop

end_loop:
    mov rsp, rbp
    pop rbp
    ret

null_pointer_error:
    int3                             ; Trigger breakpoint for debugging
    mov rsp, rbp
    pop rbp
    ret

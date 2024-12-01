section .data
    factor dq 255.0                ; Constant for scaling (1.0 * 255)

section .text
bits 64
default rel

global imgCvtGrayDoubleToInt

imgCvtGrayDoubleToInt:
    ; Function arguments:
    ; xmm0 = input (double value, grayscale intensity in range [0.0, 1.0])

    push rbp
    mov rbp, rsp
    sub rsp, 16                     ; Reserve stack space

    ; Scale the value by 255
    lea rax, [rel factor]           ; Load address of 'factor'
    movsd xmm1, qword [rax]         ; xmm1 = 255.0
    mulsd xmm0, xmm1                ; xmm0 *= 255.0

    ; Round to the nearest integer
    roundsd xmm0, xmm0, 0           ; Round xmm0 to nearest integer (mode 0)

    ; Convert to integer (truncate after rounding)
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

    ; Return the result in AL (lower 8 bits of EAX)
    mov rsp, rbp
    pop rbp
    ret

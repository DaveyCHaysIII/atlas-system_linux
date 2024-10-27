BITS 64

section .text:
	global asm_strcasecmp

asm_strcasecmp:
	push rbp
	mov rbp, rsp
	push rbx

_while:
	movzx eax, byte [rdi]
	movzx ebx, byte [rsi]
	cmp al, 0
	jne _al_case
	cmp bl, 0
	jne _bl_case
	jmp _done

_continue:
	inc rdi
	inc rsi
	jmp _while

_al_case:
	cmp al, 65
	jl _bl_case
	cmp al, 90
	jg _bl_case
	add ax, 32

_bl_case:
	cmp bl, 65
	jl _compare
	cmp bl, 90
	jg _compare
	add bx, 32

_compare:
	cmp al, bl
	je _continue
	jmp _done

_done:
	sub rax, rbx
	pop rbx
	mov rsp, rbp
	pop rbp
	ret

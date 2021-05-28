section .bss
	input resb 24

section .data
	msg db "Welcome "
	msg_len equ $ - msg

section .text
	global _start
_start:
	mov rax, 0
	mov rdi, 1
	mov rsi, input
	mov rdx, 24
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, msg
	mov rdx, msg_len
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, input
	mov rdx, 24
	syscall

	mov rax, 60
	mov rdi, 0
	syscall

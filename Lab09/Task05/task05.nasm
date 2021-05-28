section .bss
	in resb 24
	in_len equ $ - in

section .data
	msg db "Welcome "
	msg_len equ $ - text

section .text
	global _start
_start:
	mov rax, 0
	mov rdi, 1
	mov rsi, in
	mov rdx, in_len
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, msg
	mov rdx, msg_len
	syscall

	mov rax, 1
	mov rdi, 1
	mov rsi, in
	mov rdx, in_len
	syscall

	mov rax, 60
	mov rdi, 0
	syscall

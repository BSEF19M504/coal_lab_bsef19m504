SECTION .data
	num1    db    0x4
	num2    db    0x32

SECTION .bss
	res resb 1

SECTION .text
	global _start
_start:
	mov rcx,num1
	add rcx,num2
	add rcx,num2
	sub rcx,num2
	mov [res],rcx
	push byte res
	mov rax,60
	mov rdi,0
	syscall
	

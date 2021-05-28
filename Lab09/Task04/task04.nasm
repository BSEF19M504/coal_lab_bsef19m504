SECTION .data
	num1    db    0x4
	num2    db    0x32

SECTION .bss
	res resb 1

SECTION .text
	global _start
_start:
	mov [res],num1
	add [res],num2
	add [res],num2
	sub [res],num2
	push [res]
	mov rax,60
	mov rdi,0
	syscall
	

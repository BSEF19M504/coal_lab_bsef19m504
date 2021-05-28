SECTION .data
	num1    dd    0x41414141
 	num2    dq    0x42424242
SECTION .text
	global _start
_start:
	mov rcx,num1
	mov rdx,num2
	add rcx,rdx
	mov rax,60
	mov rdi,0
	syscall
	

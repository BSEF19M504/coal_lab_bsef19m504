// Computes RAM[1] = 1+...+RAM[0]
// Usage: put a number in RAM[0]
@16
M=1 // RAM[16] = 1 (i)
@17
D=0 // RAM[17] = 0 (sum)
@16
D=M
@ 0
D= D  -M
@17 // if i>RAM[0] goto 17
D;JGT
@16
D=M
@17
M=D+M // sum += i
@16
M=M+1 // i++
@4 // goto 4 loop
0;JMP
@17
D=A
@1
M=D //RAM[1] = sum
@21 //program end
0;JMP // infinite loop

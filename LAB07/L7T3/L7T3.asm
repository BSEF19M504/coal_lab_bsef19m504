@2
D=A
@R0	//p1
M=D

@3
D=A
@R1	//p2
M=D

@1
D=A
@R2	//q1
M=D

@4
D=A
@R3	//q2
M=D

@R2
D=M

@R0
D=D-M

@GOTO1
D;JGE
D=-D

(GOTO1)
@R5
M=D

@R3
D=M

@R1
D=D-M

@GOTO2
D;JGE
D=-D

(GOTO2)
@R7
M=D

@R5
D=M

@iter1
M=D

@R6
M=0

(LOOP1)
@R6
D=M

@R5
D=D+M

@R6
M=D

@iter1
M=M-1
D=M

@LOOP1
D;JGT

@R7
D=M

@iter2
M=D

@R8
M=0

(LOOP2)
@R8
D=M

@R7
D=D+M

@R8
M=D

@iter2
M=M-1
D=M

@LOOP2
D;JGT

@R6
D=M

@R8
D=D+M

@dist
M=D

(END)
@END
0;JMP

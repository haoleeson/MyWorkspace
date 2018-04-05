;N字节二进制数转换为 十进制 压缩BCD数
SrcADR		EQU	40H		;源二进制数首地址
BcdADR		EQU	50H		;转换后的BCD码首地址
N		EQU	2		; N字节 的二进制数
;N个字节的二进制数要转换成，N+1个字节BCD码(N<=6 时成立)
;SrcLength	EQU	N*8		;要转换的二进制位数

		ORG	00H
		SJMP	MAIN
		ORG	30H
MAIN:		
;传入参数赋值.将待转换二进制数存入;源二进制数地址;将源二进制数首地址存到R0
;N=1		
		MOV	R0,#SrcADR+N-1
		MOV	@R0,#055H	;(高位)
;N=2
		DEC	R0
		MOV	@R0,#055H	;(低位)
;N=3		
;		DEC	R0
;		MOV	@R0,#0FFH	;(低位)
;N=4		
;		DEC	R0
;		MOV	@R0,#0FFH	;(低位)
;N=5		
;		DEC	R0
;		MOV	@R0,#0FFH	;(低位)
		;完成赋值操作后R0，存的地址为 源二进制数首地址
		MOV	R1,#BcdADR	;将存十进制结果的BCD码首地址存到R1
		MOV	R2,#N
		ACALL	_dwBCD		;调用双字节BCD转换子程序
		;ACALL	_BCD		;[选做]调用N字节BCD转换
		SJMP	$	
		RET

;双字节二进制数转换为 十进制 压缩BCD数
;涉及 R0,R1,R2,R3,R6,R7,A
_dwBCD:
		MOV	A,R0
		MOV	R6,A		;将源二进制数首地址 暂存到R6
		MOV	A,R1
		MOV	R7,A		;将转换后的BCD码首地址 暂存到R7
;清结果BCD数单元
		MOV	R2,#2		;[方式2]要转换2个字节的二进制数，N+1个字节BCD数(N<=6)
		INC	R2
		CLR	A		;清A,A=00H
dwBCDclc:	MOV	@R1,A
		INC	R1
		DJNZ	R2,dwBCDclc
;清结果BCD数单元 完成
		MOV	R3,#16		;设置 BCDLoop 循环次数 2*8=16

dwBCDLoop:
;二进制数左移
		;MOV	R0,#SrcADR	;[方式1]将源二进制数首地址 存到R0
		MOV	A,R6		;[方式2]将源二进制数首地址 存到R0
		MOV	R0,A
		MOV	R2,#2		;N字节，移2次
		CLR	C		;清进位
		
dwBCDL1:	MOV	A,@R0		;取1个字节到A
		RLC	A		;二进制数带进位C循环左移一位
		MOV	@R0,A		;左移后暂存	
		INC	R0
		DJNZ	R2,dwBCDL1	;将Ai移位到C中，i = 15,14,13,...,0
		MOV	R2,#2
		INC	R2
		;MOV	R1,#BcdADR	;[方式1]将转换后的BCD码首地址 存到R1
		MOV	A,R7		;[方式2]将转换后的BCD码首地址 存到R1
		MOV	R1,A
			
dwBCDL2:	;实现x2：通过自加 + 进位(通过前面左移最高位跑到进位里)
		MOV	A,@R1		
		ADDC	A,@R1		;进行 y=(y+Ai)*2 Ai跑到进位里
		DA	A		;十进制调整
		MOV	@R1,A
		INC	R1
		DJNZ	R2,dwBCDL2
		
		DJNZ	R3,dwBCDLoop

		RET


;N字节二进制数转换为 十进制 压缩BCD数
;涉及 R0,R1,R2,R3,R5,R6,R7,A
_BCD:
		MOV	A,R0
		MOV	R6,A		;将源二进制数首地址 暂存到R6
		MOV	A,R1
		MOV	R7,A		;将转换后的BCD码首地址 暂存到R7
		MOV	A,R2
		MOV	R5,A		;将被转换数的长度N 暂存R5
;清结果BCD数单元
		;MOV	R2,#N+1		;[方式1]要转换N个字节的二进制数，N+1个字节BCD数(N<=6)
		INC	R2		;[方式2]要转换N个字节的二进制数，N+1个字节BCD数(N<=6),R2在传入时已被赋值N
		CLR	A		;清A,A=00H
BCDclc:		MOV	@R1,A
		INC	R1
		DJNZ	R2,BCDclc
;清结果BCD数单元 完成
		;MOV	R3,#SrcLength	;[方式1]设置 BCDLoop 循环次数 8*N 到R3
		MOV	A,R5		;[方式2]设置 BCDLoop 循环次数 8*N 到R3
		MOV	B,#08H
		MUL	AB		;8*N
		MOV	R3,A		;因为计算的字节数N比较小，8*N存在低位A中,高位B为0
BCDLoop:
;二进制数左移
		;MOV	R0,#SrcADR	;[方式1]将源二进制数首地址 存到R0
		MOV	A,R6		;[方式2]将源二进制数首地址 存到R0
		MOV	R0,A
		
		;MOV	R2,#N		;[方式1]N字节，移N次
		MOV	A,R5		;[方式2]N字节，移N次
		MOV	R2,A
		CLR	C		;清进位
		
BCDL1:		MOV	A,@R0		;取1个字节到A
		RLC	A		;二进制数带进位C循环左移一位
		MOV	@R0,A		;左移后暂存	
		INC	R0
		DJNZ	R2,BCDL1	;将Ai移位到C中，i = 15,14,13,...,0
		;MOV	R2,#N+1		;[方式1]N字节，移N+1次
		MOV	A,R5		;[方式2]N字节，移N+1次
		MOV	R2,A
		INC	R2
		;MOV	R1,#BcdADR	;[方式1]将转换后的BCD码首地址 存到R1
		MOV	A,R7		;[方式2]将转换后的BCD码首地址 存到R1
		MOV	R1,A
		
		
BCDL2:		;实现x2：通过自加 + 进位(通过前面左移最高位跑到进位里)
		MOV	A,@R1		
		ADDC	A,@R1		;进行 y=(y+Ai)*2 Ai跑到进位里
		DA	A		;十进制调整
		MOV	@R1,A
		INC	R1
		DJNZ	R2,BCDL2
		
		DJNZ	R3,BCDLoop

		;转换结束，返回R2--BCD结果的字节数N+1(N<=4时满足)
		MOV	A,R5
		MOV	R2,A
		INC	R2

		RET

		END
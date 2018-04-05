;双字节 无符号数乘法 子函数
;双字节 有符号数乘法 子函数
ADR	EQU	40H	;结果（积）的存放的首地址，占用4个字节 40~43H
		ORG	00H
		SJMP	MAIN
		ORG	30H
MAIN:
		;被乘数，乘数赋值
		MOV	R7,#0FFH
		MOV	R6,#0FFH
		MOV	R5,#0FFH
		MOV	R4,#0FEH
;		ACALL	_dwMUL	;调用双字节 无符号数乘法 子函数
		ACALL	_nMUL	;调用双字节 有符号数乘法 子函数
		SJMP	$
		RET
	
;双字节无符号数乘法 子函数
_dwMUL:	
;存放结果的首地址后的4字节空间清零
		MOV	R0,#ADR
		MOV	R1,#04H
dwMULclc:	MOV	@R0,#00H
		INC	R0
		DJNZ	R1,dwMULclc
		MOV	R0,#ADR

;部分相乘
;R6 * R4  --结果存 31,30H
		MOV	A,R4
		MOV	B,R6
		MUL	AB
		MOV	30H,A
		MOV	31H,B

;R7 * R4  --结果存 33,32H
		MOV	A,R4
		MOV	B,R7
		MUL	AB
		MOV	32H,A
		MOV	33H,B

;R6 * R5  --结果存 35,34H
		MOV	A,R5
		MOV	B,R6
		MUL	AB
		MOV	34H,A
		MOV	35H,B

;R7 * R5  --结果存 37,36H
		MOV	A,R5
		MOV	B,R7
		MUL	AB
		MOV	36H,A
		MOV	37H,B


;以上部分相乘的乘积求和（考虑进位）

;将积的第一个低字节填入 [首地址]，指针++
;@ADR[0]=30H

		MOV	@R0,30H	;@ADR[0]=30H	
		INC	R0

;将积的第二个低字节填入 [首地址+1]，指针++
;@ADR[1]=31H + 32H + 34H	
		MOV	A,31H
		ADD	A,32H	;A=31H + 32H
		MOV	32H,A	;把结果A暂存到32H
		
		;把进位加到33H，下次计算@ADR[2]会用到33H
		MOV	A,33H
		ADDC	A,#00H;加进位
		MOV	33H,A	;33H = 33H	+进位
		
		MOV	A,32H	;把上上步暂存在32H中的结果取出到A
		ADD	A,34H	;A=A+34H	;A=(31H+32H)+34H
		MOV	@R0,A	;@ADR[1]=31H + 32H + 34H	
		INC	R0

;将积的第三个低字节填入 [首地址+2]，指针++
;@ADR[2]=33H + 35H + 36H
		MOV	A,33H	
		ADDC	A,35H	;A=33H + 35H 带进位+
		MOV	35H,A		;把结果A暂存到35H
		
		;把进位加到37H，下次计算@ADR[3]会用到37H
		MOV	A,37H
		ADDC	A,#00H	;加进位
		MOV	37H,A	;37H = 37H	+进位
		
		MOV	A,35H	;把上上步暂存在35H中的结果取出到A
		ADD	A,36H	;A=A+36H	;A=(33H+35H)+36H
		MOV	@R0,A	;@ADR[2]=33H + 35H + 36H	
		INC	R0
		
;将积的第四个字节填入 [首地址+3]
;@ADR[3]=37H + 进位		
		MOV	A,37H
		ADDC	A,#00H	;加进位
		MOV	@R0,A		;@ADR[3]=37H + 进位

	RET

;双字节有符号数乘法 子函数
_nMUL:
		MOV	R2,#00H	;R7符号标志00H为正数，01H为负数
		MOV	R3,#00H	;R5符号标志00H为正数，01H为负数
		
		;判断R7R6正负
		MOV	A,R7
		JNB	ACC.7,nMUL1	;直接寻址位为0跳转，为正数，跳转
		;R7为负数
		MOV	R2,#01H	;R7负数符号标志
		
		;将R7,R6双字节取补码(变成无符号正数存在R7,R6)
		MOV A,R6	;原码低字节送A
        CPL A		;A内容取反+1(取补)
        INC A
        MOV R6,A	;补码低字节R6
        JZ	nMULZ1	;(A)=0,有进位，高字节需要反码+1(加上进位)，无进位只取反
        MOV A,R7	;原码高字节送A
        CPL A		;取反
        MOV R7,A	;高字节反码存入R7单元
        SJMP nMUL1
nMULZ1:	MOV A,R7	;有进位时	
        CPL A		;A内容取反+1(加上进位)
        INC A
        MOV R7,A	;高字节补码存入R7单元
		
		;判断R5R4正负
nMUL1:	MOV	A,R5
		JNB	ACC.7,nMUL2	;直接寻址位为0跳转，为正数，跳转
		;R5为负数
		MOV	R3,#01H	;R3负数符号标志

		;将R5,R4双字节取补码(变成无符号正数存在R5,R4)
		MOV A,R4	;原码低字节送A
        CPL A		;A内容取反+1(取补)
        INC A
        MOV R4,A	;补码低字节R4
        JZ	nMULZ2	;(A)=0,有进位，高字节需要反码+1(加上进位)，无进位只取反
        MOV A,R5	;原码高字节送A
        CPL A		;取反
        MOV R5,A	;高字节反码存入R5单元
        SJMP nMUL2
nMULZ2:	MOV A,R5	;有进位时	
        CPL A		;A内容取反+1(加上进位)
        INC A
        MOV R5,A	;高字节补码存入R5单元

nMUL2:	ACALL	_dwMUL	;调用双字节无符号数乘法 子函数
		;判断R2、R3 状态 <结果为正，跳转到Fin>
		MOV	A,R2
		XRL	A,R3	;R2与R3异或
		JZ	nMUL_Fin
		;JNB	ACC.0,nMUL_Fin	;直接寻址位为0跳转，结果为正数，跳转到结束
		;<为负>乘积结果<四字节补码>
		ACALL	_QuBuMa	;调用取补码
		
nMUL_Fin:	RET
		
;求以ADR为首地址的 N个字节 的负数的补码 ,子函数
;用到 R0(首字节),R1(N个字节),A,B		
_QuBuMa:	
		;第一位取补(不考虑进位)
		MOV	R0,#ADR
		MOV	R1,#04H	;循环次数
		MOV	B,#01H	;B进位值，初始值为1，第一次最低位+1	
QBMLoop:	
		MOV	A,@R0	;原码低字节送A
		CPL A		;A内容取反+1(取补)
		ADD	A,B		;B表示进位
		MOV	@R0,A	;补码低字节存回
		INC	R0
		JZ	QBMJin	;(A)=0,有进位，高字节需要反码+1(加上进位)，无进位只取反
		MOV	B,#00H	;无进位+0
		SJMP	QBMJudg
QBMJin:	MOV	B,#01H	;有进位+1
QBMJudg:DJNZ	R1,QBMLoop
		RET
		
		END
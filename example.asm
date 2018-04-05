DATAS SEGMENT
    ;此处输入数据段代码
    MS DB 0
    SEC DB 0
    MIN DB 0
    BUF DB 'This program is written by BeiFeng', 0DH,0AH,'$'  
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
    STA DB 256 DUP(?)
    TOP EQU $-STA
STACKS ENDS

CODES SEGMENT
MAIN PROC FAR
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
	XOR AX,AX
    MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码
    MOV AX,STACKS
    MOV SS,AX
    MOV AX,TOP
    MOV SP,AX
    
    ;-----读取1CH原中断向量-----
    CLI
    MOV AL,1CH
    MOV AH,35H	;读取1CH原中断向量
    
    INT 21H
    PUSH ES		;保存原中断向量的段地址 CS
    PUSH BX		;保存原中断向量的偏移地址 IP
    
    ;-----设置中断向量-----
    PUSH DS
    MOV DX,OFFSET CLOCK		;取计时处理程序的偏移地址送DX
    MOV AX,SEG CLOCK		;取计时处理程序的段地址送DS
    MOV DS,AX
    MOV AX,251CH
    INT 21H		;改写1CH号中断向量
    POP DS
    
    ;-----定位光标-----
    MOV DH,05H		;第5行
    MOV DL,11H		;第11列
    MOV BH,00H
    MOV AH,02H
    INT 10H
    
    ;-----在光标指定位置显示提示-----
    LEA DX,BUF
    MOV AH,09H
    INT 21H
    
    STI		;开中断，IF=1
    
    ; -----等待中断-----
LOP:CALL CURSOR		;定位光标
	CALL DISPTIME
	MOV AH,0BH		;用INT21H/0BH功能号，检测是否有按键按下
	INT 21H
	CMP AL,00H
	JZ DON		;(AL)=0,无按键按下，跳转
	MOV AH,08H		;有键，用INT 21H/08H功能号读键值AL
	INT 21H
	CMP AL,1BH		;是ESC键？
	JE END1		;是，退出；否，跳转
DON:JMP LOP

	;-----恢复系统1CH类型中断向量-----
END1:POP AX
	POP DS
	MOV AL,1CH
	MOV AH,25H
	INT 21H
	MOV AH,4CH		;返回DOS
	INT 21H
    RET
MAIN ENDP

;-----定位屏幕光标位置，确定时间在屏幕的显示位置-----
CURSOR	PROC NEAR
	PUSH AX
	PUSH BX
	PUSH DX
	MOV DH,07H		;第7行
	MOV DL,1AH		;第26列
	MOV BH,00H
	MOV AH,02H		;将光标设置在第7行，第26列
	INT 10H
	POP DX
	POP BX
	POP AX
	RET
CURSOR ENDP

;-----1CH中断服务程序-----
CLOCK PROC NEAR
	PUSH AX
	PUSH DS
	MOV AX,DATAS
	MOV DS,AX		;取主程序的数据段 段地址
	INC MS
	CMP MS,18		;判断是否到1秒
	JNE LL		;不到一秒，退出
	MOV MS,0		;将计时单元清零
	INC SEC		;秒位加1
	CMP SEC,60	;判断是否到1分钟
	JNE LL		;不到1分钟，退出
	MOV SEC,0	;将秒位清零
	MOV AL,MIN
	INC MIN		;分钟位加1
	CMP MIN,60		;判断是否到1小时
	JNE LL		;不到1小时，退出
	MOV MIN,0
LL: POP AX
	MOV DS,AX
	POP AX
	STI
	IRET
CLOCK ENDP

;-----时钟显示子程序-----
DISPTIME PROC NEAR
	PUSH AX
	MOV AL,MIN
	CALL DISP		;显示分
	MOV AL,':'
	MOV AH,0EH		;显示分与秒之间的分隔符':'
	INT 10H
	MOV AL,SEC
	CALL DISP		;显示秒
	POP AX
	RET
DISPTIME ENDP

DISP PROC NEAR
	PUSH CX
	MOV CL,10
	MOV AH,0
	DIV CL
	PUSH AX
	ADD AL,30H
	MOV AH,0EH
	INT 10H		;BIOS功能调用 10H/0E，显示时间的十位
	POP AX
	MOV AL,AH
	ADD AL,30H
	MOV AH,0EH
	INT 10H		;显示时间各位
	POP CX
	RET
DISP ENDP
CODES ENDS
	END START


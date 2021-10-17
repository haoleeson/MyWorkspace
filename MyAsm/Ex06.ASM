;_IIC_利用P1端口访问CAT24WC02
;**************************************************************************************
;【第六次作业：串行总线扩展实验 利用P1端口访问CAT24WC02(IIC)】
;先将单片机内部RAM中30H~37H单元的值复制到CAT24WC02中的00H~07H单元。
;然后又将这8个数从CAT24WC02中复制到单片机内部RAM的40H~47H单元中。
;利用P1端口访问CAT24WC02(兼容AT24C02).   P1.7--SDA ; P1.6--SCL ;
;**************************************************************************************
;宏定义
N		EQU	8			;数据个数
SCL		EQU	P1.6			;串行时钟线 SCL
SDA		EQU	P1.7			;串行数据线 SDA
Send_ADR	EQU	30H			;发送数据缓冲区首地址
Receive_ADR	EQU	40H			;接收数据缓冲区首地址
CAT24WC02_ADR	EQU	0A0H			;CAT24WC02的器件地址：	0A0H
AT24CRAM_ADR	EQU	00H			;CAT24WC02中的00H~07H单元
;参数定义
ACK		BIT	10H			;响应标志位，要求可以单独位操作
SLA		DATA	50H			;器件地址缓冲单元
SUBA		DATA	51H			;AT24C02片内字节地址缓冲单元
NUMBYTE		DATA	52H			;发送及读取字节数目缓冲单元
VAR_END		EQU	52H			;最后一个字节变量的位置
;堆栈定义
STACK_INI	EQU	VAR_END+1		;须保证足够的空间
;**************************************************************************************
		ORG	0000H
		SJMP	MAIN
		ORG	0030H
;MAIN程序开始**************************************************************************
MAIN:		MOV	SP,#STACK_INI		;设置栈底指针
;数组初始化开始，查表法 将TABLE中8个数存放在ADR后,免去直接在内存中修改*****************
		MOV	A,#00H
		MOV	DPTR,#TABLE
		MOV	R0,#Send_ADR
InitLoop:	MOVC	A,@A+DPTR
		MOV	@R0,A
		INC	R0
		INC	DPTR
		MOV	A,#00H
		CJNE	R0,#Send_ADR+N,InitLoop
;数组初始化结束************************************************************************
		;先将单片机内部RAM中30H~37H单元的值复制到CAT24WC02中的00H~07H单元。
		ACALL	WRAT24C			;向AT24C02指定字节地址写入N个字节数据

;清接收缓冲区单元 40H~47H
		MOV	R0,#Receive_ADR
		MOV	R1,#N
RecRamClc:	MOV	@R0,#00H
		INC	R0
		DJNZ	R1,RecRamClc
		
;发送与接收间隔延时（共753个时钟周期,若晶震为11.058，延时0.817mS）
		ACALL	DELAY
		
		;从CAT24WC02中的00H~07H单元 读取数据到 单片机内部RAM的40H~47H单元中
		ACALL	RDAT24C			;从AT24C02指定字节地址中读出N个数据
		
		SJMP	$
		RET
;MAIN程序结束**************************************************************************
;设置数组值，方便测试		
TABLE:		DB	01H,02H,03H,04H,05H,06H,07H,08H

;写串行EEPROM子程序WRAT24C*************************************************************
;SLA-器件地址 ;SUBA-AT24C02片内字节地址缓冲单元 ;R3-字节数N ;R1-发送数据首地址
		;向AT24C02指定字节地址写入N个字节数据
WRAT24C:	MOV	SLA,#CAT24WC02_ADR	;AT24C02器件地址
		MOV	NUMBYTE,#N		;欲发送字节数N
		MOV	SUBA,#AT24CRAM_ADR	;AT24C02片内字节地址00H
		LCALL	IWRNBYTE		;写AT24C02子程序
		RET
		;可对应  书 P182 时序图(a)		
IWRNBYTE:	MOV	A,NUMBYTE
		MOV	R3,A			;将要发送的字节数N送R3
		;启动IIC总线
		LCALL	START			
		MOV	A,SLA			;取器件地址 0A0H
		LCALL	WRBYTE			;调用 字节写入子程序
		LCALL	CACK			;检查响应信号
		JNB	ACK,RETWRN		;无响应信号，退出
		;JNB为0跳转，为1检测到响应信号，继续
		MOV	A,SUBA			;取字节地址
		LCALL	WRBYTE			;调用 字节写入子程序
		LCALL	CACK			;检查响应信号
		JNB	ACK,RETWRN		;无响应信号，退出
		;JNB为0跳转
		MOV	R1,#Send_ADR		;发送缓冲区首地址 送R1		
		;开始发送数据
WRDA:		MOV	A,@R1	
		LCALL	WRBYTE			;调用 字节写入子程序
		LCALL	CACK			;检查响应信号
		JNB	ACK,IWRNBYTE		;无响应信号，重新操作 ，中途出现无响应就从头开始
		INC	R1
		ACALL	I2C_DELAY
		DJNZ	R3,WRDA			;循环N次，将N个字节数据发送
		
		;结束IIC总线信号
RETWRN:		LCALL	STOP
		NOP
		NOP

		RET

;读取串行EEPROM子程序 RDAT24C**********************************************************
		;从AT24C02指定字节地址中读出N个数据
RDAT24C:	MOV	SLA,#CAT24WC02_ADR	;AT24C02器件地址 0A0H
		MOV	NUMBYTE,#N		;欲读取字节数N
		MOV	SUBA,#AT24CRAM_ADR	;AT24C02片内字节地址00H
		LCALL	IRDNBYTE		;读AT24C02 子程序
		RET
;书 P183 时序图(b)
IRDNBYTE:	
		;启动IIC总线
		LCALL	START
		MOV	A,SLA			;取器件地址 0A0H
		LCALL	WRBYTE			;调用 字节写入子程序
		LCALL	CACK			;检查响应信号
		JNB	ACK,IRDNBYTE		;无响应信号,再次写器件地址
		;JNB为0跳转
		MOV	A,SUBA			;取字节地址
		LCALL	WRBYTE			;调用 字节写入子程序
		LCALL	CACK			;检查响应信号
		JNB	ACK,IRDNBYTE		;无响应信号，再次写	JNB为0跳转
		;JNB为0跳转

		LCALL	START			;再发送启动信号
		MOV	A,SLA			;0A0H
		INC	A			;器件地址，R/W位清零
		LCALL	WRBYTE			;字节写入
		LCALL	CACK			;检查响应信号
		JNB	ACK,IRDNBYTE		;无响应信号，重新启动
		;有响应信号，继续下一步操作
		MOV	R1,#Receive_ADR		;接收数据缓冲首地址
		MOV	R3,NUMBYTE		;读取字节数N-1送R3
		DEC	R3			;最后一位读完后发送 非应位

RDLoop:		LCALL	RDBYTE			;调用获取读取单字节 子程序
		MOV	@R1,A
		LCALL	MACK			;发送响应应答位
		INC	R1
		DJNZ	R3,RDLoop		;循环接收N-1字节
		;读第N位后发 非应答位
		LCALL	RDBYTE
		MOV	@R1,A
		LCALL	MNACK			;发送 非应答位
RETRDN:		LCALL	STOP			;发送结束信号
		NOP
		NOP
		RET

;发送字节子程序************************************************************************
WRBYTE:		MOV	R0,#08H			;一字节8位
		CLR	SCL			;拉低时钟开始数据传输
WLP:		RLC	A			;将待 发送位 移到 C中
		MOV	SDA,C			;发送1位数据到总线
		NOP
		NOP
		SETB	SCL			;发送时钟位
		ACALL	I2C_DELAY		;延时至少4.7us		
		CLR	SCL
		NOP
		NOP
		DJNZ	R0,WLP			;循环8位
		NOP
		RET

;读取字节子程序************************************************************************
RDBYTE:		MOV	R0,#08H			;一字节8位
		MOV	A,#00H			;清A
		SETB	SDA			;/*置数据线为输入方式*/
RLoop:		
		NOP
		CLR	SCL			;/*置时钟线为低，准备接收数据位*/
		ACALL	I2C_DELAY		;延时至少4.7us	
		SETB	SCL			;/*置时钟线为高使数据线上数据有效*/
		NOP
		NOP
		MOV	C,SDA			;把数据发送到C
		RLC	A			;移入A中 带进位C循环左移到A
		NOP
		NOP
		DJNZ	R0,RLoop		;循环8次
		CLR	SCL
		NOP
		NOP

		RET

;启动IIC总线 子程序 (使SDA产生一个有高变低的跳变)**************************************
START:
		SETB	SDA
		NOP
		SETB	SCL			;硬件进入SDA检测状态
		ACALL	I2C_DELAY		;延时至少4.7us
		CLR	SDA			;SDA由1->0,产生开始信号
		ACALL	I2C_DELAY		;延时至少4.7us
		CLR	SCL			;钳住I2C总线，准备发送或接收数据 
		NOP

		RET

;结束IIC总线 子程序 (使SDA产生一个由低变高的跳变)**************************************
STOP:		
		CLR	SDA
		NOP
		NOP		
		SETB	SCL
		ACALL	I2C_DELAY		;延时至少4.7us
		SETB	SDA			;SDA由0->1,产生结束信号
		ACALL	I2C_DELAY		;延时至少4.7us

		RET
	
;产生ACK应答 子程序********************************************************************
MACK:		
		CLR	SDA			;SDA变为低电平，为应答信号
		NOP
		NOP
		NOP
		SETB	SCL			;产生时钟脉冲
		ACALL	I2C_DELAY		;延时至少4.7us
		CLR	SCL			;/*清时钟线，钳住I2C 总线以便继续接收*/
		NOP
		NOP

		RET

;不产生ACK应答 子程序******************************************************************
MNACK:		
		SETB	SDA			;SDA变为低电平，为应答信号
		NOP
		NOP
		NOP
		SETB	SCL			;产生时钟脉冲
		ACALL	I2C_DELAY		;延时至少4.7us
		CLR	SCL			;/*清时钟线，钳住I2C 总线以便继续接收*/
		NOP
		NOP

		RET

;检查应答信号 子程序*******************************************************************
CACK:		
		SETB	SDA
		NOP
		NOP			
		SETB	SCL			;时钟线置高，进入应答检测
		ACALL	I2C_DELAY		;延时至少4.7us

		CLR	ACK			;清应答标志位
		NOP
		NOP
		MOV	C,SDA
		JC	CEND			;SDA为高电平时为 非应答信号 JC为1跳转
		;JC为1跳转	
		;SDA为低电平
		SETB	ACK			;置应答标志位
CEND:		NOP
		CLR	SCL
		NOP
		NOP

		RET

;IIC空操作延时 >=4.7us(5个机器周期)****************************************************
;算上ACALL I2C_DELAY和RET 不止4.7us
I2C_DELAY:	NOP				;1个时钟周期
		NOP				;1个时钟周期
		NOP				;1个时钟周期
		NOP				;1个时钟周期
		NOP				;1个时钟周期
		
		RET				;2个时钟周期

;发送与接收间隔延时（共753个时钟周期,若晶震为11.058，延时0.817mS）
DELAY:
		MOV	R3,#044H;调试得到延时循环次数	;1
delayLoop:	ACALL	I2C_DELAY		;2个时钟周期
		DJNZ	R3,delayLoop		;2个时钟周期
		RET				;2个时钟周期

	END



;总结：在写完N为数据后准备读取时，接连发送器件地址均不能反映，用类while循环连续发送直到接收到响应信号	

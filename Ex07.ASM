;_AD与DA实验
$INCLUDE(LCMDRV_12864.INC)			;包含库程序定义
;位变量 ****************************************
REFRESHDISP	EQU	08H			;刷新显示标志
;字节变量 **************************************
AD_VAL		EQU	30H			;AD转换结果值
SECOND_CNT	EQU	31H			;秒计数(计20次50ms)
VAR_END		EQU	31H			;最后一个字节变量的位置
;堆栈定义 **************************************
STACK_INI	EQU	VAR_END+1		;须保证足够的空间
;程序 ******************************************
		ORG	0000H			;复位入口
		LJMP	RESET
		ORG	0003H			;外部中断0 服务程序入口
		RETI
		ORG	000BH			;定时器/计数器0 溢出中断服务程序入口 计数器
		RETI
		ORG	0013H			;外部中断1 服务程序入口
		LJMP	INT_EX1
		ORG	001BH			;定时器/计数器1 溢出中断服务程序入口 定时器50ms
		LJMP	INT_T1
		ORG	0023H			;串行口中断服务程序入口
		RETI
		ORG	0040H			;复位处理程序
RESET:		MOV	SP,#STACK_INI		;设置栈底指针
;初始化外部设备 ********************************
		MOV	R7,#00H			;初始化显示器(不显示光标)
		LCALL	_LCM_Init
;中断设置 **************************************
;此处添加设置中断指令(ET1, PT1, IT1, EX1, PX1)
;50ms定时器 T1
		SETB	ET1			;外部中断允许控制	0=屏蔽	1=允许
		SETB	PT1			;中断优先级级别控制	0=低级	1=高级
;外部中断 INT1
		SETB	IT1			;外部中断触发方式控制	0=电平	1=边沿（下降沿）
		SETB	EX1			;外部中断允许控制	0=屏蔽	1=允许
		CLR	PX1			;中断优先级级别控制	0=低级	1=高级
;定时/计数设置 *********************************
;此处添加设置定时/计数器的指令(TMOD, TH1, TL1)
		MOV	TMOD,#10H
		MOV	DPTR,#65536-50000	;50ms = (2^16-计数初值)*定时周期
		MOV	TH1,DPH
		MOV	TL1,DPL
;初始化变量 ************************************
		CLR	REFRESHDISP		;清刷新显示标志
		MOV	SECOND_CNT,#20
;启动内部定时 **********************************
		SETB	TR1			;启动定时器1
;开中断 ****************************************
		SETB	EA
;主程序 ****************************************
MAIN:		JNB	REFRESHDISP,$		;判断是否需要刷新显示,为0死循环，等待中断
		CLR	REFRESHDISP		;清刷新显示标志
		MOV	R7,#01H			;从第2行第2列开始显示转换值(5位数值)
		MOV	R5,#01H
		;显示的采样值 AD_VAL
		MOV	R2,#00H			;转换值扩展成16位(高位为00H)
		MOV	R3,AD_VAL		;低位为采集的ADC值--8位,显示最大值为255		
		CALL	_LCM_DispUIntXY
		SJMP	MAIN
;A/D转换结束中断服务程序 **********************
INT_EX1:
		MOV	DPTR,#3C00H
		MOVX	A,@DPTR
		MOV	AD_VAL,A		;保存转换结果(供主程序显示用)
		;此处添加启动D/A转换的指令	DAC0832		3800H
		MOV	DPTR,#3800H
		MOVX	@DPTR,A	
		SETB	REFRESHDISP		;设置刷新显示标志 (刷新显示由主程序完成)

		RETI
;内部定时中断服务程序 **************************
INT_T1:
		;此处添加重置定时常数的指令
		MOV	DPTR,#65536-50000	;20ms重置
		MOV	TH1,DPH
		MOV	TL1,DPL	
		;此处添加判断一秒钟时间到的指令, 如果没到时间则跳转恢复现场
		DJNZ	SECOND_CNT,ExitInt_T1
		;到1s,执行下面的指令。
		MOV	SECOND_CNT,#20		;置秒计数初值
		;此处添加启动A/D转换的指令	ADC0809 3C00H~3C07H（IN0 ~ IN7）
		MOV	DPTR,#3C00H		;通道0
		MOVX	@DPTR,A			;启动A/D ADC0809
ExitInt_T1:
		RETI
;程序结束 **************************************		
		END


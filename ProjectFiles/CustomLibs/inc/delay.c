// void Setup_TIM3() 
// {
// 	RST_CLK_PCLKcmd((RST_CLK_PCLK_TIMER3), ENABLE);
// 	TIMER_DeInit(MDR_TIMER3);
// 	TIMER_BRGInit(MDR_TIMER3, TIMER_HCLKdiv1);

// 	// �������� ��������� ��� TIM2
// 	TIMER_CntStructInit(&Cnt_sTim3);
// 	Cnt_sTim3.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;			// ���� ��� ����������� ��������� �����
// 	Cnt_sTim3.TIMER_CounterDirection = TIMER_CntDir_Up;					// ���� � ������� ����������
// 	// Cnt_sTim2.TIMER_EventSource = TIMER_EvSrc_TM2; 					// ������� �� ���������� TIM2 �������� ARR
// 	Cnt_sTim3.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_4;		// ��������������� ������� ��� ������� � 4 ���� ������ ��������
// 	Cnt_sTim3.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;		// ��������� ARR ������� �� ������������
// 	Cnt_sTim3.TIMER_IniCounter = 0;										// ����������������� �������� �������
// 	Cnt_sTim3.TIMER_Period = PERIOD_T3 - 1;								// �������� ARR
// 	Cnt_sTim3.TIMER_Prescaler = PRESCALER_T3;							// ������ ��������� ������� �� 1000, �.�. ����� 16 ���           7
	
// 	TIMER_CntInit(MDR_TIMER3, &Cnt_sTim3);
// 	NVIC_EnableIRQ(Timer3_IRQn);
// 	TIMER_DMACmd(MDR_TIMER3, TIMER_STATUS_CNT_ARR, ENABLE);
	
// 	// �������� ������
// 	TIMER_Cmd(MDR_TIMER3, ENABLE);
// }
// задержка на count тактов 

#include "defines.h"
#include "MDR32F9Qx_rst_clk.h"

void delay_tick(uint32_t count)	// Ждать count тактов процессора
{	
	while (count--) 
	{									// декремент счетчика	
		__NOP();				// Не делать ничего
	}
}

void delay_ms(uint32_t delay)
{
	delay_tick(delay * (HSE_FREQ /1000));
}

void delay_us(uint32_t delay)
{
	delay_tick(delay * (HSE_FREQ /1000000));
}
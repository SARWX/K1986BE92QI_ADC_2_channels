#include "MDR32F9Qx_ssp.h"
#include "MDR32F9Qx_port.h"
#include "MDR32Fx.h"

void Setup_SPI(void)
{
	PORT_InitTypeDef* Port_sruct;

	// POT B - ������������� RESET � DC
	PORT_StructInit(Port_sruct);
	Port_sruct->PORT_Pin       = (PORT_Pin_6 | PORT_Pin_7); // PB6 = DC, PB7 = RESET
	Port_sruct->PORT_OE        = PORT_OE_OUT;
	Port_sruct->PORT_SPEED     = PORT_SPEED_MAXFAST;
	Port_sruct->PORT_MODE      = PORT_MODE_DIGITAL;         // ???
	PORT_Init(MDR_PORTB, Port_sruct);

	// PORT F - ������������� CS, MOSI, SCK
	Port_sruct->PORT_Pin       = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2);                // PF2 = CS
	PORT_Init(MDR_PORTF, Port_sruct);
	// ������������� MISO	Port_sruct->PORT_Pin       = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2);                // PF2 = CS
	Port_sruct->PORT_Pin       = (PORT_Pin_3);                // PF2 = CS
	Port_sruct->PORT_OE        = PORT_OE_IN;
	PORT_Init(MDR_PORTF, Port_sruct);

	// ������������� SPI
	SSP_InitTypeDef* SSP1_struct;
	SSP_StructInit(SSP1_struct);    // �������������� ������������ ����������
	SSP_Init((MDR_SSP_TypeDef*)MDR_SSP1, SSP1_struct);
	SSP_Cmd(MDR_SSP1, ENABLE);

	// uint16_t data = 0;
	// SSP_SendData(MDR_SSP1, data);
};
#ifndef DMA_for_porj
#define DMA_for_porj
// Структуры для DMA
extern DMA_CtrlDataInitTypeDef sDMA_PriCtrlData_ADC1;				// Основная структура канала для ADC1
extern DMA_CtrlDataInitTypeDef sDMA_AltCtrlData_ADC1;				// Альтернативная структура канала для ADC1
void SetupDMA();

#endif /* DMA_for_porj */
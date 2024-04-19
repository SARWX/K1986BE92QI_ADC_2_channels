/* Макроподстановки --------------------------------------------------------------*/
#define BUFFER_LENGTH 128				// 128
#define timeout 10
#define LED_Pin PORT_Pin_2
#define LED_Port MDR_PORTC
#define SIN_RES 500 					// Разрешение синусоиды (точек на период)
#define SIN_AMPLITUDE 2000				// должно быть меньше < 4096 / 2
#define SIN_MEDIUM_LINE 2000			// Средняя линия для синусоиды на ЦАП
#define MAX_ADC_VAL 4095				// Максимальное значение 12 битного АЦП
#define AIRCR_SETTING 0x5FA0500			// Настройка для регистра AIRCR
#define VECTOR_TABLE_OFFSET 0x08000000	// Смещение таблицы векторов (см. спецификацию)
#define WHOLE_WORD 0xFFFFFFFF			// Константа отображающая 32 битное слово
#define PERIOD_T2 30					// Определяет период работы ЦАП
#define PRESCALER_T2 30					// Определяет воо сколько раз будет делиться системная частота для ЦАП
#define HSE_FREQ 16000000
#define CPU_PLL 8
#define CPU_DIV 1
#define DISCRET_FREQ ((HSE_FREQ * CPU_PLL / CPU_DIV) / (PRESCALER_T2 * PERIOD_T2))	// определяет частоту дискретизации ЦАП 
#define CORRECTION_FACTOR 1.065			// поправочный коэфициент для задания точной частоты

#define NUM_OF_MES 128	
// Этот параметр задает количество измерений АЦП, которые будут составлять 1 пакет.
								// Но контроллером USB они будут поделены на пакеты по 64 байта, поскольку 1 измерение АЦП кодируется 2 байтами,
								// то количество измерений целесообразно выбирать кратным 32 (для достижения максимальной скорости)

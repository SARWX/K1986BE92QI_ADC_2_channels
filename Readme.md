# Использование АЦП на микроконтроллере К1986ВЕ92QI
В данном проекте, производится настройка АЦП и одновременная оцифровка с его помощью двух синусоидальных сигналов с разной частотой. \
Для запуска кода и повторения данного примера, вам потребуется:
- Отладочная плата, [(например одна из этих)](https://ldm-systems.ru/catalog/milandr?cat=k1986be92qi&scat=op) с микроконтроллером [К1986ВЕ92QI](https://ic.milandr.ru/products/mikrokontrollery_i_protsessory/32_razryadnye_mikrokontrollery/k1986ve92qi/?ysclid=lqmbaqu6ql771500733)
- На отладочной плате должен быть выведен контакт, на который можно назначить вход АЦП
- Генератор сигналов на частоте от 0 до 10 кГц, в данном проекте использовался [ADALM 2000](https://wiki.analog.com/university/tools/m2k)
- Программатор [ST-Link V2](https://www.st.com/en/development-tools/st-link-v2.html) для отладки и загрузки прошивки
- [GNU Radio](https://www.gnuradio.org/), например в сборке [Radioconda](https://github.com/ryanvolz/radioconda), которая проста в установке и включает в себя некоторые распространённые дополнения
- [Keil uVision IDE](https://www.keil.com/download/) для загрузки прошивки в микроконтроллер. Пакеты расширения и руководство по первичной настройке можно найти [здесь](https://support.milandr.ru/products/mikroskhemy_v_plastikovykh_korpusakh/k1986ve92qi/) 

Основной функционал, реализованный в этом проекте, вынесен в отдельные библиотеки, с припиской "for_proj". Там можно найти файлы для работы с ЦАПом, но этот функционал находится в разработке. \
В данном проекте используется DMA для уменьшения нагрузки на ядро. Таким образом, данные с АЦП записываются непосредственно в память, откуда затем выполняется их передача через интерфейс USB. \
Для работы с DMA используется режим "пинг-понг". \
Несмотря на наличие двух отдельных блоков АЦП, в этом проекте использован один АЦП с поочерёдной оцифровкой каналов. 
```C
// 1 стадия - заполнение буфера, с использованием основной структуры DMA, параллельная передача буфера альтернативной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) == 0) ;					// ждем, когда DMA перейдет на альтернативную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_PRIMARY, &ADC1_primary_DMA_structure);		// реинициализируем основную структуру
		USB_CDC_SendData((uint8_t *)(main_array_for_ADC), ((NUM_OF_MES) * 2 ));					// отправка буфера основной структуры DMA по USB

		// 2 стадия - заполнение буфера, с использованием альтернативной структуры DMA, параллельная передача буфера основной по USB
		while (DMA_GetFlagStatus(DMA_Channel_ADC1, DMA_FLAG_CHNL_ALT) != 0) ;					// ждем, когда DMA перейдет на основную структуру
		DMA_CtrlInit(DMA_Channel_ADC1, DMA_CTRL_DATA_ALTERNATE, &ADC1_alternate_DMA_structure);	// реинициализируем альтернативную структуру
		USB_CDC_SendData((uint8_t *)(alternate_array_for_ADC), ((NUM_OF_MES) * 2 ));			// отправка буфера альтернативной структуры DMA по USB
```
В используемой микросхеме реализован интерфейс USB 2.0 Full Speed, который позволяет установить максимальную скорость передачи, равную 12 Мбит/сек. В отличие от преобразователя USB - UART, использованного в другом проекте, для данной микросхемы не требуется устанавливать символьную скорость. \
Измерения от АЦП передаются по "пакетам", по 64 байта, так как таким образом их делит контроллер USB. Следовательно, количество измерений имеет смысл делать кратным 32, чтобы полностью реализовывать потенциал USB интерфейса и не передавать наполовину пустые посылки через USB. \
Используются контакты PD0 и PD1 для ввода данных с АЦП. В виду особенностей отладочной платы, те же разъёмы используются для загрузки прошивки. \
Использовался опорный кварцевый генератор с частотой 16 МГц. \
АЦП такируется от процессора с изменяемым коэффициентом деления тактовой частоты. С этим коэффициентом можно экспериментировать. Все приведённые на скриншотах результаты относятся к коэффициенту деления равному 32. При коэффициенте 16 и меньше, оцифровка может работать нестабильно.
```C
// Настройка АЦП
    ADC_DeInit();							// Сбросить все прежние настройки АЦП
    ADC_StructInit(&sADC);						// Проинициализировать структуру стандартными значениями
		ADC_Init (&sADC);					// Применить конфигурацию, занесенную в sADC
    ADCx_StructInit (&sADCx);						// Проинициализировать структуру для отдельного канала стандартными значениями
    sADCx.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;			// Источник тактирования - ЦПУ (т.е. от HSE)
    sADCx.ADC_SamplingMode     = ADC_SAMPLING_MODE_CYCLIC_CONV;		// Режим работы (циклические преобразования, а не одиночное)
    sADCx.ADC_ChannelSwitching = ADC_CH_SWITCHING_Enable;		// Переключение каналов разрешено, АЦП 1 будет вссегда работать на PD0,// PD1
    sADCx.ADC_ChannelNumber    = ADC_CH_ADC0;				// Указываем канал АЦП 1 (ADC0 = АЦП 1, т.к. у Миландр он то первый, то нулевой)
    sADCx.ADC_Channels         = (ADC_CH_ADC0_MSK | ADC_CH_ADC1_MSK);	// Маска для каналов 0 и 1 (АЦП 1 будет оцифровывать их поочередно)
    sADCx.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;		// Опорное напряжение от внутреннего источника
    sADCx.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;		// Выбираем неточный источник опорного напряжения
    sADCx.ADC_Prescaler        = ADC_CLK_div_32;			// Задаем скорость работы АЦП, ИМЕННО ЭТОЙ НАСТРОЙКОЙ ЗАДАЕТСЯ СКОРОСТЬ РАБОТЫ УСТРОЙСТВА
		sADCx.ADC_DelayGo          = 0x2;			// Отложенный запуск, необходиим для нормальной работы
```

В GNU Radio получение оцифрованных данных происходит при помощи побайтового чтения данных из виртуального Serial порта. Далее, поочерёдно происходит запись либо в первый выходной порт, либо во второй, так как, каналы оцифровываются по очереди. 

``` python
n = 0
            
while(n < len(outputItems[0])) :
    data = int.from_bytes(self.port.read(2), "little")
    outputItems[1][n] = data
    
    data = int.from_bytes(self.port.read(2), "little")
    outputItems[2][n] = data
    n += 1
```

Для демонстрации работы, можно собрать простую схему в GNU Radio, состоящую из блока "Embedded Python Block" и блока "Time Sink". 

<p align="center">
  <img width="" height="" src="/Imgs/simpleGraph.png">
</p>

На картинке ниже показана оцифровка двух синусоидальных сигналов с частотами 1кГц и 500 Гц по разным каналам.

<p align="center">
  <img width="" height="" src="/Imgs/1k+500HzRead.png">
</p>

Тоже оцифровка, но сигналы с частотой 5кГц и 1кГц.

<p align="center">
  <img width="" height="" src="/Imgs/5k+1kHzRead.png">
</p>

## Вывод по работе АЦП
На данный момент, по субъективному мнению, неплохо оцифровываются сигналы с частотой до 5кГц. Поскольку, основная ориентация данной разработки - оцифровка модулированных сигналов на низкой или нулевой промежуточной частоте, то с этой задачей она должна справиться, при использовании низкой частоты самого информационного сигнала. \

## Использование ЦАПа
В проекте реализована работа блока ЦАП микроконтроллера. Его работу можно описать так: в памяти микроконтроллера составляется массив ```DAC_table[SIN_RES]``` со значениями которые будут с определенной частотой записываться в ЦАП константа _SIN_RES_ определяет размер массива. \
Частота дискретизации ЦАП в проекте ограничивается 400 кГц. \
Реализована небольшая система команд (для отправки команд, используйте любимую программу для мониторинга последовательного порта с возможностью записи в него данных): 
1. Команда _set freq X_ \
вместо X подставляется частота в герцах. Команда генерирует синусоиду заданной частоты. С понижением генерируемой частоты, частота обновления напряжения ЦАП тоже понижается. \
пример:
```
set freq 1000
set freq 500
set freq 100
```
<p align="center">
  <img width="" height="" src="/Imgs/1000_500_100_HZ.jpg">        <!-- Сравнение разных частот -->
</p>

2. Команда _set X.XX X.XX ... X.XX !_ \
предназначена для задания ```DAC_table[]``` вручную. Обратите внимание, что в текущей версии прошивки, все числа для этой команды должны быть приведены к двум знакам после запятой, даже ноль. 

> [!CAUTION]
> В одной транзакции может быть максимум 64 байта, поэтому если передать 100 байт, то микроконтроллер не успеет обработать первые 64 байта, в то время как ему уже придут новые, в таком случае, предыдущие символы будут отброшены.

За 1 раз отпралять нужно не более 64 символов, между отправками делать перерыв хотя бы в милисекунду
Признаком конца команды _set_ является символ _!_ До его ввода команда исполнена не будет. 
Суммарное количество чисел должно быть меньше **SIN_RES** \
*(на данный момент SIN_RES = 500)*
 
Пример:
```
set 2.9 2.9 2.9 2.9 2.9 1.2 1.2 1.2 1.2 1.2
set 1.8 1.8 1.8 1.8 1.8 3.0 3.0 3.0 3.0 3.0
set 1.1 1.1 1.1 1.1 !
```
> [!TIP]
> Можно предварительно понизить частоту дискретизации командой 'set '
> Это может быть полезно, например, если синал описывается небольшим количеством точек
<p align="center">
  <img width="" height="" src="/Imgs/sobs_1000_500_100_HZ.jpg">        <!-- Сравнение собственного сигнала на разных частотах -->
</p>

Кастомные платы, использованные в тестах. 
<p align="center">
  <img width="" height="" src="/Imgs/miniboards.jpg">
</p>

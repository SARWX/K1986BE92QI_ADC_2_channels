
# Краткое описание проекта

В данном проекте представлен прототип аналогово цифрового интерфейса (**АЦИ**) на микроконтроллере **МИЛАНДР K1986BE92QI**.</br>

> АЦИ - устройство, предназначенное, для обеспечения связи между аналоговыми схемами и персональным компьютером.</br>

В проекте производится настройка АЦП, ЦАП, DMA, USB, SPI. 
Программа нацелена на одновременную оцифровку данных с АЦП и генерацию сигнала для ЦАП.</br>
 
> [!WARNING]
>В программе также имеется режим `dac_mode`, который обеспечивает прямой доступ к ЦАП, через USB.
>*Режим требует доработки*

# Использование программы на микроконтроллере К1986ВЕ92QI

Для запуска кода, вам потребуется:
- Отладочная плата, [(например одна из этих)](https://ldm-systems.ru/catalog/milandr?cat=k1986be92qi&scat=op) с микроконтроллером [К1986ВЕ92QI](https://ic.milandr.ru/products/mikrokontrollery_i_protsessory/32_razryadnye_mikrokontrollery/k1986ve92qi/?ysclid=lqmbaqu6ql771500733)
- На отладочной плате должны быть выведены соответствующие контакты
- Программатор [ST-Link V2](https://www.st.com/en/development-tools/st-link-v2.html) для отладки и загрузки прошивки
- [GNU Radio](https://www.gnuradio.org/), например в сборке [Radioconda](https://github.com/ryanvolz/radioconda), которая проста в установке и включает в себя некоторые распространённые дополнения
- [Keil uVision IDE](https://www.keil.com/download/) для загрузки прошивки в микроконтроллер. Пакеты расширения и руководство по первичной настройке можно найти [здесь](https://support.milandr.ru/products/mikroskhemy_v_plastikovykh_korpusakh/k1986ve92qi/) 

# Пример использования АЦИ

Сам АЦИ просто генерирует последовательность байт - измерений от АЦП, либо считывает последовательность байт, которые передает в ЦАП (*dac_mode*), а также реализует определенную систему команд через USB.</br>

Интегрировать такое устройство можно достаточно легко, поскольку используется USB CDC.
В поставляемых примерах реализована интеграция АЦИ в GNU Radio (*используется pySerial*)</br>

### Пример 1 - осциллограф

Открываем проект  `GNU Radio/examples/Oscilloscope.grc`
![Pasted image 20241226113141](https://github.com/user-attachments/assets/a1a3b5a7-467b-4ba9-9ed2-014ef7eb0888)


Пока сигнала нет, замкнем выход АЦП и ЦАП, закроем GNU Radio,</br>
откроем терминал, напишем команду `set freq 1000`, после закроем терминал.</br>
Теперь если мы запустим проект, то увидим синусоиду с частотой 1000 Гц.</br>
![Pasted image 20241226120244](https://github.com/user-attachments/assets/1c09079a-9260-4aba-80b8-1f378b6f5b4c)


### Пример 2 - генератор треугольного сигнала

Открываем проект  `GNU Radio/examples/Triangle.grc`

Тут все просто, через ползунок в GUI задаем требуемую частоту треугольника, нажимает кнопку `Triangle`, через определенный промежуток времени установится треугольный сигнал, который мы увидим на осциллограмме:
![Pasted image 20241226120758](https://github.com/user-attachments/assets/c2d0669e-43ee-4d44-827a-07a6732c65e6)


### Пример 3 - управление iFSY по SPI
![Pasted image 20241226121255](https://github.com/user-attachments/assets/057dfc32-e92b-4488-81e4-bd91901e7ec5)



Для наглядного рассмотрения этого примера понадобится подключить логический анализатор для просмотра данных передаваемых по SPI.

Коротко в примере происходит следующее:
1) мы задаем параметры в блоке `iFSY driver`
2) запускаем проект
3) нажимаем кнопку `send config`, конфигурация отправляется по SPI

пример служит для демонстрации того, как работать с SPI, в каком виде передавать данные в АЦИ, чтобы он отправил их по SPI.

### Пример 4 - модуляция / демодуляция : QPSK / QAM16

Это достаточно большой пример, его подробное объяснение приведено в прилагаемой инструкции по работе.
![Pasted image 20241226121825](https://github.com/user-attachments/assets/9e7062a9-5dff-4048-bd17-437a84e0b099)

Пример также может послужить примером для разработки своих проектов.

# Система команд

Для отправки команд, используйте любимую программу для мониторинга последовательного порта с возможностью записи в него данных, например [такая](https://sourceforge.net/projects/serial-port-terminal/files/).

В файле `command_sys_flex.c` вы можете ознакомиться с реализацией всех команд, а также легко добавить свои (*в аналогичном стиле*).

Вот список команд, с кратким пояснением:

### Команда `set freq X`

вместо X подставляется частота в герцах. Команда генерирует синусоиду заданной частоты. С понижением генерируемой частоты, частота обновления напряжения ЦАП тоже понижается. \
пример:
``` bash
set freq 1000
set freq 500
set freq 100
```
<p align="center">
  <img width="" height="" src="/Imgs/1000_500_100_HZ.jpg">        <!-- Сравнение разных частот -->
</p>
### Команда `set X.XX X.XX ... X.XX !`

предназначена для задания ```DAC_table[]``` вручную. Обратите внимание, что в текущей версии прошивки, все числа для этой команды должны быть приведены к двум знакам после запятой, даже ноль. 
> [!CAUTION]
> В одной транзакции может быть максимум 64 байта, поэтому если передать 100 байт, то микроконтроллер не успеет обработать первые 64 байта, в то время как ему уже придут новые, в таком случае, предыдущие символы будут отброшены.
За 1 раз отпралять нужно не более 64 символов, между отправками делать перерыв хотя бы в милисекунду
Признаком конца команды _set_ является символ _!_ До его ввода команда исполнена не будет. 
Суммарное количество чисел должно быть меньше **SIN_RES** \
*(на данный момент SIN_RES = 500)*
 
Пример:
``` bash
set 2.9 2.9 2.9 2.9 2.9 1.2 1.2 1.2 1.2 1.2
set 1.8 1.8 1.8 1.8 1.8 3.0 3.0 3.0 3.0 3.0
set 1.1 1.1 1.1 1.1 !
```

### Команда `mode`

устанавливает режим работы АЦИ.
Предусмотрены следующие режимы:

``` C
enum mode_setting
{                       //  1 - оба, 0 - один канал     АЦП|ЦАП
  adc1_dac1   = 0,      // 1ый канал АЦП, 1ый канал ЦАП   0 0
  adc1_dac12  = 1,      // 1ый канал АЦП, 2 канала ЦАП    0 1
  adc12_dac1  = 2,      // 2 канала АЦП, 1ый канала ЦАП   1 0
  adc12_dac12 = 3,      // 2 канала АЦП, 2 канала ЦАП     1 1
  dac_mode_s = 1000,    // Режим потоковой передачи в DAC, АЦП отключен
};
```

Задавать надо именно число.
Пример:
``` bash
mode 3
```

### Команда `clock ADC `

Эта команда устанавливает частоту дискретизации для АЦП.
Команда задает частоту для одного канала, если канала 2, то для каждого будет установлена соответствующая частота</br>

Команда установит только допустимую частоту. Список допустимых частот:
```
500000 - только для одноканального режима
250000
125000
...
```

Неверная частота не окажет влияния на устройство
Пример:
``` bash 
# установит частоту
clock ADC 250000

# допущена ошибка
clock ADC 100000
```

### Команда `clock DAC `

Эта команда устанавливает частоту дискретизации для ЦАП.
Команда задает частоту для одного канала, если канала 2, то для каждого будет установлена соответствующая частота.</br>

Команда установит ближайшую возможную частоту.
 Максимальная частота
 * 1000000 для одноканального режима
 * 500000 для двух каналов

Пример:
``` bash 
# установит частоту максимально близкую к 100 000
clock DAC 100000
```

### Команда `spi1_send `

Эта команда просто отправит данные через spi

После команды данные надо указывать в виде байт для передачи (*т.е. ровно те байты, которые будут указаны после `spi1_send ` будут отправлены по SPI*)

Пример:
``` bash
# Отправит последовательность байт: 
#  h   e   l   l   o
# 104 101 108 108 111
spi1_send hello
```

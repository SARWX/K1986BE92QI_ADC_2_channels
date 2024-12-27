"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import serial
import serial.tools.list_ports
import time

import numpy as np
from gnuradio import gr
import pmt

MAX_DAC_NUM = 500   # Максимальное количество чисел, которое может быть записано в const_signal
MAX_DAC_VAL = 10.0  # Максимальное значение на выходе ЦАП
CHUNK_SIZE = 10     # Максимальное количество чисел в одной команде
USB_PACKET_SIZE = 32 # байт

class ADIBlock(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block
    """
    Read data from serial port and forward it to output. 
    portNumber is number, you can see in the name of your 
    serial port in device manager, like COM16 or COM7 
    DAC_freq and ADC_freq are specified for 1 channel
    """

    
    def __init__(self, portNumber=7, mode = 3, adc_freq = 250000, dac_freq = 500000): 
        """arguments to this function show up as parameters in GRC"""
        self.portNumber = portNumber  # Сохраняем номер порта       
        gr.sync_block.__init__(
            self,
            name = 'Analog Digital Interface',   
            in_sig = [np.uint8, np.uint8],  # Входы
            out_sig = [np.uint8, np.uint8]  # Выходы
        )

        # Регистрация именованных входных и выходных портов
        self.message_port_register_in(pmt.intern('set_const_signal'))
        self.message_port_register_in(pmt.intern('spi'))
        self.set_msg_handler(pmt.intern('set_const_signal'), self.handle_set_const_signal)
        self.set_msg_handler(pmt.intern('spi'), self.handle_spi)
        # self.message_port_register_out(pmt.intern('msg_out'))
        self.set_min_output_buffer(2**13)        # 512 - минимальный размер
        self.set_max_output_buffer(2**13)  # Установка максимального размера буфера
        self.set_output_multiple(2**13)     # Установка шага данных
        # Инициализация переменных для COM порта
        self.port = None
        self.port_name = None
        self.baudrate = 2000000  # Здесь захардкожен baudrate
        self.adc_freq = adc_freq  
        self.dac_freq = dac_freq
        self.mode = mode
        self.remaining_data = bytearray(USB_PACKET_SIZE + 1)  # Буфер для оставшихся данных     0ой байт - флаг (0 - в массиве нет полезных данных, 1 - надо читать)
        self.spi_len = 0
        

    def open_port(self):
        """Открывает COM порт, если он существует и не занят."""
        baudrate = 2000000
        portName = 'COM' + str(self.portNumber)
        # Получаем список доступных COM портов
        available_ports = [port.device for port in serial.tools.list_ports.comports()]
        if portName not in available_ports:
            print(f"Ошибка: Порт {portName} не найден.")
            return
        try:
            # Пытаемся открыть порт
            self.port = serial.Serial(portName, baudrate, timeout=3.0)
            # Если порт уже был открыт, закрываем его и открываем заново
            if self.port.is_open:
                self.port.close()
                self.port.open()
            else:
                self.port.open()
            print(f"Порт {portName} успешно открыт.")
        except serial.SerialException as e:
            # Если не удалось открыть порт (например, он занят), выводим сообщение об ошибке
            print(f"Ошибка при открытии порта {portName}: {e}")
            self.port = None


    def set_mode(self, mode_setting):
        if mode_setting < 4:
            command = "mode " + str(mode_setting)  
        else:
            command = "dac_mode"
        try:
            self.port.write(command.encode('ascii'))
            print(f"Отправлено: {command}")
            time.sleep(0.01)
        except serial.SerialException as e:
            print(f"Ошибка при отправке данных: {e}")

    def set_clock(self, dac_or_adc, adc_freq):
    # dac_or_adc = DAC      dac_or_adc = ADC
        command = "clock " + dac_or_adc + str(adc_freq)  
        try:
            self.port.write(command.encode('ascii'))
            print(f"Отправлено: {command}")
            time.sleep(0.01)
        except serial.SerialException as e:
            print(f"Ошибка при отправке данных: {e}")


    def handle_spi(self, msg):
        if self.spi_len == 0:
            self.spi_len = pmt.to_python(msg)
            print(self.spi_len)
            print("SPI LEN IS SET")
            return
            
        spi_value = pmt.to_python(msg)        # Преобразование в int
        # Проверка
        print(spi_value)
        # Формирование ASCII строки
        # ascii_string = "spi1_send ".encode('ascii') + chr(self.spi_len) + ' ' + spi_value.to_bytes(6, 'big')
        ascii_string = (
            b"spi1_send "  # Прямо задаем байтовую строку
            + bytes([self.spi_len])  # Преобразуем spi_len в байты (один байт)
            + b' '  # Пробел
            + spi_value.to_bytes(self.spi_len, byteorder='big')  # Преобразуем spi_value в 6 байтов в big-endian
        )
        # Открытие порта, если еще не открыт
        if self.port is None:
            self.open_port()
        if self.port is not None and self.port.is_open:
            try:
                self.port.write(ascii_string)
                print(f"Отправлено spi1_send " + str(self.spi_len) + " " + str(spi_value))
                time.sleep(0.01)
            except serial.SerialException as e:
                print(f"Ошибка при отправке данных: {e}")
                
        print("SPI LEN IS RESET")
        self.spi_len = 0
        


    def handle_set_const_signal(self, msg):
        """Обработка входных сообщений."""
        # Преобразование сообщения в список чисел с плавающей запятой
        numbers = pmt.to_python(msg)        # Преобразование в строку
        numbers = [float(x) for x in numbers.split()]
        print("Обработка сообщения")
        if len(numbers) > MAX_DAC_NUM:
            print(f"Ошибка: Слишком много чисел. Максимум {MAX_DAC_NUM}.")
            return
        if any(val > MAX_DAC_VAL for val in numbers):
            print(f"Ошибка: Значения не могут превышать {MAX_DAC_VAL}.")
            return
        # Открытие порта, если еще не открыт
        if self.port is None:
            self.open_port()
        if self.port is not None and self.port.is_open:
            # Разделение данных на куски по 10 чисел и отправка
            for i in range(0, len(numbers), CHUNK_SIZE):
                chunk = numbers[i:i + CHUNK_SIZE]
                command = "set " + " ".join(map(str, chunk))
                if i + CHUNK_SIZE >= len(numbers):
                    command += " !"
                try:
                    self.port.write(command.encode('ascii'))
                    print(f"Отправлено: {command}")
                    time.sleep(0.01)
                except serial.SerialException as e:
                    print(f"Ошибка при отправке данных: {e}")

            
    def work(self, input_items, output_items):

        if self.port is None:
            # Если порт не открыт, попытаться открыть его
            self.open_port()
            if self.adc_freq > 0:
                self.set_clock("ADC ", self.adc_freq)
            if self.dac_freq > 0:
                self.set_clock("DAC ", self.dac_freq)
            self.set_mode(self.mode)

        # Случай обычной работы (Упор на АЦП)
        if self.mode < 4:
            n = 0
            chunk_size = USB_PACKET_SIZE
            output_len = len(output_items[0])
            data = bytearray(chunk_size)  # Создание массива байтов для чтения данных
            n_increment = (USB_PACKET_SIZE if self.mode < 3 else (USB_PACKET_SIZE // 2))

            while n < (output_len - n_increment):
                chunk_size = USB_PACKET_SIZE
            
                # Объединяем остаточные данные из предыдущей итерации с новыми
                if self.remaining_data[0] == 1:

                    # data = bytearray(chunk_size)  # Создание массива байтов для чтения данных
                    chunk_size = len(self.remaining_data) - 1
                    data = bytearray(chunk_size)
                    data = self.remaining_data[1:]       # Сохранить данные 
                    # print("DDDDDDDDDDDDDDDDD")
                    self.remaining_data = bytearray(USB_PACKET_SIZE + 1)  # Очищаем буфер
                else:
                    data = bytearray(chunk_size)  # Создание массива байтов для чтения данных
                    self.port.readinto(data)  # Считывание данных непосредственно в массив байтов

                if self.mode < 2:  # mode can be 0 or 1, оба включают только 1 канал АЦП
                    output_items[0][n:n + chunk_size] = data[:chunk_size]
                    n += chunk_size
                else:
                    # TEST 8 bit
                    output_items[0][n:n + chunk_size // 2] = data[0::2]
                    output_items[1][n:n + chunk_size // 2] = data[1::2]
                    n += chunk_size // 2

            # Обработка оставшегося места в output_items
            if n < output_len:
                self.port.readinto(data)  # Считываем данные в массив байтов
                if self.mode < 2:  # mode can be 0 или 1, оба включают только 1 канал АЦП
                    # bytes_to_copy = min(chunk_size, output_len - n)
                    # output_items[0][n:n + bytes_to_copy] = data[:bytes_to_copy]
                    # n += bytes_to_copy
                    # print("EEEEEEEEEEEEEEEEEEEEEEEE")
                    # self.remaining_data = data[bytes_to_copy:]  # Сохраняем оставшиеся данные




                    i = 0
                    while n < output_len and i < chunk_size:
                        output_items[0][n] = data[i] 
                        n += 1
                        i += 1
                    # print("AAAAAAAAAAAAAA")
                    self.remaining_data = bytearray(USB_PACKET_SIZE - i + 1)
                    self.remaining_data[1:] = data[i:]  # Сохраняем оставшиеся данные
                    self.remaining_data[0] = (0 if (USB_PACKET_SIZE - i) == 0 else 1)  # Флаг запроса чтения
                else:
                    i = 0
                    while n < output_len and i < chunk_size:
                        output_items[0][n] = data[i] 
                        output_items[1][n] = data[i + 1]
                        n += 1
                        i += 2
                    # print("AAAAAAAAAAAAAA")
                    self.remaining_data = bytearray(USB_PACKET_SIZE - i + 1)
                    self.remaining_data[1:] = data[i:]  # Сохраняем оставшиеся данные
                    self.remaining_data[0] = (0 if (USB_PACKET_SIZE - i) == 0 else 1)  # Флаг запроса чтения

            return len(output_items[0])  # Возвращаем количество обработанных элементов

        # Случай, когда mode >= 4 (dac_mode) - упор на ЦАП, АЦП отключен
        else:
            data = bytearray(USB_PACKET_SIZE )  # Создание массива байтов для чтения данных
            n = 0
            remaining_len = 0
            input_len = min(len(input_items[0]), len(input_items[1]))  # Используем минимальную длину для избежания выхода за границы

            # Если есть remaining_data, объединяем его с текущими данными
            if self.remaining_data:
                remaining_len = len(self.remaining_data)
                # Увеличиваем размер буфера, добавляя длину remaining_data
                data = self.remaining_data + data[:USB_PACKET_SIZE  - remaining_len]  # Ограничиваем data по размеру
                # print("BBBBBBBBBBBBBBBBBB")
                self.remaining_data = bytearray()  # Очищаем буфер после объединения

            while n < input_len:
                i = remaining_len  # Сбрасываем индекс для data
                while i < (USB_PACKET_SIZE ) and n < input_len:  # Проверяем и n
                    value1 = int((input_items[0][n]) * 4000) & 0xFFF  # Приведение к целому числу и ограничение до 16 бит
                    data[i] = value1 & 0xFF  # Младший байт
                    data[i + 1] = (value1 >> 8) & 0xFF  # Старший байт
                    i += 2
                    value2 = int((input_items[1][n]) * 4000) & 0xFFF  # Приведение к целому числу и ограничение до 16 бит
                    data[i] = value2 & 0xFF  # Младший байт
                    data[i + 1] = (value2 >> 8) & 0xFF  # Старший байт
                    i += 2
                    n += 1
                # Отправляем собранные данные в порт
                self.port.write(data)  # Отправляем только заполненную часть
                remaining_len = 0
                data = bytearray(USB_PACKET_SIZE )
            # Обработка оставшихся данных
            if n < input_len:
                # print("CCCCCCCCCCCCCCCC")
                remaining_data = bytearray()
                while n < input_len and i < USB_PACKET_SIZE :
                    value1 = int((input_items[0][n]) * 4000) & 0xFFF
                    remaining_data.append(value1 & 0xFF)
                    remaining_data.append((value1 >> 8) & 0xFF)
                    i += 2
                    value2 = int((input_items[1][n]) * 4000) & 0xFFF
                    remaining_data.append(value2 & 0xFF)
                    remaining_data.append((value2 >> 8) & 0xFF)
                    i += 2
                    n += 1
                # Сохраняем остаточные данные для следующего вызова
                # print("FFFFFFFFFFFFFFFFFF")
                self.remaining_data = remaining_data

            return len(input_items[0])

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


class ADIBlock(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block
    """
    Read data from serial port and forward it to output. 
    portNumber is number, you can see in the name of your 
    serial port in device manager, like COM16 or COM7 
    """

    adc_num = 1
    
    def __init__(self, portNumber=7, enable = 0): 
        """arguments to this function show up as parameters in GRC"""
        self.portNumber = portNumber  # Сохраняем номер порта
        # portName = 'COM' + str(portNumber)                  # Concatenate string and number
        
        gr.sync_block.__init__(
            self,
            name = 'Analog Digital Interface',   
            # in_sig = [np.float32],                          # Входы
            in_sig = [],                          # Входы
            out_sig = [np.float32, np.float32]  # Выходы
        )

        # Регистрация именованных входных и выходных портов
        self.message_port_register_in(pmt.intern('set_const_signal'))
        self.set_msg_handler(pmt.intern('set_const_signal'), self.handle_msg)
        # self.message_port_register_out(pmt.intern('msg_out'))

         # Инициализация переменных для COM порта
        self.port = None
        self.port_name = None
        self.baudrate = 2000000  # Здесь захардкожен baudrate
        self.enable = enable
        
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



    def handle_msg(self, msg):
        """Обработка входных сообщений."""
        # Преобразование сообщения в список чисел с плавающей запятой
        numbers = pmt.to_python(msg)        # Преобразование в строку
        numbers = [float(x) for x in numbers.split()]
        print("AAAAAAAAAAAAAAAAAAAAAA")
        print(numbers[30])

        # if not isinstance(numbers, list):
        #     print("Ошибка: Ожидался список чисел.")
        #     return

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

        n = 0
        while n < len(output_items[0]):
            # WORKING FOR 16 bit
            # data = bytearray(4)  # Creating an array of bytes to read 2 16-bit values (4 bytes)
            # self.port.readinto(data)  # We read the data directly into the byte array
            # output_items[1][n] = int.from_bytes(data[:2], 'little')  # Convert the first 2 bytes to a number
            # output_items[2][n] = int.from_bytes(data[2:], 'little')  # Convert the remaining 2 bytes to a number
            # # output_items[1][n] = int.from_bytes(self.port.read(1), "little")
            # n += 1


            # # TEST 12 bit
            # data = bytearray(3)  # Creating an array of bytes to read 2 16-bit values (4 bytes)
            # self.port.readinto(data)  # We read the data directly into the byte array
            # output_items[1][n] = (data[0] + (data[1] & 0x0F)*16)  # Convert the first 2 bytes to a number
            # output_items[2][n] = (((data[1] & 0xF0) / 8) + (data[2] * 8))  # Convert the first 2 bytes to a number
            # n += 1

            # TEST 8 bit
            data = bytearray(4)  # Creating an array of bytes to read 2 16-bit values (4 bytes)
            self.port.readinto(data)  # We read the data directly into the byte array
            output_items[0][n] = data[0]
            output_items[1][n] = data[1]
            n += 1
            output_items[0][n] = data[2]
            output_items[1][n] = data[3]
            n += 1
            # if self.enable == 1:
            #     print(self.enable)
            
        return len(output_items[1])
"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import numpy as np
from gnuradio import gr
# import enum
import time


class blk(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block
    """Embedded Python Block example - a simple multiply const"""

    def __init__(self, modulation_type = 0, mode = 0):  # only default arguments here
        """arguments to this function show up as parameters in GRC"""
        gr.sync_block.__init__(
            self,
            name='Extract information IQ',   # will show up in GRC
            in_sig=[np.float32, np.float32],
            out_sig=[np.float32]
        )
        # self.set_min_output_buffer(2**13)        # 512 - минимальный размер
        # # self.set_max_output_buffer(2**9)  # Установка максимального размера буфера
        # self.set_output_multiple(2**13)     # Установка шага данных
        # if an attribute with the same name as a parameter is found,
        self.num_good_bytes = 0
        self.num_bad_bytes = 0
        self.modulation_type = modulation_type
        self.mode = mode            # Stream / Messenger
        self.message = ""

    def work(self, input_items, output_items):
        i = 0
        j = 0

        GOOD_BYTE = 27

        res_msec = 0
        # num_good_bytes = 0
        output_len = len(output_items[0])
        input_len = len(input_items[0])
        packet_size_bytes = 10  # Размер пакета в байтах
        packet_size_bits = packet_size_bytes * 8  # 10 байт = 80 бит


        while i < output_len - packet_size_bytes * 8:
            # 1 - прочитать пакет:
            packet_str = ""
            readed_bytes = 0

            # start = time.time()
            while (readed_bytes < packet_size_bytes) and (i < (output_len - 8)):
                byte = 0
                # QPSK
                if self.modulation_type == 0:
                    for n in range(0, 4):
                        byte <<= 2
                        byte += (1 if input_items[1][i] > 0.5  else 0)
                        byte += (1 if input_items[0][i] > 0.5  else 0) * 2
                        i += 1
                # QAM16
                if self.modulation_type == 1:
                    for n in range(2):
                        byte <<= 4
                        
                        # Работа с input_items[1][i]
                        byte += (0 if input_items[1][i] < 0.2 else 
                                1 if input_items[1][i] < 0.4 else 
                                2 if input_items[1][i] < 0.8 else 3)

                        # Работа с input_items[0][i]
                        byte += ((0 if input_items[0][i] < 0.2 else 
                                1 if input_items[0][i] < 0.4 else 
                                2 if input_items[0][i] < 0.8 else 3) * 4)
                        
                        # Увеличиваем индекс
                        i += 1

                # if byte != 0:
                    # print(byte)
                output_items[0][j] = byte
                byte = chr(byte)

                # Messenger
                if self.mode == 1:
                    # Конец строки?
                    # if byte == '\n' or byte == '\r' or byte == ';':
                        # print(self.message)
                        # self.message = ""
                    # Символ может быть интерпретирован?
                    # elif ord(byte) > 0:
                        # print(byte)
                        # self.message += byte

                    if byte.isprintable():
                        # print(byte, end = '')
                        try:
                            print(byte, end='')
                        except UnicodeEncodeError:
                            pass  # Игнорируем символ, если его нельзя вывести



                # Stream
                else:
                    # if 31 < byte < 127:

                    # ЗАМЕР СКОРОСТИ И ОШИБКИ
                    if 0 < byte < 256:
                        if byte == GOOD_BYTE:
                            self.num_good_bytes += 1
                        else:
                            self.num_bad_bytes += 1


                    #     pass
                        # num_good_bytes += 1
                        # print(chr(byte), end = '')
                        # packet_str += chr(byte)
                    j += 1
                #     readed_bytes += 1
                # if j == 10:
                #     finish = time.time()
                #     res = finish - start
                #     res_msec = res * 1000
                # 2 - пропустить нули
                # print(packet_str, end = '')
                # print(packet_str)
                # i += (packet_size_bits * 4)

            # print('Время работы в миллисекундах: ', res_msec)
            # print('хороших байт: ', num_good_bytes)
            if self.num_good_bytes > 100000:
                print("Good bytes: ", self.num_good_bytes, "  ---  Bad bytes: ", self.num_bad_bytes)

        return output_len

"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import numpy as np
from gnuradio import gr
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
        self.num_good_bytes = 0
        self.num_bad_bytes = 0
        self.modulation_type = modulation_type
        self.mode = mode            # Stream / Messenger
        self.message = ""
        self.test_complite = 0 
        self.test_start_time = 0
        self.test_end_time = 0

    def work(self, input_items, output_items):
        GOOD_BYTE = "<"
        res_msec = 0
        output_len = len(output_items[0])
        input_len = len(input_items[0])
        packet_size_bytes = 10  # Размер пакета в байтах
        packet_size_bits = packet_size_bytes * 8  # 10 байт = 80 бит
        i = 0
        j = 0

        while i < output_len - packet_size_bytes * 8:
            # 1 - прочитать пакет:
            packet_str = ""
            readed_bytes = 0

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

                output_items[0][j] = byte
                j += 1
                byte = chr(byte)

                # Messenger
                if self.mode == 1:
                    if byte.isprintable():
                        try:
                            print(byte, end='')
                        except UnicodeEncodeError:
                            pass  # Игнорируем символ, если его нельзя вывести

                # Stream

                # Test
                elif self.mode == 2:
                    # ЗАМЕР СКОРОСТИ И ОШИБКИ
                    if ord(byte) > 0:
                        if byte == GOOD_BYTE:
                            self.num_good_bytes += 1
                        else:
                            self.num_bad_bytes += 1
                        if self.test_start_time == 0:
                            self.test_start_time = time.time()

            if self.num_good_bytes > 100000 and self.test_complite == 0:
                self.test_end_time = time.time()
                print("\n")
                print("Bitrate:\t\t\t\t", int(self.num_good_bytes / (self.test_end_time - self.test_start_time)), " Bytes/s")
                print("BER (bit error ratio):\t", round((self.num_bad_bytes / (self.num_good_bytes + self.num_bad_bytes)) * 100, 2) , " %")
                self.test_complite = 1

        return output_len

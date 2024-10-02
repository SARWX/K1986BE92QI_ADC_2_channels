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

    def __init__(self, example_param=1.0):  # only default arguments here
        """arguments to this function show up as parameters in GRC"""
        gr.sync_block.__init__(
            self,
            name='Extract information IQ QPSK',   # will show up in GRC
            in_sig=[np.float32, np.float32],
            out_sig=[np.float32]
        )
        # if an attribute with the same name as a parameter is found,
        # a callback is registered (properties work, too).
        self.example_param = example_param

    def work(self, input_items, output_items):
        i = 0
        j = 0

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

            start = time.time()
            while (readed_bytes < packet_size_bytes) and (i < (output_len - 8)):
                byte = 0
                for n in range(0, 4):
                    byte <<= 2
                    byte += int(input_items[1][i])
                    byte += int(input_items[0][i] * 2)
                    i += 1
                output_items[0][j] = byte
                if 31 < byte < 127:
                    pass
                    # num_good_bytes += 1
                    # print(chr(byte), end = '')
                    # packet_str += chr(byte)
                j += 1
                readed_bytes += 1
            if j == 10:
                finish = time.time()
                res = finish - start
                res_msec = res * 1000
            # 2 - пропустить нули
            # print(packet_str, end = '')
            # print(packet_str)
            # i += (packet_size_bits * 4)

        # print('Время работы в миллисекундах: ', res_msec)
        # print('хороших байт: ', num_good_bytes)

        return output_len

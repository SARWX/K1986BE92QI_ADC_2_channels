"""
Messenger
"""

#  epy_block_0.py
#  created 10/17/2019

import numpy as np
from gnuradio import gr

import pmt
import math

textboxValue = ""

class my_sync_block(gr.sync_block):
    """
    reads input from a message port
    outputs packets of bytes
    """
    def __init__(self, modulation_type = 0):
        gr.sync_block.__init__(self,
            name = "Messenger",
            in_sig = None,
            out_sig = [np.byte])
        self.message_port_register_in(pmt.intern('msg_in'))
        self.message_port_register_out(pmt.intern('clear_input'))
        self.set_msg_handler(pmt.intern('msg_in'), self.handle_msg)
        # Публичные атрибуты
        self.modulation_type = modulation_type
        self.cleared = 0

        self.set_min_output_buffer(2**13)        # 512 - минимальный размер
        self.set_max_output_buffer(2**13)  # Установка максимального размера буфера
        self.set_output_multiple(2**13)     # Установка шага данных

    def handle_msg(self, msg):
        global textboxValue

        textboxValue = pmt.symbol_to_string (msg)
        # print (textboxValue)
    
    def work(self, input_items, output_items):
        global textboxValue

        PACKET_SIZE = 10
        WAIT = 10

        output_len = len(output_items[0])
        output_items[0].fill(0)

        # get length of string
        _len = len(textboxValue)
        # Вставить Start condition
        if self.modulation_type == 0:
            start_condition = 3        # Это 2 единицы подряд (2 надо, чтобы на оба канала)
        else:
            start_condition = 15        # Это по 2 единицы подряд на 2 канала

        pos_send = 0
        pos_src = 0


        if (_len > 0):
            # terminate with LF
            textboxValue += "\n" 
            _len += 1

            # Find good pos_send (not at the start)
            pos_send = int(output_len - (_len * 2 + (_len // 10) + 10))

            # divide by packets
            for packet in range(math.ceil(_len / PACKET_SIZE)):
                # print(packet)
                # Start condition                                             
                output_items[0][pos_send] = start_condition
                pos_send += 1
                # Information
                for _ in range(PACKET_SIZE):
                    if pos_src < _len:
                        output_items[0][pos_send] = ord(textboxValue[pos_src])
                        pos_send += 1
                        pos_src += 1
                    else:
                        pos_send += 1
                # Wait
                # print(pos_send)
                pos_send += WAIT
            
            # store elements in output array
            # for x in range(_len):
            #     output_items[0][x + 1] = ord(textboxValue[x])
            textboxValue = ""
            self.message_port_pub(pmt.intern('clear_input'), pmt.intern(''))
            # print(output_len)
            # return (pos_send)
            self.cleared = 0
            return (output_len)
        elif self.cleared == 1:
            return (0)
        else:
            self.cleared = 1
            return(output_len)
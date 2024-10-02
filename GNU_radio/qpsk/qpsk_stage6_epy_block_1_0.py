"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import numpy as np
from gnuradio import gr

# Constants
WAIT = 10

class blk(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block
    """Embedded Python Block example - a simple multiply const"""

    def __init__(self, example_param=1.0):  # only default arguments here
        """arguments to this function show up as parameters in GRC"""
        gr.sync_block.__init__(
            self,
            name='Test string generator',   # will show up in GRC
            in_sig=[],
            out_sig=[np.byte]
        )
        # if an attribute with the same name as a parameter is found,
        # a callback is registered (properties work, too).
        self.example_param = example_param

    def work(self, input_items, output_items):
        i = 0
        default_level = "\0" * WAIT
        start_condition = chr(3)        # Это 2 единицы подряд (2 надо, чтобы на оба канала)

        # information = "Hello!!!!!"
        information = "<" * 10

        messege = default_level + start_condition + information
        message_bytes = bytes(messege, 'ascii')
        mes_len = len(messege)
        output_len = len(output_items[0])
        while(i < (output_len - mes_len)):
           # Переводим байты в целые числа и записываем в массив
            output_items[0][i:i + mes_len] = np.frombuffer(message_bytes, dtype=np.byte)
            i += mes_len
        return len(output_items[0])

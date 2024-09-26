"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import numpy as np
from gnuradio import gr


class blk(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block
    """Embedded Python Block example - a simple multiply const"""

    def __init__(self, example_param=1.0):  # only default arguments here
        """arguments to this function show up as parameters in GRC"""
        gr.sync_block.__init__(
            self,
            name='Embedded Python Block',   # will show up in GRC
            in_sig=[np.float32, np.float32],
            out_sig=[np.byte, np.byte]
        )
        # if an attribute with the same name as a parameter is found,
        # a callback is registered (properties work, too).
        self.example_param = example_param

    def work(self, input_items, output_items):
        i = 0
        output_len = len(output_items[0])
        input_len = len(intput_items[0])
        while(i < intput_len):
            # 1 - найти переход 1 -> 0
            mes = 0.0
            for mes in input_items[0][i:i+7]:
                res += mes
            res /= 7
            res = (1 if res > 0.5  else 0)
            output_items[0][(i // 7)] = int(res) 
            # 1 - найти переход 1 -> 0
            mes = 0.0
            for mes in input_items[1][i:i+7]:
                res += mes
            res = (1 if res > 0.5  else 0)
            output_items[1][(i // 7)] = int(res) 
            i += 7
            
        return len(i)

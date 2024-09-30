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
            name='Test string decoder',   # will show up in GRC
            in_sig=[np.byte],
            out_sig=[]
        )
        # if an attribute with the same name as a parameter is found,
        # a callback is registered (properties work, too).
        self.example_param = example_param

    def work(self, input_items, output_items):
        i = 0
        messege = ""
        input_len = len(input_items[0])
        while(i < (input_len)):
            messege += str(input_items[0][i])
            if(input_items[0][i] == '\n'):
                print(messege)
                messege = ""
            i += 1
        return len(input_items[0])

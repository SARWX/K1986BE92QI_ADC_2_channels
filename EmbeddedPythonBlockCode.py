"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import serial
import numpy as np
from gnuradio import gr

class blk(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block
    """
    Read data from serial port and forward it to output. 
    portNumber is number, you can see in the name of your 
    serial port in device manager, like COM16 or COM7 
    """
    adc_num = 1
    
    def __init__(self, portNumber = 7, baudrate = 2000000): 
        """arguments to this function show up as parameters in GRC"""
        
        portName = 'COM' + str(portNumber)                  # Concatenate string and number
        
        gr.sync_block.__init__(
            self,
            name = 'Serial Read',   
            in_sig = [],                                    # no inputs 
            out_sig = [np.float32, np.float32, np.float32]  # also you can try to use int
        )
        
        self.port = serial.Serial(portName, baudrate, timeout = 3.0) # open serial
        if (self.port.is_open):  #if already opened - close and open again
            self.port.close()
            self.port.open()
        else:
            self.port.open()
            
    def work(self, input_items, output_items):
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
            output_items[1][n] = data[0]
            output_items[2][n] = data[1]
            n += 1
            output_items[1][n] = data[2]
            output_items[2][n] = data[3]
            n += 1
            
        return len(output_items[1])
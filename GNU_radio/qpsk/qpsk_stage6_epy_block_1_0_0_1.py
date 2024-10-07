"""
Embedded Python Blocks:

Each time this file is saved, GRC will instantiate the first class it finds
to get ports and parameters of your block. The arguments to __init__  will
be the parameters. All of them are required to have default values!
"""

import numpy as np
from gnuradio import gr
import enum


# class Scheduler(enum.Enum):
#     first_channel = 0
#     second_channel = 1
#     deinit = 2

class blk(gr.sync_block):  # other base classes are basic_block, decim_block, interp_block
    """Embedded Python Block example - a simple multiply const"""

    def __init__(self, example_param=1.0):  # only default arguments here
        """arguments to this function show up as parameters in GRC"""
        gr.sync_block.__init__(
            self,
            name='Filter IQ QPSK',   # will show up in GRC
            in_sig=[np.float32, np.float32],
            out_sig=[np.float32, np.float32]
        )
        # if an attribute with the same name as a parameter is found,
        # a callback is registered (properties work, too).
        self.example_param = example_param

    def work(self, input_items, output_items):
        # WAIT = 10

        WAIT = 10 * 8 * 4
        packet_size_bytes = 10  # Размер пакета в байтах
        packet_size_bits = packet_size_bytes * 8  # 10 байт = 80 бит
        bit_size = 4  # Размер бита (для расчета шага при чтении)
        packet_size_mes = packet_size_bits * bit_size  # 10 байт = 80 бит
        # "Планировщик" распределяющий по каналам (кто раньше 0->1, тот первый канал) 
        # scheduler = Scheduler.first_channel
        scheduler = 0

        # 1 - Заполнить выходной массив нулями
        output_items[0].fill(0)
        output_items[1].fill(0)
        
        i = 0
        j = 0

        exact_num_of_mes_per_bit = 4.33
        count_mes_per_pack = 0
        prev_start = 0

        output_len = len(output_items[0])
        input_len = len(input_items[0])

        # print(input_len, output_len)
        test_mark = 0
        

        chan_0_start_condition = False
        chan_0_start_index = 0
        chan_1_start_condition = False
        chan_1_start_index = 0
        chan_num_0 = 0
        chan_num_1 = 1

        start_condition_found = False  # Флаг, найдено ли start_condition
        read_started = False  # Флаг, началось ли чтение
        bits_read = 0  # Счетчик прочитанных битов

        # Не надо читать буфер, если в него не может поместиться как миниум 1 полноценный пакет
        # Размер буфера почему-то постоянно меняется 
        if (input_len < WAIT + packet_size_mes):
            return(output_len)

        # Для нормализации будем делить заносимые значения на амплитуду
        amplitude = max(input_items[0])
        # Амплитуда не должна быть меньше 0.8
        if amplitude < 0.8:
            amplitude = 1.0
        threshold = amplitude * 0.4
        

        while i < (input_len - 7):
            if not start_condition_found:
                # 1 - Либо одновременно, либо с шагом в 1 оба канала должны перейти в 1 
                # 1 - Проверяем условие: оба канала последовательно перешли на 1
                if input_items[0][i] > threshold:
                    if chan_0_start_condition == False:
                        chan_0_start_index = (i + 2 + 4)
                        chan_num_0 = scheduler            # каким каналом назначен первый
                        scheduler += 1
                    chan_0_start_condition = True
                if input_items[1][i] > threshold:
                    if chan_1_start_condition == False:
                        chan_1_start_index = (i + 2 + 4)
                        chan_num_1 = scheduler            # каким каналом назначен второй
                        scheduler += 1
                    chan_1_start_condition = True

                if (chan_0_start_condition and chan_1_start_condition):
                    if (abs(chan_0_start_index - chan_1_start_index) < 4):
                        start_condition_found = True
                        # print(i - test_mark)
                        read_started = True
                        bits_read = 0  # Сбрасываем счетчик прочитанных битов
                    else:
                        chan_0_start_condition = False
                        chan_1_start_condition = False
                        # scheduler = Scheduler.first_channel
                        scheduler = 0
                    # # Посчитаем точно сколько измерений приходится на 1 бит
                    # if prev_start != 0:
                    #     count_mes_per_pack = i - prev_start
                    #     exact_num_of_mes_per_bit = count_mes_per_pack / packet_size_bits
                    #     print(exact_num_of_mes_per_bit)
                    # prev_start = i

                # if input_items[0][i] > 0.5 and input_items[1][i] > 0.5:
                #     start_condition_found = True
                #     read_started = True
                #     bits_read = 0  # Сбрасываем счетчик прочитанных битов
            else:
                if read_started and (bits_read < packet_size_bits):
                    # 2 - Читаем биты с текущего индекса с шагом exact_num_of_mes_per_bit
                    if (i - chan_0_start_index) >= 0 and (i - chan_0_start_index) % exact_num_of_mes_per_bit < 1.0:
                        # output_items[chan_num_0][j // 2] = (1 if input_items[0][i] > 0.5 else 0)
                        output_items[chan_num_0][j // 2] = (input_items[0][i] / amplitude)
                        j += 1
                        bits_read += 1
                    if (i - chan_1_start_index) >= 0 and (i - chan_1_start_index) % exact_num_of_mes_per_bit < 1.0:
                        # output_items[chan_num_1][j // 2] = (1 if input_items[1][i] > 0.5 else 0)
                        output_items[chan_num_1][j // 2] = (input_items[1][i] / amplitude)
                        j += 1
                        bits_read += 1
                else:
                    # Чтение завершено, сбрасываем флаг и ищем новое start_condition
                    start_condition_found = False
                    read_started = False
                    chan_0_start_condition = False
                    chan_1_start_condition = False
                    bits_read = 0
                    scheduler = 0
                    j += packet_size_bits * 4   # (packet_size_bits * 2)    - нули и полезная нагрузка
                                                                            # (+ 1) - 0x3               - начало фрейма
                                                                            # (- packet_size_bits)      - мы уже передали 1 пакет битов, надо их учесть
                    stop_trig = 0
                    # i += (WAIT / 2)
                    while (i < input_len and stop_trig < (WAIT / 2)):
                        if ((input_items[0][i] < threshold) and (input_items[0][i] < threshold)):
                            stop_trig += 1
                        else:
                            # print("STOP: ", stop_trig)
                            stop_trig = 0
                        i += 1
                    # print("END: ", stop_trig)
                    test_mark = i

            i += 1  # Шаг в любом случае

        # output_items[0][0] = 2
        # output_items[0][output_len - 1] = 3
        # print(output_len)
        # print(input_len)

        # # Нормализуем данные
        # amplitude = np.max(output_items[0][0])
        # if amplitude > 1.0:
        #     output_items[0][0] = np.divide(output_items[0][0], amplitude)
        #     output_items[0][1] = np.divide(output_items[0][1], amplitude)
        #     # print(amplitude)


        return output_len

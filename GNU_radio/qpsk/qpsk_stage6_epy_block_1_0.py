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
            out_sig=[np.float32, np.float32]
        )
        # if an attribute with the same name as a parameter is found,
        # a callback is registered (properties work, too).
        self.example_param = example_param

    def work(self, input_items, output_items):
        # 1 - найти переход 1 -> 0
        output_items[0].fill(0)
        output_items[1].fill(0)
        i = 0
        j = 0
        output_len = len(output_items[0])
        input_len = len(input_items[0])
        # while (i < (input_len - 1)) and (abs(input_items[0][i] - input_items[0][i+1]) < 0.3) and (abs(input_items[1][i] - input_items[1][i+1]) < 0.3):
        #     i += 1
        # while (i < (input_len - 1)):
        #     while (i < (input_len - 1)) and (abs(input_items[0][i] - input_items[0][i+1]) < 0.3) and (abs(input_items[1][i] - input_items[1][i+1]) < 0.3):
        #         output_items[0][i] = input_items[0][i]
        #         output_items[1][i] = input_items[1][i]
        #         i += 1   
        #     output_items[1][i] = 3

        # Works but only for 0x10
        # while (i < (input_len - 7)):
        #     # Копируем текущие элементы в output_items до тех пор, пока условие выполняется
        #     diff_0 = abs(input_items[0][i] - input_items[0][i+1])
        #     diff_1 = abs(input_items[1][i] - input_items[1][i+1])
        #     # Ищем опору для отсчетов
        #     if diff_0 < 0.3 and diff_1 < 0.3:
        #         pass
        #     else:
        #         output_items[1][j] = input_items[1][i+2]    # Маркировка считывания 1
        #         output_items[1][j+1] = input_items[1][i+6]    # Маркировка считывания 1
        #         # Второй канал
        #         output_items[0][j] = input_items[0][i+2]    # Маркировка считывания 1
        #         output_items[0][j+1] = input_items[0][i+6]    # Маркировка считывания 1
        #         i += 6
        #         j += 2

        #     i += 1



        # Параметр N — количество выборок, которые нужно сделать после нахождения опоры
        N = 5  # Можно изменить на нужное значение
        step = 4  # Шаг для выборки (каждый четвертый элемент)
        start_index = 0   # Индекс опорного элемента
        opora_found = False  # Флаг, указывающий, найдена ли опора

        while i < (input_len - 7):
            if not opora_found:
                # Если опора не найдена, продолжаем брать каждый четвертый элемент
                if (i - start_index + 1) % step == 0:
                    output_items[0][j] = (1 if input_items[0][i] > 0.5  else 0)
                    output_items[1][j] = (1 if input_items[1][i] > 0.5  else 0)
                    j += 1

                # Проверяем, нашли ли мы опору
                diff_0 = abs(input_items[0][i] - input_items[0][i+1])
                diff_1 = abs(input_items[1][i] - input_items[1][i+1])
                
                if diff_0 >= 0.3 or diff_1 >= 0.3:
                    opora_found = True  # Опора найдена, переключаемся на выборки с i+2
                    i += 2  # Сдвиг на i+2 для начала новой выборки
                    start_index = i     # Новый индекс опорного элемента
            else:
                # Опора найдена, выполняем N выборок с шагом 4, начиная с i+2
                for n in range(N):
                    idx = i + n * step  # Первая выборка на i, остальные с шагом 4
                    if idx < input_len:
                        output_items[0][j] = (1 if input_items[0][idx] > 0.5  else 0)
                        output_items[1][j] = (1 if input_items[1][idx] > 0.5  else 0)
                        j += 1
                    else:
                        break  # Прерываем цикл, если индекс выходит за пределы массива
                
                # После завершения выборок продолжаем с обычным шагом 4
                i += (N - 1) * step
                opora_found = False  # Опора обработана, продолжаем искать новую
            
            i += 1  # Шаг в любом случае





        # if (i > (input_len - 11)):
        #     return(i)

        # TEST
        # output_items[0][0:output_len] = input_items[0][0:output_len]
        # output_items[1][0:output_len] = input_items[1][0:output_len]
        # # Делаем каждый 4-й элемент равным 100
        # for i in range(0, output_len, 4):
        #     output_items[0][i] = 3
        #     output_items[1][i] = 3    


        # while(i < (input_len)):
            # mes = 0.0
            # res = 0.0
            # for mes in input_items[0][i:i+3]:
            #     res += mes
            # res /= 3
            # res = (1 if res > 0.5  else 0)
            # output_items[0][(i // 3)] = int(res) 
            # # 1 - найти переход 1 -> 0
            # mes = 0.0
            # res = 0.0
            # for mes in input_items[1][i:i+3]:
            #     res += mes
            # res = (1 if res > 0.5  else 0)
            # output_items[1][(i // 3)] = int(res) 
            # i += 3






            # 1 - найти переход 1 -> 0
            # mes = 0.0
            # res = 0.0
            # for mes in input_items[0][i:i+4]:
            #     res += mes
            # res /= 4
            # res = (1 if res > 0.5  else 0)
            # output_items[0][(i // 4)] = int(res) 
            # # 1 - найти переход 1 -> 0
            # mes = 0.0
            # res = 0.0
            # for mes in input_items[1][i:i+4]:
            #     res += mes
            # res /= 4
            # res = (1 if res > 0.5  else 0)
            # output_items[1][(i // 4)] = int(res) 
            # i += 4
        # return (i)
        return (output_len)

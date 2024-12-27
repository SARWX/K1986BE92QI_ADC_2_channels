import numpy as np
from gnuradio import gr
import pmt
import time

class TriangleWaveGenerator(gr.sync_block):
    """
    Генератор значения 48 битного регистра iFSY-304-M36.
    """

    def __init__(
        self, 
        mux_sel = 0, 
        mux_en = 0, 
        ref_div_ctrl = 0, 
        input_div_ctrl = 0, 
        pre_divider_mode = 0, 
        enable = 0.0, 
        in_freq = 1000000, 
        out_freq = 2000000
    ):
        gr.sync_block.__init__(
            self,
            name="iFSY driver",
            in_sig=[],
            out_sig=[np.uint8]
        )

        # Инициализация переменных
        self.mux_sel = mux_sel
        self.mux_en = mux_en
        self.ref_div_ctrl = ref_div_ctrl
        self.input_div_ctrl = input_div_ctrl
        self.pre_divider_mode = pre_divider_mode
        self.enable = enable
        self.target_register_len = 6    # байт
        self.in_freq = in_freq
        self.out_freq = out_freq

        # Регистрация выходного порта для отправки данных
        self.message_port_register_out(pmt.intern('spi'))


    def generate_iFSY_setting(self, mux_sel_new, mux_en_new, ref_div_ctrl_new, input_div_ctrl_new, pre_divider_mode_new, in_freq, out_freq):
        """Генерация значения 48 битного регистра"""
        # Проверка на выход за диапазоны
        # Проверка входной частоты
        if not (1e7 <= in_freq <= 1e8):  # Диапазон 10 МГц - 100 МГц
            print("Ошибка: Входная частота должна быть в диапазоне от 10 до 100 МГц.")
            return

        # Расчет минимальной и максимальной выходной частоты
        min_out_freq = in_freq * (400 / 64)
        max_out_freq = in_freq * (600 / 2)

        # Проверка выходной частоты
        if not (min_out_freq <= out_freq <= max_out_freq):
            print(
                f"Ошибка: Выходная частота должна быть в диапазоне от {min_out_freq:.2f} до {max_out_freq:.2f} Гц "
                f"при входной частоте {in_freq} Гц."
            )
            return

        # Расчет параметров выход

        


        # Приведение значений к типу uint64 перед выполнением операций
        mux_sel                 = np.uint64(mux_sel_new)            << np.uint64(0)     # Выбор режима работы выходного мультиплексора
        mux_en                  = np.uint64(mux_en_new)             << np.uint64(3)     # Вкл./ выкл. мультиплексора 
        reserve_1               = np.uint64(0)                      << np.uint64(4)     # резервный
        capture_detector_div    = np.uint64(int('0010', 2))         << np.uint64(5)     # коэффициент деления делителя детектора захвата
        capture_detector_en     = np.uint64(1)                      << np.uint64(10)    # вкл./выкл. детектора захвата
        current_key_mode        = np.uint64(0)                      << np.uint64(11)    # режим работы секций токового ключа
        ref_div_ctrl            = np.uint64(ref_div_ctrl_new)       << np.uint64(17)    # управление коэффициентом деления опорного делителя (Коп)
        reserve_2               = np.uint64(0)                      << np.uint64(23)    # резервный
        input_div_ctrl          = np.uint64(input_div_ctrl_new)     << np.uint64(24)    # управление коэффициентом деления входной частоты (Кгун)
        current_key_sections_1  = np.uint64(int('111', 2))          << np.uint64(37)    # секции токового ключа
        current_key_work_mode   = np.uint64(int('11', 2))           << np.uint64(40)    # рабочий режим токового ключа
        current_key_sections_2  = np.uint64(int('111', 2))          << np.uint64(42)    # секции токового ключа (еще раз упоминаются)
        pre_divider_mode        = np.uint64(pre_divider_mode_new)   << np.uint64(45)    # предварительный делитель частоты «8/9», «16/17»
        reserve_3               = np.uint64(0)                      << np.uint64(47)    # резервный



        # Объединение в одно 64-битное число
        combined = (
            mux_sel                 |
            mux_en                  |
            reserve_1               |
            capture_detector_div    |
            capture_detector_en     |
            current_key_mode        |
            ref_div_ctrl            |
            reserve_2               |
            input_div_ctrl          |
            current_key_sections_1  |
            current_key_work_mode   |
            current_key_sections_2  |
            pre_divider_mode        |
            reserve_3
        )

        # Выделение младших 48 бит
        extracted_48_bits = combined & np.uint64((1 << 48) - 1)
        print(f"Generated signal: {extracted_48_bits}")
        return extracted_48_bits

    done = 0
    def work(self, input_items, output_items):
        # Функция work выполняется пустой, так как сигнал генерируется только один раз
        n = 0
        while n < len(output_items[0]): 
            output_items[0][n] = self.enable 
            n += 1 
        if self.enable == 1: 
            # Отправка длины сообщения
            self.message_port_pub(pmt.intern('spi'), pmt.from_long(self.target_register_len)) 

            # Генерация значения регистра
            spi_value = self.generate_iFSY_setting(
                self.mux_sel, 
                self.mux_en, 
                self.ref_div_ctrl, 
                self.input_div_ctrl, 
                self.pre_divider_mode, 
                self.in_freq, 
                self.out_freq
            ) 
             
            # Отправка сгенерированных данных в ADI блок 
            self.message_port_pub(pmt.intern('spi'), pmt.from_uint64(spi_value)) 

            time.sleep(1.00)

        # done = 1 
        # return 0 
        return len(output_items[0]) 

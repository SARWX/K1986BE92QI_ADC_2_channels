import numpy as np
from gnuradio import gr
import pmt
import time

class TriangleWaveGenerator(gr.sync_block):
    """
    Генератор треугольного сигнала.
    Принимает частоту и амплитуду как параметры через графический интерфейс.
    Передает сгенерированные значения в ADI блок.
    """

    def __init__(self, start_p = 0.0, end_p = 1.0, sample_rate = 250000, freq = 1000, enable = 0.0):
        gr.sync_block.__init__(
            self,
            name="Triangle Wave Generator",
            in_sig=[],
            out_sig=[np.uint8]
        )

        # Инициализация переменных
        self.start_p = start_p
        self.end_p = end_p
        self.sample_rate = sample_rate
        self.freq = freq
        self.enable = enable 

        # Регистрация выходного порта для отправки данных
        self.message_port_register_out(pmt.intern('set_const_signal'))

        # Генерация и отправка треугольного сигнала при инициализации
        # signal_str = self.generate_triangle_wave(start_p, end_p, sample_rate, freq)

        # time.sleep(2.00)

        # # Отправка сгенерированных данных в ADI блок
        # self.message_port_pub(pmt.intern('set_const_signal'), pmt.intern(signal_str))

    def generate_triangle_wave(self, start, end, sample_rate, freq):
        """Генерация треугольного сигнала на основе параметров"""
        # 1. Округляем точки старта и конца
        start = round(start, 2)
        end = round(end, 2)
        
        # 2. Рассчитываем время для половины периода
        period = 1 / freq
        t_half = period / 2
        
        # 3. Вычисляем количество отсчетов
        num_samples = int(t_half * sample_rate)
        
        if num_samples < 1:
            raise ValueError("Количество отсчетов должно быть больше или равно 1")
        
        # 5. Вычисляем дельту
        delta = (end - start) / num_samples
        
        # 6. Генерируем треугольный сигнал
        signal = []
        
        # Генерация увеличения
        for i in range(num_samples):
            value = round(start + i * delta, 2)
            signal.append(value)
        
        # Генерация уменьшения
        for i in range(num_samples):
            value = round(end - i * delta, 2)
            signal.append(value)
        
        # Преобразование в строку
        signal_str = " ".join(map(str, signal))
        print(f"Generated signal: {signal_str}")
        return signal_str

    done = 0
    def work(self, input_items, output_items):
        # Функция work выполняется пустой, так как сигнал генерируется только один раз
        n = 0
        while n < len(output_items[0]):
            output_items[0][n] = self.enable
            n += 1
        if self.enable == 1:
                # print(f"Works")
        # # Генерация и отправка треугольного сигнала при инициализации
            signal_str = self.generate_triangle_wave(self.start_p, self.end_p, self.sample_rate, self.freq)

            time.sleep(2.00)

            # Отправка сгенерированных данных в ADI блок
            self.message_port_pub(pmt.intern('set_const_signal'), pmt.intern(signal_str))
        # done = 1
        # return 0
        return len(output_items[0])
import numpy as np

# Приведение значений к типу uint64 перед выполнением операций
    mux_sel                 = np.uint64(0)              << np.uint64(0)         # Выбор режима работы выходного мультиплексора
    mux_en                  = np.uint64(0)              << np.uint64(3)             # Вкл./ выкл. мультиплексора 
reserve_1               = np.uint64(0)              << np.uint64(4)         # резервный
capture_detector_div    = np.uint64(int('0010', 2)) << np.uint64(5)         # коэффициент деления делителя детектора захвата
capture_detector_en     = np.uint64(1)              << np.uint64(10)         # вкл./выкл. детектора захвата
current_key_mode        = np.uint64(0)              << np.uint64(11)         # режим работы секций токового ключа
    ref_div_ctrl            = np.uint64(0)              << np.uint64(17)             # управление коэффициентом деления опорного делителя (Коп)
reserve_2               = np.uint64(0)              << np.uint64(23)         # резервный
    input_div_ctrl          = np.uint64(0)              << np.uint64(24)             # управление коэффициентом деления входной частоты (Кгун)
current_key_sections_1  = np.uint64(int('111', 2))  << np.uint64(37)         # секции токового ключа
current_key_work_mode   = np.uint64(int('11', 2))   << np.uint64(40)         # рабочий режим токового ключа
current_key_sections_2  = np.uint64(int('111', 2))  << np.uint64(42)         # секции токового ключа (еще раз упоминаются)
    pre_divider_mode        = np.uint64(0)              << np.uint64(45)             # предварительный делитель частоты «8/9», «16/17»
reserve_3               = np.uint64(0)              << np.uint64(47)         # резервный

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

# Формирование ASCII строки
ascii_string = "spi2_send ".encode('ascii') + extracted_48_bits.tobytes()

# Теперь можно отправить команду

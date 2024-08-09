import serial
import serial.tools.list_ports
import time
import math


def get_available_ports():
    """Возвращает список доступных COM портов."""
    ports = serial.tools.list_ports.comports()
    available_ports = [port.device for port in ports]
    return available_ports

def select_com_port():
    """Функция для выбора COM порта пользователем."""
    available_ports = get_available_ports()
    
    while True:
        print("Доступные COM порты:")
        for port in available_ports:
            print(port)
        
        port_number = input("Введите номер COM порта (например, 7 для COM7): ")
        selected_port = f'COM{port_number}'
        
        if selected_port in available_ports:
            return selected_port
        else:
            print(f"Порт {selected_port} не найден. Пожалуйста, выберите номер из списка.")
            available_ports = get_available_ports()

# Запрос у пользователя выбора COM порта
com_port = select_com_port()

# Параметры подключения к COM порту
# com_port = 'COM7'  # Указать нужный COM порт
baud_rate = 115200  # Скорость передачи данных
SIN_RES = 500  # Максимальное количество чисел

# Параметры синусоид
samples = min(SIN_RES // 2, 250)  # Общее количество семплов для каждой синусоиды
amplitude = 0.5  # Амплитуда сигналов
offset = amplitude  # Смещение для устранения отрицательных значений
freq1 = 1  # Частота первой синусоиды
freq2 = 2  # Частота второй синусоиды (в 2 раза больше)

# Генерация синусоидальных сигналов
sin1 = [round(amplitude * math.sin(2 * math.pi * freq1 * x / samples) + offset, 2) for x in range(samples)]
sin2 = [round(amplitude * math.sin(2 * math.pi * freq2 * x / samples) + offset, 2) for x in range(samples)]

# Объединяем значения, чередуя их
data = []
for i in range(samples):
    data.append(sin1[i])  # Нечетные числа — первый канал
    data.append(sin2[i])  # Четные числа — второй канал

# Открываем COM порт
with serial.Serial(com_port, baud_rate, timeout=1) as ser:
    i = 0
    while i < len(data):
        # Подготавливаем часть данных (не более 10 чисел) для отправки
        chunk = data[i:i + 10]
        
        # Формируем команду "set" с числовыми значениями
        command = "set " + " ".join(map(str, chunk))
        
        # Если мы достигли конца данных, добавляем "!" к команде
        if i + 10 >= len(data):
            command += " !"
        
        # Отправляем команду
        ser.write(command.encode())
        print(f"Отправлено: {command}")  # Для отладки
        
        # Ждем 1 миллисекунду перед следующей отправкой
        time.sleep(0.001)
        
        # Сдвигаем индекс на 10 чисел
        i += 10
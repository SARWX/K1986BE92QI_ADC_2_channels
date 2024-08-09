import serial
import time

# Параметры подключения к COM порту
com_port = 'COM7'   # Указать COM порт
baud_rate = 115200  # Скорость передачи данных

# Создаем массивы данных для отправки
packet0 = bytes([0] *  64)
packet01 = bytes([1] * 64)
packet02 = bytes([2] * 64)
packet03 = bytes([3] * 64)
packet04 = bytes([4] * 64)
packet05 = bytes([5] * 64)
packet06 = bytes([6] * 64)
packet07 = bytes([7] * 64)
packet08 = bytes([8] * 64)
packet09 = bytes([9] * 64)
packet1 = bytes(range(0, 64))
packet2 = bytes(range(64, 128))
packet3 = bytes(range(128, 192))
packet4 = bytes(range(192, 256))
packet = bytes([i for i in range(16) for _ in range(4)])


# Открываем COM порт
with serial.Serial(com_port, baud_rate, timeout=1) as ser:
    while(1):
        # Отправляем данные на максимальной скорости
        # ser.write(packet0)
        # ser.write(packet0)
        # ser.write(packet1)
        # ser.write(packet2)
        # ser.write(packet3)
        # ser.write(packet4)

        ser.write(packet0)
        ser.write(packet01)
        ser.write(packet02)
        ser.write(packet03)
        ser.write(packet04)
        ser.write(packet05)
        ser.write(packet06)
        ser.write(packet07)
        ser.write(packet08)
        ser.write(packet09)


        # ser.write(packet)
        # print("Данные успешно отправлены.")
    # except serial.SerialException as e:
        # print(f"Ошибка при работе с COM портом: {e}")

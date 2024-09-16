import serial
import time

# Параметры подключения к COM порту
com_port = 'COM7'   # Указать COM порт
baud_rate = 10000000  # Скорость передачи данных

SIZE = 64


def send_dac_packet(packet):
    ser.write(packet)
    # ser.read()




packet01_256 = bytes([1] * 256)
packet02_256 = bytes([0] * 256)
# Создаем массивы данных для отправки
packet0 = bytes([0] *  SIZE)
packet01 = bytes([1] * SIZE)
packet02 = bytes([2] * SIZE)
packet03 = bytes([3] * SIZE)
packet04 = bytes([4] * SIZE)
packet05 = bytes([5] * SIZE)
packet06 = bytes([6] * SIZE)
packet07 = bytes([7] * SIZE)
packet08 = bytes([8] * SIZE)
packet09 = bytes([9] * SIZE)
packet1 = bytes(range(0, 64))
packet2 = bytes(range(64, 128))
packet3 = bytes(range(128, 192))
packet4 = bytes(range(192, 256))
packet = bytes([i for i in range(16) for _ in range(4)])
packet256_1 = bytes(range(0, 256))
packet256_2 = bytes(range(256, 0))


# Открываем COM порт
with serial.Serial(com_port, baud_rate, timeout=1) as ser:
    while(1):
        # Отправляем данные на максимальной скорости
        # ser.write(packet0 )
        # ser.write(packet01)
        # ser.write(packet02)
        # ser.write(packet03)
        # ser.write(packet04)
        # ser.write(packet05)
        # ser.write(packet06)
        # ser.write(packet07)
        # ser.write(packet08)
        # ser.write(packet09)


        send_dac_packet(packet0)
        send_dac_packet(packet01)
        send_dac_packet(packet02)
        send_dac_packet(packet03)
        send_dac_packet(packet04)
        send_dac_packet(packet05)
        send_dac_packet(packet06)
        send_dac_packet(packet07)
        send_dac_packet(packet08)
        send_dac_packet(packet09)

        # time.sleep(0.00003)
        # ser.write(packet05)
        # ser.write(packet06)
        # ser.write(packet07)
        # ser.write(packet08)
        # time.sleep(0.00003)

        
        # ser.write(packet04)
        # ser.write(packet08)

        # i = 0
        # while ser.write(packet04) < (SIZE - 1) and i < 8:
        #     i += 1
        # i = 0
        # while ser.write(packet06) < (SIZE - 1) and i < 8:
        #     i += 1
        # i = 0
        # while ser.write(packet09) < (SIZE - 1) and i < 8:
        #     i += 1
        # i = 0


        # ser.write(packet)
        # print("Данные успешно отправлены.")
    # except serial.SerialException as e:
        # print(f"Ошибка при работе с COM портом: {e}")
        # ser.write(packet256_1)
        # time.sleep(0.001)
        # ser.write(packet256_2)
        # time.sleep(0.001)



    

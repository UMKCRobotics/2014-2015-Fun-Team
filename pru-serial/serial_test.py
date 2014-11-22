import Adafruit_BBIO.UART as UART
import serial
import time

# IMPORTANT: this requires Adafruit_BBIO and pyserial installed via pip.

UART.setup("UART1")

# ser = serial.Serial(port="/dev/ttyO1", baudrate=115200)
ser = serial.Serial(port="/dev/ttyO1", baudrate=9600)
ser.close()
ser.open()

counter = 0
if ser.isOpen():
    print("Serial opened")
    while True:
        for i in range(1111, 9999):
            ser.write(str(i))
            time.sleep(0.1)

ser.close()

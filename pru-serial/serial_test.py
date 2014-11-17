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
        for i in range(0, 10):
            ser.write(str(i))
            time.sleep(0.25)
        for i in ['a', 'b', 'c', 'd', 'e', 'f']:
            ser.write(i)
            time.sleep(0.25)
        for i in ['A', 'B', 'C', 'D', 'E', 'F']:
            ser.write(i)
            time.sleep(0.25)

ser.close()

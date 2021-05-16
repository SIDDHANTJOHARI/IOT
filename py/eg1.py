import serial 
import time
#serial ek package hai
# Serial ek class hai
# board ek pointer hai
board=serial.Serial(port="/dev/ttyUSB0",baudrate=9600)
time.sleep(4)
print(type(board))
board.close()
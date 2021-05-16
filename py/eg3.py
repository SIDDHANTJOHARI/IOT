import serial
import time
board=serial.Serial(port="/dev/ttyUSB0",baudrate=9600)
print("Initalizing Arduino")
time.sleep(4)
print("Arduino Iniatialized")
while True:
    command=input("arduino>")
    if(command=="quit"):
        print("Bye..")
        break     
    command+='\n'
    board.write(bytes(command,"utf-8"))
    time.sleep(1)

    print(str(board.readline(),encoding='utf-8'))
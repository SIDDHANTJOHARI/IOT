import serial 
import time
#serial ek package hai
# Serial ek class hai
# board ek pointer hai
print("Initalizing communication channel with Arduino")
board=serial.Serial(port="/dev/ttyUSB0",baudrate=9600)
time.sleep(4)

print("Communication channel with Arduino initialized")

while True:
    command=input("Enter command: ")
    if command=="quit":
        break
    #command+="\n"
    board.write(bytes(command,"utf-8"))
    print(str(board.readline(),encoding="utf-8"))
board.close()
print("Thank you for using application")
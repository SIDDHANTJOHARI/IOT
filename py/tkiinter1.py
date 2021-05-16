import tkinter
import tkinter.ttk
import serial
import time


print("Initializing Arduino")
board=serial.Serial(port="/dev/ttyUSB0",baudrate=9600)
time.sleep(4)
print("Arduino Initailized")
window=tkinter.Tk()
window.geometry("600x400")
#window naam ke pointer ke liye geometry naam ke function chala

def sendButtonClicked():
    commandToSend=commandEntryBox.get()
    if len(commandToSend)==0:return
    commandToSend+='\n'
    board.write(bytes(commandToSend,encoding='utf-8'))
    commandEntryBox.delete(0,tkinter.END)
    time.sleep(1)
   
    commandEntryBox.focus()
    responseText=str(board.readline(),encoding='utf-8')
    responseTextBox.delete(1.0,tkinter.END)
    responseTextBox.insert(1.0,responseText)

commandEntryBox=tkinter.ttk.Entry(master=window,width=50)
commandEntryBox.grid(row=0,column=0,sticky='W')

commandSendButton=tkinter.ttk.Button(master=window,text="Send",command=sendButtonClicked)
commandSendButton.grid(row=0,column=1)

responseTextBox=tkinter.Text(master=window,width=50,height=20)
responseTextBox.grid(row=1,column=0)
window.mainloop()
#mainloop ki vjh se vo atk jayega window
# TK class ka object bnke window naam ke pointer ko assign kiya

"""Visense Testing Script

This script intended for the use of testing visense units. This scripts actually
dumps data from a COM port to a CSV file. 

Script will dump the live JSON data from visense units to a csv file unless a STOP
button is pressed in the UI. Also this UI supports selecting different visense units
selecting file to dump. Also configuring of serial port.
"""

# Import packages
from tkinter import *
from tkinter import messagebox, ttk, filedialog
from tkinter.filedialog import askopenfile
from PIL import ImageTk, Image
import serial
import json
import csv
import re
import os
import time
import datetime
from time import strftime, localtime
import threading
from subprocess import Popen

Json = ""
filepath = ""
Com = ""
Baud = 0
data = ""
decoded_data = ""
Dumpflag = False
JsonFound = False
csv_header = []
ser = None
csv_file = None
csv_writer = None
t1 = None


def openfile():
    '''
    This is the click event for browse button
    Args:
        None
    Returns:
        None
    '''
    file = filedialog.asksaveasfilename(filetypes=[("csv file", ".csv")], defaultextension=".csv")
    print("Path of the file..", os.path.abspath(file))
    filepath = os.path.abspath(file)
    FileInput.insert(0, filepath)
    #filepath = s
    fob=open(file,'w')
    fob.close()


def ReceiveJSON():
    '''
    This is the function to recieve data from uart
    Args:
        None
    Returns:
        JSON received
    '''    
    global ser
    global JsonFound
    global Dumpflag
    Json = ""
    JsonStr = ""
    while True:
        if Dumpflag:
            ser.close()
            p = Popen(FileInput.get(), shell=True)
            return

        data = ser.readline()
        decoded_data = data.decode('utf-8')
        print("Decodeddata", decoded_data)
        if decoded_data.__contains__('*'):
            JsonFound = True
            idx = decoded_data.find("{")
            decoded_data = decoded_data[idx:]
            print("start", decoded_data)
        if JsonFound:
            JsonStr = JsonStr + decoded_data
            if JsonStr.__contains__('#'):
                JsonFound = False
                Json += JsonStr
                idx = Json.find('#')
                Json = Json[:idx]
                return Json

def DoIrroMtrDataDump():
    '''
    This is the task to dump IrroMeter data
    Args:
        None
    Returns:
        None
    '''    
    global csv_writer
    global Dumpflag
    try:
        with open(FileInput.get(), 'w', newline='') as csv_file:
            csv_writer = csv.writer(csv_file)
            csv_writer.writerow(csv_header)
            while True:
                Json = ReceiveJSON()
                print("first json................................",Json)
                if Dumpflag:
                    Dumpflag = False
                    #UpdateBtn['text'] = 'CONNECT'
                    return
                data = json.loads(Json)  
                if data:
                    # try:
                    for sensor_name, sensor_data in data.items():
                        # Extract values for each sensor
                        if isinstance(sensor_data, dict):
                            values = [
                                sensor_name,
                                str(sensor_data.get('ADC1', '')),
                                str(sensor_data.get('ADC2', '')),
                                str(sensor_data.get('CB', '')),
                                str(data.get('Temp', '')),
                                str(data.get('TS', '')),
                                str(data.get('DIAG', ''))
                            ]
                            csv_writer.writerow(values)
                else:
                    print("No JSON data received in this cycle.")            
    except KeyboardInterrupt:
        print("Exiting...")
        ser.close()



def DoPressuresensorDatDump():
    '''
    This is the task to dump pressure sensor data
    Args:
        None
    Returns:
        None
    '''
    global ser
    global csv_file
    global Dumpflag
    global csv_writer
    global csv_header
    print("Writing...")

    with open(FileInput.get(), 'w', newline='') as csv_file:
        csv_writer = csv.writer(csv_file)
        csv_writer.writerow(csv_header)
        try:
            while True:
                Json = ReceiveJSON()
                print("JSON:",Json)
                if Dumpflag:
                    Dumpflag = False
                    #UpdateBtn['text'] = 'CONNECT'
                    return
                if Json:
                    try:
                        if Json.__contains__('ADCValue'):
                            json_data = json.loads(Json)    
                            if isinstance(json_data, dict):
                                value1 = json_data.get('ADCValue','')
                                value3 = json_data.get('DIAG', '')
                                value4 = json_data.get('Pressure')
                                timestamp = json_data.get('TS', '')
                                value2 = strftime('%Y-%m-%d %H:%M:%S', localtime(timestamp))
                                l1 = [value2, value1, value4, value3]
                                print("list....................",l1)
                                print("Time",timestamp)
                                csv_writer.writerow(l1)
                                print("writing...")
                                print("Data written to CSV:", [value2, value1, value4, value3])
                                
                                    
                        else:
                            print("No valid JSON found in received data.")
                    except json.JSONDecodeError as e:
                        print(f"JSON decoding error: {e}")
                else:
                    print("No JSON data received in this cycle.")
                # Json=""
                # JsonStr =""                
        except KeyboardInterrupt:
            print("Exiting...")
            ser.close()
    

def RunTest():
    '''
    This is for running test
    Args:
        None
    Returns:
        None
    '''    
    global csv_file
    global csv_header
    global csv_writer
    global t1
    select = combo.get()
    if select == "PRESSURE SENSOR":
        t1 = threading.Thread(target=DoPressuresensorDatDump)
        t1.start()
    elif select == "IRROMETER":
        t1 = threading.Thread(target=DoIrroMtrDataDump)
        t1.start()
    elif select == "GPS TRACKER":
        messagebox.showinfo(title="RunTest event", message=f"Not implemented")
    elif select == "FLOW METER":
        messagebox.showinfo(title="RunTest event", message=f"Not implemented")
        


def clicked(BtnTxt):
    '''
    This is Click event callback for buttons
    Args:
        BtnTxt (string): text property of clicked button
    Returns:
        None
    '''
    global ser
    global csv_file
    global Dumpflag
    if BtnTxt == "CONNECT":
        Com = ComInput.get()
        print(Com)
        Baud = BrInput.get()
        print(Baud)
        ser = serial.Serial(Com, Baud) 
        messagebox.showinfo(title="Click event", message=f"Com Settings updated")
    elif BtnTxt == "RUN":
        RunTest()
    elif BtnTxt == "STOP":
        Dumpflag = True

def OnSelected(event):
    '''
    This is drop down menu selection event
    Args:
        event (string): selected event
    Returns:
        None
    '''
    global csv_header
    selection = combo.get()
    if selection == "PRESSURE SENSOR":
        csv_header = ["DateTime", "ADCValue", "Pressure", "DIAG"]
    elif selection == "IRROMETER":
        csv_header = ['Sensor', 'ADC1', 'ADC2', 'CB', 'Temp', 'TS', 'DIAG']
        messagebox.showinfo(title="New Selection", message=f"Selected option: {selection}")
    elif selection  == "GPS TRACKER":
        messagebox.showinfo(title="New Selection", message=f"Selected option: {selection}")
    elif selection == "FLOW METER":
        messagebox.showinfo(title="New Selection", message=f"Selected option: {selection}")
        
# create root window
root = Tk()
# root window title and dimension
root.title("TestUI")
# Set geometry(widthxheight)
root.geometry('800x600')
img = ImageTk.PhotoImage(Image.open("TestBackground.jpg"))  
l=Label(image=img)
l.pack()
#Header
HeaderLbl = Label(root, text = "Visense Test App 0.0.1", font='Helvetica 18 bold')
HeaderLbl.place(x=300, y=40)

#Config Params
SettingLbl = Label(root, text = "ComPort Settings", font='Helvetica 18 bold')
#ComLbl.grid()
SettingLbl.place(x=50, y=100)

# adding a label to the root window
ComLbl = Label(root, text = "COM:")
#ComLbl.grid()
ComLbl.place(x=200, y=150)

# adding Entry Field
ComInput = Entry(root, width=10)
ComInput.place(x=250, y=150)

BrLbl = Label(root, text = "Baudrate:")
BrLbl.place(x=380, y=150)

# adding Entry Field
BrInput = Entry(root, width=10)
BrInput.place(x=460, y=150)
UpdateBtn = Button(root, text = "CONNECT" ,
			fg = "blue", command=lambda: clicked("CONNECT"))
UpdateBtn.place(x=550, y=150)

DevSetLbl = Label(root, text = "Device Settings", font='Helvetica 18 bold')
DevSetLbl.place(x=50, y=200)

DevTypeLbl = Label(root, text = "DEVICE TYPE:")
DevTypeLbl.place(x=200, y=250)

combo = ttk.Combobox(values=["PRESSURE SENSOR", "IRROMETER", "GPS TRACKER", "FLOW METER"])
combo.bind("<<ComboboxSelected>>", OnSelected)
combo.place(x=290, y=250)

FileLocLbl = Label(root, text = "File:")
FileLocLbl.place(x=240, y=300)
FileInput = Entry(root, width=60)
FileInput.place(x=300, y=300)
ttk.Button(root, text="Browse", command=openfile).place(x=600, y =300)

RunBtn = Button(root, text = "RUN" ,
			fg = "blue", command=lambda: clicked("RUN"))
RunBtn.place(x=350, y=350)
StopBtn = Button(root, text = "STOP" ,
			fg = "blue", command=lambda: clicked("STOP"))
StopBtn.place(x=450, y=350)

root.mainloop()

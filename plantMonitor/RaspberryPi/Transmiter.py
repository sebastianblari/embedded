import os
import random
import datetime
import subprocess
import serial
import time
import sys

# List of devices in the node 
DEVICESLIST = ['TEMP','LUX']

# Initial status of each sensor in the node, 1 means ON, 0 means OFF
DEVICESSTATUS = {"LUX" : 1, "TEMP" : 1}

# Port in which the MSP432 is connected
PORT = '/dev/ttyACM0'

# Baudrate for the serial comunication
BAUDRATE = 9800
0

# Sends a message to i_StrTargetDeviceID (target device) from i_StrSenderDeviceID (sender) containing i_StrDataValue (data)
def sendC2DMessage(i_StrTargetDeviceID,i_StrSenderDeviceID,i_StrDataValue):
    time = str(datetime.datetime.now())[11:-1]
    l_StrSentData =  i_StrDataValue + '-' + time
    l_StrJSexcecutionCall = 'node send_c2d.js ' + i_StrTargetDeviceID + ' ' +i_StrSenderDeviceID + ' ' +l_StrSentData
    os.system(l_StrJSexcecutionCall)
    
    return l_StrSentData

# Receive any message sent to i_StrDeviceID
def receiveC2DMessage(i_StrDeviceID):
    l_StrJSexcecutionCall = 'node receive_c2d.js ' + i_StrDeviceID
    l_StrProcessOutput = subprocess.Popen(l_StrJSexcecutionCall, stdout=subprocess.PIPE, shell=True)
    l_StrProcessOutput = str(l_StrProcessOutput.communicate()[0])
    l_StrProcessOutput = l_StrProcessOutput.split("\n")[0]
    l_StrProcessOutput = l_StrProcessOutput.split("'")[1]
    l_StrProcessOutput = l_StrProcessOutput.split("\\")[0]
    print(l_StrProcessOutput)

    return l_StrProcessOutput



m_SerialConnection = serial.Serial(port = PORT,baudrate=BAUDRATE)
value_rx = ''
deviceStatus = ''
while True:
    m_SerialConnection.write(b'1010')
    data_rx = ' '
    while not(data_rx== b'.'):
        data_rx = m_SerialConnection.read()
        value_rx = value_rx + str(data_rx).replace("b","").replace("'","")
    value_rx = str(value_rx)
    value_rx = value_rx.split("b",)
    value_rx = "".join(value_rx)
    dList = value_rx.split('\\r\\n')
    print(dList)
    for item in dList:
        dev = item.split(':')[0]
        data = item.split(':')[-1]
        if dev in DEVICESLIST:
            sent = sendC2DMessage('DataMonitor',dev,data) # Le envía un mensaje Device Monitor 
            sent = sent.split('-')[-1]
            while ( sent != received):
                received = receiveC2DMessage(dev)
                deviceStatus = received.split('-')[-1]
                received = received.split('-')[-2]
                deviceStatus = int(deviceStatus)
            
                if (DEVICESSTATUS[dev] == 1 and deviceStatus == 0):
                    if (dev == 'LUX'):
                        DEVICESSTATUS[dev] = deviceStatus
                        m_SerialConnection.write(b'0001') # codigo para apagar LUZ
                    elif (dev == 'TEMP'):
                        DEVICESSTATUS[dev] = deviceStatus
                        m_SerialConnection.write(b'0000') # codigo para apagar TEMPERATURA
                elif (DEVICESSTATUS[dev] == 0 and deviceStatus == 1):
                    if (dev == 'LUX'):
                        DEVICESSTATUS[dev] = deviceStatus
                        m_SerialConnection.write(b'1101') # codigo para encender LUZ
                    elif (dev == 'TEMP'):
                        DEVICESSTATUS[dev] = deviceStatus
                        m_SerialConnection.write(b'1100') # codigo para encender TEMPERATURA
    value_rx = ''


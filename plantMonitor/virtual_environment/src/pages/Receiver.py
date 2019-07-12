import os
import random
import subprocess


def receiveC2DMessage(i_StrDeviceID):
    l_StrJSexcecutionCall = 'node receive_c2d.js ' + i_StrDeviceID
    l_StrProcessOutput = subprocess.Popen(l_StrJSexcecutionCall, stdout=subprocess.PIPE, shell=True)
    l_StrProcessOutput = str(l_StrProcessOutput.communicate()[0])
    l_StrProcessOutput = l_StrProcessOutput.split("\n")[0]
    l_StrProcessOutput = l_StrProcessOutput.split("'")[1]
    l_StrProcessOutput = l_StrProcessOutput.split("\\")[0]
    # l_StrProcessOutput = l_StrProcessOutput.split("-")[2:]
    # l_StrProcessOutput  = "-".join(l_StrProcessOutput)
    print(l_StrProcessOutput)

    return l_StrProcessOutput

def sendC2DMessage(i_StrResponse):
    l_StrTargetDeviceID = i_StrResponse.split('-')[1]
    l_StrSenderDeviceID = i_StrResponse.split('-')[0]
    l_StrDataValue = i_StrResponse.split('-')[2:]
    l_StrDataValue = "-".join(l_StrDataValue)
    
    l_StrJSexcecutionCall = 'node send_c2d.js ' + l_StrTargetDeviceID + ' ' +l_StrSenderDeviceID + ' ' + l_StrDataValue
    print(l_StrJSexcecutionCall)
    # print(l_StrJSexcecutionCall)
    # print(datetime.datetime.now())
    os.system(l_StrJSexcecutionCall)
    
    return l_StrDataValue


while True:
    response = receiveC2DMessage('DataMonitor')
    # response = "DataMonitor-LUX-25-15:09:35.47798"
    sendC2DMessage(response)
    
    # receiveC2DMessage('DataMonitor')
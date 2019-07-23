#   TrafficLight
#
#
import subprocess
from base64 import b64encode
import googleapiclient.discovery
from oauth2client.client import GoogleCredentials
import RPi.GPIO as GPIO
import re
import time
import random
import os
from pathlib import Path
from trafficlight import TrafficLight

parentDir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
logPath = os.path.join(parentDir,'flags.txt')

#PC_HOST = "192.168.0.34"
Pi_HOST = "192.168.0.29"
TOPIC = "stl/message"
CREDENTIALS_FILE = "credentials.json"
TIMEX = 7
TIME_DUMMY = 3
TIME_PER_CAR = 5
FORCE_LED_PIN = 22
BUTTON_0_INT_PIN = 7
BUTTON_2_INT_PIN = 37

#FORCE_STATE_ON = 0

class TrafficLightManager:
    
    #constructor
    def __init__(self):
        self.CurrentState = 'Init'
        self.NextState = 'Init'
        self.TimerCounter = 0
        self.ExitDummyFlag = 1
        #algoritmo para determinar quien empieza aleatoriamente
        self.Light0 = TrafficLight('0', 11)
        self.Light1 = TrafficLight('2', 29)
   
        self.FORCE_STATE_id0 = 0
        self.FORCE_STATE_id2 = 0
        self.DUMMY_STATE = 0
        self.LastLine = ""
        
    def hardware_config(self):
        GPIO.setmode(GPIO.BOARD)
        
        GPIO.setup(FORCE_LED_PIN,GPIO.OUT)
        GPIO.setup(BUTTON_0_INT_PIN,GPIO.IN)
        GPIO.setup(BUTTON_2_INT_PIN,GPIO.IN)
	
        GPIO.add_event_detect(BUTTON_0_INT_PIN,GPIO.FALLING)
        GPIO.add_event_callback(BUTTON_0_INT_PIN,self.buttonEventHandler)
	
        GPIO.add_event_detect(BUTTON_2_INT_PIN,GPIO.FALLING)
        GPIO.add_event_callback(BUTTON_2_INT_PIN,self.buttonEventHandler)
	
    # send message
    def sendMessage(self, message):
        try:
            l_StrExcecutionCall = "mosquitto_pub -h " + Pi_HOST + " -t \"" + TOPIC + "\" -m \"" + message + "\""
            l_StrProcessOutput = subprocess.Popen(l_StrExcecutionCall, stdout=subprocess.PIPE, shell=True)
        except:
            #pass
            print("PASS")
            
    # update flags log
    def updateFlags(self, flag):
        try:
            f =  open(logPath,'a') 
            f.write(str(flag)+"\n")
            f.close()
        except:
            #pass
            print("\n\nSEDN PASS\n\n")
    
    # read flags
    def readFlags(self):
        try:
            with open(logPath,'r') as f:
                lines = f.readlines()
                flags = lines[-1]
                flags = flags.rstrip('\n')
            print("\nFLAGS: "+ flags)
            
            if(self.LastLine != flags):
                self.LastLine = flags 
               
                if(flags == "000"):
                    self.FORCE_STATE_id0 = 0
                    self.FORCE_STATE_id2 = 0
                    #print("Exit Force Light state\n" )
                    GPIO.output(FORCE_LED_PIN,GPIO.LOW)
                    
                elif(flags == "010"):
                    print("\n--- Force Light 1 ---")
                    GPIO.output(FORCE_LED_PIN,GPIO.HIGH)
                    self.FORCE_STATE_id2 = 1
                    
                    if(self.Light1.mStatus == 'STOP'):
                        self.Light0.toggleTrafficLight()
                        self.Light1.toggleTrafficLight()
                    print('...')
                    
                elif(flags == "100"):                
                    print("\n--- Force Light 0 ---")
                    GPIO.output(FORCE_LED_PIN,GPIO.HIGH)
                    self.FORCE_STATE_id0 = 1 
                    
                    if(self.Light0.mStatus == 'STOP'):
                        self.Light1.toggleTrafficLight()
                        self.Light0.toggleTrafficLight()
                    print('...')
                
                elif(flags == "001"):
                    self.NextState = 'Dummy'
                    
                else:
                    pass
        except:
            #pass
            print("PASS")
        
    #generates the interrupt
    def buttonEventHandler(self,pin):
        flag = ""
        # Light 0 
        if(pin == BUTTON_0_INT_PIN): 
            if((self.FORCE_STATE_id0 == 0) and (self.FORCE_STATE_id2 == 0)):
                print("\n--- Force Light 0 ---")
                GPIO.output(FORCE_LED_PIN,GPIO.HIGH)
                self.FORCE_STATE_id0 = 1 
                
                self.Light0.mStatus = 'STOP'
                self.Light1.mStatus = 'GO'
                
                self.Light1.toggleTrafficLight()
                self.Light0.toggleTrafficLight()
                    
                #if(self.Light0.mStatus == 'STOP'):
                    #self.Light1.mStatus = 'GO'
                    #self.Light1.toggleTrafficLight()
                    #self.Light0.toggleTrafficLight()
                print('...')
                self.updateFlags("100")
                self.sendMessage("100")
        
            elif((self.FORCE_STATE_id0 == 0) and (self.FORCE_STATE_id2 == 1)):
                print("Can't Force Light 0, Light 1 is already forced\n..." )
            
            elif(self.FORCE_STATE_id0 == 1):
                print("Exit Force Light 0 state\n" )
                self.FORCE_STATE_id0 = 0
                GPIO.output(FORCE_LED_PIN,GPIO.LOW)
                self.updateFlags("000")
                self.sendMessage("000")
                
        # Light 1         
        else:
            if((self.FORCE_STATE_id2 == 0) and (self.FORCE_STATE_id0 == 0)):
                print("\n--- Force Light 1 ---")
                GPIO.output(FORCE_LED_PIN,GPIO.HIGH)
                self.FORCE_STATE_id2 = 1
                
                self.Light0.mStatus = 'GO'
                self.Light1.mStatus = 'STOP'
                self.Light0.toggleTrafficLight()
                self.Light1.toggleTrafficLight()
                    
                #if(self.Light1.mStatus == 'STOP'):
                    #self.Light0.mStatus = 'GO'
                    #self.Light0.toggleTrafficLight()
                    #self.Light1.toggleTrafficLight()
                print('...')
                self.updateFlags("010")
                self.sendMessage("010")
                
            elif((self.FORCE_STATE_id2 == 0) and (self.FORCE_STATE_id0 == 1)):
                print("Can't Force Light 1, Light 0 is already forced\n..." )
            
            elif(self.FORCE_STATE_id2 == 1):
                print("Exit Force Light 1 state\n" )
                self.FORCE_STATE_id2 = 0
                GPIO.output(FORCE_LED_PIN,GPIO.LOW)
                self.updateFlags("000")
                self.sendMessage("000")
        
        # Update Log
        #self.updateFlags(flag)
        
        # Send message
        #self.sendMessage(flag)

        ###
        time.sleep(1)
    
    def run(self):
        if((self.CurrentState == 'Init') and (self.FORCE_STATE_id0 == 0) and (self.FORCE_STATE_id2 == 0)):
            print('\n--- State: Init ---')
            self.TimerCounter = TIMEX   #starts with a random timeout
            RandomLight = random.randrange(2)
            print('GO ', RandomLight,'\n')
            if RandomLight:
                self.Light1.setStatus('STOP')
                self.Light0.setStatus('GO')
            else:
                self.Light0.setStatus('STOP')
                self.Light1.setStatus('GO')
                
            self.NextState = 'Idle'
            print('--- State: Idle ...')
            self.readFlags()
            
        elif((self.CurrentState == 'Idle') and (self.FORCE_STATE_id0 == 0) and (self.FORCE_STATE_id2 == 0)):
            #print('\n--- State: Idle ---')
            if(self.TimerCounter == 0):
                self.NextState = 'UpdateLights'
            else:
                self.NextState = 'Idle'
                time.sleep(1)
                self.TimerCounter = self.TimerCounter - 1
            self.readFlags()
            
        elif((self.CurrentState == 'UpdateLights') and (self.FORCE_STATE_id0 == 0) and (self.FORCE_STATE_id2 == 0)):
            print("--- State: UpdateLights ...")
            image_file = ''
            if(self.Light0.mStatus == 'GO' and self.Light1.mStatus == 'STOP'):
                image_file = self.Light1.mID + "cars.jpg"
                subprocess.call("fswebcam -d /dev/video" + self.Light1.mID + " -S0 " + image_file,shell=True) 
                
            elif(self.Light1.mStatus == 'GO' and self.Light0.mStatus == 'STOP'):
                image_file = self.Light0.mID + "cars.jpg"
                subprocess.call("fswebcam -d /dev/video" + self.Light0.mID + " -S0 " + image_file,shell=True)
            #print(image_file)
            CarsWaiting = self.ImageRecognition(image_file)
            print('Cars waiting: ' + str(CarsWaiting), '\n')
            if(CarsWaiting > 0):
                self.TimerCounter = CarsWaiting*TIME_PER_CAR
                self.NextState = 'Toggle'
                self.updateFlags("000")
                self.sendMessage("000")
            elif(CarsWaiting == 0): #Zero cars waiting
                self.TimerCounter = TIMEX
                self.NextState = 'Idle'
                self.updateFlags("000")
                self.sendMessage("000")
            else:
                self.NextState = 'Dummy'
            self.readFlags()
            
        elif((self.CurrentState == 'Toggle') and (self.FORCE_STATE_id0 == 0) and (self.FORCE_STATE_id2 == 0)):
            print('--- State: Toggle ...')
            # call toggle function
            if(self.Light1.mStatus == 'STOP'):
                self.Light0.toggleTrafficLight()
                self.Light1.toggleTrafficLight()
                
            elif(self.Light0.mStatus == 'STOP'):
                self.Light1.toggleTrafficLight()
                self.Light0.toggleTrafficLight()
            
            self.NextState = 'Idle'
            print('--- State: Idle ...')
            self.readFlags()
            
        elif((self.CurrentState == 'Dummy') and (self.FORCE_STATE_id0 == 0) and (self.FORCE_STATE_id2 == 0)):
            print('--- State: Dummy ...')
            if(self.Light0.mStatus == 'GO'):
                self.Light0.toggleTrafficLight()
                self.Light1.toggleTrafficLight()
            else:
                self.Light1.toggleTrafficLight()
                self.Light0.toggleTrafficLight()
            
            time.sleep(TIME_DUMMY)
            self.NextState = 'UpdateLights'
            
            # Update Log
            self.updateFlags("001")
        
            # Send message
            self.sendMessage("001")
            
            # Read Log
            self.readFlags()
            
        #elif(self.CurrentState == 'Reset'):
            #pass
            #self.readFlags()
        
        #FORCE state
        else:
            self.NextState = 'UpdateLights'
            self.readFlags()

        ##    
        self.CurrentState = self.NextState
    
    def ImageRecognition(self , image_file):
        IMAGE_FILE = image_file
        try:
            # Connect to the Google Cloud-ML Service
            credentials = GoogleCredentials.from_stream(CREDENTIALS_FILE)
            service = googleapiclient.discovery.build('vision', 'v1', credentials=credentials)

            # Read file and convert it to a base64 encoding
            with open(image_file, "rb") as f:
                image_data = f.read()
                encoded_image_data = b64encode(image_data).decode('UTF-8')

            # Create the request object for the Google Vision API
            batch_request = [{
                'image': {
                    'content': encoded_image_data
                },
                'features': [
                    {
                        'type': 'OBJECT_LOCALIZATION'
                    }
                ]
            }]
            request = service.images().annotate(body={'requests': batch_request})

            # Send the request to Google
            response = request.execute()
        
        except:
            return -1
        
        # Check for errors
        if 'error' in response:
            return -1

        else:
            try:
                labels = response['responses'][0]['localizedObjectAnnotations']

                counter= 0
                for label in labels:
                    tag = label['name']
                    if(re.search('Car',tag)):
                        counter = counter + 1 
                return counter
            except:
                return 0

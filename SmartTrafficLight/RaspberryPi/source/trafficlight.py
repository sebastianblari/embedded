import RPi.GPIO as GPIO
import time

RED_TRANSITION_TIME = 0.5
YELLOW_TRANSITION_TIME = 3
GPIO.setmode(GPIO.BOARD)
#GPIO.cleanup()

class TrafficLight:

    def __init__(self,pID,pPin):
        self.mID = pID
        self.mPin = pPin
        self.mRedLight = self.mPin
        self.mYellowLight = self.mPin + 2
        self.mGreenLight = self.mPin + 4

        GPIO.setup(self.mRedLight, GPIO.OUT)
        GPIO.setup(self.mYellowLight, GPIO.OUT)
        GPIO.setup(self.mGreenLight, GPIO.OUT)

    def setStatus(self,pStatus):
        self.mStatus = pStatus
        if (self.mStatus == 'GO'):
            GPIO.output(self.mRedLight, GPIO.LOW)
            GPIO.output(self.mYellowLight, GPIO.LOW)
            GPIO.output(self.mGreenLight, GPIO.HIGH)    
        elif(self.mStatus == 'STOP'):
            GPIO.output(self.mGreenLight, GPIO.LOW)
            GPIO.output(self.mYellowLight, GPIO.LOW)
            GPIO.output(self.mRedLight, GPIO.HIGH)

    def toggleTrafficLight(self):
        print(self.mID, ' ', self.mStatus)
        #if(self.mID == '0' and self.mStatus == 'GO'):
            #GPIO.output(self.mGreenLight, GPIO.LOW)
            #GPIO.output(self.mYellowLight, GPIO.HIGH)
        if(self.mStatus == 'GO'):
            GPIO.output(self.mGreenLight, GPIO.LOW)
            GPIO.output(self.mYellowLight, GPIO.HIGH)
            #print("yellow")
            time.sleep(YELLOW_TRANSITION_TIME)
            GPIO.output(self.mYellowLight, GPIO.LOW)
            GPIO.output(self.mRedLight, GPIO.HIGH)
            self.mStatus = 'STOP'
        elif (self.mStatus == 'STOP'):
            #time.sleep(YELLOW_TRANSITION_TIME)
            GPIO.output(self.mRedLight, GPIO.LOW)
            #GPIO.output(self.mYellowLight, GPIO.HIGH)
            time.sleep(RED_TRANSITION_TIME)
            #GPIO.output(self.mYellowLight, GPIO.LOW)
            GPIO.output(self.mGreenLight, GPIO.HIGH)
            self.mStatus = 'GO'

if __name__ == "__main__":
    trafficLightA = TrafficLight('A',11)
    trafficLightA.setStatus('GO')
    print(trafficLightA.mStatus) 
    time.sleep(5)
    trafficLightA.toggleTrafficLight()
    print(trafficLightA.mStatus)
    time.sleep(5)
    trafficLightA.toggleTrafficLight()
    print(trafficLightA.mStatus)
    time.sleep(5)
    GPIO.cleanup()


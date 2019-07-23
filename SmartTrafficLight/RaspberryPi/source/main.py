from trafficlightmanager import TrafficLightManager
import time
import RPi.GPIO as GPIO
import os

BUTTON_0_INT_PIN = 18
DEBUGG_LED_PIN = 32
#BUTTON_2_INT_PIN = 18
FORCE_STATE = 0
FORCE_STATE_ON = 0

def main():
	#absPath = os.path.abspath(__file__)
	#parentDir = os.path.dirname(os.path.abspath(__file__))
	#parentDir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
	#print(absPath)
	#print(parentDir)
	#print(dir)
	#logPath = os.path.join(parentDir,'flags.txt')
	#print(logPath)

	try:
		TrafficSystem = TrafficLightManager()
		TrafficSystem.hardware_config()
		TrafficSystem.readFlags()
		while(True):
			TrafficSystem.run()
	finally:
		GPIO.cleanup()
		TrafficSystem.updateFlags("000")
		TrafficSystem.sendMessage("000")

if __name__ == "__main__":main()

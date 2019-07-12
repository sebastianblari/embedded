#!usr/bin/env python 3

from django.http import JsonResponse
from django.http import HttpResponse
from django.shortcuts import render
from django.views.generic import View

#django rest framework
from rest_framework.views import APIView
from rest_framework.response import Response

##
import subprocess
import random 
import time
import os

DEVICESTATUS = {'LUX' : 1, 'TEMP' : 1}
#----------------------------------------------
class HomeView(View):
    def get(self, request, *args, **kwargs):
        return render(request, 'home.html', {})

#----------------------------------------------	        
def contact_view(request, *args, **kwargs):			
	contact_context = {
		"names_list": ["Dunia Barahona", "Sebastian Blanco", "Laura Rincón"],
		}
	return render(request, "contact.html", contact_context)

#----------------------------------------------	
def light_view(request):
	return render(request, "light.html", {})

#----------------------------------------------
def temperature_view(request):
	return render(request, "temperature.html", {})

#----------------------------------------------	
class PostStatus(APIView):
	authentication_classes = []
	permission_classes = []
	
	def post(self, request, format=None):
		sensor = request.data.get("sensor")
		status = request.POST.get("stat")
		status = int(status)
		
		print(str(sensor)+" sensor: "+str(status))
		
		#DEVICESTATUS = {'LUX' : 1, 'TEMP' : 1}
		DEVICESTATUS[sensor] = status+0
		print("button: "+str(DEVICESTATUS[sensor]))
		#send message logic goes here. Variable sensor identifies which sensor is it,
		#varable status: 0 is off and 1 is on
		
		data = {
			# "status": status,
		}
		
		return Response(data)
#----------------------------------------------
class GetValue(APIView):
	authentication_classes = []
	permission_classes = []
	
	def receiveC2DMessage(self, i_StrDeviceID):
		l_StrJSexcecutionCall = 'node receive_c2d.js ' + i_StrDeviceID
		l_StrProcessOutput = subprocess.Popen(l_StrJSexcecutionCall, stdout=subprocess.PIPE, shell=True)
		l_StrProcessOutput = str(l_StrProcessOutput.communicate()[0])
		l_StrProcessOutput = l_StrProcessOutput.split("\n")[0]
		l_StrProcessOutput = l_StrProcessOutput.split("'")[1]
		l_StrProcessOutput = l_StrProcessOutput.split("\\")[0]
			# l_StrProcessOutput = l_StrProcessOutput.split("-")[2:]
			# l_StrProcessOutput  = "-".join(l_StrProcessOutput)
			#print(l_StrProcessOutput)

		return l_StrProcessOutput

	def sendC2DMessage(self, i_StrResponse):
		print(i_StrResponse)
		l_StrTargetDeviceID = i_StrResponse.split('-')[1]
		l_StrSenderDeviceID = i_StrResponse.split('-')[0]
		l_StrDataValue = i_StrResponse.split('-')[2:]
		l_StrDataValue = "-".join(l_StrDataValue)
			
		#l_StrJSexcecutionCall = 'node send_c2d.js ' + l_StrTargetDeviceID + ' ' +l_StrSenderDeviceID + ' ' + l_StrDataValue
		print("mssg: "+str(DEVICESTATUS[l_StrTargetDeviceID]))
		l_StrJSexcecutionCall = 'node send_c2d.js ' + l_StrTargetDeviceID + ' ' +l_StrSenderDeviceID + ' ' + l_StrDataValue+'-'+str(DEVICESTATUS[l_StrTargetDeviceID])
			#print(l_StrJSexcecutionCall)
			# print(l_StrJSexcecutionCall)
			# print(datetime.datetime.now())
		os.system(l_StrJSexcecutionCall)
			
		return l_StrDataValue	
		
	def get(self, request, format=None):
		try:
			response = self.receiveC2DMessage('DataMonitor')
				# response = "DataMonitor-LUX-25-15:09:35.47798"
			self.sendC2DMessage(response)
		
			device = response.split("-")[1]
			value = int(response.split("-")[2])
			date = response.split("-")[3]
		
		except:
			device = '-'
			value = 0
		
			#print("response: "+device+" "+str(value))
		if(device=='LUX'):
			temp_value = 0
			light_value = value
		else:
			temp_value = value
			light_value = 0
		
		data = {
			"temp_value": temp_value,
			"light_value": light_value,
		}
		print('device: '+device+' light: '+str(light_value)+' temp '+str(temp_value))
		return Response(data)
#----------------------------------------------	
class GetValueX(APIView):
	authentication_classes = []
	permission_classes = []
	
	def get(self, request, format=None):
		command = "az iot device c2d-message receive -n greenhouseHub -d DataMonitor"
		p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
		message = str(p.communicate()[0])
		
		try:
			value = message.split('"data": "')[-1]
			value = value.split('"')[0]
			device = value
			value = value.split(':')[-1]
			value = int(value)
			device = device.split(':')[0]
		except:
			value = 0

		if(device=='LUX'):
			temp_value = 0
			light_value = value
		else:
			temp_value = value
			light_value = 0
		
		data = {
			"temp_value": temp_value,
			"light_value": light_value,
		}
		print('device: '+device+' light: '+str(light_value)+' temp '+str(temp_value))
		return Response(data)
#----------------------------------------------	




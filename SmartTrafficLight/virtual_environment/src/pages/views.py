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
import os

#
parentDir = os.path.dirname(os.path.abspath(__file__))
parentDir = os.path.dirname(parentDir)
parentDir = os.path.dirname(parentDir)
logPath = os.path.join(parentDir,'flags.txt')
HOST = "192.168.0.34"
#HOST = "192.168.0.29"
TOPIC = "stl/message"
	
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
class PostStatus(APIView):
	authentication_classes = []
	permission_classes = []
	
	def post(self, request, format=None):
		FL0_status = request.POST.get("FL0_stat")
		FL1_status = request.POST.get("FL1_stat")
		Dummy_status = request.POST.get("Dummy_stat")
		FLAGS = str(FL0_status) + str(FL1_status) + str(Dummy_status)
		
		#print(logPath)
		f =  open(logPath,'a') 
		f.write(str(FLAGS)+"\n")
		f.close()
		
		print("FLAGS: " + str(FLAGS)+"\n")
		
		l_StrExcecutionCall = "mosquitto_pub -h "+ HOST +" -t \""+ TOPIC +"\" -m \"" + FLAGS + "\""
		print(l_StrExcecutionCall)
		l_StrProcessOutput = subprocess.Popen(l_StrExcecutionCall, stdout=subprocess.PIPE, shell=True)
		print(l_StrProcessOutput)
					
		data = {
			# "status": status,
		}
		
		return Response(data)
#----------------------------------------------
class GetFlags(APIView):
	authentication_classes = []
	permission_classes = []
	
	def get(self, request, format=None):
		flags = "000"
		
		try:
			with open(logPath,'r') as f:
				lines = f.readlines()
				flags = lines[-1]
				flags = flags.rstrip('\n')
		except:
			pass
            
		data = {
			"received_flag_state": flags,
		}
		return Response(data)
		
#----------------------------------------------

from django.http import JsonResponse
from django.http import HttpResponse
from django.shortcuts import render
from django.views.generic import View

#django rest framework
from rest_framework.views import APIView
from rest_framework.response import Response

# Create your views here.
# def home_view(request, *args, **kwargs):
	# print(args, kwargs)
	# print(request.user)
	# #return HttpResponse("<h1>Hello World!</h>")
	# my_context = {
		# "my_text": "This is a random generated number: ",
		# "my_number": 123,
		# "my_list": [123, 424, 789]
	# }
	# return render(request, "home.html", my_context)

def contact_view(request, *args, **kwargs):
	contact_context = {
		"names_list": ["Dunia Barahona", "Sebastian Blanco", "Laura Rincón"]
		}
	return render(request, "contact.html", contact_context)
	
def index_view(request, *args, **kwargs):
    return render(request, "index.html", {})

#
class HomeView(View):
    def get(self, request, *args, **kwargs):
        return render(request, 'charts.html', {"customers": 10})
	
def get_data(request, *args, **kwargs):
	data = {
		"sales": 100,
		"customers": 10,
	}
	return JsonResponse(data) # http response

# django rest framework
class ChartData(APIView):
	authentication_classes = []
	permission_classes = []
    
	def get(self, request, format=None):
		# qs_count = User.objects.all().count()
		labels = ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange']
		default_items = [2, 12, 33, 22, 8, 2]
		default_items1 = [32, 14, 54, 8, 12, 2]
		data = {
		"labels": labels,
		"default": default_items,
		"default1": default_items1,
		}
		return Response(data)

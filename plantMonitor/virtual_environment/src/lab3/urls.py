"""lab3 URL Configuration"""
from django.contrib import admin
from django.urls import path

from pages.views import HomeView, contact_view, light_view, temperature_view, GetValue, PostStatus

urlpatterns = [
	path('', HomeView.as_view()),
    path('home/', HomeView.as_view()),
	path('contact', contact_view),
	path('light/', light_view),
	path('temperature/', temperature_view),
	path('api/temperature/data/', GetValue.as_view()),
	path('api/light/data/', GetValue.as_view()),  
	path('api/switch/', PostStatus.as_view()),  
]

"""lab3 URL Configuration"""
from django.contrib import admin
from django.urls import path

from pages.views import HomeView, contact_view, GetFlags, PostStatus

urlpatterns = [
	path('', HomeView.as_view()),
    path('home/', HomeView.as_view()),
	path('contact', contact_view),
	path('api/flags/data/', GetFlags.as_view()),
	path('api/updateflags/', PostStatus.as_view())
]

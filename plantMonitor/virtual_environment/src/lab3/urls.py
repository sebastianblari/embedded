"""lab3 URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path

from pages.views import HomeView, contact_view, get_data, ChartData, index_view

urlpatterns = [
	path('api/data/', get_data, name='api-data'),
	path('api/chart/data/', ChartData.as_view()),
    path('', HomeView.as_view()),
    path('home/', HomeView.as_view()),
    # path('home/', home_view, name='home'),
    path('contact/', contact_view),
    path('index/', index_view),
    path('admin/', admin.site.urls),
]

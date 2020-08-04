# -*- coding: utf-8 -*-
"""
Created on Sun Aug  2 01:25:41 2020

@author: kwphillips13
"""
from django.urls import include, path
from rest_framework import routers
from . import views

router = routers.DefaultRouter()
router.register(r'measurements', views.SpectrometermeasureViewSet)

# Wire up our API using automatic URL routing.
# Additionally, we include login URLs for the browsable API.
urlpatterns = [
    path('', include(router.urls)),
    path('api-auth/', include('rest_framework.urls', namespace='rest_framework'))
]
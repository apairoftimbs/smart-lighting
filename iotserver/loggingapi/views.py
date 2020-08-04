from django.shortcuts import render

# Create your views here.
from rest_framework import viewsets

from .serializers import SpectrometermeasureSerializer
from .models import Spectrometermeasure


class SpectrometermeasureViewSet(viewsets.ModelViewSet):
    queryset = Spectrometermeasure.objects.all().order_by('id')
    serializer_class = SpectrometermeasureSerializer
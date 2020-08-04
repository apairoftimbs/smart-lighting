# -*- coding: utf-8 -*-
"""
Created on Sun Aug  2 01:12:59 2020

@author: kwphillips13
"""
from rest_framework import serializers
from .models import Spectrometermeasure

class SpectrometermeasureSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = Spectrometermeasure
        fields = ('time', 'r', 'g', 'b')
        
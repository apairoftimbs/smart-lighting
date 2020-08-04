from django.db import models

# Create your models here.
class Spectrometermeasure(models.Model):
    time = models.DateTimeField()
    r = models.PositiveSmallIntegerField()
    g = models.PositiveSmallIntegerField()
    b = models.PositiveSmallIntegerField()
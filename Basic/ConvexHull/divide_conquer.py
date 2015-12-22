import random as rd
from shapely.geometry import Point as Pt

def ccw(p1, p2, p3):
	# ccw if > 0
	# collinear if ccw = 0
	# cw if < 0
	return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)

# def mergeCVHull(cv1, cv2):
	# assume that cv1 is to the left of cv2

	
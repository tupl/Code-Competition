import random as rd
from shapely.geometry import Point
from shapely.geometry.polygon import LinearRing


'''
	The algorithm follows the book Computational Geometry with Application (DeBerg)
	The purpose of 'basic' folder is to contribute to the understanding
		of basic algorithm with their implementation.

	Below is the implementation of convex hull, a basic algorithm, it follows
		the pseudocode in Computational Geometry with Application

	Suggestion:
		Implement our own ccw tester
'''

# Getting a list of points
# their x, y values range from 0 to 20
min = 0
max = 20

# rdUsage = rd.randint
rdUsage = rd.uniform

numPoints = 25
allPoints = [Point(rdUsage(min, max), rdUsage(min, max)) for i in range(numPoints)]

def prtPoly(ps):
	for _ in ps:
		print "(%f, %f)" % (_.x, _.y)

def cmpFunc(p1, p2):
	if p1.x < p2.x:
		return 1
	elif p1.x == p2.x:
		return 0
	else:
		return -1

allPoints.sort(cmp=cmpFunc, reverse=True)
n = len(allPoints)

cvHullUpper = [allPoints[0], allPoints[1]]

#Find the upper convex jull
for _ in range(2, n):
	_ = allPoints[_]
	while True:
		nCount = len(cvHullUpper)
		if nCount < 2:
			cvHullUpper.append(_)
			break
		top = nCount - 1
		begin = (cvHullUpper[top - 1].x, cvHullUpper[top - 1].y)
		middle = (cvHullUpper[top].x, cvHullUpper[top].y)
		end = (_.x, _.y)
		ring = LinearRing([begin, middle, end])
		if not ring.is_ccw: # if clock wise
			cvHullUpper.append(_)
			break
		else:
			cvHullUpper.pop() # take out one

cvHullLower = [allPoints[n - 1], allPoints[n - 2]]

#Find the lower convex hull
for _ in range(n - 3, -1, -1):
	_ = allPoints[_]
	while True:
		nCount = len(cvHullLower)
		if nCount < 2:
			cvHullLower.append(_)
			break
		top = nCount - 1
		begin = (cvHullLower[top - 1].x, cvHullLower[top - 1].y)
		middle = (cvHullLower[top].x, cvHullLower[top].y)
		end = (_.x, _.y)
		ring = LinearRing([begin, middle, end])
		if not ring.is_ccw: # if clock wise or right turn
			cvHullLower.append(_)
			break
		else:
			cvHullLower.pop() # take out one

# Remove last, first point in lower convex hull
cvHullLower.pop()
cvHullLower.pop(0)
cvHullUpper.extend(cvHullLower)

prtPoly(allPoints)
print
prtPoly(cvHullUpper)

# Implement matplotlib with scatter
import numpy as np
import matplotlib.pyplot as plt

xCoor = [_.x for _ in allPoints]
yCoor = [_.y for _ in allPoints]
plt.scatter(xCoor, yCoor, marker="x", color="red")
for i in range(len(cvHullUpper)):
	if i < len(cvHullUpper) - 1:
		fr = cvHullUpper[i]
		to = cvHullUpper[i + 1]
	else:
		fr = cvHullUpper[i]
		to = cvHullUpper[0]
	plt.plot([fr.x, to.x], [fr.y, to.y], 'k-')
plt.show()

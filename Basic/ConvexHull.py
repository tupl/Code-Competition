import random as rd
from shapely.geometry import Point
from shapely.geometry.polygon import LinearRing

# The algorithm follows the book Computational Geometry with Application (DeBerg)

# Getting a list of points
# their x, y values range from 0 to 20
min = 0
max = 20

# rdUsage = rd.uniform
rdUsage = rd.randint

numPoints = 15
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

prtPoly(allPoints)

allPoints.sort(cmp=cmpFunc, reverse=True)
n = len(allPoints)

cvHullUpper = [allPoints[0], allPoints[1]]

#Find the upper convex cvhull
for _ in range(2, n):
	nCount = len(cvHullUpper)
	if nCount < 2:
		cvHullUpper.append(_)
	else:
		top = nCount - 1
		ring = LinearRing([cvHullUpper[top - 1],
						   cvHullUpper[top], _])
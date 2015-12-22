import random as rd
from sortedcontainers import SortedListWithKey as SLWK
import heapq
class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __str__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"
    def __repr__(self):
        return str(self)
    def __cmp__(self, _):
        if self.x == _.x and self.y == _.y:
            return 0
        if self.y > _.y:
            return -1
        if self.y == _.y and self.x < _.x:
            return -1
        return 1

class Line(object):
    def __init__(self, p, q):
        self.p = p
        self.q = q
    def __str__(self):
        return str(self.p) + " - " + str(self.q)
    def __repr__(self):
        return str(self)

def orientation(p, q, r):
    # cw return 1
    # ccw return 2
    # collinear return 0
    val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if val == 0:
        return 0
    elif val > 0:
        return 1
    else:
        return 2

def intersect(l1, l2):
    p1 = l1.p
    q1 = l1.q
    p2 = l2.p
    q2 = l2.q

    def onSegment(p, q, r):
        if q.x <= max(p.x, r.x) and q.x >= min(p.x, r.x) and q.y <= max(p.y, r.y) and q.y >= min(p.y, r.y):
           return True
        return False
    
    o1 = orientation(p1, q1, p2);
    o2 = orientation(p1, q1, q2);
    o3 = orientation(p2, q2, p1);
    o4 = orientation(p2, q2, q1);
 
    if o1 != o2 and o3 != o4:
        return True
    if o1 == 0 and onSegment(p1, p2, q1): return True
    if o2 == 0 and onSegment(p1, q2, q1): return True
    if o3 == 0 and onSegment(p2, p1, q2): return True
    if o4 == 0 and onSegment(p2, q1, q2): return True
    return False

l1 = Line(Point(0, 0), Point(1.9, 1.9))
l2 = Line(Point(4, 0), Point(0, 4))

def endPoints(l):
    # This function should return top and bottom end points
    # we assume two endpoints are different
    p = l.p
    q = l.q
    if p.y > q.y:
        return p, q
    elif p.y < q.y:
        return q, p
    else:
        if p.x < q.x:
            return p, q
        else:
            return q, p

# finish event queue

class EventQueue(object):
    '''
        Basic operation requires for event queue
            push(obj)
            pop()
        obj need to be in the follwing form
            {
                key: 'our key'
                data: data goes together with this key
            }
    '''
    def __init__(self):
        self._hq = []
        self._dct = {}

    def __len__(self):
        return len(self._hq)

    def isEmpty(self):
        return len(self._hq) == 0

    def test(self, _):
        return _["key"] in self._dct

    def push(self, _):
        if _["key"] not in self._dct:
            heapq.heappush(self._hq, _["key"])
            self._dct[_["key"]] = _["data"]

    def pop(self):
        _ = heapq.heappop(self._hq)
        return {
            "key": _,
            "data": self._dct[_]
        }

    def __str__(self):
        return str(self._hq) + "\n" + str(self._dct)

    def __repr__(self):
        return str(self)

class StatusTree(object):
    pass

numLine = 10
min = 0
max = 40
lines = []
rdU = rd.uniform
for _ in range(numLine):
    p = Point(rdU(min, max), rdU(min, max))
    q = Point(rdU(min, max), rdU(min, max))
    l = Line(p, q)
    lines.append(l)

import numpy as np
import matplotlib.pyplot as plt

def draw(lines):
    for _ in lines:
        plt.plot([_.p.x, _.q.x], [_.p.y, _.q.y], 'k-')
    plt.show()

def findIntersection(lines):

    eq = EventQueue()

    def putEndPoints():
        '''
            This function puts all the endpoints in
                the event queue
        '''
        for _ in lines:
            p, q = endPoints(_)
            eq.push({
                    "key": p,
                    "data": {
                        "type": "upper",
                        "line": _
                    }
                })
            eq.push({
                    "key": q,
                    "data": {
                        "type": "lower",
                        "line": _
                    }
                })

    def handleEventPoint(_):
        pass

    putEndPoints()

    while not eq.isEmpty():
        next = eq.pop()

findIntersection(lines)

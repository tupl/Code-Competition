class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __str__(self):
        return "(" + str(self.x) + "," + str(self.y) + ")"
    def __repr__(self):
        return str(self)

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


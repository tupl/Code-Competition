class Node:
	def __init__(self, value, left, right, parent):
		self.value = value
		self.left = left
		self.right = right
		self.parent = parent
		self.m = None
		if value is not None:
			self.m =
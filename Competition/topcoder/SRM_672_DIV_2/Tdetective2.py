'''
	Problem Statement
	
	There is a group of n people. The people are numbered 0 through n-1. Person number 0 is the principal witness. Exactly one of people 1 through n-1 is the killer. In addition to the n people there is a single detective who wants to find the killer.

	Whenever the detective talks to a person, he can determine with absolute certainty whether the person is the killer or not. Thus, all he needs to do is to talk to all the people in some order and he will certainly find the killer. However, the time needed to find the killer depends on the order in which the detective talks to the suspects.

	During the investigation the detective maintains a list of his suspicion levels: for each person between 0 and n-1, inclusive, the suspicion level of that person is an integer between 0 and 9, inclusive. (The larger the number, the more the detective currently suspects the person.) Initially, the suspicion levels of all n suspects are equal to 0. At the beginning of investigation, the detective will interview the principal witness (person 0) and he will use the information he receives to update his suspicion levels. (The way this works is explained in detail below.)

	The investigation then proceeds in rounds. Each round of investigation looks as follows: First, the detective must choose whom to interview next. Then, the detective interviews the chosen person. If that person is the killer, the investigation is over. Otherwise, the detective will receive new information from the witness and he will use it to update his suspicion levels.

	When choosing whom to interview next, the detective decides as follows:
	He must choose a person he did not interview yet.
	Among those, he must choose a person with the highest suspicion level.
	Among those, he may choose any person.
	You are given a String[] s with n elements, each with n characters. Each of those characters is a digit between 0 and 9, inclusive. The string s[i] is the information received when the detective interviews person i and that person is not the killer. For each j, the digit s[i][j] is the level to which person i and person j dislike each other. (Note that the information in s is symmetric: s[i][j] always equals s[j][i].) The more person i dislikes person j, the more incriminating evidence against person j will be presented by person i to the detective. When the detective receives this information, he will update the suspicion level of person j from its current value to the maximum of its current value and the value s[i][j]. (For example, after interviewing person 0 the detective's current suspicion level of each person j is increased from 0 to s[0][j].)

	For each k between 1 and n-1, we are now going to solve the following problem: Assume person k is the killer. What is the smallest number of rounds of interviewing (NOT counting the initial interview with person 0) the detective needs to interview in order to find the killer? Let's denote the answer to this question as ans[k]. In other words, ans[k] is the smallest value X such that there is a valid sequence of X people the detective could interview after person 0 (according to the above rules) that ends with person k.

	Compute the value ans[k] for each valid k. Return the sum of k*ans[k] over all valid k. (For example, if n=4, return the value 1*ans[1] + 2*ans[2] + 3*ans[3].)

	 
	Definition
	    	
	Class:	Tdetectived2
	Method:	reveal
	Parameters:	String[]
	Returns:	int
	Method signature:	int reveal(String[] s)
	(be sure your method is public)
	    
	 
	Constraints
	-	s will contain n elements.
	-	n will be between 2 and 18, inclusive.
	-	Each element in s will contain exactly n characters.
	-	Each character in s will be between '0' and '9', inclusive.
	-	s will be symmetric, so s[i][j] will be equal to s[j][i].
	-	Diagonal characters are not significant, so s[i][i] will be equal to '0'.
	 
	Examples
	0)	
	    	
	{"000","000","000"}
	Returns: 3
	Nobody knows anything about anybody else.

	If the killer is person 1, the smallest number of rounds is ans[1]=1: after the initial interview of person 0 there will be a single round in which the detective interviews person 1.

	If the killer is person 2, the smallest number of rounds is again ans[1]=1: after interviewing person 0 both other people have the same suspicion level, so the detective can also choose person 2 in the first round.

	The correct return value is 1*1 + 2*1 = 3.

	1)	
	    	
	{"0224","2011","2104","4140"}
	Returns: 10
	After the initial interview the detective will always choose person 3 in the first round. If person 3 is not the killer, the detective will receive new information that will increase the suspicion level of person 2. Therefore, in the second round the detective will interview person 2. If person 2 is also not the killer, there will be a third round in which the detective interviews the last remaining person: person 1.

	Hence, the answers are ans[1]=3, ans[2]=2, and ans[3]=1. Therefore, the correct return value is 1*3 + 2*2 + 3*1 = 10.

	2)	
	    	
	{"0886","8086","8801","6610"}
	Returns: 12
	3)	
	    	
	{"064675511","603525154","430262731","652030511","726302420","552020464","517544052","153126500","141104200"}
	Returns: 170
	4)	
	    	
	{"0313131","3030020","1301132","3010031","1010003","3233003","1021330"}
	Returns: 37
	This problem statement is the exclusive and proprietary property of TopCoder, Inc. Any unauthorized use or reproduction of this information without the prior written consent of TopCoder, Inc. is strictly prohibited. (c)2010, TopCoder, Inc. All rights reserved.
'''
class Tdetectived2:
	def __init__(self):
		pass

	def reveal(self, s):
		self.n = len(s)
		self.s = s
		self.k = [100 for i in range(self.n)]
		self.c = [0 for i in range(self.n)] # suspicious level
		self.o = [0 for i in range(self.n)] # order
		self.visited = [False for i in range(self.n)]
		self.compute(0, 0) # interview person 0 for round 0
		return self.calculate()

	def calculate(self):
		mySum = 0
		for i in range(1, self.n):
			mySum += i * self.k[i]
		return mySum

	def findList(self):
		# find maximum between not interview person
		val = 0
		for i in range(1, self.n):
			if not self.visited[i]:
				val = max(val, self.c[i])

		rList = []
		for i, _ in enumerate(self.c):
			if _ == val and not self.visited[i]:
				# if same value as maximum
				# and we haven't visited that person
				rList.append(i)
		return rList

	def update(self, i):
		data = self.s[i]
		for j in range(1, self.n):
			self.c[j] = max(self.c[j], int(data[j]))

	def updateBest(self):
		for i, _ in enumerate(self.k):
			self.k[i] = min(_, self.o[i])

	def compute(self, r, i):
		# if this is 'round' r and we visit person i
		self.o[i] = r
		if r == self.n - 1:
			print self.o
			self.updateBest()
		else:
			self.visited[i] = True
			saved = self.c[:]
			self.update(i) # update with new su
			# print saved
			# print self.c
			# What list we should visit next

			propose_list = self.findList()
			# print propose_list
			for _ in propose_list:
				self.compute(r + 1, _) # next round visit _
			self.c = saved
			self.visited[i] = False
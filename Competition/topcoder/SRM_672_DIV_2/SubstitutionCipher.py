'''
	Problem Statement
	    	
	Recently you learned about substitution ciphers. This problem is about such a cipher. All strings in this problem (both encrypted and decrypted ones) will consist of only uppercase English letters ('A'-'Z').

	When encrypting text using a substitution cipher we choose a substitution table: a permutation p of the alphabet. In other words, for each letter x in the alphabet we choose a letter p(x) that will be used to encode x. This encoding must be one-to-one: if x and y are two different letters, the letters p(x) and p(y) chosen to encode them must also be different.

	You decided to try it out: you chose some specific substitution table and used it to encrypt some strings.

	At some later point in time you found an encrypted string y. You believe it was encrypted using the substitution table you once had. Sadly, you do not remember the substitution table anymore. The only thing you remember about it is that when you used it to encrypt the string a you got the string b. Is this information sufficient to decrypt y?

	You are given the Strings a, b, and y. If it is possible to decrypt the string y, return the original string x that was encrypted into y. (More precisely: If there is exactly one string x such that the same permutation table can be used to encrypt a into b and to encrypt x into y, return x.) Otherwise, return an empty string.

	 
	Definition
	    	
	Class:	SubstitutionCipher
	Method:	decode
	Parameters:	String, String, String
	Returns:	String
	Method signature:	String decode(String a, String b, String y)
	(be sure your method is public)
	    
	 
	Constraints
	-	a will contain between 1 and 50 characters, inclusive.
	-	a and b will contain the same number of characters.
	-	It is guaranteed that b can be obtained from a by applying some substitution cipher.
	-	y will contain between 1 and 50 characters, inclusive.
	-	Each character in a, b, and y will be an uppercase English letter ('A'-'Z').
	 
	Examples
	0)	
	    	
	"CAT"
	"DOG"
	"GOD"
	Returns: "TAC"
	By observing a and b we see that each C is encoded as a D, each A is encoded as an O, and each T is encoded as a G. Formally, we have p(C)=D, p(A)=O, and p(T)=G. This information is sufficient to determine that the encrypted string "GOD" must have been created from the plaintext string "TAC".
	1)	
	    	
	"BANANA"
	"METETE"
	"TEMP"
	Returns: ""
	We do not know which character was encoded as the letter P. Thus, there are multiple possiblities for the string x. For example, x can be "NABC" or "NABD".
	2)	
	    	
	"THEQUICKBROWNFOXJUMPSOVERTHELAZYHOG"
	"UIFRVJDLCSPXOGPYKVNQTPWFSUIFMBAZIPH"
	"DIDYOUNOTICESKIPPEDLETTER"
	Returns: "CHCXNTMNSHBDRJHOODCKDSSDQ"
	This test case is tricky. Note that the letter E does occur in y but it does not occur in b. However, in this specific case we can still determine that the letter E must be decrypted to a D.
'''

class SubstitutionCipher:
	def __init__(self):
		self.d = {}
	def _decode(self, y):
		curr = ""
		for _ in y:
			if _ not in self.d:
				return ""
			else:
				curr += self.d[_]
		return curr
	
	def decode(self, a, b, y):
		self.mapping(a, b)
		return self._decode(y)
		
	def mapping(self, a, b):
		N = 26
		for i, _ in enumerate(b):
			self.d[_] = a[i]
		tmp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		
		# all character appears in a
		extra = {}
		for _ in a:
			extra[_] = 0
		
		if len(self.d) == N - 1: # Len is 25
			# find missing character
			miss_b = ""
			for i in range(N):
				if tmp[i] not in self.d:
					miss_b = tmp[i]
					break
			miss_a = ""
			for i in range(N):
				if tmp[i] not in extra:
					miss_a = tmp[i]
					break
			self.d[miss_b] = miss_a
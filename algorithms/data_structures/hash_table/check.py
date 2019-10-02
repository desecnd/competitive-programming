def check(s, A, m): 
	power = len(s) - 1
	alfa = A + 1
	polyHash = 0
	for i in range(len(s)):
		digit = ord(s[i]) - ord('a') + 1
		polyHash += ( alfa ** power * digit ) % m
		power -= 1
	return (polyHash % m)
		
			
		
	
while True:
	s = input()
	print("H({}) -> {}".format(s, check(s, 26, 10007)))

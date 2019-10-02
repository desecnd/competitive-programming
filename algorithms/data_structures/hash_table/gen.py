from random import choice as rc
n = 100 
length = 5
for i in range(n):
	option = rc(["del", "add", "find"])
	x = ''.join([ rc('abcdef') for i in range(length) ])
	print (option, x)

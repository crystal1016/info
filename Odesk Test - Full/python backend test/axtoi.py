#################   first task   #################

def simulater():
    gateway = ['0','0','0','0','0','0','0','0'] #the state of 8 boxes, 0:close, 1 : open
    prim_num = [0,1,2,3,5,7]
    next_gateway = gateway
    flag = 1
    while (flag<10):
        for j in range(1,7): # repeat this operation to every first~8th box in the hallway
            for i in range(1,8, j):
                # first item
                if (i+1 in prim_num):
                    gateway[i-1] = gateway[i]
                elif(i-1 in prim_num):
                    gateway[i-1] = gateway[i+1]
                # second item
                if (not i+1 in prim_num)&(not i-1 in prim_num):
                    if gateway[i-1] == '0':
                        gateway[i-1] = '1'
                    else:
                        gateway[i-1] = '0'

        if next_gateway == gateway:
            return gateway.count('1') #return counts that boxes	are	open
        flag = flag + 1

print(simulater())

#result 3, time : 1hr

#################   2nd task   #################

def axtoi(x):
    arr = ['0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f']
    s = 0
    i = 0
    x = x[::-1]
    for str in x:
        try:
            k = arr.index(str) # get string's location on array
        except:
            return "bad input value"
        s += k*(16**i)
        i +=1
    # Return the results as a decimal value
    return s

print axtoi('a11f')

#result 41247 time : 20mins


#################   4th task   #################

def almostLargest(arr):
    count = 0
    m1 = m2 = float('-inf') # initialize
    for x in arr:
        count += 1
        if x > m2:
            if x >= m1:
                m1, m2 = x, m1
            else:
                m2 = x
    return m2 if count >= 2 else None

print(almostLargest([-1,-2,-3,-4,-5]))

#result -2 time : 10mins

#################   5th task   #################

print str(max(x * y
    for x in xrange(100,1000)
        for y in xrange(100,1000)
            if str(x*y) == str(x*y)[::-1]))

#result 906609 time : 10mins
#################   3rd task   #################

class LimitedClass(object):

	def __init__(self):
		self._num = 0

	def stooge(self):
		if self._num < 7:
			self.super()
			self._num += 1
		else:
			raise Exception("ERROR: too many instances")

# time : 20mins



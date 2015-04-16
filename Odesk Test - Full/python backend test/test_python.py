L = [[[1, 2, 3], [4, 5]], 6]
import re

def Flatten(L):
    a = str(L)
    b,crap = re.subn(r'[\[,\]]', ' ', a)
    c = b.split()
    d = [int(x) for x in c]

    return(d)
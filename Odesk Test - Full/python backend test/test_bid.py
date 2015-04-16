# l =  "1"
# l =  "car truck bus"
# l =  "8 4 6 1 -2 9 5"
l =  "car truck 8 4 bus 6 1"

lint, lalph, lnew, c,d   = [],[],[],0,0
for i in l.split():
    if ord(i[0]) >96 and  ord(i[0]) < 123:
        lalph.append(i)
    else:
        lint.append(int(i))

lalph.sort()
lint.sort()
for i in l.split():
    if ord(i[0]) >96 and  ord(i[0]) < 123:
        lnew.append(lalph[c])
        c+=1
    else:
        lnew.append(lint[d])
        d+=1

print (l)
print (" ".join(map(str, (lnew))))

def checkPassword(password):
    import re
    password = raw_string(password)
    print(password)
    print (len([c for c in password if c.isdigit()]))
    if len(password) > 6:
        if len([c for c in password if c.isdigit()]) > 3:
            return False
        elif re.match("^[a-zA-Z0-9+$#/]*$", password):
            return True
        else:
            return False
    else:
        return False

def raw_string(s):
    if isinstance(s, str):
        s = s.encode('string-escape')
    elif isinstance(s, unicode):
        s = s.encode('unicode-escape')
    return s

print checkPassword("poP$o00\vs")
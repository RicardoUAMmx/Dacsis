
def lineHandler(s,sep=',',quote='"'):
    result = []
    sub = []
    n = len(s)
    i = 0
    while i < n:
        while s[i] != sep: 
            if s[i] == quote:
                i += 1
                while s[i] != quote:
                    sub.append(s[i])
                    i += 1

            else:
                sub.append(s[i])

            i += 1
            if i == n:
                break

        result.append(''.join(sub))
        sub = []
        i += 1

    return result

def lineColumn(file, n=[], columns=[]):
    result = []
    line = []
    i = 0
    with open(file, 'r') as f:
        s = f.readline().strip()
        while s:
            if i in n:
                if columns != []:
                    for c in columns:
                        line.append(lineHandler(s)[c])
                    result.append(line)
                else:
                    line = lineHandler(s)
                    result.append(line)

            line = []
            s = f.readline().strip()
            i += 1
    return result



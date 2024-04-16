
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

def printLine(file, n):
    i = 0
    with open(file, 'r') as f:
        while True:
            s = f.readline().strip()
            if i == n:
                print(f'Line {i} Contents: --------')
                print('\n'.join(lineHandler(s)))
                print('---------------------------')

            i += 1
            if not s:
                break

if __name__ == '__main__':
    csvfile = 'data/openings.csv'
    printLine(csvfile, 203)


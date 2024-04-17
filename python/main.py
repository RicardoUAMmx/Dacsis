
import linehandler as lh

if __name__ == '__main__':
    csvfile = 'data/openings.csv'
    lines = range(1884)
    n = len(lines)
    fullresult = lh.lineColumn(csvfile, lines,[1,2])
    repeated = []
    unique = []
    accrepeat = []

    i = 0
    while i < n-1:
        i += 1
        j = i-1
        if fullresult[i][0] == fullresult[j][0]:
            acc = 0
            unique.append(fullresult[j][0])
            repeated.append(fullresult[j][0])
            while fullresult[i][0] == fullresult[j][0] and i < n:
                i += 1
                acc += 1
            accrepeat.append(acc)
        else:
            unique.append(fullresult[j][0])
        
    for i in range(len(repeated)):
        print(f'{repeated[i]}: {accrepeat[i]}')

    print(f'Unique (values without repetition): {len(unique)}')
    print(f'Repeated values: {len(repeated)}')
    print(f'Accumulated (Sum of each repeteated value): {sum(accrepeat)}')
    print(f'From: {len(unique) + sum(accrepeat)}')



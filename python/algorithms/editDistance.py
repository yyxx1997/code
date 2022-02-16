def edit_distance(a, b):
    la, lb = len(a), len(b)
    edit = [list([None]*(lb+1)) for _ in range(la+1)]
    edit[0] = [i for i in range(lb+1)]
    for j in range(la+1):
        edit[j][0] = j
    for i in range(1, la+1):
        for j in range(1, lb+1):
            if a[i-1] == b[j-1]:
                edit[i][j] = edit[i-1][j-1]
            else:
                edit[i][j] = min(edit[i-1][j-1]+1, edit[i-1]
                                 [j]+1, edit[i][j-1]+1)
    return edit[la][lb]


if __name__ == "__main__":
    a = "coffee"
    b = "cafe"
    dis = edit_distance(a, b)
    print(dis)

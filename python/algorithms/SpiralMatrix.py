def spiral_print(ma):
    grid = len(ma)
    r, c = 0, -1
    count = grid**2
    while count:
        nexts = [(1, "→")]*(grid)+[(1, "↓")]*(grid-1) + \
            [(1, "←")]*(grid-1)+[(1, "↑")]*(grid-2)
        for command in nexts:
            if count <= 0:
                break
            step, direct = command[0], command[1]
            if direct == "↑":
                r -= step
            elif direct == "↓":
                r += step
            elif direct == "←":
                c -= step
            else:
                c += step
            count -= step
            print(ma[r][c])
        grid -= 2


if __name__ == "__main__":
    matrix1 = [
        [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9]
    ]
    grid = 6
    count = grid
    matrix = []
    temp = []
    for i in range(1, grid**2+1):
        temp.append(i)
        count -= 1
        if count == 0:
            print(temp)
            matrix.append(list(temp))
            count = grid
            temp = []

    spiral_print(matrix)

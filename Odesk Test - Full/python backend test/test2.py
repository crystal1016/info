def matrix_circles(matrix):
    N = len(matrix)
    M = len(matrix[0])
    output = []
    k = 0
    for i in range(k, N-k):
        for j in range(k, M-k):
            output.append(matrix[i][j])

        for j in range(k+1, N-k):
            if (M-k)> k:
                output.append(matrix[j][M-k-1])

        for j in range(k+1, M-k):
            if (N-k-1)> k:
                output.append(matrix[N-k-1][M-j-1])

        for j in range(k+1, N-k-1):
            if (M-k)> k:
                output.append(matrix[N-j-1][k])
        k = k + 1
    return output

matrix = [(1, 2, 3, 4), (5, 6, 7, 8), (9, 10, 11, 12), (13, 14, 15, 16), (17, 18, 19, 20), (21, 22, 23, 24)]

print matrix_circles(matrix)

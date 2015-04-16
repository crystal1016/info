def find_the_way(btree, A, B):
    K = 0
    for x in btree:
        L = 0
        for btree_node in x:
            if btree_node == A:
                A_posi_i = K
                A_posi_j = L
            if btree_node == B:
                B_posi_i = K
                B_posi_j = L
            L = L + 1
        K = K + 1
    try:
        A_posi_i
        B_posi_i
    except:
        return "Bad input data"
    list_A = []
    A_tree =  A_posi_j
    for i in range(A_posi_i-1, -1, -1):
        A_tree = A_tree/2
        list_A.append(btree[i][A_tree])
        B_tree = B_posi_j
        list_B = []
        for j in range(B_posi_i-1, -1, -1):
            B_tree = B_tree/2
            if (i == j)and (A_tree == B_tree):
                result = list_A + list_B[::-1]
                return result
            list_B.append(btree[j][B_tree])
btree = [(1,), (2,3), (4,5,6,7), (8, 9,10,11,12,13,14,15)]
A = 12
B = 13
print(find_the_way(btree, A, B))

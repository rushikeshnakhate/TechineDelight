def minIncrementForUnique(v):
    v.sort()
    i = 1
    result = 0
    # 1, 1, 1, 8, 9
    while i < len(v):
        if v[i] <= v[i - 1]:
            a = v[i - 1] + 1
            result += a - v[i]
            v[i] = a
        i += 1
    print(result)


if __name__ == "__main__":
    v = [1, 1, 2]
    minIncrementForUnique(v)

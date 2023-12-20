def isFibonacci(n):
    a = 0
    a2 = 1
    b = 1
    while b<n:
        a = a2
        a2 = b
        b= a + a2

    return b <= n

def isSquare(n):
    i = 1
    while i*i < n:
        i += 1
    return i*i <= n

def main():
    print(isFibonacci(144))
    print(isFibonacci(233))
    print(isFibonacci(377))
    print(isFibonacci(610))
    print(isFibonacci(987))

    print(isSquare(100))
    print(isSquare(121))
    print(isSquare(144))
    print(isSquare(169))
    print(isSquare(196))
    

if __name__ == "__main__":
    main()
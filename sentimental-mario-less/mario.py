import cs50


def main():
    while True:
        n = cs50.get_int("Height? : ")
        if n > 0 and n <= 8:
            break
    pyramid(n)


def pyramid(n):
    total = n
    for x in range(total):
        print(" " * (n-1) + "#"*(x+1))
        n -= 1


main()

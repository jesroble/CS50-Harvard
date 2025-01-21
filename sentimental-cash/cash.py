import cs50


def main():
    while True:
        n = cs50.get_float("change: ")
        if n >= 0:
            break
    cash(n)


def cash(n):
    change = round(n * 100)
    coins = 0
    while (change > 0):
        if change >= 25:
            change -= 25
            coins += 1
        elif change >= 10:
            change -= 10
            coins += 1
        elif change >= 5:
            change -= 5
            coins += 1
        elif change >= 1:
            change -= 1
            coins += 1
    print(coins)


main()

import cs50


def main():
    while True:
        card = cs50.get_int("Number: ")
        if card > 0:
            break
    leng = len(str(card))
    start = get_start(card)
    luhn_algorithm(card)
    get_card(card, leng, int(start))


def get_start(card):
    nbr = card
    start = str(nbr)[:2]
    return start


def luhn_algorithm(card):
    nbr = str(card)
    sum = 0
    second = False

    for digit in reversed(nbr):
        digit = int(digit)
        if second:
            digit = digit * 2
            if digit > 9:
                digit -= 9
        sum += digit
        second = not second
    if not sum % 10 == 0:
        print("INVALID")
        exit()


def get_card(card, leng, start):

    if leng == 15 and (start == 34 or start == 37):
        print("AMEX")
    elif leng == 16 and (start >= 51 and start <= 55):
        print("MASTERCARD")
    elif (leng == 13 and (start > 39 and start < 50)) or (leng == 16 and (start > 39 and start < 50)):
        print("VISA")
    else:
        print("INVALID")


main()

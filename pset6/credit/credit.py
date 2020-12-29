from cs50 import get_int

cc = get_int("Number: ")

# get number of digits
digits = 1
ccDigits = cc

while ccDigits / 10 > 1:
    digits += 1
    ccDigits /= 10

# check sum of even digits
evenSum = 0
for i in range(1, digits, 2):
    n1 = int(cc / pow(10, i))
    n2 = int(n1 % 10 * 2)
    while (n2 > 9):
        n2 = int(n2 % 10 + n2 / 10)
    evenSum += int(n2)

# check sum of odd digits
oddSum = 0
for j in range(0, digits, 2):
    j1 = int(cc / pow(10, j))
    j2 = int(j1 % 10)
    oddSum += int(j2)

# total
totalSum = evenSum + oddSum

if totalSum % 10 != 0:
    print("INVALID")

else:
    amex = int(cc / pow(10, 13))
    mastercard = int(cc / pow(10, 14))
    visa1 = int(cc / pow(10, 12))
    visa2 = int(cc / pow(10, 15))

    if digits == 15 and (amex == 34 or amex == 37):
        print("AMEX")

    elif digits == 16 and (51 <= mastercard <= 55):
        print("MASTERCARD")

    elif (digits == 13 and visa1 == 4) or (digits == 16 and visa2 == 4):
        print("VISA")

    else:
        print("INVALID")

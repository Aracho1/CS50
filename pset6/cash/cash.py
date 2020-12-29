while True:
    try:
        dollars = float(input("Cash owed: "))

        if dollars > 0:
            cents = dollars * 100
            coins = 0

            while cents >= 25:
                cents -= 25
                coins += 1

            while 10 <= cents < 25:
                cents -= 10
                coins += 1

            while 5 <= cents < 25 and cents < 10:
                cents -= 5
                coins += 1

            while 1 <= cents < 25 and cents < 10 and cents < 5:
                cents -= 1
                coins += 1

            print(coins)

            break

        else:
            continue

    except ValueError:
        continue
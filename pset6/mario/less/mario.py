while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            for i in range(0, height, 1):
                print(" " * (height - 1 - i), end="")
                print("#" * (i + 1))
            break
        else:
            continue
    except ValueError:
        continue


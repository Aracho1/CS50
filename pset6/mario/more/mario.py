while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            for i in range(0, height, 1):
                print(" " * (height - 1 - i), end="")
                print("#" * (i + 1), end="")
                print(" " * 2, end="")
                print("#" * (i + 1), end="")
                print("\n", end="")
            break
        else:
            continue
    except ValueError:
        continue
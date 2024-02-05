# TODO
from cs50 import get_int

# Force the user to enter required integer
while True:
    times = get_int("Enter an integer for mario pyramid height: ")
    if times <= 0 or times > 8:
        print("Wrong input")
    elif times >= 1 or times <= 8:
        break

for i in range(1, times + 1):
    # print the space
    print(" " * (times - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i, end="")
    print()
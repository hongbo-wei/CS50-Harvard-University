# TODO

numbers = input("Number: ")
card_numbers = [n for n in reversed(numbers)]

# Luhn's Algorithm
sum = 0
for number in card_numbers[1::2]:
    adding = int(number) * 2
    if adding >= 10:
        adding_0 = 1
        adding_1 = adding - 10
        sum += adding_0 + adding_1

    else:
        sum += adding

for number in card_numbers[::2]:
    sum += int(number)

# If  the total modulo 10 is congruent to 0, the number is valid!
if sum % 10 == 0:
    prefix = int(card_numbers[-1] + card_numbers[-2])

    # Store a prefix for different kinds of credit card
    amex_prefix = [34, 37]
    mastercard_prefix = [51, 52, 53, 54, 55]
    visa_prefix = [4]

    if len(card_numbers) == 15 and prefix in amex_prefix:
        print("AMEX")

    elif len(card_numbers) == 16 and prefix in mastercard_prefix:
        print("MASTERCARD")

    # Visa card starts with 4, so we only check the first number of input card numbers
    elif (len(card_numbers) == 13 or len(card_numbers) == 16) and int(prefix / 10) in visa_prefix:
        print("VISA")

    else:
        print("INVALID")

else:
    print("INVALID")
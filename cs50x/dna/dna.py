import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txtp")
        return

    # TODO: Read database file into a variable
    dna_list = []
    with open(sys.argv[1], 'r') as database_file:
        dna_database = csv.reader(database_file)
        for row in dna_database:
            dna_list.append(row)

    # TODO: Read DNA sequence file into a variable
    sequence_file = open(sys.argv[2], 'r')
    dna_sequence = sequence_file.read()
    sequence_file.close()

    # TODO: Find longest match of each STR in DNA sequence
    # Store the dna subsequence from .csv into a list to iterate
    dna_subsequences = dna_list[0][1:]
    sequence_count = []

    for subsequence in dna_subsequences:
        sequence_count.append(str(longest_match(dna_sequence, subsequence)))

    # TODO: Check database for matching profiles
    for person in dna_list[1:]:
        if person[1:] == sequence_count:
            print(person[0])
            break
    # If no body matches
    if person[1:] != sequence_count:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

import csv
import sys


def main():

    # Ensure correct command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Read database CSV inside a dictionary and the header of the CSV file inside a variable
    database = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)

        header = reader.fieldnames

        for line in reader:
            database.append(line)

    header.remove("name")

    # Read sequence TXT inside a variable
    with open(sys.argv[2]) as f:
        dna_sequence = f.read()

    # Store inside str_amount the longest str match inside the sequence for each STR
    str_amount = {}
    for i in range(len(header)):
        str_amount[header[i]] = longest_match(dna_sequence, header[i])

    # Print result, if anybody matchs the sequence, print their name, else print "No Match"
    print(find_carrier(database, str_amount))

    return


def find_carrier(database, str_amount):

    # For each person inside the database, compares their STR to the sequence, if equal return
    # their name. If nobody inside the database corresponds to the sequence, return "No Match".
    for person in database:
        str_counter = 0
        for str in str_amount:
            if int(person[str]) == str_amount[str]:
                str_counter += 1
                if str_counter == len(str_amount):
                    return person["name"]
            else:
                break

    return "No match"


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

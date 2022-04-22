from cs50 import get_string
import re


def main():

    # Get user input
    input = get_string("Text: ")

    # Get amount of setences from the input
    setences = len(re.findall('[.!?]', input))

    # Get amount of words from the input
    words = (len(re.findall(' ', input))) + 1

    # Get amount of letters from the input
    letters = 0
    for char in input:
        if str.isalpha(char):
            letters += 1

    # Get the average amount of letters per 100 words
    letters_100 = round((letters / words) * 100, 2)

    # Get the average amount of setences per 100 words
    setences_100 = round((setences / words) * 100, 2)

    # Print the index based on the user input
    print(coleman_liau_index(letters_100, setences_100))


def coleman_liau_index(letters_100, setences_100):

    lial_index = round(0.0588 * letters_100 - 0.296 * setences_100 - 15.8)

    if lial_index > 15:
        return "Grade 16+"

    if lial_index < 1:
        return "Before Grade 1"

    return "Grade " + str(lial_index)


if __name__ == "__main__":
    main()
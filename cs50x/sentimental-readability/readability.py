# TODO
import re
from cs50 import get_string

text = get_string("Text: ")

text = text.replace('?', '.')
text = text.replace('!', '.')

# Get the sentences from text into a list
sentences = text.split('. ')

# Get the words from sentences into a list
words_list = []
for sentence in sentences:
    words = sentence.split()
    words_list += words

# Compute the total number of letters
letters = 0
for word in words_list:
    for letter in word:
        if letter.lower() >= 'a' and letter.lower() <= 'z':
            letters += 1

# The Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8,
# L is the average number of letters per 100 words in the text
# S is the average number of sentences per 100 words in the text.
L = letters / len(words_list) * 100
S = len(sentences) / len(words_list) * 100

grade = 0.0588 * L - 0.296 * S - 15.8

grade = round(grade)

# Differenciate tree situations
if grade >= 1 and grade <= 16:
    print("Grade", grade)
elif grade > 16:
    print("Grade 16+")
else:
    print("Before Grade 1")
from cs50 import get_string

text = get_string("Text: ")
letters = 0
words = 1
sentences = 0
for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    elif text[i].isspace():
        words += 1
    elif text[i] == '.' or text[i] == '!' or text[i] == '?':
        sentences += 1

l = letters / words * 100
s = sentences / words * 100
r = round(0.0588 * l - 0.29 * s - 15.8)
if r > 16:
    print("Grade 16+")
elif r > 1 and r < 17:
    print(f"Grade {r}")
else:
    print("Before Grade 1")

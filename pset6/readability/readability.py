letters = 0
words = 1
sentences = 0

text = input("Text: ")

for i in range(0, len(text), 1):
    if text[i].isalpha():
        letters += 1
    if text[i].isspace():
        words += 1
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

l = letters / words * 100
s = sentences / words * 100
index = round(0.0588 * l - 0.296 * s - 15.8)

if (index < 1):
    print("Before Grade 1")
elif (1 <= index <= 16):
    print("Grade %d" % index)
else:
    print("Grade 16+")
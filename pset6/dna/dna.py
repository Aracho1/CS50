import sys  # sys.argv for comand-line arguments
import csv
import re
from re import finditer

if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)
else:
    # open the CSV file and DNA sequence, read contents into memory
    with open(sys.argv[1], "r") as file:
        #reader / DictReader
        reader = csv.reader(file)
        list = list(reader)
    if sys.argv[1] == "databases/small.csv":
        # for each STR, compute the longest run of consecutive repeats in the DNA sequence
        results = []
        with open(sys.argv[2], "r") as sequences:
            for data in sequences:
                a = max([i for i in range(len(data)) if data.find("AGATC" * i) != -1])
                b = max([i for i in range(len(data)) if data.find("AATG" * i) != -1])
                c = max([i for i in range(len(data)) if data.find("TATC" * i) != -1])
                results.append(a)
                results.append(b)
                results.append(c)

            match = 0
            for i in range(1, len(list), 1):
                if int((list[i][1])) == a and int((list[i][2])) == b and int((list[i][3])) == c:
                    print(list[i][0])
                    match += 1
                else:
                    continue

            if (match == 0):
                print("No match")

    if sys.argv[1] == "databases/large.csv":
        results = []
        with open(sys.argv[2], "r") as sequences:
            for data in sequences:
                a = max([i for i in range(len(data)) if data.find("AGATC" * i) != -1])
                b = max([i for i in range(len(data)) if data.find("TTTTTTCT" * i) != -1])
                c = max([i for i in range(len(data)) if data.find("AATG" * i) != -1])
                d = max([i for i in range(len(data)) if data.find("TCTAG" * i) != -1])
                e = max([i for i in range(len(data)) if data.find("GATA" * i) != -1])
                f = max([i for i in range(len(data)) if data.find("TATC" * i) != -1])
                g = max([i for i in range(len(data)) if data.find("GAAA" * i) != -1])
                h = max([i for i in range(len(data)) if data.find("TCTG" * i) != -1])
                results.append(a)
                results.append(b)
                results.append(c)
                results.append(d)
                results.append(e)
                results.append(f)
                results.append(g)
                results.append(h)

            match = 0
            for i in range(1, len(list), 1):
                if int((list[i][1])) == a and int((list[i][2])) == b and int((list[i][3])) == c and int((list[i][4])) == d and int((list[i][5])) == e and int((list[i][6])) == f and int((list[i][7])) == g and int((list[i][8])) == h:
                    print(list[i][0])
                    match += 1
                else:
                    continue

            if (match == 0):
                print("No match")
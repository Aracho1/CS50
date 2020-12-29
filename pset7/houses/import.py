import csv
import sys
from cs50 import SQL

db = SQL("sqlite:///students.db")

# check command line arguments
if (len(sys.argv) != 2):
    print("INVALID COMMAND LINE ARGUMENTS")
    exit(1)

else:
    # open CSV file given by command-line argument
    with open(sys.argv[1], "r") as file:
        # csv.reader or csv.DictReader
        reader = csv.DictReader(file)
        for row in reader:
            # For each row, parse name (into first, middle and last name)
            # Use the split method on strings to split into words
            # Use None for student's middle name if they don't have one
            splitName = row["name"].split()
            if len(splitName) == 2:
                first = splitName[0]
                last = splitName[1]
                middle = None
            else:
                first = splitName[0]
                middle = splitName[1]
                last = splitName[2]

            # Insert each student into the students table of students.db
            # Use db.execute to INSERT a row into the table
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       first, middle, last, row["house"], row["birth"])
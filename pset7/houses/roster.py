import sys
from cs50 import SQL


db = SQL("sqlite:///students.db")

# check command line arguments
if (len(sys.argv) != 2):
    print("ERROR")
    exit(1)

# query database for all students in the house
else:
    house = sys.argv[1]
    rows = db.execute("SELECT first, middle, last, birth FROM students where house = ? ORDER BY last, first", house)
    for x in rows:
        if (x["middle"] == None):
            print("{0} {1}, born {2}".format(x["first"], x["last"], x["birth"]))
        else:
            print("{0} {1} {2}, born {3}".format(x["first"], x["middle"], x["last"], x["birth"]))


# print out each student's full name and birth year
    # Use db.execute to SELECT rows from the table
    # Return value will be list of Python dicts, where each dict represents a row in the table
    # Remember to check for NULL values for middle names (do not print NULL)

# students should be sorted alphabetically by last name, then first name
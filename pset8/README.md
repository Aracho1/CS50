# C$ 50 Finance
- Virtual stock trading website with an account for users to register for, the ability to get quotes for shares of stocks and virtually buy or sell them
- ```application.py``` file runs Flask app, a connection to a database file ``finance.db`` 
- Used sqlite3 database
- ```index``` queries the database for a user's stocks and cash balances and uses API to get the current price
- This follows the MVC, Model-View-Controller, pattern, which generally separates the concerns of data and how that’s stored (our database)
![SCREENSHOT](https://github.com/Aracho1/CS50/blob/main/pset8/Screenshot%202021-02-06%20at%2023.22.22.png)

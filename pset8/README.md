# C$ 50 Finance
- Virtual stock trading website with an account for users to register for, the ability to get quotes for shares of stocks and virtually buy or sell them
- ```application.py``` file runs Flask app, a connection to a database file ``finance.db`` 
- Used sqlite3 database
- ```index``` queries the database for a user's stocks and cash balances and uses API to get the current price
- This follows the MVC, Model-View-Controller, pattern, which generally separates the concerns of data and how that’s stored (our database)

## To start the app
```git clone```
- You’ll need to register for an API key in order to be able to query IEX’s data on iexcloud.io/cloud-login#/register
- In a terminal in the project folder, run ```$ export API_KEY=value```
- Run ```flask run```

![SCREENSHOT](https://github.com/Aracho1/CS50/blob/main/pset8/Screenshot%202021-02-06%20at%2023.22.22.png)

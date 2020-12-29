import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    users = db.execute("SELECT * FROM portfolio WHERE user_id = :user_id", user_id = session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
    return render_template("index.html", users = users, cash = cash[0]['cash'])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        users = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])

        """check valid symbol"""
        if not request.form.get("symbol") or lookup(request.form.get("symbol")) == None:
            return apology("Enter a valid symbol")

        """check share is positive integer"""
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Not valid shares")

        if request.form.get("shares").isdigit() == False:
            return apology("enter a positive integer value")

        """check the price of the share"""
        quote = lookup(request.form.get("symbol"))
        price = quote.get("price")
        symbol = quote.get("symbol")
        name = quote.get("name")
        cost = price * shares

        """check if the user can afford the stocks"""
        if cost > users[0]["cash"]:
            return apology("not enough cash")
        else:
            db.execute("INSERT INTO portfolio VALUES (:user_id, :trans_type, :name, :symbol, :share, :price, :cost, datetime('now'))", user_id = session["user_id"], trans_type = "purchase", name = name, symbol = symbol, share = shares, price = price, cost = cost)

            db.execute("UPDATE users SET cash = cash - :cost WHERE id = :user_id", cost = cost, user_id = session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")

    else:
        if not request.form.get("symbol") or lookup(request.form.get("symbol")) == None:
            return apology("enter a valid input", 403)
        else:
            return render_template("quoted.html", name = lookup(request.form.get("symbol"))["name"], symbol = lookup(request.form.get("symbol"))["symbol"], price = lookup(request.form.get("symbol"))["price"])


@app.route("/register", methods=["GET", "POST"])
def register():

    session.clear()

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        password_hash = generate_password_hash(password)
        if not request.form.get("username"):
            return apology("enter username", 403)
        elif not request.form.get("password"):
            return apology("enter password", 403)
        elif not request.form.get("confirmation"):
            return apology("confirm password", 403)
        elif not password == confirmation:
            return apology("passwords do not match", 403)
        else:
            try:
                db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = username, hash = password_hash)
                return redirect("/")

            except RuntimeError:
                return apology("username exists", 403)

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

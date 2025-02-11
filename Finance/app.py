import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():  # name as portfolio

    rows = db.execute("SELECT * FROM portfolio WHERE userid = :id", id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    cash = cash[0]['cash']
    sum = cash

    for row in rows:
        look = lookup(row['symbol'])
        row['name'] = look['name']
        row['price'] = look['price']
        row['total'] = row['price'] * row['shares']
        sum += row['total']

    # convert price and total to usd format
        row['price'] = usd(row['price'])
        row['total'] = usd(row['total'])

    return render_template("portfolio.html", rows=rows, cash=usd(cash), sum=usd(sum))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "GET":
        return render_template("buy.html")

    elif request.method == "POST":

        # Get values
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        quotes = lookup(symbol)

        # Validate values
        if not symbol or quotes is None:
            return apology("Must provide a valid stock symbol", 400)

        if not shares or not shares.isdigit() or int(shares) < 1:
            return apology("Select at least 1 valid share", 400)

        # Cast values
        shares = int(shares)
        symbol = symbol.upper()
        spent = shares * quotes['price']

        # Check if there is sufficient cash
        balance = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        balance = balance[0]['cash']
        remain = balance - spent

        if remain < 0:
            return apology("Insufficient money", 400)

        # Check if the share already exists in the portfolio
        rows = db.execute("SELECT * FROM portfolio WHERE userid = :id AND symbol = :symbol",
                          id=session["user_id"], symbol=symbol)

        if len(rows) == 0:
            db.execute("INSERT INTO portfolio (userid, symbol, shares) VALUES (:id, :symbol, 0)",
                       id=session["user_id"], symbol=symbol)

        # Get old shares from portfolio
        oldshares = db.execute("SELECT shares FROM portfolio WHERE userid = :id AND symbol = :symbol",
                               id=session["user_id"], symbol=symbol)
        oldshares = oldshares[0]["shares"]

        # Update new share count
        newshares = oldshares + shares

        db.execute("UPDATE portfolio SET shares = :newshares WHERE userid = :id AND symbol = :symbol",
                   newshares=newshares, id=session["user_id"], symbol=symbol)
        db.execute("UPDATE users SET cash = :remain WHERE id = :id",
                   remain=remain, id=session["user_id"])

        # Register purchase into history
        db.execute("INSERT INTO history (userid, symbol, shares, method, price) VALUES (:userid, :symbol, :shares, 'Buy', :price)",
                   userid=session["user_id"], symbol=symbol, shares=shares, price=quotes['price'])

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":

        rows = db.execute("SELECT * FROM history WHERE userid = :id", id=session["user_id"])

        return render_template("history.html", rows=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

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

    # If user reach route via GET; render template form
    if request.method == "GET":
        return render_template("quote.html")

    # if user send the form via POST; process the input
    elif request.method == "POST":

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("you must provide a valid stock symbol", 400)

        stock = lookup(symbol)
        if stock is None:
            return apology("invalid stock symbol", 400)

        # render quoted.html with new data
        return render_template("quoted.html", stock=stock)


@app.route("/register", methods=["GET", "POST"])
def register():

    # forget every session
    session.clear()

    if request.method == "POST":

        # check credentials
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif not request.form.get("password"):
            return apology("must provide a password", 400)

        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords do not match", 400)

        # create a hash and check if username already exist
        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))

        rows = db.execute("SELECT * FROM users WHERE username = :username", username=username)

        if len(rows) != 0:
            return apology("username already exist", 400)

        # inserte new username and hash into sql
        db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                   username=username, hash=hash)

        return redirect("/")

    else:
        # user reached route via GET
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "GET":

        rows = db.execute("SELECT symbol FROM portfolio WHERE userid = :id", id=session["user_id"])

        if not rows:
            return apology("You dont have any stocks in your portfolio", 400)
        return render_template("sell.html", rows=rows)

    elif request.method == "POST":

        # Get values
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        quotes = lookup(symbol)

        # Validate values
        if not symbol or quotes is None:
            return apology("Must provide a valid stock symbol", 400)

        if not shares or not shares.isdigit() or int(shares) < 1:
            return apology("Select at least 1 valid share", 400)

        # Cast values
        shares = int(shares)
        symbol = symbol.upper()
        earned = shares * quotes['price']

        # Check if there is sufficient cash
        balance = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
        balance = balance[0]['cash']
        remain = balance + earned

        # Get old shares from portfolio
        oldshares = db.execute("SELECT shares FROM portfolio WHERE userid = :id AND symbol = :symbol",
                               id=session["user_id"], symbol=symbol)
        oldshares = oldshares[0]["shares"]

        # Update new share count
        newshares = oldshares - shares

        if newshares < 1:
            return apology("insufficient shares in portfolio")

        db.execute("UPDATE portfolio SET shares = :newshares WHERE userid = :id AND symbol = :symbol",
                   newshares=newshares, id=session["user_id"], symbol=symbol)
        db.execute("UPDATE users SET cash = :remain WHERE id = :id",
                   remain=remain, id=session["user_id"])

        # Register purchase into history
        db.execute("INSERT INTO history (userid, symbol, shares, method, price) VALUES (:userid, :symbol, :shares, 'sell', :price)",
                   userid=session["user_id"], symbol=symbol, shares=-shares, price=quotes['price'])

        return redirect("/")

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import datetime

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


def get_current_datetime():
    now = datetime.datetime.now()
    return now


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Clear coockies
    # session.clear()

    if not session:
        return render_template('login.html')

    user_id = session["user_id"]

    # Check stocks hold by the user
    stocks = db.execute("SELECT * FROM stocks WHERE user_id=?", user_id)
    current_prices = []
    current_total = []
    stocks_total = 0
    for stock in stocks:
        current_price = lookup(stock['symbol'])['price']
        current_prices.append(current_price)

        total_price = current_price * stock['shares']
        stocks_total += total_price
        current_total.append(total_price)

    # Calculate total assets
    user_cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]['cash']
    total = stocks_total + user_cash

    stock_details = zip(stocks, current_prices, current_total)

    return render_template('index.html',
                           stock_details=stock_details,
                           user_cash=user_cash,
                           total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        # Make sure a user inputs a correct symbol
        symbol = request.form.get('symbol')
        quote = lookup(symbol)
        if not symbol or not quote:
            return apology('invalid symbol', 400)

        # Make sure a user inputs correct shares
        shares = request.form.get('shares')
        if shares.isdigit():
            shares = int(shares)
        else:
            return apology('shares must be integer', 400)

        name = quote['name']
        price = float(quote['price'])
        shares = int(request.form.get('shares'))
        total = shares * price
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]['cash']

        if total > cash:
            return apology('not enough cash', 400)

        # Get current time in datetime format
        user_id = session["user_id"]
        time = get_current_datetime()

        # record stock purchase
        db.execute("INSERT INTO history (user_id, symbol, shares, price, bought_or_sold, time) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, symbol, shares, price, 'Bought', time)

        # Update stock holdings
        db.execute("INSERT INTO stocks (user_id, symbol, name, shares) VALUES (?, ?, ?, ?) ON CONFLICT(user_id, symbol) DO UPDATE SET shares = stocks.shares + excluded.shares",
                   user_id, symbol, name, shares)

        # update user remaining cash
        update_cash = round(cash - total, 2)
        db.execute("UPDATE users SET cash=? WHERE id=?", update_cash, session["user_id"])

        # Return a message to get_flashed_messages() to layout.html
        flash('Bought!')

        return redirect('/')

    else:
        return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session['user_id']
    histories = db.execute("SELECT * FROM history WHERE user_id=?", user_id)
    return render_template('history.html', histories=histories)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    """Get stock quote."""
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        quote = lookup(symbol)
        if not quote:
            return apology('invalid symbol', 400)

        return render_template('quoted.html', quote=quote)

    else:
        return render_template('quote.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        username = request.form.get("username")
        exist_status = db.execute("SELECT * FROM users WHERE username = ?", username)
        if exist_status != []:
            return apology("username already exists", 400)

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if password == confirmation:
            hashed_password = generate_password_hash(password)
            # Query database for username
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)

        else:
            return apology("Passwords don't match", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        # Log the user in
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == 'POST':
        user_id = session['user_id']
        symbol = request.form.get('symbol')

        sell_shares = request.form.get('shares')
        if sell_shares.isdigit():
            sell_shares = int(sell_shares)
        else:
            return apology('shares must be integer', 400)

        user_shares = int(db.execute("SELECT shares FROM stocks WHERE user_id=? AND symbol=?", user_id, symbol)[0]['shares'])

        # Check for any invalid input
        if sell_shares < 0:
            return apology('shares must be integer', 400)
        elif sell_shares > user_shares:
            return apology("you don't have that many shares in your account", 400)

        # Update shares of table 'stocks'
        remaining_shares = user_shares - sell_shares
        db.execute("UPDATE stocks SET shares=? WHERE user_id=? AND symbol=?", remaining_shares, user_id, symbol)

        # Update cash of table 'users'
        user_cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]['cash']
        cash_gained = sell_shares * lookup(symbol)['price']
        cash_total = cash_gained + user_cash
        db.execute("UPDATE users SET cash=? WHERE id=?", cash_total, user_id)

        # Update history table
        price = lookup(symbol)['price']
        time = get_current_datetime()
        db.execute("INSERT INTO history (user_id, symbol, shares, price, bought_or_sold, time) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, symbol, sell_shares, price, 'Sold', time)

        return redirect('/')

    else:
        symbols = db.execute("SELECT symbol FROM stocks WHERE user_id=?", session['user_id'])
        return render_template('sell.html', symbols=symbols)


@app.route("/account")
@login_required
def account():
    user_id = session['user_id']
    username = db.execute("SELECT username FROM users WHERE id=?", user_id)[0]['username'].title()
    return render_template('account.html', username=username)


@app.route("/change-password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == 'POST':
        user_id = session['user_id']
        old_password = request.form.get('old_password')

        # Check if old password is correct
        print(db.execute("SELECT hash FROM users WHERE id=?", user_id))
        if check_password_hash(db.execute("SELECT hash FROM users WHERE id=?", user_id)[0]['hash'], old_password):
            new_password = request.form.get('new_password')
            confirmation = request.form.get('confirmation')

            # Check if new passwords match each other
            if new_password == confirmation:
                db.execute("UPDATE users SET hash=? WHERE id=?", generate_password_hash(new_password), user_id)
            else:
                return apology('new passwords do not match', 400)

        else:
            return apology('old passwords do not match', 400)

        return render_template('changed-password.html')

    else:
        return render_template('change-password.html')

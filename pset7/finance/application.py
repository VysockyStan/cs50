from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import gettempdir

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = gettempdir()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    
    select = "SELECT symbol, name, SUM(amount) FROM portfolio WHERE user_id = :id GROUP BY symbol HAVING SUM(amount > 0)"
    index_query = db.execute(select, id = session["user_id"])
    
    cash_query =  db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]['cash']
    
    for temp in index_query:
        data = lookup(temp["symbol"])
        temp['price'] = data['price']
        temp['total'] = temp['price'] * temp['SUM(amount)']
    
    total = 0
    for temp in index_query:
        total += temp['total']
    total += cash_query

    return render_template("index.html", query = index_query, cash = cash_query, total = total) 

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST": 
        if not request.form.get("symbol"):
            return apology("must provide symbol")
            
        if not request.form.get("amount"):
            return apology("must provide amount")
        
        if int(request.form.get("amount")) < 0:
            return apology("amount must be a positive integer")

        if lookup(request.form.get("symbol")) == None:
            return apology("Such symbol doesn't exist")
        
        query_res = lookup(request.form.get("symbol"))
        
        cash_query =  db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]['cash']
        
        total = cash_query - query_res.get("price") * int(request.form.get("amount"))
        
        if total < 0:
            return apology("You've got lack of money")
        
        insert = """ INSERT INTO portfolio (user_id, symbol, name, amount, price)
        VALUES (:user_id, :symbol, :name, :amount, :price)"""
        
        db.execute(insert, user_id = session["user_id"], symbol = query_res.get("symbol"), name = query_res.get("name"), 
                   amount = int(request.form.get("amount")), price = query_res.get("price"))
        
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = total, id = session["user_id"])
        
        return render_template("buy.html")
     
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    
    select = "SELECT symbol, amount, price, timestamp FROM portfolio WHERE user_id = :id ORDER BY timestamp ASC"
    history_query = db.execute(select, id = session["user_id"])
    
    return render_template("history.html", history = history_query)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    
    if request.method == "POST": 
        if not request.form.get("quote"):
            return apology("must provide symbol")
        
        if lookup(request.form.get("quote")) == None:
            return apology("Such symbol doesn't exist")
        
        query_res = lookup(request.form.get("quote"))
        return render_template("quoted.html", symbol = query_res) 
    
    else:
        return render_template("quote.html") 
    

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    if request.method == "POST": 
         
        if not request.form.get("username"):
            return apology("must provide username")

        elif not request.form.get("password"):
            return apology("must provide password")
        
        elif not request.form.get("password_2"):
            return apology("must provide the same password")
        
        elif request.form.get("password_2") != request.form.get("password"):
            return apology("must provide the same password")
            
        if db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username")):
            return apology("Such username already exists!")
       
        db.execute("INSERT INTO users (username, hash) VALUES(:username, :password)", username=request.form["username"], password=pwd_context.encrypt(request.form["password"]))
        return render_template("success.html")
        
    else:
        return render_template("register.html") 
        
@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    
    if request.method == "POST": 
        
        if not request.form.get("symbol"):
            return apology("must provide symbol")
            
        if not request.form.get("amount"):
            return apology("must provide amount")
        
        if int(request.form.get("amount")) < 0:
            return apology("amount must be a positive integer")

        if lookup(request.form.get("symbol")) == None:
            return apology("Such symbol doesn't exist")
            
        query_res = lookup(request.form.get("symbol"))

        if not db.execute("SELECT symbol FROM portfolio WHERE symbol = :symbol AND user_id = :id", 
                            symbol=query_res.get('symbol').upper(), id = session["user_id"]):
            return apology("You have not bought such share")
            
        symbol = query_res.get('symbol')
        amount = int(request.form.get("amount"))
        totalAmount = db.execute("SELECT SUM(amount) FROM portfolio WHERE user_id=:id AND symbol=:symbol" ,
                                id=session["user_id"], symbol=symbol)[0]['SUM(amount)']
        if totalAmount - amount < 0:
            return apology("Youn don't have such amount of shares!")
        
        cash_query = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]['cash']
        
        total = cash_query + query_res.get("price") * int(request.form.get("amount"))
        
        insert = """ INSERT INTO portfolio (user_id, symbol, name, amount, price)
        VALUES (:user_id, :symbol, :name, :amount, :price)"""
        
        db.execute(insert, user_id = session["user_id"], symbol = query_res.get("symbol"), name = query_res.get("name"), 
                   amount = -int(request.form.get("amount")), price = query_res.get("price"))
        
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = total, id = session["user_id"])
        
        return render_template("sell.html")
     
    else:
        return render_template("sell.html")

@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add additional cash to the account."""
    
    if request.method == "POST":
        if not request.form.get("cash"):
            return apology("must provide symbol")
            
        elif int(request.form.get("cash")) < 0:
            return apology("cash amount must be a positive")
        
        cash_query = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]['cash']
        
        total = cash_query + int(request.form.get("cash"))
        
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = total, id = session["user_id"])
        
        return render_template("add.html")
    
    else:
        return render_template("add.html")
    
import os

from flask import Flask, render_template, request, jsonify
from cs50 import SQL

# Configure application
app = Flask(__name__)
db = SQL("sqlite:///boxinghub.db")
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Retrieve "likes" and "loves" from database
def get_likes_and_loves():
    likes = db.execute("SELECT likes FROM boxinghub")
    loves = db.execute("SELECT loves FROM boxinghub")
    return likes, loves


# Index page
@app.route("/")
def index():
    likes, loves = get_likes_and_loves()
    return render_template("index.html", likes=likes, loves=loves)


# Clubs page
@app.route("/clubs")
def clubs():
    likes, loves = get_likes_and_loves()
    return render_template("clubs.html", likes=likes, loves=loves)


# Gears page
@app.route("/gears")
def gears():
    likes, loves = get_likes_and_loves()
    return render_template("gears.html", likes=likes, loves=loves)


# Recovery page
@app.route("/recovery")
def recovery():
    likes, loves = get_likes_and_loves()
    return render_template("recovery.html", likes=likes, loves=loves)


# Rules page
@app.route("/rules")
def rules():
    likes, loves = get_likes_and_loves()
    return render_template("rules.html", likes=likes, loves=loves)


# Technuqies page
@app.route("/techniques")
def techniques():
    likes, loves = get_likes_and_loves()
    return render_template("techniques.html", likes=likes, loves=loves)


# Update the number of "likes" of database boxinghub.db
@app.route("/update_like", methods=["POST"])
def update_like():
    new_like = request.json["like"]

    db.execute("UPDATE boxinghub SET likes = ?", (new_like,))

    return jsonify({"message": "Like updated successfully"})


# Update the number of "loves" of database boxinghub.db
@app.route("/update_love", methods=["POST"])
def update_love():
    new_love = request.json["love"]

    db.execute("UPDATE boxinghub SET loves = ?", (new_love))

    return jsonify({"message": "Love updated successfully"})


if __name__ == "__main__":
    app.run(debug=True)

# BoxingHub

#### Video Demo: https://youtu.be/9yuzUpK1MCM

#### Description: **_BoxingHub_ is dedicated to speading boxing knowledge and develope boxing culture.**

#### Author: Hongbo Wei from Guiyang, China. A software engineer who loves boxing 🥊!

- It is a web application based on the Flask framework of Python, HTML, CSS, JavaScript and SQLite.
- This project is an educational website that helps users to lear how to box.
- Users can learn boxing knowledge here, including techniques, theories, rules, and gears.
- It also provides information on top boxing clubs, such as address and contact.
- At the end of each page, the contact information of the developer of the site is displayed.

---

#### Explanation of what each folder contains and each files does:

##### 1. Folder "env": a virtual environment contains special edition of packages that support the application to run.

##### 2. Folder "static":

- bootstrap: control the aesthetics of the web application.
- css: control the aesthetics of the web application, for example: color, size, and position. It also makes certain elements more responsive.
- fonts: control the fonts of the web application.
- images: images resources used by this application. Such as logos, background, images for the content of different pages.
- js: control how the view effects of how a page is loaded, for example, when a user scrolls down, the navigation bar shrinks to provide a better view and convenientce to navigate to other pages; when a user is scroll a page, and when "likes" or "loves" button is clicked.

##### 3. Folder "templates": HTML files that determine the structure of the website.

- base.html: the base layout of each page, so other pages can extend from this one.
- clubs.html: the Club page displays the information of boxing clubs.
- gears.html: the Gear page talks about boxing gears, such as gloves, handwraps, headgear, mouthguards, no-foul protectors.
- index.html: the index page introduces what BoxingHub is, what it is about.
- recovery.html: the Recovery page is about how a athlete should eat, stretch, and rest, so that he/she can avoid and prevent injuries, recover well from high-intense training.
- rules.html: the Rules page talks about the basic rules of professional boxing, such as weight class, size of gloves, rounds, and titles.
- techniques.html: the Techniques page talks about the fundamental techniques of boxing.

##### 4. File "app.py": the flask configuration file. It connects to the database boxinghub.db, auto reloads the cotent of the page if anything changed, provides different route for users to brose, and update the database according to the interation between users and the web app.

##### 5. File "boxinghub.db: a SQLite3 database that records every "likes" and "loves" given by users.

---

#### Follow below two steps to run the web app:

    flask run

---

😁 **Thanks for your attention!**

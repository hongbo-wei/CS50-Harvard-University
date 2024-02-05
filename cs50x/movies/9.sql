SELECT name FROM people
JOIN movies ON movies.id = stars.movie_id
JOIN stars ON people.id = stars.person_id
WHERE year = '2004'
ORDER BY birth;
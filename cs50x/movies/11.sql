SELECT title FROM movies
JOIN ratings
ON ratings.movie_id = movies.id
WHERE id IN
(
    SELECT movie_id FROM stars
    WHERE person_id IN
    (
        SELECT id FROM people
        WHERE name = 'Chadwick Boseman'
    )
)
ORDER BY rating DESC
LIMIT 5;
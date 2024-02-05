SELECT ROUND(AVG(rating), 2) AS 'Average rating of all movies in 2012'
FROM ratings
JOIN movies
ON ratings.movie_id = movies.id
WHERE movies.year = 2012;
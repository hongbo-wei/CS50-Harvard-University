SELECT SUM(energy)/COUNT(energy) FROM songs
WHERE artist_id = (SELECT id FROM artists
WHERE name = 'Drake');
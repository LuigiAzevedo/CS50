SELECT m.title
FROM people p
INNER JOIN stars s
ON p.id = s.person_id
INNER JOIN movies m
ON m.id = s.movie_id
INNER JOIN ratings r
ON m.id = r.movie_id
WHERE p.name LIKE "Chadwick Boseman"
ORDER BY r.rating DESC
LIMIT 5;
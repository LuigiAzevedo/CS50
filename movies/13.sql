SELECT p.name
FROM people p
INNER JOIN stars s
ON p.id = s.person_id
INNER JOIN movies m
ON m.id = s.movie_id
WHERE m.id IN (
    SELECT m.id
    FROM people p
    INNER JOIN stars s
    ON p.id = s.person_id
    INNER JOIN movies m
    ON m.id = s.movie_id
    WHERE p.name LIKE "Kevin Bacon"
)
AND p.name != "Kevin Bacon"
;
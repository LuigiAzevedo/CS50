SELECT title
FROM movies
WHERE id IN (
    SELECT m.id
    FROM people p
    INNER JOIN stars s
    ON p.id = s.person_id
    INNER JOIN movies m
    ON m.id = s.movie_id
    WHERE p.name LIKE "Johnny Depp")
AND id IN   (
    SELECT m.id
    FROM people p
    INNER JOIN stars s
    ON p.id = s.person_id
    INNER JOIN movies m
    ON m.id = s.movie_id
    WHERE p.name LIKE "Helena Bonham Carter");
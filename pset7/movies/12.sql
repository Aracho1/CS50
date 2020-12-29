SELECT DISTINCT title FROM
movies JOIN stars ON movies.id = stars.movie_id JOIN
people ON people.id = stars.person_id
WHERE name in ("Johnny Depp", "Helena Bonham Carter")
GROUP BY title
HAVING count(distinct name) = 2;

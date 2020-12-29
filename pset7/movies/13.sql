SELECT name FROM people WHERE people.id
IN
(SELECT person_id from stars JOIN movies ON stars.movie_id = movies.id
WHERE movie_id IN
(SELECT movie_id FROM movies JOIN stars ON stars.movie_id = movies.id JOIN people ON
people.id = stars.person_id WHERE people.id IN
(SELECT id FROM people WHERE people.name = "Kevin Bacon" and people.birth = 1958)))
EXCEPT
SELECT name FROM people WHERE people.name = "Kevin Bacon" and people.birth = 1958
-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Discover more about the crime reading the police reports
-- Theft was 10:15 AM at Humphrey Street bakery
SELECT *
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2021
AND street = "Humphrey Street";

-- Read the interviews taken after the crime
-- Thief wen't inside a car between 10:15 AM - 10:25 AM at the bakery parking lot
-- Called someone after the robbery and asked to purchase the flight ticket to the earliest flight in the next day.
SELECT transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2021
AND transcript LIKE "%bakery%";


-- Discover suspects name
-- Vanessa, Bruce, Barry, Luca, Sofia, Iman, Diana, Kelsey
SELECT name
FROM people p
INNER JOIN bakery_security_logs b
ON b.license_plate = p.license_plate
WHERE day = 28
AND month = 7
AND year = 2021
AND hour  = 10
AND minute > 14
AND minute < 26
AND activity = "exit";

-- Discover how withdraw money that day at Leggett Street
-- Common suspects: Bruce, Diana, Iman, Luca
SELECT p.name
FROM atm_transactions a
INNER JOIN bank_accounts b
ON a.account_number = b.account_number
INNER JOIN people p
ON b.person_id = p.id
WHERE a.atm_location LIKE "Leggett Street"
AND a.transaction_type = "withdraw"
AND a.day = 28
AND a.month = 7
AND a.year = 2021;

-- Discover who called for less than a minute within 10 minutes of the robbery
-- Common suspects: Bruce, Diana
SELECT p.name
FROM people p
INNER JOIN phone_calls ph
ON p.phone_number = ph.caller
WHERE day = 28
AND month = 7
AND year = 2021
AND duration < 60;

-- Common suspects: Bruce
SELECT p.name
FROM people p
INNER JOIN passengers pa
ON p.passport_number = pa.passport_number
INNER JOIN flights f
ON pa.flight_id = f.id
INNER JOIN airports a
ON a.id = f.origin_airport_id
WHERE a.city = "Fiftyville"
AND f.day = 29
AND f.month = 7
AND f.year = 2021
AND f.hour = 8
AND f.minute = 20
ORDER BY f.hour, f.minute;

-- ACCOMPLICE: Robin
SELECT p.name, ph.caller, ph.receiver
FROM people p
INNER JOIN phone_calls ph
ON p.phone_number = ph.receiver
WHERE day = 28
AND month = 7
AND year = 2021
AND duration < 60
AND ph.caller IN
(
    SELECT phone_number
    FROM people
    WHERE name = "Bruce"
);

-- Thief destiny: New York City
SELECT a.city
FROM people p
INNER JOIN passengers pa
ON p.passport_number = pa.passport_number
INNER JOIN flights f
ON pa.flight_id = f.id
INNER JOIN airports a
ON a.id = f.destination_airport_id
WHERE f.day = 29
AND f.month = 7
AND f.year = 2021
AND f.hour = 8
AND f.minute = 20
AND p.name = "Bruce"
ORDER BY f.hour, f.minute;
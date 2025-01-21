-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT id FROM crime_scene_reports WHERE day = 28 AND month = 7 AND year = 2023 AND street = "Humphrey Street";
    Result: 295 and 297. These are the crime scene reports occurred the day of the robbery.

SELECT description FROM crime_scene_reports WHERE id = 295;
    The theft of the CS50 duck took place at 10:15 a.m. at the Humphrey Street bakery. Interviews were conducted today
    with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

SELECT id FROM interviews WHERE day = 28 AND month = 7 AND year = 2023 AND transcript LIKE '%bakery%';
    RESULT; 161, 162 and 163 are the interviews done the day of the robbery that mention the bakery.


                                                    THE INTERVIEWS

SELECT name, transcript FROM interviews WHERE id = 161;
    RUTH: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
    If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

SELECT name, transcript FROM interviews WHERE id = 162;
    EUGENE: I don't know the thief's name, but it was someone I recognized.
    Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.


SELECT name, transcript FROM interviews WHERE id = 163;
    RAYMOND: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
    In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
    The thief then asked the person on the other end of the phone to purchase the flight ticket.

    So, whe should search for the thief´s car seen from the bakery cameras, someone recognized by Eugene, money withdrawals on Leggett Street that day,
    the earliest flight the next day and the name of the person who booked the ticket (based in the phone call and ticket information)


                                                    THE FLIHGT

SELECT f.id, f.destination_airport_id, f.hour, f.minute FROM flights f JOIN airports a ON f.origin_airport_id = a.id
WHERE a.city = 'Fiftyville'AND f.year = 2023 AND f.month = 7 AND f.day = 29 ORDER BY f.hour ASC, f.minute ASC LIMIT 1;

    +----+------------------------++------+--------+
    | id | destination_airport_id || hour | minute |
    +----+------------------------++------+--------+
    | 36 | 4                      || 8    | 20     |
    +----+------------------------++------+--------+

    This is the first flight from Fiftyville the next day


SELECT city FROM airports WHERE id = 4;

    New York City is where the thiefs scaped to.


                                                    THE CALL

SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2023 AND duration < 60);

     Kenny, Sofia, Benista, Taylor, Diana, Kelsey, Bruce, Carina are the people whose number match with the callers


                                                    THE TRAVELERS

SELECT p.name FROM people p JOIN passengers pa ON p.passport_number = pa.passport_number WHERE pa.flight_id = 36;

    Sofia, Bruce, Kelsey, Taylor, Kenny are the travelers on that flight.



                                                    THE TRANSACTION

SELECT p.name FROM people p JOIN bank_accounts b ON b.person_id = p.id JOIN atm_transactions a ON b.account_number = a.account_number
WHERE a.day = 28 AND a.month = 7 AND a.year = 2023 AND a.atm_location = 'Leggett Street' AND a.transaction_type = 'withdraw';

    Bruce, Kenny, Taylor are the travelers thah also made withdrawals the day of the robbery.



                                                    THE BAKERY

SELECT name FROM people WHERE license_plate IN  (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND month = 7 AND year = 2023 AND hour = 1
0 AND minute BETWEEN 15 AND 25);

    Burce is the only person whose license plate matches with the one found in the bakery at that precise moment, so he must be the thief.



                                                    THE PARTNER IN CRIME


    SELECT name FROM people p JOIN phone_calls c ON p.phone_number = c.receiver WHERE c.id =
    (SELECT id FROM phone_calls p WHERE caller IN
    (SELECT phone_number FROM people WHERE name = "Bruce" AND day = 28 AND month = 7 AND year = 2023 AND duration <= 60));

    Robin was the receiver when Bruce made the call.

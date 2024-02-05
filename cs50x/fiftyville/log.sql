-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find the description about 'the stolen CS50 Duck'
SELECT description
  FROM crime_scene_reports
 WHERE month = 7 AND day = 28
   AND street = 'Humphrey Street';

-- The description mentions that there were three interviews conducted
-- Check the interviews happened on July 28th
SELECT transcript
  FROM interviews
 WHERE month = 7 AND day = 28;

-- The 1st interview mentioned that the thief drove a car from the barkery parking lot within 10 mins of the theft
-- Check the barkery parking lot within that time span
SELECT license_plate
  FROM bakery_security_logs
 WHERE activity = 'exit'
   AND month = 7
   AND day =28
   AND hour = 10
   AND minute >= 15
   AND minute <= 25;
-- We get 8 records of a license plate during that time span, the thief's car is in one of it.
-- Then find the owners of those cars
SELECT *
  FROM people
 WHERE license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
        WHERE activity = 'exit'
          AND month = 7
          AND day =28
          AND hour = 10
          AND minute >= 15
          AND minute <= 25);

-- According to the 2nd interview, eailer than 10: 15, the theif withdrawed some money
-- Let's see the transaction record to find out the account number that the thief used
SELECT account_number
  FROM atm_transactions
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND atm_location = 'Leggett Street'
   AND transaction_type = 'withdraw';
-- We got 8 rows of the account number
-- And then find the owners of those accounts
SELECT name
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
 WHERE account_number IN
       (SELECT account_number
          FROM atm_transactions
        WHERE year = 2021
          AND month = 7
          AND day = 28
          AND atm_location = 'Leggett Street'
          AND transaction_type = 'withdraw');

-- According to the 3rd interview, the thief called someone less than 1 min while leaving the bakery
-- Check phone calls happened around that time
SELECT caller
  FROM phone_calls
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND duration <= 60;

-- And it also mentioned that the thief was going to take the earliest flight out of Fiftyville June 29th
-- Let's check the earliest flight on that day
SELECT *
  FROM flights
 WHERE year = 2021
   AND month = 7
   AND day = 29
   ORDER BY hour
   LIMIT 1;

-- Next we check the passengers on that particular flight
SELECT passport_number
  FROM passengers
 WHERE flight_id IN
       (SELECT id
          FROM flights
         WHERE year = 2021
           AND month = 7
           AND day = 29
           ORDER BY hour
           LIMIT 1);

-- Therefore the criminal is the person have license_plate, account_number, phone_number, and passport_number from previous list
SELECT name
  FROM people
  JOIN bank_accounts
    ON people.id = bank_accounts.person_id
 WHERE account_number IN
       (SELECT account_number
          FROM atm_transactions
        WHERE year = 2021
          AND month = 7
          AND day = 28
          AND atm_location = 'Leggett Street'
          AND transaction_type = 'withdraw')
   AND license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE activity = 'exit'
           AND month = 7
           AND day =28
           AND hour = 10
           AND minute >= 15
           AND minute <= 25)
   AND phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration <= 60)
    AND passport_number IN
        (SELECT passport_number
           FROM passengers
          WHERE flight_id IN
                (SELECT id
                    FROM flights
                  WHERE year = 2021
                    AND month = 7
                    AND day = 29
                    ORDER BY hour
                    LIMIT 1)
          );

-- The city the thief ESCAPED TO corresponds to the earliest flight on July 29th
SELECT city
  FROM airports
 WHERE id IN
       (SELECT destination_airport_id
          FROM flights
         WHERE year = 2021
           AND month = 7
           AND day = 29
           ORDER BY hour
           LIMIT 1);

-- The ACCOMPLICE is the reciever called by the thief on June 28
SELECT name
  FROM people
 WHERE phone_number IN
       (SELECT receiver
          FROM phone_calls
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND duration <= 60
           AND caller IN
               (SELECT phone_number
                  FROM people
                 WHERE name = 'Bruce')
       );
#include <iostream>

int month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void updateLeapYear(int year) {
    if(year % 400 == 0) {
        month[2] = 28;
    }
     else if(year % 100 == 0) {
        month[2] = 29;
    } 
    else if(year % 4 == 0) {
        month[2] = 29;
    } 
    else {
        month[2] = 28;
    }
}

void storeMonth() {
    month[1] = 31;
    month[2] = 28;
    month[3] = 31;
    month[4] = 30;
    month[5] = 31;
    month[6] = 30;
    month[7] = 31;
    month[8] = 31;
    month[9] = 30;
    month[10] = 31;
    month[11] = 30;
    month[12] = 31;
}

/*
    Time O(n)
    Space O(1)
*/
int findPrimeDates(int d1, int m1, int y1, int d2, int m2, int y2) {
    int result = 0;  // Counter for prime dates

    // Loop until we reach the end date (d2, m2, y2)
    while (true) {
        int x = d1;
        x = x * 100 + m1;    // Convert the day and month into a combined number (ddmm)
        x = x * 10000 + y1;  // Convert the above result into a full date number (ddmmyyyy)

        // Check if the number is divisible by 4 or 7 (prime date condition)
        if (x % 4 == 0 || x % 7 == 0) {
            result = result + 1;  // Increment result if the date is prime
        }

        // Break the loop if the current date matches the end date
        if (d1 == d2 && m1 == m2 && y1 == y2) {
            break;
        }

        // Update the leap year status (if it's a leap year, February has 29 days)
        updateLeapYear(y1);

        // Move to the next day
        d1 = d1 + 1;

        // Check if the day exceeds the number of days in the current month
        if (d1 > month[m1]) {
            m1 = m1 + 1;  // Move to the next month
            d1 = 1;       // Reset day to 1

            // Check if the month exceeds 12, move to the next year
            if (m1 > 12) {
                y1 = y1 + 1;  // Increment the year
                m1 = 1;       // Reset month to January
            }
        }
    }

    return result;  // Return the count of prime dates
}
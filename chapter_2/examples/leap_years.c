/* A year is a leap year if it is divisble by 4 but not by 100, except years divisible by 400 are leap years */

void leap_year(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
        printf("%d is a leap year\n", year
    }
    else {
        printf("%d is not a leap year\n", year);
    }
}


/* There is no error checking in day_of_year or month_day. Remedy this defect. */

/* Could set a minimum year to ensure the year aligns with a period in which the Gregorian Calendar had been implemented (from 1752 in Great Britain), seeing as leap years are a result of the chosen calendar. */
/* I have opted to not impose the above restriction */

#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;

    /* check for negative year value and month values outside of the interval [1,12] */
    if (year < 0) {
        printf("Year is negative.\n");
        return -1;
    } else if (month < 1 || month > 12) {
        printf("Month must be between 1 and 12 inclusive.\n");
        return -1;
    } 
    /* exploit the fact that a boolean value is 0 or 1 */
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;

    /* check that the day is valid for the month */
    if (day < 1 || day > daytab[leap][month]) {
        printf("The day exceeds the number of days in the month for the year, or is less than 1.\n");
        return -1;
    }


    for (i = 1; i < month; i++) {
        day += daytab[leap][i];
    }
    return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    /* check for negative or 0 yearday and negative year values */
    if (year < 0) {
        printf("Year is negative.\n");
        return -1;
    }
    /* exploit the fact that a boolean value is 0 or 1 */
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (yearday <= 0 || (leap && (yearday > 366)) || (!leap && (yearday > 365))) {
        printf("Day of the year is negative, zero, or exceeds the maximum number of days in the given year.\n");
        return -1;
    }

    for ( i = 1; yearday > daytab[leap][i]; i++) {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
    return 0;
}

int main() {
    return 0;
}


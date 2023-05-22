/* Rewrite the routines of day_of_year and month_day  with pointers instead of indexing */

#include <stdio.h>
#include <stdlib.h>
#define DAY_TAB_NUM 2
#define DAY_TAB_SIZE 13

static char daytab[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

/* day_of_year: set day of year from month & day */
/* using only pointer manipulation; no indexing */
int day_of_year(int year, int month, int day) {
    int i, leap;

    /* exploit the fact that a boolean value is 0 or 1 */
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    
    /* p points to the first  */
    char * p = &daytab[leap][1];

    for (i = 1; i < month; i++) {
        //day += *(*(daytab + leap) + i);
        day += *p;
        ++p;
    }
    return day;
}

/* month_day: set month, day from day of year */
/* using only pointer manipulation; no indexing */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    char * p = &daytab[leap][1];

    for ( i = 1; yearday > *p; i++) {
        //yearday -= *(*(daytab + leap) + i);
        yearday -= *p;
        ++p;
    }
    *pmonth = i;
    *pday = yearday;
}



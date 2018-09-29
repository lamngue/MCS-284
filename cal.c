#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define WEEK_DAYS 7

int month,year,startDayOfWeek;
int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
char *months[] = {"","january","february","march","april","may","june","july","august","september","october","november","december"};
char *capitalizedMonths[] = {"","January","February","March","April","May","June","July","August","September","October","November","December"};
struct tm tm;

void printHeader(int month,int year)
{
    int length = (16 - strlen(months[month])) /2;
    for(int i = 0; i<length;i++){
        printf(" ");
    }
    printf(" %s %d\n", capitalizedMonths[month], year);
    printf(" Su Mo Tu We Th Fr Sa\n");
}


void checkLeapYears(int year)
{
    if((year%4==0)&&(year%100!=0)){
        daysInMonth[2] = 29;
    }
    else if(year%400 == 0){
        daysInMonth[2] = 29;
    }
}

void printCalendar(int daysInMonth,int startDateInMonth)
{
    int i;
    //print the space for the start date in Month
    for(i = 0; i<startDateInMonth;i++){
        printf("   ");
    }
    //print the dates
    for(i = 1; i<=daysInMonth;i++){
        printf("%3d",i);
        if((i + startDateInMonth) % WEEK_DAYS == 0){
            printf("\n");
        }
    }
    printf("\n");
}

int findStartDateInMonth(int month,int year)
{
    tm.tm_mon = month -1;
    tm.tm_year = year - 1900;
    tm.tm_mday = 1;
    tm.tm_hour = tm.tm_min = tm.tm_sec = 0;
    tm.tm_isdst = -1;
    if(mktime(&tm) != -1)
    {
        startDayOfWeek = tm.tm_wday;
    }
    return startDayOfWeek;
}

bool isInteger(const char *str)
{
    while(*str)
    {
        if(!isdigit(*str))
            return false;
        str++;
    }
    return true;
}
void printTheRest(int yearGiven)
{
    if(yearGiven < 1 || yearGiven > 9999){
        printf("cal: year %d not in range 1..9999\n",yearGiven);
    }
    else{
        year = yearGiven;
        checkLeapYears(year);
        printHeader(month,year);
        printCalendar(daysInMonth[month],findStartDateInMonth(month,year));
    }
}

void convertMonthToLowercase(char *monthName)
{
   while (*monthName != '\0') {
         *monthName = tolower(*monthName);
         monthName++;
   }
}
void printQuarters(int year, int month1, int month2, int month3)
{
    int spacingLeft;
    //print 3 months
    int pad = 0;
    for (int i = month1; i <= month3; i++) {
        int pad1 = strlen(months[i]) + (20 - strlen(months[i])) / 2 +1; //padding from beginning to the end of month string
        printf("%*s", pad + pad1, capitalizedMonths[i]);
        pad = 22 - pad1; // padding after month string till 22
    }

    printf("\n");
    for(int i = 0;i<3;i++){
        printf(" Su Mo Tu We Th Fr Sa ");
    }
    printf("\n");
    //January, February and March
    //first line of days...
    int record1 = 0;
    int record2 = 0;
    int record3 = 0;
    bool numberInLine5Month1 = true,numberInLine5Month2 = true,numberInLine5Month3 =true;
    bool numberInLine6Month1 = true,numberInLine6Month2 = true,numberInLine6Month3 = true;
    int recordForFebruary = 0;
        for(int k = 0;k<findStartDateInMonth(month1,year);k++){
            printf("   ");
        }
        for(int j = 1;j<=daysInMonth[month1];j++){
            printf("%3d",j);
            if((j+findStartDateInMonth(month1,year)) % 7 == 0){
                record1 = j +1;
                break;
            }
        }
        printf(" ");
        for(int k = 0;k<findStartDateInMonth(month2,year);k++){
            printf("   ");
        }
        for(int j = 1;j<=daysInMonth[month2];j++){
            printf("%3d",j);
            if((j+findStartDateInMonth(month2,year)) % 7 == 0){
                record2 = j+1;
                break;
            }
        }
        printf(" ");
        for(int k = 0;k<findStartDateInMonth(month3,year);k++){
            printf("   ");
        }
        for(int j = 1;j<=daysInMonth[month3];j++){
            printf("%3d",j);
            if((j+findStartDateInMonth(month3,year)) % 7 == 0){
                record3 = j+1;
                break;
            }
        }
        printf("\n");
        //second line
        for(int i = record1;i<record1+7;i++){
            printf("%3d",i);
        }
        record1 += 7;
        printf(" ");
        for(int i = record2;i<record2+7;i++){
            printf("%3d",i);
        }
        record2 += 7;
        printf(" ");
        for(int i = record3;i<record3+7;i++){
            printf("%3d",i);
        }
        record3 += 7;
        printf("\n");
        //third line
        for(int i = record1;i<record1+7;i++){
            printf("%3d",i);
        }
        record1 += 7;
        printf(" ");
        for(int i = record2;i<record2+7;i++){
            printf("%3d",i);
        }
        record2 += 7;
        printf(" ");
        for(int i = record3;i<record3+7;i++){
            printf("%3d",i);
        }
        record3 += 7;
        printf("\n");
        //fourth line
        for(int i = record1;i<record1+7;i++){
            printf("%3d",i);
        }
        record1 += 7;
        //printf("%d",record1);
        printf(" ");
        for(int i = record2;i<record2+7;i++){
            printf("%3d",i);
            if(i == daysInMonth[month2]){
                recordForFebruary = i;
                numberInLine5Month2 = false;
                numberInLine6Month2 = false;
                break;
            }
        }
        if(record2 < daysInMonth[month2])
            record2 += 7;
        //printf("%d",record2);
        printf(" ");
        for(int i = record3;i<record3+7;i++){
            printf("%3d",i);
        }
        record3 += 7;
        printf("\n");
        //fifth line
        for(int i = record1;i<record1+7;i++){
            printf("%3d",i);
            if(i == daysInMonth[month1]){
                record1 = i;
                numberInLine6Month1 = false;
                break;
            }
        }
        //space between left and middle month
        if(record1 +6 < daysInMonth[month1]){
            printf(" ");
        }
        else if(record1+6> daysInMonth[month1]){
            printf(" ");
            spacingLeft = 7 - (int)((findStartDateInMonth(month1,year) +daysInMonth[month1] ) % 7);
            if(spacingLeft == 7 && numberInLine5Month1 == false){
                spacingLeft = 0;
                printf("                    ");
            }
            else if(spacingLeft == 7 && numberInLine5Month1 == true){
                spacingLeft = 0;
            }
            if(spacingLeft>0){
                for(int i = 0;i<spacingLeft;i++){
                    printf("   ");
                }
            }
        }
        if(record2 -1 < daysInMonth[month2]){
            for(int i = record2;i<record2+7;i++){
                printf("%3d",i);
                if(i == daysInMonth[month2]){
                    record2 = i;
                    numberInLine6Month2 = false;
                    break;
                }
            }
        }
        //printf("%i",numberInLine5Feb);
        if(record2 +6 < daysInMonth[month2]){
            printf(" ");
        }
        else if(record2 +6 > daysInMonth[month2]){
            printf(" ");
            spacingLeft = 7 - (int)((findStartDateInMonth(month2,year) +daysInMonth[month2] ) % 7);
            //printf("%d",spacingLeft);
            if(!numberInLine5Month2){
                printf(" ");
            }
            if(spacingLeft == 7 && numberInLine5Month2 == false){
                spacingLeft = 0;
                printf("                    ");
            }
            else if(spacingLeft == 7 && numberInLine5Month2 == true){
                spacingLeft = 0;
            }
            if(spacingLeft>0){
                for(int i = 0;i<spacingLeft;i++){
                    printf("   ");
                }
            }
        }
        for(int i = record3;i<record3+7;i++){
                printf("%3d",i);
                if(i == daysInMonth[month3]){
                    record3 = i;
                    numberInLine6Month3 = false;
                    break;
            }
        }
        //printf("%d  %d   %d",record1,record2,record3);
        printf("\n");
        //sixth lines(if there is possible...)
        if(numberInLine6Month1){
            for(int i = record1+7;i<record1+14;i++){
                printf("%3d",i);
                if(i == daysInMonth[month1]){
                    record1 = i;
                    break;
                }
            }
        }
        if(numberInLine6Month2){
            if(!numberInLine6Month1)
                printf("                     ");
            printf(" ");
            for(int i = record2+7;i<record2+14;i++){
                printf("%3d",i);
                if(i == daysInMonth[month2]){
                    record2 = i;
                    break;
                }
            }
        }

        if(numberInLine6Month3){
            printf("                                            ");
            for(int i = record3+7;i<record3+14;i++){
                printf("%3d",i);
                if(i == daysInMonth[month3]){
                    record3 = i;
                    break;
                }
            }
        }
        printf("\n");
}
struct current{
    int currentMonth;
    int currentYear;
};
struct current findCurrentMonthAndCurrentYear()
{
    struct current cur;
    time_t timeCur;
    struct tm * ptr_time;
    time(&timeCur);
    ptr_time = localtime ( &timeCur);
    cur.currentMonth = ptr_time->tm_mon+1;
    cur.currentYear = ptr_time->tm_year+1900;
    return cur;
}

int main(int argc, char *argv[])
{
    if(argc == 2){
        // input "cal"
        struct current cur = findCurrentMonthAndCurrentYear();
        checkLeapYears(cur.currentYear);
        printHeader(cur.currentMonth,cur.currentYear);
        printCalendar(daysInMonth[cur.currentMonth],findStartDateInMonth(cur.currentMonth,cur.currentYear));
    }
    else if(argc == 3){
        //print the whole year
        checkLeapYears(atoi(argv[2]));
        printf("                               %d\n",atoi(argv[2]));
        printQuarters(atoi(argv[2]),1,2,3);
        printQuarters(atoi(argv[2]),4,5,6);
        printQuarters(atoi(argv[2]),7,8,9);
        printQuarters(atoi(argv[2]),10,11,12);
    }
    else if(argc > 3){
        if(argc == 4){
            //input "cal -m month"
            struct current cur = findCurrentMonthAndCurrentYear();
            if(strcmp(argv[2],"-m")==0){
                if(!isInteger(argv[3])){
                    for(int i = 1;i<=12;i++){
                        // if find an exact match for month
                        if(strcmp(argv[3],months[i]) == 0){
                            month = i;
                            printTheRest(cur.currentYear);
                        }
                        // else convert the month to lowercase, then convert to a number
                        else{
                            convertMonthToLowercase(argv[3]);
                            if(strncmp(argv[3],months[i],3)==0){
                                month = i;
                                printTheRest(cur.currentYear);
                            }
                        }
                    }
                }
                else if(isInteger(argv[3]) && atoi(argv[3])>12){
                    printf("cal: %d is neither a month number (1..12) nor a name\n",atoi(argv[3]));
                }
                else{
                    checkLeapYears(cur.currentYear);
                    printHeader(atoi(argv[3]),cur.currentYear);
                    printCalendar(daysInMonth[atoi(argv[3])],findStartDateInMonth(atoi(argv[3]),cur.currentYear));
                }
            }
            // if argument is a month strings (not an integer), convert them to a month number
            // input "cal month year"
            else if(!isInteger(argv[2])){
                for(int i = 1;i<=12;i++){
                    // if find an exact match for month
                    if(strcmp(argv[2],months[i]) == 0){
                        month = i;
                        printTheRest(atoi(argv[3]));
                    }
                    // else convert the month to lowercase, then convert to a number
                    else{
                        convertMonthToLowercase(argv[2]);
                        if(strncmp(argv[2],months[i],3) == 0){
                            month = i;
                            printTheRest(atoi(argv[3]));
                        }
                    }
                }
            }
            // else month is a number
            else if(atoi(argv[2])<=12){
                month = atoi(argv[2]);
                printTheRest(atoi(argv[3]));
            }
            else if(isInteger(argv[2]) && atoi(argv[2])>12){
                printf("cal: %d is neither a month number (1..12) nor a name\n",atoi(argv[3]));
            }
        }
        // input "cal -m month year";
        else if(argc ==5 && strcmp(argv[2],"-m") == 0){
            // if argument is a month strings (not an integer), convert them to a month number
            if(!isInteger(argv[3])){
                for(int i = 1;i<=12;i++){
                    // if find an exact match for month
                    if(strcmp(argv[3],months[i]) == 0){
                        month = i;
                        printTheRest(atoi(argv[4]));
                    }
                    // else convert the month to lowercase, then convert to a number
                    else{
                        //matches entirely or first 3 characters
                        convertMonthToLowercase(argv[3]);
                        if(strncmp(argv[3],months[i],3)==0){
                            month = i;
                            printTheRest(atoi(argv[4]));
                        }
                    }
                }
            }
            // else month is a number
            else if(atoi(argv[3])<=12){
                month = atoi(argv[3]);
                printTheRest(atoi(argv[4]));
            }
            else if(isInteger(argv[3]) && atoi(argv[3])>12){
                printf("cal: %d is neither a month number (1..12) nor a name\n",atoi(argv[3]));
            }
        }
        else{
            printf("Invalid input for the calendar\n");
        }
    }
    return 0;
}


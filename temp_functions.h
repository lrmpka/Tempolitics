/*
 ============================================================================
 Name        : temp_stat.h
 Author      : Pavel Karasev / GU_IoT_3216
 Version     : 
 Description : Library for Final work for Basic C course in GeekBrains IoT. Functional
                description in readme.md
 ============================================================================
*/
#ifndef TEMP_H
#define TEMP_H

// Cтруктура данных, получаемых от датчика
struct sensor {
    int8_t minute;
    int8_t hour;
    int8_t day;
    int8_t month;
    int16_t year;
    int8_t temp;
};

// Cтруктура хранения обработанных данных
struct temperature {
    int8_t sum;
    int8_t qty;
    struct sensor max, min;
};

extern struct temperature month[12];

// Прототипы применяемых функций
void record_data (struct temperature *month, int, int, int, int, int, int);
void readfile (struct temperature *month, char *, int);
int monthly_avetemp(struct temperature *month, int );
int yearly_mintemp(struct temperature *month);
int yearly_maxtemp(struct temperature *month);
int yearly_avetemp(struct temperature *month);
void tstatprint(struct temperature *month, int);
void showreadme(void);
void showhelp(void);

#endif
/* Библиотечные функции для обработки и вывода статистики температуры */

#include <stdio.h>
#include <inttypes.h>
#include "temp_functions.h"

// Описание структуры хранения обработанных данных для каждого месяца
struct temperature month[12] = {0};

// Перевод номера месяца в текстовое наименование для более наглядного представления
#define NUM_TO_MONTH switch (m) { \
                case 1: smonth = "Jan"; \
                break; \
                case 2: smonth = "Feb"; \
                break; \
                case 3: smonth = "Mar"; \
                break; \
                case 4: smonth = "Apr"; \
                break; \
                case 5: smonth = "May"; \
                break; \
                case 6: smonth = "Jun"; \
                break; \
                case 7: smonth = "Jul"; \
                break; \
                case 8: smonth = "Aug"; \
                break; \
                case 9: smonth = "Sep"; \
                break; \
                case 10: smonth = "Oct"; \
                break; \
                case 11: smonth = "Nov"; \
                break; \
                case 12: smonth = "Dec"; \
            }

// Функция записи данных в структуру month
void record_data (struct temperature *month, int y, int m, int d, int h, int mi, int t) {
    month[m].sum += t;
    if (month[m].qty == 0) {    // проверяем, впервые ли мы "зашли" в текущий месяц, если да, то кладем в min и max первые же значения
        month[m].max.temp = t;
        month[m].max.day = d;
        month[m].max.month = m;
        month[m].max.year = y;
        month[m].max.minute = mi;
        month[m].max.hour = h;
        month[m].min.temp = t;
        month[m].min.day = d;
        month[m].min.month = m;
        month[m].min.year = y;
        month[m].min.minute = mi;
        month[m].min.hour = h;
    }
    if (month[m].max.temp < t) {
        month[m].max.temp = t;
        month[m].max.day = d;
        month[m].max.month = m;
        month[m].max.year = y;
        month[m].max.minute = mi;
        month[m].max.hour = h;
    }
    if (month[m].min.temp > t) {
        month[m].min.temp = t;
        month[m].min.day = d;
        month[m].min.month = m;
        month[m].min.year = y;
        month[m].min.minute = mi;
        month[m].min.hour = h;
    }
    month[m].qty++;
}

// Функция чтения данных из файла
void readfile (struct temperature *month, char *filename, int currentyear) {
    int y, m, d, h, mi, t;
    int count=0, a;
    FILE *f;
    (currentyear == 0)||(currentyear < 1900) ? currentyear = 2023 : currentyear; // если пользователем был введен явно неверный год или если год не был введен после ключа, то присваеваем дефолтный год
    f = fopen(filename, "r");
    printf("\n");
    while ((a = (fscanf(f, "%d;%d;%d;%d;%d;%d",  &y, &m, &d, &h, &mi, &t)))!= EOF) {   // считываем файлы в жестком формате, пока не встретим конец файла
        if (a != 6) {   // если какая-то из позиций данных содержала не int, а что-то другое, то печатаем ошибку и игнорируем строку
            char error[100] = {0};
            fscanf(f, "%s", error);
            printf("***Error*** in string %d of %s wrong data format: %s Data of the string is ignored!\n", count+1, filename, error);
            count++;
        }
        else { 
            if (y != currentyear) { // если год строки отличается от анализируемого, то печатаем ошибку и игнорируем строку
                printf("***Error*** in string %d of %s the YEAR value is not correct: %d, should be: %d. Data of the string is ignored!\n", count+1, filename, y, currentyear);
            }
            else if ((m > 12)||(m < 1)) { // если месяц строки содержит ложные данные, то печатаем ошибку и игнорируем строку
                printf("***Error*** in string %d of %s the MONTH value is not correct: %d, should be from 1 to 12. Data of the string is ignored!\n", count+1, filename, m);
            }
            else if ((h > 24)||(h < 0)) { // если час строки содержит ложные данные, то печатаем ошибку и игнорируем строку
                printf("***Error*** in string %d of %s the MONTH value is not correct: %d, should be from 0 to 24. Data of the string is ignored!\n", count+1, filename, h);
            }
            else if ((m > 59)||(m < 0)) { // если минута строки содержит ложные данные, то печатаем ошибку и игнорируем строку
                printf("***Error*** in string %d of %s the MONTH value is not correct: %d, should be from 0 to 59. Data of the string is ignored!\n", count+1, filename, mi);
            }
            else if (((m==1)||(m==3)||(m==5)||(m==7)||(m==8)||(m==10)||(m==12))&&(d>31)) { // если день более, чем 31 для соответствующих месяцев, то ошибка и игнорируем строку
                printf("***Error*** in string %d of %s the DAY value is not correct: %d, should be from 1 to 31. Data of the string is ignored!\n", count+1, filename, d);
            }
            else if (d<1) { // если день менее 1, то ошибка и игнорируем строку
                printf("***Error*** in string %d of %s the DAY value is not correct: %d, should be from 1 to 31. Data of the string is ignored!\n", count+1, filename, d);
            }
            else if (((m==4)||(m==6)||(m==9)||(m==11))&&(d>30)) {  // если день более, чем 30 для соответствующих месяцев, то ошибка и игнорируем строку
                printf("***Error*** in string %d of %s the DAY value is not correct: %d, should be from 1 to 30. Data of the string is ignored!\n", count+1, filename, d);
            }
            else if ((m==2)&&((currentyear%4==0)&&(currentyear%100 == 0)||(currentyear%400 == 0))&&(d>29)) { // если день более, чем 29, а месяц февраль и год високосный, то ошибка и игнорируем строку
                printf("***Error*** in string %d of %s the DAY value is not correct: %d, should be from 1 to 29. Data of the string is ignored!\n", count+1, filename, d);
            }
            else if ((m==2)&&((currentyear%4)&&(currentyear%100)&&(currentyear%400))&&(d>28)) { // если день более, чем 28, а месяц февраль и год не високосный, то ошибка и игнорируем строку
                printf("***Error*** in string %d of %s the DAY value is not correct: %d, should be from 1 to 28. Data of the string is ignored!\n", count+1, filename, d);
            }
            else {
                record_data(month, y, m, d, h, mi, t);
            }
            count++;
        }
    }
    fclose(f);
}

// Функция вычисления средней температуры конкретного месяца
int monthly_avetemp(struct temperature *month, int m) {
    return (month[m].sum/month[m].qty);
}

// Функция вычисления минимальной температуры в году
int yearly_mintemp(struct temperature *month) {
    int min = month[1].min.temp;
    for (int i=2; i<13; i++) {
        if (month[i].min.temp < min) {
            min = month[i].min.temp;
        }
    }
    return min;
}

// Функция вычисления максимальной температуры в году
int yearly_maxtemp(struct temperature *month) {
    int max = month[1].max.temp;
    for (int i=2; i<13; i++) {
        if (month[i].max.temp > max) {
            max = month[i].max.temp;
        }
    }
    return max;
}

// Функция вычисления среднегодовой температуры
int yearly_avetemp(struct temperature *month) {
    int sum = 0;
    for (int i=1; i<13; i++) {
        sum += monthly_avetemp(month, i);
    }
    return sum/12;
}

// Функция вывода в терминал статистики
void tstatprint(struct temperature *month, int m_user) {
    char *smonth;
    if (m_user == 0) {  // стандартный вывод, если пользователь не задал ключ -m
        printf("\n**Temperature statistics**\n\n");
        for (int m=1; m < 13; m++) {
            NUM_TO_MONTH;
            printf("%s: ===> min temp: %3d    max temp: %3d    average temp: %3d\n", smonth, month[m].min.temp, month[m].max.temp, monthly_avetemp(month, m));
        }
        printf("\n");
        printf("Year %4d ===> min temp: %3d    max temp: %3d    average temp: %3d\n\n", month[1].max.year,  yearly_mintemp(month), yearly_maxtemp(month), yearly_avetemp(month));
    }
    else {      // если пользователь задал ключ -m, вывод только статистики за выбранный месяц
        int m = m_user;
        NUM_TO_MONTH;
        printf("\n**Temperature statistics (for month %d)**\n\n", m);
        printf("%s: ===> min temp: %3d    max temp: %3d    average temp: %3d\n", smonth, month[m].min.temp, month[m].max.temp, monthly_avetemp(month, m));
        printf("\n");
    }
}

// Функция вывода текста файла readme.md, в котором описан функционал программы подробно
void showreadme(void) {
    FILE *f;
    char c;
    f = fopen("readme.md", "r");
    while (!feof(f)) {
        fscanf(f, "%c", &c);
        printf("%c", c);
    }
    fclose(f);
}

// Функция вывода минимального Help, показывающего применимые ключи
void showhelp(void) {
    printf("Possible command switches:\n");
    printf("-h - show the information about program and interface\n");
    printf("-a - show readme.md file which contains functional description");
    printf("-m <month number> - show the temperature statistics for chosen month only (you need to put integer number from 1 to 12)");
    printf("-f <filename.csv> - you can specify the name (or full path) of the .csv file with temperature statistics which you want to analyze (standard filename is tempdata.csv)");
    printf("-y <year number> - change the value of currentyear to analyze data of any different year than default\n");
}

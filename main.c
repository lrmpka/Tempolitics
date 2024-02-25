/*
============================================================================
 Name        : temp_stat
 Author      : Pavel Karasev / GU_IoT_3216
 Version     : 
 Description : Final work for Basic C course in GeekBrains IoT. Functional
                description in readme.md
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>
#include "temp_functions.h"

enum {FILE_PATH = 256, SIZE = 100};

int main (int argc, char *argv[]) {
    char filename[FILE_PATH] = "tempdata.csv";
    int rez = 0, m_user = 0;
    int currentyear = 2023;
    while ((rez = getopt(argc, argv, "haf:m:y:")) != -1) {
        switch(rez) {
            case 'h': showhelp();   // "Help"
            return 0;
            case 'a': showreadme(); // "About"
            return 0;
            case 'f': strcpy(filename, optarg); // "File"
            case 'm': m_user = atoi(optarg);    // "Month"
            case 'y': currentyear = atoi(optarg);   // "Year"
        }
    }
    readfile(month, filename, currentyear);
    tstatprint(month, m_user);
    return 0;
}
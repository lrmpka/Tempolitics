============================================================================  
 Name        : Tempolitics  
 Author      : Pavel Karasev  
 Version     : 0.1.0  
 Description : Console application for make analysis of temperature data from file  
============================================================================  
  
This programm collects temperature data from .csv file which contains strings in format yyyy;mm;dd;h;min;temp  
Default output: min, max and average temperature value per each month and same statistics value for the whole year.  
Default year - 2023. If you have data for different year, use command line switch.  
  
You can use special command line switches:  
-h - show the information about command switches  
-a - show readme.md file which contains functional description  
-m <month number> - show the temperature statistics for chosen month only (you need to put integer number from 1 to 12)  
-f <filename.csv> - you can specify the name (or full path) of the .csv file with temperature statistics which you want to analyze  
                    (standard filename is "tempdata.csv")  
-y <year number> - change the value of currentyear to analyze data of any different year than default  

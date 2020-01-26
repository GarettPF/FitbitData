#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _TARGET_PATIENT "12cx7"
#define _MINUTES_PER_DAY 1440

typedef enum sleep {
	NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit {
	char patient[10];
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

/*
Function: mystrtok
Description: My version of strtok(). Will allow me to get a 
			token with NULL value & not skip over.
	@param **stringp			The string value to get a token
	@param *delim				The char/string to cut token off
	@return	char*				The starting address of the token
*/
char* mystrtok(char** stringp, const char* delim);

/*
Function: read_data
Description: Function able to read data from a fitbit data file
	@param	userData[]			The array to store fitbit data
	@param	*fitbit_data		The fitbit data FILE
	@return	void
*/
void read_data(FitbitData userData[], FILE* fitbit_data);

/*
Function: calc_total
Description: Function to calculate the total of calories,
			distance walked, floors, heart rate, and steps taken
	@param userData[]			The fitbit user data
	@param *total_calories		return value for total calories
	@param *total_distance		return value for total distance
	@param *total_floors		return value for total floors
	@param *total_heartRate		return value for total heartRate
	@param *total_steps			return value for total steps
	@return void
*/
void calc_total(FitbitData userData[], double* total_calories, double* total_distance, 
	unsigned int* total_floors, unsigned int* total_heartRate, unsigned int* total_steps);

/*
Function: get_max_steps
Description: will get the last and maximum number of steps
			taken in one minute.
	@param userData[]			The fitbit user data
	return int					The maximum
*/
int get_max_steps(FitbitData userData[]);

/*
Function: poorest_sleepRange
Description: Gets the range from beggining time to end time of the 
			worse sleep range of the day
	@param userData[]			The fitbit user data
	@param *startTime			start time of the range
	@param *endTime				end time of the range
	@return void
*/
void poorest_sleepRange(FitbitData userData[], char* startTime, char* endTime);
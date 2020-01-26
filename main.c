/**********************************************************
* Programmer: Garett Pascual-Folster				   *
* Class: CptS 122, Spring, 2020; Lab Section 4		   *
* Programming Assignment: PA1						   *
* Date: January 20, 2020							   *
* Description: This program works with fitbit data	   *
**********************************************************/

#include "fitbit.h"

int main(void)
{
	FitbitData userData[_MINUTES_PER_DAY] = {"", "", 0.0, 0.0, 0, 0, 0, NONE};
	FILE *fitbit_data = fopen("FitbitData.csv", "r");

	double calories_t, distance_t;
	unsigned int floors_t, heartR_t, steps_t, max_steps;

	char startTime[9], endTime[9];

	if (fitbit_data == NULL)
	{ // check if file exists
		printf("File failed to open\n");
		exit(-1);
	}

	// Reading each record into fitbit_data
	read_data(userData, fitbit_data);
	fclose(fitbit_data);

	// calculate total
	calc_total(userData, &calories_t, &distance_t,
			 &floors_t, &heartR_t, &steps_t);

	// average heart rate over the day
	double avg_heartR = (double)heartR_t / _MINUTES_PER_DAY;

	// get maximum steps in a minute
	max_steps = get_max_steps(userData);

	// get poorest sleep range
	poorest_sleepRange(userData, startTime, endTime);

	// write results
	FILE *results = fopen("Results.csv", "w");
	fprintf(results, "Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
	fprintf(results, "%lf, %lf, %d, %d, %lf, %d, %s:%s\n",
		   calories_t, distance_t, floors_t, steps_t, avg_heartR, max_steps, startTime, endTime);
	fclose(results);

	printf("Finished Execution\n");

	return 0;
}
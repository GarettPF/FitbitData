#include "fitbit.h"

char* mystrsep(char** string_ptr, const char* breakpoint) {
	char* start = *string_ptr, * p;

	p = (start != NULL) ? strpbrk(start, breakpoint) : NULL;
	if (p == NULL) {
		*string_ptr = NULL;
	}
	else {
		*p = '\0';
		*string_ptr = p + 1;
	}
	return start;
}

void read_data(FitbitData userData[], FILE* fitbit_data) {
	char* line,
		* tok = NULL;
	int entry = 0, isDuplicate = 0;

	while (entry < _MINUTES_PER_DAY) {
		// get next line
		line = (char*)malloc(256);
		fgets(line, 256, fitbit_data);

		// get patient ID
		tok = mystrsep(&line, ",");
		if (!strcmp(tok, _TARGET_PATIENT)) { // Check if right patient
			strcpy(userData[entry].patient, tok);
			
			// get minute
			tok = mystrsep(&line, ",");

			// check if duplicate minute
			for (int i = entry; i >= 0; i--) {
				isDuplicate = 1 ? !strcmp(tok, userData[i].minute) : 0;
			}

			if (!isDuplicate) {
				strcpy(userData[entry].minute, tok);

				// rest of the data
				tok = mystrsep(&line, ",");
				userData[entry].calories = tok != NULL ? atof(tok) : 0.0;

				tok = mystrsep(&line, ",");
				userData[entry].distance = tok != NULL ? atof(tok) : 0.0;

				tok = mystrsep(&line, ",");
				userData[entry].floors = tok != NULL ? atoi(tok) : 0;

				tok = mystrsep(&line, ",");
				userData[entry].heartRate = tok != NULL ? atoi(tok) : 0;

				tok = mystrsep(&line, ",");
				userData[entry].steps = tok != NULL ? atoi(tok) : 0;

				tok = mystrsep(&line, ",");
				switch (atoi(tok)) {
				case ASLEEP:
					userData[entry].sleepLevel = ASLEEP;
					break;
				case AWAKE:
					userData[entry].sleepLevel = AWAKE;
					break;
				case REALLYAWAKE:
					userData[entry].sleepLevel = REALLYAWAKE;
					break;
				default:
					userData[entry].sleepLevel = NONE;
				}
				entry++;
			}
		}
	}
}

void calc_total(FitbitData userData[], double* total_calories, double* total_distance, 
	unsigned int* total_floors, unsigned int* total_heartRate, unsigned int* total_steps) {

	// initialize values to 0 just incase
	*total_calories = *total_distance = 0.0;
	*total_floors = *total_heartRate = *total_steps = 0;

	for (int i = 0; i < _MINUTES_PER_DAY; ++i) {
		*total_calories += userData[i].calories;
		*total_distance += userData[i].distance;
		*total_floors += userData[i].floors;
		*total_heartRate += userData[i].heartRate;
		*total_steps += userData[i].steps;
	}
}

int get_max_steps(FitbitData userData[]) {
	unsigned int maximum = 0;

	for (int i = 0; i < _MINUTES_PER_DAY; ++i) {
		if (userData[i].steps >= maximum) {
			maximum = userData[i].steps;
		}
	}

	return maximum;
}

void poorest_sleepRange(FitbitData userData[], char* startTime, char* endTime) {
	int maximum_sum = 0, sum = 0;
	char tmpStart[9], tmpEnd[9];

	for (int i = 0; i < _MINUTES_PER_DAY; ++i) {
		sum = 0;

		if (userData[i].sleepLevel > ASLEEP) {
			strcpy(tmpStart, userData[i].minute);
			sum += userData[i].sleepLevel;

			for (int j = i + 1; j < _MINUTES_PER_DAY; ++j) {

				if (userData[j].sleepLevel > ASLEEP) {
					sum += userData[j].sleepLevel;
					strcpy(tmpEnd, userData[j].minute);

				}
				else j = _MINUTES_PER_DAY;

			}

			// update if sum > current max
			if (sum >= maximum_sum) {
				maximum_sum = sum;
				strcpy(startTime, tmpStart);
				strcpy(endTime, tmpEnd);
			}

		}

	}

}
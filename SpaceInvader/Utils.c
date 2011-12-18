#include "Utils.h"

void milisec_sleep(int milisec)
{
	// Transforme les milisecs en secondes et nano secondes
	struct timespec req = { 0 }, rem = { 0 };
	time_t sec = milisec / 1000;
	milisec = milisec - (sec * 1000);
	req.tv_sec = sec;
	req.tv_nsec = milisec * 1000000L;
	nanosleep(&req, &rem);
}
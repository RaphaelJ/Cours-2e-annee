#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

#define NTHREADS 4

using namespace std;

pthread_mutex_t mutex;

void* testThreads(void* vdata);
int main(void);

void* testThreads(void* vdata)
{
	int id = *((int*) vdata);
	
	sleep(2);
	
	pthread_mutex_unlock(&mutex);
	
	sleep(10);
	
	cerr << getpid()
	     << '.' << pthread_self()
	     << ": " << id << '/'
	     << *((int*) vdata) << endl;
}

pthread_t IDs[NTHREADS];

int main(void)
{
	pthread_mutex_init(&mutex, NULL);
		
	pthread_mutex_lock(&mutex);
	
	for (int i = 0; i < NTHREADS; i++) {
		if (pthread_create(&IDs[i], NULL, testThreads, &i) != 0)
			cerr << "Erreur lors du lancement du thread" << endl;
		else
			cout << "Thread n°" << IDs[i] << " lancé" << endl;
		
	}
	cout << "Threads lancés" << endl;
	
	pause();
	
	return 0;
}
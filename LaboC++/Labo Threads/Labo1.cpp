#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <pthread.h>

using namespace std;

typedef struct _DATA {
	char nom[40];
	int age;
} DATA;

void* testThreads(void* vdata)
{
	sleep(rand() % 10 + 1);
	
	DATA* data = (DATA*) vdata;
	
	cout << "Nom : " << data->nom << endl
	     << "Age : " << data->age << endl;
	
	return NULL;
}

int main(void)
{
	DATA args[] = {
	     { "Raphael", 19 },
	     { "Pierre", 23 },
	     { "Alexandre", 12 }
	};
	const int nThreads = 3;
	
	srand(time(NULL));
	pthread_t IDs[nThreads];
	
	for (int i = 0; i < nThreads; i++) {
		if (pthread_create(&IDs[i], NULL, testThreads, &args[i]) != 0)
			cerr << "Erreur lors du lancement du thread" << endl;
		else
			cout << "Thread n°" << IDs[i] << " lancé" << endl;
		
	}
	cout << "Threads lancés" << endl;
	
	for (int i = 0; i < nThreads; i++) {
		void* retval;
		if (pthread_join(IDs[i], &retval) != 0)
			cerr << "Erreur lors de la jointure au thread" << endl;
		else
			cout << "Thread n°" << IDs[i] << " coupé" << endl;
	}
	cout << "Threads arretés" << endl;
	
	return 0;
}
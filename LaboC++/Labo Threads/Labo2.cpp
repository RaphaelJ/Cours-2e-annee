#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NTHREADS 4
#define NITE 80

using namespace std;

void* testThreads(void* vdata)
{
	int nTabs = *((int*) vdata);
	
	for (int i = 0; i < NITE; i++) {
		char c;
		
		FILE* f = fopen("fichier", "r");
		
		while (fread(&c, 1, 1, f)) {
			for (int iTab = 0; iTab < nTabs; iTab++)
				cout << '\t';
		
			cout << '*' << endl;
			fflush(stdout);
		}
		fclose(f);
	}
	
	return NULL;
}

int main(void)
{
	int args[NTHREADS];
	pthread_t IDs[NTHREADS];
	
	for (int i = 0; i < NTHREADS; i++) {
		args[i] = i;
		
		if (pthread_create(&IDs[i], NULL, testThreads, args + i) != 0)
			cerr << "Erreur lors du lancement du thread" << endl;
		else
			cout << "Thread n°" << IDs[i] << " lancé" << endl;
		
	}
	cout << "Threads lancés" << endl;
	
	for (int i = 0; i < NTHREADS; i++) {
		void* retval;
		if (pthread_join(IDs[i], &retval) != 0)
			cerr << "Erreur lors de la jointure au thread" << endl;
		else
			cout << "Thread n°" << IDs[i] << " coupé" << endl;
	}
	cout << "Threads arretés" << endl;
	
	return 0;
}
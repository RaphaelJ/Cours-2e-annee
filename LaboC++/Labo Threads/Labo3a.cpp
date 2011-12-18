#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

#define NTHREADS 4

using namespace std;

void* testThreads(void* vdata);
void FermetureThreadsSecondaires(int sig);
int main(void);
void FermetureThreadPrincipal(int sig);

void* testThreads(void* vdata)
{
	cerr << "Debut du thread " << getpid()
	     << '.' << pthread_self() << endl;
	
	// Remet à zéro les signaux
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	
	// Initialise le signal d'annulation
	Action.sa_handler = FermetureThreadsSecondaires;
	sigaction(SIGUSR1, &Action, NULL);
	
	pause();
}

void FermetureThreadsSecondaires(int sig)
{
	cerr << "Fin du thread " << getpid() << getpid()
	     << '.' << pthread_self() << endl;
	    
	// Remet à zéro les signaux
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	
	kill(getpid(), SIGUSR1);
	     
	pthread_exit(NULL);
}

pthread_t IDs[NTHREADS];

int main(void)
{
	// Remet à zéro les signaux
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	
	// Initialise le signal d'annulation
	Action.sa_handler = FermetureThreadPrincipal;
	sigaction(SIGINT, &Action, NULL);
	
	int args[NTHREADS];	
	for (int i = 0; i < NTHREADS; i++) {
		args[i] = i;
		
		if (pthread_create(&IDs[i], NULL, testThreads, args + i) != 0)
			cerr << "Erreur lors du lancement du thread" << endl;
		else
			cout << "Thread n°" << IDs[i] << " lancé" << endl;
		
	}
	cout << "Threads lancés" << endl;
	
	pause();
	
	return 0;
}

void FermetureThreadPrincipal(int sig)
{
	kill(getpid(), SIGUSR1);
	
	for (int i = 0; i < NTHREADS; i++) {
		void* retval;
		if (pthread_join(IDs[i], &retval) != 0)
			cerr << "Erreur lors de la jointure au thread" << endl;
		else
			cout << "Thread n°" << IDs[i] << " coupé" << endl;
	}
	cout << "Threads arretés" << endl;
	
	exit(0);
}
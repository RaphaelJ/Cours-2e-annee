#include <stdio.h>
#include <stdlib.h>

#define MAX_CH_LENGHT 100

char* LireChaine(void)
{
	char* ch = (char*) malloc(sizeof (char) * MAX_CH_LENGHT);
	char c;
	short i = 0;
	
	while (i < MAX_CH_LENGHT && (c = getchar()) != '\n') {
		ch[i] = c;
		
		i += 1;
	}
	
	return ch;
}

void AfficheChaine(char* ch)
{
	printf("%s", ch);
}
#include "ReadChar.h"

struct termios Term, SaveTerm;

int ReadChar()
{
	char ChLu;
	
	if (tcgetattr(0, &Term) == -1)
		return -1;

	// Passe le terminal en mode non cannonique
	SaveTerm = Term;
	Term.c_lflag &= ~(ICANON | ECHO | ISIG);
	Term.c_cc[VMIN] = 1;
	
	if (tcsetattr(0, TCSANOW, &Term) == -1)
		return -1;

	fflush(stdin);

	if (read(0, &ChLu, 1) != 1)
		return SortieIoctl(-1);
	if (ChLu == Term.c_cc[VINTR])
		return SortieIoctl(3);
	if (ChLu == '\033') {
		if (read(0, &ChLu, 1) == 1) {
			if ((char) ChLu == '[') {
				if (read(0, &ChLu, 1) != 1)
					return SortieIoctl(-1);
				if ((char) ChLu == 'A')
					return SortieIoctl(KEY_UP);
				if ((char) ChLu == 'B')
					return SortieIoctl(KEY_DOWN);
				if ((char) ChLu == 'C')
					return SortieIoctl(KEY_RIGHT);
				if ((char) ChLu == 'D')
					return SortieIoctl(KEY_LEFT);
				return SortieIoctl(-1);
			}
		}
	}

	return SortieIoctl(ChLu);
}

// Restaure la configuration du terminal (mode cannonique)
int SortieIoctl(int Code)
{
    if (tcsetattr(0, TCSANOW, &SaveTerm) == -1)
	return -1;
    return Code;
}

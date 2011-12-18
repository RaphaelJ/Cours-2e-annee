#ifndef READCHAR_H
#define READCHAR_H

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "Defines.h"

int ReadChar();
int SortieIoctl(int Code);

#endif
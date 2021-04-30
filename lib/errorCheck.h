#ifndef ERRORCHECK_H_
#define ERRORCHECK_H_

#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


void check_getLine(ssize_t nRead);

void check_fscanf(int nRead);


#endif
#include "Integer.h"

void copyInt(void *target, void *dest)
{
	int *obj = (int *)target;
	int *cbBuffer = (int *)dest;
	
	*cbBuffer = *obj ;
}
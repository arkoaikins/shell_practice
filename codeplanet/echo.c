#include "alxse.h"

/**
 * egfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: true if freed, otherwise false.
 */

int egfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

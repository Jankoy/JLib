# JLib

## About

JLib is a STB header-only style library I am developing for personal use with strings and allocators and such things.

## Quick Start

```c
#include <stdio.h>
#define JLIB_IMPLEMENTATION
#include "jlib.h"

int main(void)
{
	arena_t arena = {0};

	int* number = arena_alloc(&arena, sizeof(int));
	*number = 69;

	string_t string = string_create(&arena, sizeof(char) * 5);
	string.str = "jlib";

	printf("*number = %d, string.str = %s\n", *number, string.str);

	return 0;
}
```

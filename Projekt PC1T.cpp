
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "1985.h"


int main()
{	

	printTitle();
	int film;
	int z = 1;
	int fail = 0;
	while (z == 1)
	{
		film = films();
		int r = 1;
		int d;
		printf("Prejete si mazat(O) nebo obsadit(1)\n");
		scanf_s("%d", &d);

		if (d == 1)
		{
			while (r == 1)
			{
				int random;
				salprint(film);
				printf("Prejete si vybrat nahodne?(1/0)\n");
				scanf_s("%d", &random);
				if (random == 1)
				{
					randomizer(film);
				}
				else
				{
					book(film);
				}
				printf("Prejete si dalsi listek? (1/0)\n");
				scanf_s("%d", &r);
				system("cls");

			}
		}
		else if (d == 0)
		{
			while (r == 1)
			{
				if (remove(film) == -1)
				{
					r = 0;
					fail = 1;
				}
				else
				{
					salprint(film);
					printf("Prejete si mazat dalsi listek? (1/0)\n");
					scanf_s("%d", &r);
					system("cls");
				}
			}

		}
		if (fail == 1)
		{	
			fail = 0;
		}
		else
		{
			salprint(film);
			resetSal(film);
		}
		printf("Prejete se vratit na uvodni stranku?(0/1)\n");
		scanf_s("%d", &z);
	}
}


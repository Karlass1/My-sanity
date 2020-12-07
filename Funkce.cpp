#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "1985.h"


void printTitle()
{
	char welcome[] = "Welcome to Kozmostar!";
	int width = 42;
	int offset = width / 2 - strlen(welcome) / 2;

	for (int i = 0; i < width; i++) {
		printf("=");
	}
	printf("\n");
	for (int i = 0; i < offset; i++) printf(" ");

	for (int i = 0; i < strlen(welcome); i++) {
		printf("%c", welcome[i]);
	}
	printf("\n");
	for (int i = 0; i < width; i++) {

		printf("=");
	}
	printf("\n");
	printf("\n");
}
int films()
{
	printf("1 - Tohle je Sparta\n");
	printf("2 - Johhny English\n");
	printf("3 - Blazniva strela\n");
	printf("4 - Team America\n");
	printf("5 - Spaceballs\n");
	printf("6 - Disaster movie\n");
	printf("\nZadejte cislo filmu\n");
	int f = 0;
	while (f < 1 || f>6)
	{
		scanf_s("%d", &f);
		if (f < 1 || f>6)
		{
			printf("Neplatny vstup, opakujte akci\n");
		}
	}
	printf("1 - 15:00-16:40\n");
	printf("2 - 16:50-18:30\n");
	printf("3 - 18:40-20:20\n");
	int c = 0;
	printf("\nZadejte cas\n");
	while (c < 1 || c>3)
	{
		scanf_s("%d", &c);
		if (c < 1 || c>3)
		{
			printf("Neplatny vstup, opakujte akci\n");
		}
	}
	f--;
	c--;
	int skip;
	skip = f * 3 * 108 + c * 108;
	return skip;
}
void codeGen()
{
	srand(time(NULL));
	int c = 0;
	rand();
	c = rand();
	printf("Vas kod vstupenky je %05d\n", c);
}
void randomizer(int film)
{
	for (size_t i = 0; i < 3; i++)
	{
		printf("|");
		for (size_t j = 0; j < 3; j++)
		{
			printf("%d|", i * 3 + j);
		}
		printf("\n");
	}
	printf("Zadejte sektor\n");
	int sector = -1;
	while (sector < 0 || sector>8)
	{
		scanf_s("%d", &sector);
		if (sector < 0 || sector>8)
		{
			printf("Neplatny vstup, opakujte akci\n");
		}
	}
	FILE* sal;
	fopen_s(&sal, "sal.txt", "r+");
	int p = (sector % 3) * 4 + (sector - sector % 3) / 3 * 36;
	fseek(sal, p + film, SEEK_SET);
	int cyend = 0;
	for (size_t i = 0; i < 3 && cyend == 0; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (fgetc(sal) == '0')
			{
				fseek(sal, -1, SEEK_CUR);
				fputc('1', sal);
				fclose(sal);
				cyend = 1;
				break;

			}
		}
		fseek(sal, 8, SEEK_CUR);
	}
	if (cyend == 0)
	{
		printf("Sektor je plny\n");
	}
	codeGen();
}
void resetSal(int film)
{
	int r;
	printf("Prejete si resetovat obsazeni?(1/0)\n");
	scanf_s("%d", &r);
	if (r == 1)
	{

		FILE* fl;
		fopen_s(&fl, "sal.txt", "r+");
		fseek(fl, film, SEEK_SET);
		for (int i = 0; i < 9 * 12; i++) {
			fputc('0', fl);
		}
		fclose(fl);
	}
}
int getPlace()
{
	printf("Vyberte radu\n");
	char rada;
	while (true)
	{
		scanf_s("%c", &rada);

		if (rada >= 'a' && rada <= 'z')
		{
			rada -= 'a';
		}
		else if (rada >= 'A' && rada <= 'Z')
		{
			rada -= 'A';
		}
		else if (rada != '\n')
		{
			printf("Musite zadat pismeno, opakujte akci\n");
			continue;
		}
		if (rada >= 0 && rada < 9)
		{
			break;
		}
		else if ((rada < 0 || rada >= 9) && rada != '\n')
		{
			printf("Byla vybrana neplatna rada, opakujte akci\n");
			continue;
		}
	}
	printf("Vyberte misto\n");
	char misto[3];
	char* test;
	int ret;
	while (true)
	{
		scanf_s("%2s", misto, 3);
		ret = strtod(misto, &test);
		if (strcmp(test, "") == 0)
		{
			if (ret > 0 && ret <= 12)
			{
				break;
			}
			else
			{
				printf("Zadali jste neplatny vstup, opakujte akci\n");
			}
		}
		else if (strcmp(test, ""))
		{
			printf("Zadali jste neplatny vstup, opakujte akci\n");
		}
	}
	int total = rada * 12 + (ret - 1);
	return total;
}
void book(int film)
{
	FILE* sal;
	fopen_s(&sal, "sal.txt", "r+");
	if (sal == NULL)
	{
		printf("Soubor se nepovedlo nacist\n");
	}
	else
	{
		while (true)
		{
			fseek(sal, getPlace() + film, SEEK_SET);
			if (fgetc(sal) == '1')
			{
				printf("Misto je obsazeno\n");
			}
			else
			{
				fseek(sal, -1, SEEK_CUR);
				fputc('1', sal);
				fclose(sal);
				break;
			}
		}
	}
	codeGen();
}
void salprint(int film)
{

	printf("==================PLATNO==================\n\n");
	FILE* sal;
	fopen_s(&sal, "sal.txt", "r+");
	fseek(sal, film, SEEK_SET);
	for (size_t i = 0; i < 9; i++)
	{
		printf("%c ", 'A' + i);
		if (i % 2 == 1)
		{
			printf(" ");
		}
		printf("|");
		for (size_t j = 1; j <= 12; j++)
		{
			if (fgetc(sal) == '1')
			{
				printf("\x1B[31m");
				printf("XX");
				printf("\x1B[0m");
				printf("|");
			}
			else
			{
				printf("%02d|", j);
			}
			if (j == 12)
			{
				if (i % 2 == 0)
				{
					printf(" ");
				}
				printf(" %c ", 'A' + i);
				printf("\n");
			}

		}
	}
	fclose(sal);
}
int remove(int film)
{
	FILE* sal;
	fopen_s(&sal, "sal.txt", "r+");
	if (sal == NULL)
	{
		printf("Soubor se nepovedlo nacist\n");
		return -1;
	}
	bool empty = true;
	fseek(sal, film, SEEK_SET);
	for (size_t i = 0; i < 108; i++)
	{
		if (fgetc(sal) == '1')
		{
			empty = false;
			break;
		}

	}
	if (empty == true)
	{
		system("cls");
		printf("Sal neni obsazen\n");
		fclose(sal);
		return -1;
	}
	else
	{
		fclose(sal);
		salprint(film);
		while (true)
		{
			fopen_s(&sal, "sal.txt", "r+");
			fseek(sal, getPlace() + film, SEEK_SET);
			if (fgetc(sal) == '0')
			{
				printf("Misto neni obsazeno\n");
			}
			else
			{
				fseek(sal, -1, SEEK_CUR);
				fputc('0', sal);
				fclose(sal);
				break;
			}
		}
		system("cls");
	}
	return 0;
}
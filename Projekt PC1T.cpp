
#include <string.h>
#include <iostream>
void resetSal()
{
	int r;
	printf("Prejete si resetovat obsazeni?(1/0)\n");
	scanf_s("%d", &r);
	if(r == 1)
	{

		FILE* fl;
		fopen_s(&fl, "sal.txt", "w");
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
		else if(rada != '\n')
		{
			printf("Musite zadat pismeno, opakujte akci\n");
			continue;
		}
		if (rada >= 0 && rada < 9)
		{
			break;
		}
		else if ((rada < 0 || rada >= 9) && rada!= '\n')
		{
			printf("Byla vybrana neplatna rada, opakujte akci\n");
			continue;
		}
	}
	printf("Vyberte misto\n");
	char misto [3];
	char* test;
	int ret;
	while (true)
	{
		scanf_s("%2s",misto, 3);
		ret = strtod(misto, &test);
		if (strcmp(test, "") == 0)
		{
			if (ret>0 && ret<=12)
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
	int total = rada * 12 + (ret-1);
	return total;
}
void book()
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
			fseek(sal, getPlace(), SEEK_SET);
			if (fgetc(sal) == '1')
			{
				printf("Misto je obsazeno");
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
}
void salprint()
{

	printf("==================PLATNO==================\n\n");
	FILE* sal;
	fopen_s(&sal, "sal.txt", "r+");
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
				printf(" %c ", 'A'+ i);
				printf("\n");
			}
			
		}
	}
	fclose(sal);
}
int main()
{	
	int r = 1;
	while (r == 1)
	{	
		int random;
		salprint();
		printf("Prejete si vybrat nahodne?(1/0)");
		scanf_s("%d", &random);
		if (random == 1)
		{

		}
		else
		{
			book();
		}
		printf("Prejete si dalsi listek? (1/0)\n");
		scanf_s("%d", &r);
		system("cls");

	}
	salprint();
	resetSal();
}


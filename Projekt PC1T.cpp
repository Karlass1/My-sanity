

#include <iostream>
void book()
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
			printf("Musite zadat pismeno\n");
		}
		if (rada >= 0 && rada < 9)
		{
			break;
		}
		else if ((rada < 0 || rada >= 9) && rada!= '\n')
		{
			printf("Byla vybrana neplatna rada\n");
		}


	}
	


	printf("Vyberte misto\n");
	int misto;
	scanf_s("%d", &misto);

}
void salprint()
{

	printf("=============PLATNO=============\n\n");

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
			printf("%02d|", j);
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
}
int main()
{
	salprint();
	book();
}


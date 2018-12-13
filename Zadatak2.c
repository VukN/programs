#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	char ime[15];
	char prezime[20];
	int index;
}student;


student Unos_Studenta()
{
	student s = { "", "", 0};
	printf("Ime studenta: ");
	scanf("%s", s.ime);
	printf("\n Prezime: ");
	scanf("%s", s.prezime);
	printf("\n Index: ");
	scanf("%d", &s.index);

	return s;
}

void pretraga( student s[], size_t size)
{
	int match = 0 ;
	int i ;
	char prez ;

	printf("Uneti prvo slovo prezimena: ");
	scanf(" %c", &prez);
	for( i=0; i < size; ++i)
	{
		if(s[i].prezime[0] == prez)
		{
		 	match += 1;
			printf( "Ime: %s\nPrezime:%s\nIndex:%d\n", s[i].ime, s[i].prezime, s[i].index );
		}
	}
	if( match == 0)
		printf("Nema prezimena na slovo '%c'\n\n", prez);
}

int izmena( student s[], size_t size)
{
	int unos = 0;
	int n;

	printf("Redni broj studenta: ");
	scanf("%d", &n );

	if( n<=0 || n>size)
		return -1;
	n -= 1;
	printf( "Ime:%s\nPrezime:%s\nIndex:%d\n", s[n].ime, s[n].prezime, s[n].index);
	do{
		printf("Odaberite sta menjate: \n\n1.) Ime\n2.) Prezime\n3.) Index\n4.) Izlaz\n\n Broj: ");
		scanf("%d", &unos);

		if( unos == 1)
		{
			printf("Novo ime: ");
			scanf( "%s", s[n].ime);
		}
		else if( unos == 2)
		{
			printf("Novo prezime: ");
			scanf( "%s", s[n].prezime);
		}
		else if(unos == 3)
		{
			printf("Nov index: ");
			scanf("%d", &s[n].prezime);
		}
		else
			printf("Nepostojeci broj: \n");

	  }while( unos != 4);

	return 0;
}

void ispis( student s[ ], size_t size )
{
  int i ;
  for( i = 0 ; i < size ; ++i )
    if( strcmp( s[ i ].ime, "" ) != 0 )
    {
      printf( "r.br: %d\n", i + 1 ) ;
      printf( "Ime:%s\nPrezime:%s\nIndex:%d\n", s[ i ].ime, s[ i ].prezime, s[ i ].index ) ;
    }
}

int Unos_ispis()
{
		int unos = 0;

		printf("******************** MENI ***********************\n");
		printf ("1. Unos novog studenta\n");
		printf ("2. Pretraga studenta po prezimenu\n");
		printf ("3. Ispis svih studenata\n");
		printf ("4. Izmena studenta\n");
		printf ("5. Izlaz\n\n");

		printf("***********************************************\n");
		scanf("%d%", &unos);

		if(unos<1 || unos >5)
			unos = 0;

		return unos;
}

int main()
{
	FILE* file;
	student s[10] = {"", "", 0};
	int br_s = 0;
	int unos ;
	int i;
	size_t size = 10;
	size_t nob = sizeof(student);
	char* name = "studenti.txt";
	char* str;


	if(!(file = fopen( name, "r")))
	{
		file = fopen( name, "w");
		fclose(file);
	}
	else
	{
		file = fopen( name, "r");
		str = (char* ) malloc(nob +1);
		while(! feof(file))
		{
			if( getline( &str, &nob, file) == -1)
				continue;

			strcpy( s[br_s].ime, strtok(str, " "));
			strcpy( s[br_s].prezime, strtok(str, " "));
			s[br_s].index = atoi(strtok( NULL, " "));
			br_s++;
		}
		free(str);
		fclose(file);
	}

	do
	{
		unos = Unos_ispis();

		if(unos == 1)
		{
			if(br_s >= size)
			{
				printf("Nema kapaciteta za unos studenata!\n");
				continue;
			}
			s[br_s++] =  Unos_Studenta();
		}
		else if( unos == 2)
			pretraga(s, size);
		else if(unos == 3)
			ispis(s, size);//treba ispis da se otkuca
		else if( unos == 4)
			izmena(s, size);
	}while(unos !=5);

	file = fopen(name, "w");
	for( i = 0; i < br_s; i++)
		fprintf( file, "%s %s %d \n", s[i].ime, s[i].prezime, s[i].index);


}

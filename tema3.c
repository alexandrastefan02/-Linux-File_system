#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Stefan Alexandra 324CB
// structura director
typedef struct director
{
	char *nume;
	struct director *parinte, *directories;
	struct fisier *files;
	struct director *st, *dr;
} director, *TArbdir;

// structura fisier
typedef struct fisier
{
	char *nume;
	struct director *parinte;
	struct fisier *st, *dr;
} fisier, *TArbfisier;

// functie utilitara care ne ajuta sa cream frunza
TArbfisier ConstrF(char *nume)
{
	TArbfisier aux = (TArbfisier)malloc(sizeof(fisier));
	if (!aux)
		return NULL;
	aux->nume = malloc(50);
	strcpy(aux->nume, nume);
	aux->st = aux->dr = NULL;
	return aux;
}

int touch(TArbdir a, char *nume)
{
	// cazul1:
	// inseram o frunza, arborele fiind initial gol
	if (a->files == NULL)
	{
		a->files = ConstrF(nume);
		if (!a->files)
			return 0;
		a->files->parinte = a;
	}
	else
	// caz2
	{
		TArbfisier aux, n, p;
		n = a->files;
		while (n)
		{
			p = n;
			if (strcmp(n->nume, nume) == 0)
			{
				// am gasit un fisier care deja are numele celui
				// pe care am fi vrut sa l inseram
				printf("File %s already exists!\n", nume);
				// afisez mesajul coresp.
				return 0;
			}
			if (strcmp(nume, n->nume) < 0)
				n = n->st;
			else
				n = n->dr;
		}
		TArbdir x = a->directories;
		TArbdir y;
		while (x)
		{
			y = x;
			if (strcmp(x->nume, nume) == 0)
			{
				// verificam daca exista director cu acelasi nume
				// ca fisierul pe care voiam sa l inseram
				printf("Directory %s already exists!\n", nume);
				return 0;
			}
			if (strcmp(nume, x->nume) < 0)
				x = x->st;
			else
				x = x->dr;
		}
		aux = ConstrF(nume);
		if (!aux)
			return 0;
		aux->parinte = a;
		if (strcmp(nume, p->nume) < 0)
			p->st = aux;
		else
			p->dr = aux;
		return 1;
	}
	return 1;
}
TArbdir ConstrD(char *nume)
{
	TArbdir aux = (TArbdir)malloc(sizeof(director));
	if (!aux)
		return NULL;
	aux->nume = malloc(50);
	strcpy(aux->nume, nume);
	aux->st = aux->dr = NULL;
	return aux;
}
int mkdir(TArbdir a, char *nume)
{
	// caz 1
	if (a->directories == NULL)
	{
		a->directories = ConstrD(nume);
		if (!a->directories)
			return 0;
		a->directories->parinte = a;
	}
	else
	{
		TArbdir aux, n, p;
		n = a->directories;
		// caz 2
		while (n)
		{
			p = n;
			if (strcmp(n->nume, nume) == 0)
			// deja exista directorul
			{
				printf("Directory %s already exists!\n", nume);
				return 0;
			}
			if (strcmp(nume, n->nume) < 0)
				n = n->st;
			else
				n = n->dr;
		}
		TArbfisier x = a->files;
		TArbfisier y;
		while (x)
		{
			y = x;
			if (strcmp(x->nume, nume) == 0)
			{
				printf("File %s already exists!\n", nume);
				return 0;
			}
			if (strcmp(nume, x->nume) < 0)
				x = x->st;
			else
				x = x->dr;
		}
		aux = ConstrD(nume);
		if (!aux)
			return 0;
		aux->parinte = a;

		if (strcmp(nume, p->nume) < 0)
			p->st = aux;
		else
			p->dr = aux;
		return 1;
	}
	return 1;
}


void ls1(TArbdir a)
{
	if (!a)
		return;
	ls1(a->st);
	printf("%s ", a->nume);
	ls1(a->dr);
}
void ls2(TArbfisier a)
{
	if (!a)
		return;
	ls2(a->st);
	printf("%s ", a->nume);
	ls2(a->dr);
}
void ls(TArbdir a)
{
	ls1(a->directories);
	ls2(a->files);
}

TArbdir SDRd(TArbdir a, char *nume) // parcurgere ajutatoare
{
	if (!a)
		return 0;
	TArbdir x = SDRd(a->st, nume);
	if (x)
		return x;
	x = SDRd(a->dr, nume);
	if (x)
		return x;
	if (strcmp(a->nume, nume) == 0)
		return a;
	return 0;
}
TArbfisier SDRf(TArbfisier a, char *nume) // parc. pt fisier
{
	if (!a)
		return 0;
	TArbfisier x = SDRf(a->st, nume);
	if (x)
		return x;
	x = SDRf(a->dr, nume);
	if (x)
		return x;
	if (strcmp(a->nume, nume) == 0)
		return a;
	return 0;
}
TArbfisier minF(TArbfisier a)
{
	TArbfisier current = a;

	/* cea mai din stg frunza */
	while (current && current->st != NULL)
		current = current->st;

	return current;
}

TArbfisier rm(TArbfisier a, char *nume, TArbdir current)
{
	if (a == NULL)
		return a;
	if (!SDRf(a, nume))
	{
		printf("File %s doesn't exist!\n", nume);
		return 0;
	}
	if (strcmp(a->nume, nume) > 0)
	{
		a->st = rm(a->st, nume, current);
	}
	else if (strcmp(a->nume, nume) < 0)
	{
		a->dr = rm(a->dr, nume, current);
	}
	else
	{
		if (a->st == NULL)
		{
			if (current->files == a)
			{
				current->files = a->dr;
			}
			TArbfisier aux = a->dr;
			free(a);
			return aux;
		}
		else if (a->dr == NULL)
		{
			if (current->files == a)
			{
				current->files = a->st;
			}
			TArbfisier aux = a->st;
			free(a);
			return aux;
		}
		TArbfisier aux = minF(a->dr);
		strcpy(a->nume, aux->nume);
		a->dr = rm(a->dr, aux->nume, current);
	}
	return a;
}
TArbdir minD(TArbdir a)
{
	TArbdir current = a;

	while (current && current->st != NULL)
		current = current->st;

	return current;
}
TArbdir rmdir(TArbdir a, char *nume, TArbdir current)
{
	if (a == NULL)
		return a;
	if (!SDRd(a, nume))
	{
		printf("Directory %s doesn't exist!\n", nume);
		return 0;
	}
	if (strcmp(a->nume, nume) > 0)
	{
		a->st = rmdir(a->st, nume, current);
	}
	else if (strcmp(a->nume, nume) < 0)
	{
		a->dr = rmdir(a->dr, nume, current);
	}
	else
	{
		if (a->st == NULL)
		{
			if (current->directories == a)
			{
				current->directories = a->dr;
			}
			TArbdir aux = a->dr;
			free(a);
			return aux;
		}
		else if (a->dr == NULL)
		{
			if (current->directories == a)
			{
				current->directories = a->st;
			}
			TArbdir aux = a->st;
			free(a);
			return aux;
		}
		TArbdir aux = minD(a->dr);
		strcpy(a->nume, aux->nume);
		a->dr = rmdir(a->dr, aux->nume, current);
	}
	return a;
}

TArbdir cd(TArbdir a, char *nume)
{

	if (strcmp(nume, "..") == 0)
	{
		if (a->parinte != NULL)
			return a->parinte;
		else
			return NULL;
	}
	// printf("p1:%s\n", a->parinte->nume);
	TArbdir found = SDRd(a->directories, nume);
	if (found == NULL)
		return a;
	// printf("Directory not found!\n");
	else
		return found;
}
void deallocateD(TArbdir a)
{
	deallocateD(a->st);
	if (a == NULL)
	{
		return;
	}
	deallocateD(a->dr);
	free(a);
}

void deallocateF(TArbfisier a)
{
	deallocateF(a->st);
	if (a == NULL)
	{
		return;
	}
	deallocateF(a->dr);
	free(a);
}
void pwd(TArbdir a)
{
	if (a == NULL)
		return;
	else
	{
		pwd(a->parinte);
		printf("/%s", a->nume);
	}
}

int main()
{
	director *root = malloc(sizeof(director));
	director *current = malloc(sizeof(director));
	root->directories = NULL;
	root->dr = NULL;
	root->st = NULL;
	root->files = NULL;
	root->parinte = NULL;
	root->nume = "root";
	current->nume = NULL;
	current = root;
	fisier *file = malloc(sizeof(fisier));
	file->dr = NULL;
	file->st = NULL;
	file->parinte = NULL;
	// file->nume = NULL;
	size_t length = 40;
	char *divider;
	char *input = (char *)malloc(length * sizeof(char));
	while (getline(&input, &length, stdin) != -1)
	{
		int ok = 1;
		divider = strtok(input, " \n");
		if (strcmp(divider, "touch") == 0)
		{
			char *fileName = strtok(NULL, " \n");
			touch(current, fileName);
		}
		if (strcmp(divider, "ls") == 0)
		{
			ls(current);
			printf("\n");
		}
		if (strcmp(divider, "mkdir") == 0)
		{
			char *dirName = strtok(NULL, " \n");
			mkdir(current, dirName);
		}
		if (strcmp(divider, "quit") == 0)
		{
			ok = 0;
		}
		if (strcmp(divider, "rm") == 0)
		{
			char *name = strtok(NULL, " \n");
			rm(current->files, name, current);
		}
		if (strcmp(divider, "rmdir") == 0)
		{
			char *nume = strtok(NULL, " \n");
			rmdir(current->directories, nume, current);
		}
		if (strcmp(divider, "cd") == 0)
		{
			char *nme = strtok(NULL, " \n");
			if (cd(current, nme) == current)
				printf("Directory not found!\n");
			else
				current = cd(current, nme);
		}
		if (strcmp(divider, "pwd") == 0)
		{

			pwd(current);
			printf("\n");
		}
	}

	return 0;
}
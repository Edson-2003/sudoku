#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int impedimento=0;
int vitoria=0;
int naoalterado=0;

typedef struct{
	int valor;
	int verificador;
}Elementos;



Elementos** alocae(int n)
{
	Elementos** e = (Elementos**) malloc(n * (sizeof(Elementos*)));

	for(int i = 0; i < n; i++ )
	{
	
		e[i] = (Elementos*) malloc(n * sizeof(Elementos));
	
	}

	return e;

}

void limpabuffer(Elementos** e, int n)
{
	for(int i = 0; i < n; i++)
		free(e [i]);

	free(e);
}


void vlinha(Elementos** e, int n,int i, int j, int key)
{
	for(int k = 0; k < n; k ++)
	{
		if(j == k)
		{
			k++;
		}
		else
		{
			if(e [i] [k].valor == key)
			{
				e [i] [j].valor = 0;
			}
		}
	}
}

void vcoluna(Elementos** e, int n, int i, int j, int key)
{
	for(int k = 0; k < n; k++)
	{
		if(k == i)
		{
			k ++;
		}
		else
		{
			if(e [k] [j].valor == key)
			{
				e [i] [j].valor = 0;
			}
		}
	}
}

int ainicio(int n)
{
	while((n % 3) != 0)
		n--;

	return n;
}
void vquadrado(Elementos** e,int n,int i,int j,int key) // validar quadrado
{
	int il = ainicio(i);
	int ic = ainicio(j);


	for(int k = il;k <(il + 3);k++)     //para nao sair do quadrado
	{
		for(int l = ic;l <(ic + 3);l++)
		{
			if(k == i && l == j) //pulando a key
			{
				l++;
			}				
			else
			{
				if(e [k] [l].valor == key)
				{
					e [i] [j].valor = 0; //zerar o valor repetido 
				}
			}	
		}	
	}
}

//verifica o sudoku e gera os verificadores
void vinicio(Elementos** e, int n)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			vlinha(e, n, i, j, e [i] [j].valor);
			vcoluna(e, n, i, j, e [i] [j].valor);
			vquadrado(e, n, i, j, e [i] [j].valor);
			if(e[i] [j]. valor == 0)
			{
				e[i] [j].verificador = 1;
			}
			else
				e[i] [j].verificador = 0;
		}
	}
}


// gera os numeros aleatórios no sudoku
Elementos** gsudoku(int n)
{	
	int base=(rand()%10);
	srand(time(NULL));
	Elementos** sudoku = alocae(n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++ )
		{
			if(base==0)
			{
			base=(rand()%12+1);
			sudoku [i] [j].valor = (rand() % 9+1);
			}
			else
			{
			sudoku [i] [j].valor=0;
			}
			base--;
		}
	}
	
	return sudoku;
}

void imprime(Elementos** e, int n)
{
	int cont=0;
	for(int i = 0; i < n; i++)
	{
	cont=0;
	if((i%3)==0 && i!=0)
			{
				while(cont<(3*n)-6)
				{
				printf("_");
				cont++;
				}
				printf("\n");
			
			}
		for(int j = 0; j < n; j++)
		{
			if((j%3)==0 && j!=0)
			{
				printf("|");

			
			}
			if(e [i] [j].valor == 0)
			{
				printf("  ");
			}
			else
			{
				printf(" %d", e [i] [j].valor);
				if(impedimento==0)
				{
				vitoria++;
				}
			}
		}
		printf("|");
		printf("\n");
	
	}
	impedimento=1;
	printf("\n");
}

void imprimet(Elementos** e, int n)
{
	printf("valores\n");
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++ )
		{
			printf("%d ", e[i][j].valor);
		}
		printf("\n");
	}
	printf("verificadores\n");
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			printf("%d", e[i][j].verificador);
		}
		printf("\n");
	}
}
int usuario(Elementos** e,int n)
{
vitoria=81-vitoria;
int i,j,key,count;
int nid=10;
printf("\n diga a linha e coluna e o valor que deseja que seja inserido");
for(count=0;count<nid;count++)
{
nid=nid+1;
printf("\n diga a linha e coluna e o valor:   ");
scanf("%d%d%d",&i,&j,&key);
i--;
j--;
if (e[i][j].verificador==1)
{
if(e[i][j].valor==0)
{
naoalterado=1;
}
else
{naoalterado=0;}
e[i][j].valor=key;
vlinha(e, n, i, j, e [i] [j].valor);
vcoluna(e, n, i, j, e [i] [j].valor);
vquadrado(e, n, i, j, e [i] [j].valor);
if (e[i][j].valor==0)
{
printf("valor nao valido pois ja existe o mesmo numero na mesma linha coluna ou quadrado\n");
}
else
{
if(naoalterado==1)
{
vitoria--;
}
}
imprime(e,n);
}
else
{
printf("posiçao invalida\n");
}
if(vitoria==0)
{
return 1;
}
}   
    

}
void sudoku()
{
	int ganhou=0;
	int n = 9;
	Elementos** sudoku;
	sudoku = gsudoku(n);
	vinicio(sudoku, n);
	imprime(sudoku, n);
	imprimet(sudoku, n);
    ganhou=usuario(sudoku,n);
	if(ganhou==1)
	{
	printf("\ntu ganhou");
	}
}




void main()
{
	sudoku();
}
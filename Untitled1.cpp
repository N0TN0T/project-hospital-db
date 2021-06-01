#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

  

typedef struct { 
        char nome[50]; 
        float salario; 
} ficha; 

FILE *f; 
int nreg; 

  

int AbrirFich() 
{ 
    if ((f=fopen("c:\\temp\\pessoal.dat","r+b"))==NULL) 
                return 0; 
    fseek(f,0,SEEK_END);
    nreg = ftell(f)/sizeof(ficha);
    printf("\nExistem %d registos\n",nreg);
    return -1;

}

  

void Mostrar() 
{
    int i; 
    ficha x; 

    rewind(f); 

 
    for (i=0; i<nreg; i++) 
    { 
          fread(&x, sizeof(x), 1, f); 
          printf("Nome    : %s ;", x.nome); 
          printf("Salario : %f\n", x.salario); 
    } 
    printf("\n"); 
} 

  

void Maximo() 
{ 
    int i; 
    float m=-1.0; 
    char n[50]; 
    ficha x; 

    rewind(f); 
    for (i=0; i<nreg; i++) 
    { 
           fread(&x, sizeof(x), 1, f); 
           if (x.salario>m) { 
                        m = x.salario; 
                        strcpy(n, x.nome); 
           } 
    } 
    printf("Maior salario: %s, %f\n\n", n, m); 
} 

  

void AlterarSal() 
{ 
    int k; 
    ficha x; 

    printf("\nRegisto  "); scanf("%d", &k);

    if (k>=1 && k<=nreg){ 
            fseek(f,(long)(k-1)*sizeof(x),SEEK_SET); 
            fread(&x, sizeof(x), 1, f); 
            printf("%s , %f\n", x.nome, x.salario); 

            printf("Novo valor do salario  "); 
            scanf("%f", &x.salario); 
            fseek(f, -(long)sizeof(x), SEEK_CUR); 
	// é necessário ir atrás porque o anterior fread incrementou a posição 
	
            fwrite(&x, sizeof(x), 1, f); 
    } 
    else printf("registo inválido\n"); 
    printf("\n"); 
} 

  

main() 
{ 
    char op; 

    if (AbrirFich()==0) 
    { 
        printf("Ficheiro não existe\n"); 
        exit(1); 
    } 
 
    do { 
            printf("m=Mostrar; M=Máximo; a=Alterar Sal. s=Sair\n"); 
            scanf(" %c", &op); 
            switch (op) 
            { 
				case 'm': Mostrar(); break; 
				case 'M': Maximo(); break; 
                case 'a': AlterarSal(); break; 
                case 's': break; 
                default: printf("opção inválida!"); 
            } 
    } 
    while (op != 's'); 

 
    fclose(f); 
    printf("FIM\n"); 
} 

 

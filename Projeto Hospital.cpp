#include <stdio.h>		//We do not want do disrespect Bob - God of C++
#include <iostream>
#include <string>		//Realizado por João Beirão e Ruben Silva
#include <locale.h>
using namespace std;

typedef struct paciente
{
 char Nome[20];
 char doenca[40];
 int Ano ;
 long int contacto;
 int utente;
} paciente;


int menu();
void inserir();
void listar();
void consultar();
void alterar();
void eliminar();


FILE *fp;


main()
{
	setlocale(LC_ALL, "Portuguese");
	system("color F0");
	int escolha; 
	int repetir=1;

	do{
		escolha=menu();
		switch (escolha)
		{
			case 1: inserir();break;
			case 2: listar();break;
			case 3: consultar();break;
			case 4: alterar();break;
			case 5: eliminar();break;
			case 6: return 0;break;
		}

		do{
			cout << endl << "\t\tDeseja efetuar mais alguma operação?\n\t\t1-Sim\n\t\t2-Não\n\n\t\t\t-->";
			scanf("%d", &repetir);
			system("cls");
		}while(repetir!=1&&repetir!=2);
	
	}while(repetir==1);
	
	
}

int menu(){	
	
	int num = 1;
	char cruz = 135;
	do
	{

		cout << "\t_______________________________________________________\n\n";
		cout << "\t         "<<cruz<< "  H O S P I T A L   S Ã O   B O B  "<<cruz<<endl;
		cout << "\t_______________________________________________________\n";
	
		if(num!=1&&num!=2&&num!=3&&num!=4&&num!=5&&num!=6&&num!=7)
			cout << endl << "\tNúmero inválido, tente novamente: " << endl;
		else 
			cout << endl << endl; 
		
		cout << endl << "\t[1] - Adicionar Paciente";
		cout << endl << "\t[2] - Lista de Pacientes";
		cout << endl << "\t[3] - Consultar Ficha de Paciente";
		cout << endl << "\t[4] - Alterar dados de um Paciente";
		cout << endl << "\t[5] - Eliminar dados de um Paciente";
		cout << endl << "\t[6] - Sair";

		cout << endl << "\t_______________________________________________________" << endl << endl << "\t--> ";
		cin >> num;
		system("cls");
		
	}while(num!=1&&num!=2&&num!=3&&num!=4&&num!=5&&num!=6);
	fflush(stdin);
	return num;
}
	
void inserir (){
	FILE *fp;
	setlocale(LC_ALL, "Portuguese");
	fp= fopen("pacientes.dat", "rb"); 
	fseek(fp,(long) 0, SEEK_END);
	
	int num_pacientes; num_pacientes = ftell(fp)/sizeof(paciente);
	
	fclose(fp);
	
	paciente p;
	
	printf("Introduza o nome: "); gets(p.Nome);
	printf("Introduza a doença: "); gets(p.doenca);
	printf("Introduza o ano de nascença: "); scanf(" %d", &p.Ano);
	printf("Introduza o contacto: "); scanf("%ld", &p.contacto);
	

	
	if(num_pacientes<0)
	p.utente = 1;
	else
	p.utente = num_pacientes+1;
	
	
	
	printf("O seu número de utente é: %d", p.utente);
 	fflush(stdin);
 	
 	fp= fopen("pacientes.dat", "ab"); // abrir escrita do ficheiro em binário
 	fwrite(&p,sizeof(paciente),1,fp);
 	fclose(fp);
}
	
void listar (){
	
	setlocale(LC_ALL, "Portuguese");
	
	paciente p;
	char c;
	int num_pacientes;
	int i=0;
	fp=fopen("pacientes.dat", "rb"); // abrir escrita do ficheiro em binário
	fseek(fp,0,SEEK_END);
	num_pacientes = ftell(fp)/sizeof(paciente);
	rewind(fp);
	
	printf("\nNome\n"); 
	printf("Doença\n"); 
	printf("Ano de nascença\n");
	printf("Contacto\n"); 
	printf("Número de utente\n\n____________________________________________\n\n"); 
	
	
	do{
 		fread(&p, sizeof(paciente),1,fp);
		puts(p.Nome);
		puts(p.doenca);
		printf("%d\n",p.Ano);
		printf("%d",p.contacto);
		printf("\n%ld\n\n",p.utente);
		i++;
		fseek(fp,(long) i*sizeof(paciente), SEEK_SET);
 	}while(i<num_pacientes);
 	
 	scanf("%c", &c);
 	fclose(fp);
	

}
	
void consultar(){
	
	FILE *fp;
	fp=fopen("pacientes.dat", "rb"); // abrir escrita do ficheiro em binário
	int i=0;
	int Valido = 0;
    paciente x;
    int num_utente=0;
	int num_pacientes;
	fseek(fp,(long) 0, SEEK_END);
	num_pacientes = ftell(fp)/sizeof(paciente);
	char c;
	
	
	cout<<"Introduza o número do utente que pretende procurar  --> ";
	cin>>num_utente;
	
    rewind(fp);
   	do{
 		fread(&x, sizeof(paciente),1,fp);
 		if(x.utente==num_utente){
			puts(x.Nome);
			puts(x.doenca);
			printf("%d\n",x.Ano);
			printf("%d",x.contacto);
			printf("\n%ld\n\n",x.utente);
			Valido=1;
		}
		
		
		i++;
		fseek(fp,(long) i*sizeof(paciente), SEEK_SET);
 	}while(i<num_pacientes);
        	
           	
    
    if(Valido==0){
    	printf("Número de Utente inválido");
    	getchar();
	}
	fclose(fp);
}

void alterar(){


	FILE *fp;
	fp=fopen("pacientes.dat", "rb"); // abrir escrita do ficheiro em binário
	int i=0;
	int Valido = 0;
    int num_utente=0;
	int num_pacientes;
	fseek(fp,(long) 0, SEEK_END);
	num_pacientes = ftell(fp)/sizeof(paciente);
	paciente x[num_pacientes];
	char c;
	paciente p;
	
	cout<<"Introduza o número do utente que pretende alterar  --> ";
	cin>>num_utente;
	
    rewind(fp);
   	do{
 		fread(&x[i], sizeof(paciente),1,fp);
 		
 		
 		if(x[i].utente==num_utente){
			puts(x[i].Nome);
			puts(x[i].doenca);
			printf("%d\n",x[i].Ano);
			printf("%d",x[i].contacto);
			printf("\n%ld\n\n",x[i].utente);
			
			
			printf("\n\nMUDAR PARA:\n\n");
		
			fflush(stdin);
			printf("Introduza o nome: "); gets(p.Nome);
			printf("Introduza a doença: "); gets(p.doenca);
			printf("Introduza o ano de nascença: "); scanf(" %d", &p.Ano);
			printf("Introduza o contacto: "); scanf("%ld", &p.contacto);
			p.utente=x[i].utente;
		
			x[i]=p;
			
			Valido=1;
		}
		
		
		
		i++;
		fseek(fp,(long) i*sizeof(paciente), SEEK_SET);
 	}while(i<num_pacientes);
 	
 	
		fclose(fp);
		fp=fopen("pacientes.dat", "wb"); // abrir escrita do ficheiro em binário
		
		for(int j=0;j<num_pacientes;j++)
			fwrite(&x[j],sizeof(paciente),1,fp);
		
        	
           	
    
    if(Valido==0){
    	printf("Número de Utente inválido");
    	getchar();
	}
	fclose(fp);
		
}




void eliminar(){
	
	int num_utente;
	FILE *fp;
	fp=fopen("pacientes.dat", "rb"); // abrir escrita do ficheiro em binário
	fseek(fp,(long) 0, SEEK_END);
	int num_pacientes = ftell(fp)/sizeof(paciente);
	rewind(fp);
	paciente x[num_pacientes];
	
	cout<<"Introduza o número do utente que pretende eliminar  --> ";
	cin>>num_utente;
	
	for(int i=0; i<num_pacientes;i++){
		fread(&x[i], sizeof(paciente),1,fp);
	}
	
	
	fclose(fp);
	fp=fopen("pacientes.dat", "wb");
	
	for(int i=0; i<num_pacientes;i++){
		if(i<num_utente-1)
			fwrite(&x[i],sizeof(paciente),1,fp);
		else if(i>num_utente-1){
			x[i].utente--;
			fwrite(&x[i],sizeof(paciente),1,fp);
		}
	
	}
	
	
	
	fclose(fp);
}











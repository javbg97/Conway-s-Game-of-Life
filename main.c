/*
Bernab� Garc�a Javier			201842143	
C�rdova R�os Alfredo			201833121
Maldonado Lozano Juan Carlos	201863146
Programacion I
Spring 2019
*/

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string.h>

#define FILA 101
#define COLUMNA 101

typedef struct registro{ //Struct donde se guardaran las generaciones recientes dentro de la cadena
	char cad[2501];
}guardado;

void clearg();//Funci�n limpia pantalla con system getch
void clearp();//Funci�n limpia pantalla con system  pause
void evolution(int *op);//Funci�n que cuestiona al usuario de que manera se visualizara la evoluci�n de las generaciones
void display(int);//Funci�n que determina de que manera se visualizara la evoluci�n de las celulas
void crearmatriz(char M[FILA][COLUMNA], char M1[FILA][COLUMNA]);//Funci�n que crea las cuadriculas de las dos matrices
void vaciarmatriz(char M[FILA][COLUMNA]);
void llenarmanualmente(char M[FILA][COLUMNA], struct registro saved[]); //Funci�n para llenar manualmente las celulas vivas
void llenadorandom(char M[FILA][COLUMNA], struct registro saved[]);//Funci�n que llena la matriz inicial de valores random
void printfmat(char M[FILA][COLUMNA]); //Funci�n que imprime la matriz
void compararmat(char M[FILA][COLUMNA], char M1[FILA][COLUMNA]);//Funci�n que recorre las celdas de la matriz
void genesis(char M[FILA][COLUMNA], int, int, char M1[FILA][COLUMNA]);//Funci�n que determina si una celula vivira o morira
void copyandregistermat(char M[FILA][COLUMNA], char M1[FILA][COLUMNA], int, struct registro saved[]);//Funci�n que copia la matriz1 a la matriz0 y a la vez registra las generaciones en cadenas
void registrar(char M[FILA][COLUMNA], int i, int j, struct registro saved[], int z);//Funcion que registra las celdas de la generacion en una cadena
int pattern(struct registro saved[], int);//Funci�n que realiza una comparaci�n de los guardados de las generaciones mas recientes y asi determinar s� es estable
int muertacompletamente(struct registro saved[], int);//Funci�n que verifica que la ultima generaci�n no este muerta completamente
void lecturaArchivo(FILE *fd, char M[FILA][COLUMNA], struct registro saved[], int *, int *);
void salidaArchivo(FILE *fs, char M[FILA][COLUMNA], int); //Funcion para la lectura de las celulas mediante el archivo.

int celulas;//Variable global que cuenta las celulas vivas de la generaci�n actual y las muestra en pantalla
			//Meramente estetico

void main()
{
	srand(time(NULL));//Funcion que le asigna un numero incial a random de acuerdo a la hora del sistema
	FILE *fd, *fs;
	int i, j, op, stop, ban=0, ban1;
	char MAT0[FILA][COLUMNA], MAT1[FILA][COLUMNA], archivo[50], extension[5] = ".txt";
	guardado saved[4];//Declaraci�n de los guardados donde se almacenaran las generaciones recientes
	saved[0].cad[2500]='\0';//Introducci�n manual del caracter nulo al final de los guardados
	saved[1].cad[2500]='\0';
	saved[2].cad[2500]='\0';
	saved[3].cad[2500]='\0';
	crearmatriz(MAT0,MAT1);//Llamada a crear las cuadriculas
	do
	{
		system("color f0");
		printf("\n\n\n\n\n\t\t\t**********************************************************\n");
		printf("\t\t\t**********************************************************\n");
		printf("\t\t\t**\t\t\t\t\t\t\t**\n");
		printf("\t\t\t**\t\tBIENVENIDO A EL JUEGO DE LA VIDA\t**\n\t\t\t**\t\tQUE DESEA HACER?\t\t\t**\n");
		printf("\t\t\t**\t\t1. INICIAR JUEGO\t\t\t**\n");
		printf("\t\t\t**\t\t2. LEER REGLAS\t\t\t\t**\n");
		printf("\t\t\t**\t\t0. SALIR\t\t\t\t**\n");
		printf("\t\t\t**\t\t\t\t\t\t\t**\n");
		printf("\t\t\t**********************************************************\n");
		printf("\t\t\t**********************************************************\n\n\t\t\t");
		scanf("%d",&op);
		vaciarmatriz(MAT0);//Vaciar la matriz 0 en caso de que tenga datos de un juego pasado
		stop=1;//Variable que condiciona el ciclo de generaciones
		clearg();
		switch(op)
		{
			case 1:
				printf("\n\n\n\n\n\t\t**************************************************************************\n\t\t**************************************************************************\n");
				printf("\t\t**\t\t\t\t\t\t\t\t\t**\n\t\t**\tDE QUE MANERA DESEA INICIALIZAR LA PRIMERA GENERACION: \t\t**\n\t\t**\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t1. LEER DESDE UN ARCHIVO\t\t\t\t\t**\n");
				printf("\t\t**\t2. INTRODUCIR MANUALMENTE\t\t\t\t\t**\n");
				printf("\t\t**\t3. GENERACION INICIAL ALEATORIA\t\t\t\t\t**\n");
				printf("\t\t**\t4. REGRESAR AL MENU PRINCIPAL\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t**\t\t\t\n");
				printf("\t\t**************************************************************************\n\t\t**************************************************************************\n\t\t");
				printf("\n\t\t");
				scanf("%d",&op);
				clearg();
				switch(op)
				{
					case 1:
						celulas=0;
						printf("\n\n\n\t\t*******************************************************************************************************************\n\n");
						printf("\n\n\n\n\n\t\t\tINTRODUCE EL NOMBRE DEL ARCHIVO A LEER: ");
						scanf ("%s", archivo);
						strcat(archivo, extension); //Concatena la cadena leida por el usuario con la extension ".txt" para que el usuario no tenga que ponerla.
						if ((fd = fopen(archivo, "r")) == NULL) //Verifica si el archivo que escribio existe o esta mal escrito.
						{
							printf("\n\t\t\t--EL ARCHIVO NO SE ENCUENTRA EN EL DIRECTORIO, NO EXISTE O NO LO ESCRIBISTE CORRECTAMENTE--\n\n\n");
						}
						else
						{
							lecturaArchivo(fd, MAT0, saved, &ban, &ban1);
							if (ban == 0 && ban1 == 2) //En caso de que el archivo no este debidamente correcto, no correra el programa.
							{
								if ((fs = fopen("Estados.txt", "w")) == NULL){
									// Crea el archivo
								}								
								evolution(&op);//Determinar el tipo de vizualizaci�n
								for(i=0; stop!=0; i++)//Ciclo de evoluci�n de generaciones
								//i actuara como el numero de generaci�n
								{
									printf("\n\n\t\t\t\t\t\tGENERACION %d\t\tCELULAS VIVAS %d\n",i+1,celulas);
									printfmat(MAT0);
									salidaArchivo(fs, MAT0, i+1);
									if(muertacompletamente(saved,i)!=0)//En caso de que la generaci�n este completamente muerta
									{
										printf("\t\t\tLAS CELULAS SE HAN EXTINGUIDO POR COMPLETO :(\n\n");
										getch();
										stop=0;
										system("cls");
									}									
									if(pattern(saved,i)!=0)//En caso de ser detectada una generaci�n estable
									{	
										printf("\t\t\tPARECE SER QUE LA EVOLUCION HA ALCANZADO UN PUNTO ESTABLE\n\n\t\t\t");
										fflush(stdin);
										getch();
										printf("\t\t\t\tPARA TERMINAR EL JUEGO PRESIONA 0\n\t\t\t");
										fflush(stdin);
										scanf("%d",&stop);
										if(stop==0)
										{
											system("cls");
										}
									}
									compararmat(MAT0,MAT1);//Proceso de evoluci�n de celulas
									copyandregistermat(MAT0,MAT1,i+1,saved);//copiado y registro de celulas
									fflush(stdin);
									if(stop!=0)//Solo en caso de que el usuario aun no quiera dar por terminado el juego y aun este inestable
									{
										display(op);//La manera en que se visualizara
									}
								}
								printf("\n\n\n\n\t\t\t\tGAME OVER...\n\t\t\t");
								clearg();
							}
							else
							{
								printf("\n\t\t\tDADO QUE EL ARCHIVO NO TIENE NADA O CONTIENE CELULAS INVALIDAS\n\t\t\tPOR LO TANTO NO SE EJECUTARA, MODIFICA EL ARCHIVO E INTENTALO NUEVAMENTE\n\n\n");
							}
						}
						fclose(fd);
					break;
					case 2://Llenar manualmente la matriz
						llenarmanualmente(MAT0,saved);
						evolution(&op);//Determinar el tipo de visualizaci�n
						for(i=0; stop!=0; i++)//Ciclo de evolucion de generaciones
						//i actuara como el numero de generaci�n
						{
							printf("\n\n\t\t\t\t\t\tGENERACION %d\t\tCELULAS VIVAS %d\n",i+1,celulas);
							printfmat(MAT0);
							if(muertacompletamente(saved,i)!=0)//En caso de que la generaci�n este completamente muerta
							{
								printf("\t\t\tLAS CELULAS SE HAN EXTINGUIDO POR COMPLETO :(\n\n");
								getch();
								stop=0;
								system("cls");
							}
							if(pattern(saved,i)!=0)//En caso de ser detectada una generaci�n estable 
							{	
								printf("\t\t\tPARECE SER QUE LA EVOLUCION HA ALCANZADO UN PUNTO ESTABLE\n\n\t\t\t");
								fflush(stdin);
								getch();
								printf("\t\t\t\tPARA TERMINAR EL JUEGO PRESIONA 0\n\t\t\t");
								fflush(stdin);
								scanf("%d",&stop);
								if(stop==0)
								{
									system("cls");
								}
							}
							compararmat(MAT0,MAT1);//Proceso de evoluci�n de celulas
							copyandregistermat(MAT0,MAT1,i+1,saved);//copiado y registro de celulas
							fflush(stdin);
							if(stop!=0)//Solo en caso de que el usuario aun no quiera dar por terminado el juego y aun este inestable
							{
								display(op);//La manera en que se visualizara
							}
						}
						printf("\n\n\n\n\t\t\t\tGAME OVER...\n\t\t\t");
						clearg();
					break;
					case 3:
						evolution(&op);//Cuestionar a el usuario el tipo de visualizaci�n
						llenadorandom(MAT0,saved);//La matriz se llena con valores random
						for(i=0; stop!=0; i++)
						//i actuara como el numero de generaci�n
						{
							printf("\n\n\t\t\t\t\t\tGENERACION %d\t\tCELULAS VIVAS %d\n",i+1,celulas);
							printfmat(MAT0);//Se imprime la matriz
							if(muertacompletamente(saved,i)!=0)//En caso de que la generaci�n este completamente muerta
							{
								printf("\t\t\tLAS CELULAS SE HAN EXTINGUIDO POR COMPLETO :(\n\n");
								getch();
								stop=0;
								system("cls");
							}
							if(pattern(saved,i)!=0)//En caso de ser detectada una generaci�n estable
							{	
								printf("\t\t\tPARECE SER QUE LA EVOLUCION HA ALCANZADO UN PUNTO ESTABLE\n\n\t\t\t");
								fflush(stdin);
								getch();
								printf("\t\t\t\tPARA TERMINAR EL JUEGO PRESIONA 0\n\t\t\t");
								fflush(stdin);
								scanf("%d",&stop);
								if(stop==0)
								{
									system("cls");
								}
							}
							compararmat(MAT0,MAT1);//Proceso de evoluci�n de celulas
							copyandregistermat(MAT0,MAT1,i+1,saved);//copiado y registro de celulas
							fflush(stdin);
							if(stop!=0)//Solo en caso de que el usuario aun no quiera dar por terminado el juego y aun este inestable
							{
								display(op);//La manera en que se visualizara
							}
						}
						printf("\n\n\n\n\t\t\t\tGAME OVER...\n\t\t\t");
						clearg();
					break;
					case 4://Retornar al menu principal
						system("cls");
					break;
					default:
						printf("\n\n\n\n\n\t\t\tOPCION INVALIDA\n\t\t\t");
						clearp();
					break;
				}
			break;
			case 2:
			
				printf("\n\n\n\n\n\t\t**************************************************************************************************************************\n");
				printf("\t\t**************************************************************************************************************************\n");
				printf("\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t\t\t\t\t\tREGLAS\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t1. LOS VECINOS DE UNA CELDA SON LOS OCHO QUE LA TOCAN VERTICAL, HORIZONTAL O DIAGONALMENTE.\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t2. SI UNA CELDA ESTA VIVA, PERO NO TIENE CELDAS VECINAS VIVAS O SOLAMENTE UNA VIVA, MUERE\t\t\t**\n\t\t**\t   DE SOLEDAD EN LA SIGUIENTE GENERACION.\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t3. SI UNA CELDA ESTA VIVA Y TIENE CUATRO O MAS CELDAS VECINAS TAMBIEN VIVAS, EN LA SIGUIENTE\t\t\t**\n\t\t**\t   GENERACI�N MUERE POR HACINAMIENTO (SUPERPOBLACION).\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t4. UNA CELDA VIVA CON DOS O TRES VECINAS PERMANECE VIVA EN LA SIGUIENTE GENERACION.\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t5. SI UNA CELDA ESTA MUERTA, EN LA SIGUIENTE GENERACI�N RECUPERAR� LA VIDA SI TIENE EXACTAMENTE 3\t\t**\n\t\t**\t   VECINAS, NI UNA M�S NI UNA MENOS QUE YA EST�N VIVAS. TODAS LAS OTRAS CELDAS MUERTAS PERMANECEN\t\t**\n\t\t**\t   ASI EN LA SIGUIENTE GENERACION.\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t6. TODOS LOS NACIMIENTOS Y MUERTES TIENEN LUGAR EXACTAMENTE AL MISMO TIEMPO, DE MANERA QUE LAS\t\t\t**\n\t\t**\t   QUE MUEREN AYUDAN A PRODUCIR OTRAS; PERO NO PUEDEN IMPEDIR LA MUERTE DE OTRAS REDUCIENDO EL\t\t\t**\n\t\t**\t   NACIMIENTO, NI LAS QUE NACEN PUEDEN PRESERVAR O DESTRUIR A LAS QUE TIENEN VIDA EN LA GENERACION ANTERIOR.\t**\n\t\t**\t   ES DECIR, LOS NACIMIENTOS Y MUERTES EN UNA GENERACION DADA NO PUEDEN AFECTAR A LAS GENERACIONES PASADAS Y\t**\n\t\t**\t   SOLO AFECTAN A LAS FUTURAS EN BASE A LAS REGLAS ANTERIORES.\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**\n");
				printf("\t\t**************************************************************************************************************************\n");
				printf("\t\t**************************************************************************************************************************\n\n\t\t");
				clearp();
			break;
			case 0:
				printf("\n\n\n\n\t\t\t\tCERRANDO...");
			break;
			default:
				printf("\n\n\n\n\n\t\t\tOPCION INVALIDA\n\n\t\t\t");
				clearp();
			break;
		}
	}while(op!=0);
}
void clearg(){
	getch();
	system("cls");
}
void clearp(){
	system("pause");
	system("cls");
}
void evolution(int *op){
	int c=0;//Contador que ayuda a repetir el ciclo
	
	do
	{
		printf("\n\n\n\n\t\t**********************************************************************************\n\t\t**********************************************************************************\n\t\t**\t\t\t\t\t\t\t\t\t\t**\n");
		printf("\t\t**\tDE QUE MANERA DESEAS VER LA EVOLUCION DE LAS GENERACIONES?\t\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t**\n");
		printf("\t\t**\t1. MANUAL (PRESIONAR ENTER PARA VER GENERACION POR GENERACION)\t\t**\n");
		printf("\t\t**\t2. AUTOMATICA (SE DESPLEGARAN LAS GENERACIONES DE MANERA CONSECUTIVA)\t**\n\t\t**\t\t\t\t\t\t\t\t\t\t**\n");
		printf("\t\t**\t\t\t\t\t\t\t\t\t\t**\n");
		printf("\t\t**********************************************************************************\n\t\t**********************************************************************************\n\n\t\t");
		scanf("%d",&*op);
		if(*op==1 || *op==2)
		{
			c++;
		}
		else
		{
			printf("\t\t\tOPCION INVALIDA");
		}
	}while(c==0);
}
void display(int op){
	if(op==2)
		{
			system("cls");
		}
	else
		{
			clearg();
		}
}
void crearmatriz(char M[FILA][COLUMNA], char M1[FILA][COLUMNA]){
	int i,  j;
	
	for(i=0; i<FILA; i++)
	{
		for(j=0; j<COLUMNA; j++)
		{
			if(i%2==0)
			{
				M[i][j]='-';
				M1[i][j]='-';
			}
			else
			{
				if(j%2==0)
				{
					M[i][j]='|';
					M1[i][j]='|';
				}
				else
				{
					M[i][j]=' ';//Agrega por defecto espacios en los lugares donde van las celulas
					//La matriz 1 no se llena debido que no es necesario
				}
			}
		}
	}
}
void vaciarmatriz(char M[FILA][COLUMNA]){
	int i,  j;

	for(i=1; i<=99; i+=2)//El ciclo compara solamente las celdas donde se encuentran las celulas, es decir las impares
	{
		for(j=1; j<=99; j+=2)
		{
				M[i][j]=' ';//Vacia todas las celdas de las celulas de la matriz
		}
	}
}
void llenarmanualmente(char M[FILA][COLUMNA], struct registro saved[]){
	int i, j, k;
	
	for(i=0; i<2500; i++)//Lleno el guardado de la primera generaci�n con puras celulas muertas para garantizar 
						//Un "tipo" reinicio del guardado cero
	{
		saved[0].cad[i]='M';
	}
	printf("\n\n\n\n\t\t*************************************************\n\t\t*\t\t\t\t\t\t*");
	printf("\n\t\t*\tCUANTAS CELULAS VIVAS DESEAS TENER?\t*\n\t\t*\t\t\t\t\t\t*\n");
	printf("\t\t*************************************************\n\t\t\n\t\t");
	scanf("%d",&celulas);//Escaneo la variable global celulas
	printf("\n\n\n\n\t\t*****************************************************************************************\n\t\t*\t\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*\tINSERTA EL NUMERO DE FILA, SEGUIDAMENTE DEL NUMERO DE LA COLUMNA DE LA CELULA\t*\n\t\t*\tRECUERDA QUE DEBES INGRESAR DATOS ENTRE UN RANGO DE 1 Y 50\t\t\t*\n\t\t*\t\t\t\t\t\t\t\t\t\t\t*\n");
	printf("\t\t*****************************************************************************************\n\n\n");
	for(i=1; i<=celulas; i++)
	{
		do
		{
			printf("\t\t\tCELULA VIVA %d\t\tFILA ",i);
			scanf("%d",&j);
			printf("\t\t\t\t\t\tCOLUMNA ");
			scanf("%d",&k);
			printf("\n\n");
			if(saved[0].cad[((50*(j-1))+(k-1))]=='V')//En caso de que ya se haya introducido previamente
			{
				printf("\t\t\tYA HAS REGISTRADO ESA CELULA PREVIAMENTE :(\n\n");//Mostrar ese mensaje
				i-=1;//Y decrementar el contador para asi no afectar la cantidad de celulas introducidas
			}
			if((j<1 || j>50) || (k<1 || k>50))//En caso de que los valores no esten dentro del rango
			{
				printf("\t\t\tVALORES INVALIDOS, INTENTA DE NUEVO\n\n");
			}
		}while((j<1 || j>50) || (k<1 || k>50));//Condici�n que restringe el rango
		M[j+(j-1)][k+(k-1)]=219;//Las celulas vivas introducidas por el usuario son introducidas en la matriz 0 con su codigo ascii
		saved[0].cad[((50*(j-1))+(k-1))]='V';//Guardado de las celulas introducidas a la generaci�n cero
	}
	printf("\t\t\t");
	clearp();
}
void llenadorandom(char M[FILA][COLUMNA], struct registro saved[]){
	int i,  j, random;
	
	celulas=0;//Reinicio del contador de celulas vivas
	for(i=1; i<=99; i+=2)
	{
		for(j=1; j<=99; j+=2)
		{
			random=rand()%2;//rand()% n+1. Rango definido de los valores random (0 y 1)
			if(random==0)
			{
				M[i][j]=219;
				celulas++;//Aumenta el contador de celulas vivas
			}
			else
			{
				M[i][j]=' ';
			}
		}
	}
	//Puesto que es imposible que la primera generaci�n sea estable
	//Para que no se detecte el saved (0) como totalmente muerto, agregamos un "V" a dicha cadena en un lugar arbitrario
	saved[0].cad[0]='V';
}
void printfmat(char M[FILA][COLUMNA]){//Impresi�n de la matriz
	int i,  j;
	printf("\t\t\t");
	for(i=0; i<FILA; i++)
	{
		for(j=0; j<COLUMNA; j++)
		{
			printf("%c",M[i][j]);
		}
		printf("\n\t\t\t");
	}
}
void compararmat(char M[FILA][COLUMNA], char M1[FILA][COLUMNA]){//funcion que recorre celulas vivas y muertas
	int i,  j;
	celulas=0; //Reinicio del contador de celulas vivas global cada vez que se pasa a otra generaci�n
	for(i=1; i<=99; i+=2)//El ciclo compara solamente las celdas donde se encuentran las celulas, es decir las impares
	{
		for(j=1; j<=99; j+=2)
		{
				genesis(M,i,j,M1);//Determina si la celula vivira o moririra
		}
	}
}
void genesis(char M[FILA][COLUMNA], int i, int j, char M1[FILA][COLUMNA]){//continuaci�n de compararmat
	int a, b, cell=0;
		for(a=i-2; a<=i+2; a=a+2)//Algoritmo de comparaci�n con las celdas vecinas
		{
			for(b=j-2; b<=j+2; b=b+2)
			{
				if((a!=i) || (b!=j))//Evitar comparar con la celda a comparar
				{
					if((a>0 && a<100) && (b>0 && b<100))//Definicion del rango de comparacion de celdas vecinas
					{
						if(M[a][b]!=' ')//En caso de que la celda vecina este viva, agregarla a un contador
						{
							cell++;
						}	
					}	
				}
			}
		}
	if(M[i][j]!=' ')//S� la celula evaluada esta viva, determina su vida en la sig. generaci�n
	{
		if(cell==2 || cell==3)
		{
			M1[i][j]=219;
			celulas++;//Incremento de variable global de celulas vivas
		}
		else
		{
			M1[i][j]=' ';
		}
	}
	else//si la celula evaluada esta muerta, determina su vida en la sig. generaci�n
	{
		if(cell==3)
		{
			M1[i][j]=219;
			celulas++;//Incremento de variable global de celulas vivas
		}
		else
		{
			M1[i][j]=' ';
		}
	}
}
void copyandregistermat(char M[FILA][COLUMNA], char M1[FILA][COLUMNA], int k, struct registro saved[]){
	int i, j;
	if(k>3)//En caso de que el numero de generaciones sea mayor al numero de guardados (saved), recorrer dichos guardados para guardar la generaci�n reciente
	{
		for(i=0; i<3; i++)
		{
			for(j=0; j<2501; j++)
			{
				saved[i].cad[j]=saved[i+1].cad[j];//Recorrer los arrays dentro del struct
				
			}
		}
	}
	for(i=1; i<=99; i+=2)//El ciclo copia y registra solamente las celdas donde se ubican las celulas
	{
		for(j=1; j<=99; j+=2)
		{
			M[i][j]=M1[i][j];//Proceso de copiado de la matriz 1 a la matriz 0
			registrar(M,i,j,saved,k);//Registrar las celulas de la generacion en una cadena
		}
	}
}
void registrar(char M[FILA][COLUMNA], int i, int j, struct registro saved[],int k){//Proceso de registro de generaciones
	
	if(k<4)//Si la generacion es menor al numero de guardados disponible, guardar la generaci�n segun su numero
	{
		if(M[i][j]!=' ')
		{
			saved[k].cad[(50*(((i+1)/2)-1))+(((j+1)/2)-1)]='V';//Se utiliza una "V" para indicar que esta viva
		}
		else
		{
			saved[k].cad[(50*(((i+1)/2)-1))+(((j+1)/2)-1)]='M';//Se utiliza una "M" para indicar que esta muerta una celula
		}
	}
	else//En caso de que sea mayor, puesto que anteriormente ya se recorrieron los guardados, entonces siempre la generacion
	//a guardar se guardara en saved[3], es decir el guardado mas actual
	{
		if(M[i][j]!=' ')
		{
			saved[3].cad[(50*(((i+1)/2)-1))+(((j+1)/2)-1)]='V';//Se utiliza una "V" para indicar que esta viva
		}
		else
		{
			saved[3].cad[(50*(((i+1)/2)-1))+(((j+1)/2)-1)]='M';//Se utiliza una "M" para indicar que esta muerta una celula
		}
	}
}
int pattern(struct registro saved[], int z){
	//Esta funci�n pretendera encontrar patrones y oscilaciones dentro de los guardados de las generaciones
	//Retorna 1 si se encuentra una estabilidad, si no se retornara cero.
	if(z>=3)//Si los guardados estan llenos, se comparara el guardado reciente (el 3) con los otros
	//Para asi detectar patrones y oscilaciones.
	{
		if(((strcmp(saved[3].cad,saved[2].cad)==0) || (strcmp(saved[3].cad,saved[1].cad)==0)) || (strcmp(saved[3].cad,saved[0].cad)==0))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else//En caso contrario solo se comparara la generaci�n mas reciente (es decir z) con sus antecesoras
	{
		if(z==1)
		{
			if((strcmp(saved[0].cad,saved[1].cad)==0))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if(z==2)
			{
				if((strcmp(saved[2].cad,saved[1].cad)==0) || (strcmp(saved[2].cad,saved[0].cad)==0))
				{
					return 1;	
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}
}
int muertacompletamente(struct registro saved[], int k){
	int i, contadorprovisional=0;
	
	if(k<4)//S� la generacion es menor al numero de guardados disponibles, se usa su numero tal cual
	{
		for(i=0; i<2500; i++)//Analiza completamente el guardado de la generaci�n mas reciente
		{
			if(saved[k].cad[i]=='V')//Si encuentra una celula viva, aumenta un contador
			{
				contadorprovisional++;
			}
		}
	}
	else//si no, por defecto compara saved(3)
	{
		for(i=0; i<2500; i++)//Analiza completamente el guardado de la generaci�n mas reciente
		{
			if(saved[3].cad[i]=='V')//Si encuentra una celula viva, aumenta un contador
			{
				contadorprovisional++;
			}
		}
	}
	if(contadorprovisional==0)//Si toda la generaci�n esta muerta, retorna 1
	{
		return 1;
	}
	else//De lo contrario 0
	{
		return 0;
	}
}
void lecturaArchivo(FILE *fd, char M[FILA][COLUMNA], struct registro saved[], int *ban, int *ban1){
	int i, j, k=0, q=0, ban3=1, invalid[(50*50*2)+2], valid[(50*50*2)+2];
	char cad[10];
	printf("\n\t\t\t--------------------------------------------------------\n");
	valid[0]=0, invalid[0]=1;
	while(!feof(fd))
	{
		fscanf(fd, "%s%d", cad, &i);
		fscanf(fd, "%s%d", cad, &j);
		if ((i>-3000 && i<3000) && (j>-3000 && j<10000))
		{
			if ((i<1 || i>50) || (j<1 || j>50))
			{
				invalid[k] = i;
				invalid[k+1] = j;
				k += 2;
			}
			else
			{
				valid[q] = i;
				valid[q+1] = j;
				q += 2;
			}
		}
	}
	if (valid[0] == 0 && invalid[0] == 1)
	{
		printf("\t\t\tEL ARCHIVO LEIDO NO CONTIENE NINGUNA CELULA\n\n");
		*ban = 1;
	}
	else
	{
		if (valid[0] != 0)
		{
			printf("\t\t\tCELULAS VIVAS:\n\n");
			for (i=0; i<q; i+=2)
			{
				for (j=i; j<q+2; j+=2)
				{
					if ((valid[i] == valid[j+2]) && (valid[i+1] == valid[j+3]))
					{
						ban3 = 0;
					}
				}
				if (ban3 == 1)
				{
					printf("\t\t\t\tFILA: %d\n\t\t\t\tCOLUMNA: %d\n\n", valid[i], valid[i+1]);
					M[valid[i]+(valid[i]-1)][valid[i+1]+(valid[i+1]-1)]=219;
					saved[0].cad[(50*(valid[i]-1))+(valid[i+1]-1)]='V';//Guardo	
				}
				ban3 = 1;
			}
			*ban1 = 2;
		}
		if (invalid[0] != 1)
		{
			printf("\t\t\tCELULAS INVALIDAS:\n\n");
			for (i=0; i<k; i+=2)
			{
				if ((invalid[i] != invalid[i+2]) || (invalid[i+1] != invalid[i+3]))//Condicion para evitar celular duplicadas.
				{
					printf("\t\t\t\tFILA: %d\n\t\t\t\tCOLUMNA: %d\n\n", invalid[i], invalid[i+1]);				
				}
			}
			if (*ban1 == 2)
			{
				printf("\t\t\t--DADO QUE EXISTE AL MENOS UNA CELULAR VIVA, LAS INVALIDAS LAS OMITIREMOS--\n\n");
			}
		}
	}
}
void salidaArchivo(FILE *fs, char M[FILA][COLUMNA], int cont){
	int i, j;
	fprintf(fs, "\t\t\t\t\t\t\t\tGeneracion %d\n\n", cont);
	fprintf(fs, "\t\t\t");
	for (i=0; i<FILA; i++)
	{
		for (j=0; j<COLUMNA; j++)
		{
				fprintf(fs, "%c", M[i][j]);
		}
		fprintf(fs,"\n\t\t\t");
	}
	fprintf(fs, "\n\n");
}

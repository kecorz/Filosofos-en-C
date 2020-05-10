// PROBLEMA DE LOS FILOSOFOS DE E. DIKJSTRA
//MATERIA: FUNDAMENTOS DE SISTEMAS EMBEBIDOS
//NOMBRE: CORELLA PÉREZ ELDA
//LIBRERIAS
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include <errno.h>
#include <limits.h>

int tiempo_para_comer;
float tiempo_para_comer_aux;
int Nfilosofos;
pthread_mutex_t *tenedor;

void tomaTenedor( int n ){

	pthread_mutex_lock( &tenedor[n] ); //OPERACIÓN SOLICITA RECURSOS P
        printf("\nEl filosofo %d ya tomó el tenedor izquierdo \n" ,n); //REPORTA QUE TOMA EL TENEDOR IZQUIERO Y SU NÚMERO
        if (n!=0){
        	pthread_mutex_lock ( &tenedor[n-1] ); //OPERACIÓN SOLICITA RECURSOS P
		printf("\nEl filosofo %d ya tomó el tenedor derecho \n" ,n); //REPORTA QUE TOMA EL TENEDOR DERECHO Y SU NÚMERO
        }
	else{
		pthread_mutex_lock( &tenedor[Nfilosofos] ); //OPERACIÓN SOLICITA RECURSOS P
                printf("\nEl filosofo %d ya tomó el tenedor derecho  \n" ,n); //REPORTA QUE TOMA EL TENEDOR DERECHO Y SU NÚMERO
        }
}

void dejaTenedor( int n){

	
        pthread_mutex_unlock( &tenedor[n] ); //OPERACIÓN LIBERA RECURSOS V
        printf("\nEl filosofo %d ya dejó el tenedor izquierdo \n" ,n);// REPORTA QUE LIBERA EL TENEDOR IZQUIERDO Y SU NÚMERO
        if (n!=0){
        	pthread_mutex_unlock ( &tenedor[n-1] ); //OPERACIÓN LIBERA RECURSOS V
		printf("\nEl filosofo %d ya dejó el tenedor derecho\n" ,n); //REPORTA QUE LIBERA EL TENEDOR DERECHO Y SU NÚMERO
        }
	else{
		pthread_mutex_unlock( &tenedor[Nfilosofos] ); //OPERACIÓN LIBERA RECURSOS V
		printf("\nEl filosofo %d ya dejó el tenedor derecho \n" ,n); //REPORTA QUE LIBERA EL TENEDOR DERECHO Y SU NÚMERO
	}
}

void *vidaFilosofo( void *n ){

	float pensar;
	float comer;
	int aux, aux_2;
	float aux_3=0;
    int vecesCome=0;



    while(aux_3 < tiempo_para_comer_aux){
    	

		//EL FILOSOFO CALCULA EL TIEMPO QUE VA A PENSAR Y LO REPORTA
		srand(time(0)); //Segundos
		pensar = rand()%701+100;
		aux = pensar;
		pensar = pensar/1000;
		printf("\nfilósofo: %d piensa por: %d ms\n" ,*(int *)n,aux);		
		sleep(pensar);
		tomaTenedor(*(int *)n);

		//EL FILOSOFO CALCULA EL TIEMPO QUE VA A COMER Y LO REPORTA
		srand(time(NULL));
		comer = rand()%201+100;
		aux_2 = comer;
		comer = comer/1000;
		printf("\nfilosofo: %d come por: %d ms\n" ,*(int *)n,aux_2);
		sleep( comer );
		dejaTenedor(*(int *)n);
		aux_3 += 0.0017;
		
	}
    
	/*pthread_exit(NULL);*/
}


int main(int argc, char * argv[]){

	int n;
	int *salida;
	char *p;

		
	/*long a1 = strtol(argv[1], &p, 10);*/	

	if (argc != 2) { //SI SE INGRESARON DOS ARGUMENTOS, REALIZAR VALIDACIONES
		if(argc > 1){
			for(int i = 1; i<argc; i++){
				long a1= strtol(argv[i], &p, 10); 				
				if(p == argv[i]){
					fprintf(stderr, "Ingresaste un dato no numerico\n");
					printf("\nPor favor intenta con: \n filosofos.py [tiempo en segundos] [numero de filosofos]\n");
					exit(0);
					
				}
			}
		//LECTURA DE LOS VALORES INGRESADOS POR CONSOLA
		sscanf(argv[1], "%d", &tiempo_para_comer);
		sscanf(argv[2], "%d", &Nfilosofos);
		tiempo_para_comer_aux = tiempo_para_comer;
			
		}
		if(argc == 1){/*ESTABLECEMOS VALORES DEFAULT */

			Nfilosofos = 5;
			tiempo_para_comer = 30;
			tiempo_para_comer_aux = tiempo_para_comer;
			
		}
		//AL REALIZAR VALIDACIONES, EL CODIGO SE EJECUTA

		int error[Nfilosofos];
		int id[Nfilosofos];	
		pthread_t filosofo[Nfilosofos]; //ARREGLO CON LA CANTIDAD DE HILOS/FILOSOFOS
		tenedor= malloc(sizeof(pthread_mutex_t)*Nfilosofos);//ARREGLO CON VARIABLES MUTEX 	

		if(Nfilosofos == 5 && tiempo_para_comer == 30){
    		printf("Iniciando con valores default\n");
    		printf("SEGUNDOS: [%d] FILSOFOS: [%d]\n",tiempo_para_comer,Nfilosofos );
    	}

		// INICIAR SEMAFOROS A UTILZAR
		for( n=0; n<Nfilosofos; n++){
            pthread_mutex_init ( &tenedor[n], NULL );
        }       
		// CREA HILOS/FILOSOFOS INDICANDO FUNCION A EJECUTAR Y SU NUMERO DE IDENTIFICACION
		for( n=0; n<Nfilosofos; n++ ){
			id[n] = n;
			printf("SOY EL FILOSOFO: %d\n",n );
			error[n] = pthread_create( &filosofo[n], NULL, vidaFilosofo, &id[n] );
		}
		// ESPERA A QUE TERMINE CADA UNO DE LOS HILOS
		for( n=0; n<Nfilosofos; n++){
			pthread_join( filosofo[n], (void **)&salida );
		}

	}
	else{
		if(argc == 2){ //SOLO SE INGRESO UN DATO
			printf("Debes de ingresar dos numeros como argumento\n");
			printf("\nPor favor intenta con: \n filosofos.py [tiempo en segundos] [numero de filosofos]\n");

		}

	}
	
	return 0;
}


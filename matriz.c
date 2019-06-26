#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>




int main(){

	srand(time(NULL));

	int n,x,y,dato;
	float INICIO,FIN;

    x=3000; // NUMERO DE FILAS DE LA MATRIZ A
    y=3000; // NUMERO DE COLUMNAS DE LA MATRIZ B
	n=3000; // NUMERO DE COLUMNAS DE A Y NUMERO DE LAS FILAS DE B


    //##########  MATRICES ###########
	int **A;
	int **B;
    int **C;

    A = (int **)malloc(x*sizeof(int*));
  	B = (int **)malloc(n*sizeof(int*));
    C = (int **)malloc(x*sizeof(int*));

 	for (int i=0;i<x;i++){
 		A[i] = (int*)malloc(n*sizeof(int));
	}
	for (int i=0;i<n;i++){
 		B[i] = (int*)malloc(y*sizeof(int));
	}
	for (int i=0;i<x;i++){
 		C[i] = (int*)malloc(y*sizeof(int));
	}


   //################ MATRIZ A ##################
	for (int i = 0; i < x; ++i){
		for (int j = 0; j < n; ++j){
			A[i][j]=rand()%100;
		}

	}

    //################ MATRIZ B ##################
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < y; ++j){
			B[i][j]=rand()%100;
		}
	}

    //##########  CALCULO EN SERIE ###########
    INICIO= omp_get_wtime();

    for (int i = 0; i < x; ++i){
		for (int j = 0; j < y; ++j){
			dato=0;
			for (int k = 0; k < n; ++k){
				dato=dato+A[i][k]*B[k][j];
			}
			C[i][j]=dato;
		}
    }

    FIN = omp_get_wtime();
    printf(" El tiempo sin multicore es: %f segundos. \n", FIN - INICIO);

    //##########  CALCULO CON MULTICORE ###########
    INICIO= omp_get_wtime();

    #pragma omp parallel
    {
    	int i, j, k;
    	#pragma omp for
    	for ( i = 0; i < x; ++i){
			for ( j = 0; j < y; ++j){
				double dat=0;
				for ( k = 0; k < n; ++k){
					dat+=A[i][k]*B[k][j];
				}
				C[i][j]=dat;
			}
    	}
    }

    FIN = omp_get_wtime();
    printf(" El tiempo con multicore es: %f segundos. \n", FIN - INICIO);

	return 0;
}

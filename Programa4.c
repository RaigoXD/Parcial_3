/*
    Ing(c) Jhoan Esteban Raigoza Agudelo
    Universidad Tecnologica de Pereira
    Proferos Phd Ricardo Moreno Laverde.
    Fehca de creacion : 04/10/2020 

*/
#include <stdio.h> // importo la libreria de entrada y salida.
#include <stdlib.h> // Importo esta libreria para poder hacer uso de la funcion srand()
#include <time.h>   // Importo esta libreria para poder hacer uso de la funcion time()

// Prototipos de la funciones utilizadas
void llenar(float tab[8][8]);   // Prototipo de la funcion, llena la matriz dada como parametro de datos alazares entre 0.0 - 15.0
float hallar_moda(float tab[8][8]);   // prototipo de la funcion, hallar la moda de la matriz dada como parametro y la retorna.
void Diagonales(float tab[8][8]);  // prototipo de la funcion, para calcular la resta de la diagonal superior y inferior dividido el promedio del arreglo.
void Promedios(float tab[8][8]);  // Prototipo de la funcion, para calcular los promedios de toda las columans y todas las filas.
void matriz_Fac(float tab[8][8]); // Prototipo de la funcion, para calcular la matriz en factorial de cada elemento.
void Promedios_Filas_Columnas(float tab[8][8]); // prototipo de la funcion, para calcular los promedios de filas y columnas 

// Funciones creadas antes del main.
int contador_veces(float tab[8][8], float numero){ // ESta funcion me cuenta cuantas veces esta el parametro numero en una matriz de elementos flotantes-
    int contador = 0; //donde guardare el numero de veces que se repita en la matriz. 
    for(int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)   
            if(tab[i][j] == numero)
                contador++;
    return contador;  // Retorno en numero de veces.
} // Fin de la funcion contador_veces()

float Promedio(float tab[8][8]){  // Funcion para sacar el promedio de los elementos de una matriz 8x8 y ese valor se retorna
    float promedio_t = 0.0;   // Variable para guardar el valor de las sumas
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){  // Recorro la matriz sumando todos sus elementos.
            promedio_t += tab[i][j];
        }
    return promedio_t / 64;
}  // Fin de la funcion Promedio();

double Factorial(double numero){ // Funcion para calcular el factoria de un numero.
    double resultado = 1.0; // Variable donde guardare el valor resultante
    for(int i = 1; i <= numero; i++) resultado *= i;   // Calculo
    return resultado; // Retorno el resultado
} // Fin de la funcion factorial();

int main()  // Funcion main() 
{
    float Promedio_T = 0.0; int numero_i = 0;  // Algunas variables para guardar vainas importantes XD
    float tabla[8][8];   // la tabla 8x8 en donde estare afectuando todas las operaciones.
    float moda = 0;      // Variable donde guardare la moda

    llenar(tabla);  // Llamo a la funcion llenar, para llenar la matriz
    
    printf("A) \n\n");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){  // Imprimo toda la matriz
            printf("%0.1f\t", tabla[i][j]);
        }
        printf("\n");
    }  // Fin de la impresion.

    moda = hallar_moda(tabla);
    printf("\nB) La moda es: %0.1f", moda);  // Hallo la moda y la imprimo

    Promedios(tabla);   // llamo a la funcion promedios para hallar los promedios de cada fila y columna
    
    Diagonales(tabla);  // la funcion diagonales para resolver el punto numero D edl parcial
    
    printf("\n\nE)\n");
    matriz_Fac(tabla);   // La matriz de factoriales en la funcion matriz_Fac()
    
    Promedio_T = Promedio(tabla);
    numero_i = Promedio_T * 10;  // ESto lo hago para tener un solo decimal.
    Promedio_T = numero_i /10.0;
    printf("\nF) El promedio (%0.1f) en la matriz esta %i veces",Promedio_T ,contador_veces(tabla, Promedio_T));

    Promedios_Filas_Columnas(tabla);   // El punto g del ejercicio
    return 0;
} // Fin del main();

// 1.
float hallar_moda(float tab[8][8]){  // Funcion para buscar la moda, me retorna el valor el cual se repita mas veces en la matriz.
    float repetido = 0.0; int numero_veces = 0; int contador_A = 0; // Variable las cuales utilizare para guardar el numero de veces que se repite la moda y la moda.
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){ // Recorro la matriz, dandole cada elemento a la funcion contar_veces() me retorna el numero de veces que esta un numero en la matriz
            contador_A = contador_veces(tab, tab[i][j]); // llamo a la funcion  contador_veces y lo que retorne lo guardo en contador_A
            if(numero_veces < contador_A){    // Si eesta mas veces que el dato anterior lo remplazo y es mi nueva moda.
                numero_veces = contador_A;
                repetido = tab[i][j];
            }
        }
    return repetido;
} // Fin de la funcion hallar_moda();

//2
void Promedios(float tab[8][8]){    // Funcion promedios, busca los promedios de cada fila y columna
    float promedio_T = 0;
    printf("\nC)\nPromedios de las Filas\n");
    for(int i=0; i< 8; i++){
        for(int j = 0; j < 8; j++)  // Calculo los promedios de las filas 
            promedio_T += tab[i][j];
        printf("P%i: %0.1f\t", i+1, promedio_T/ 8);
        promedio_T = 0;
    }
    printf("\nPromedios de las Columnas\n");
    for(int i=0; i< 8; i++){
        for(int j = 0; j < 8; j++)  // Calculo los promedios de la columnas
            promedio_T += tab[j][i];
        printf("P%i: %0.1f\t", i+1, promedio_T/ 8);
        promedio_T = 0;
    }
} // Fin de la funcion


//3
void Diagonales(float tab[8][8]){ // La funcion diagonales calcula la diagonal superior - diagonal inferior y lo divide por el promedio 
    float diagonal_superior = tab[0][0]+tab[1][1]+tab[2][2]+tab[3][3]+tab[4][4]+tab[5][5]+tab[6][6]+tab[7][7]; // Suma de la diagonal superior.
    float diagonal_inferior = tab[0][7]+tab[1][6]+tab[2][5]+tab[3][4]+tab[4][3]+tab[5][2]+tab[6][1]+tab[7][0]; // Suma de la diagonal inferior
    float promedio_T = Promedio(tab);
    printf("\nD)  (%0.1f -  %0.1f)/  %0.1f = %0.1f", diagonal_superior, diagonal_inferior, promedio_T,  (diagonal_superior - diagonal_inferior) / promedio_T);
} // Fin de la funcion

// 4
void matriz_Fac(float tab[8][8]){ // La funcion Matriz_fac() me calcula una matriz igual a la ingresada con la diferencia es que esta seran los factoriales de los elementos
    double numero = 0; int contador = 0; //dos variables para facilitar el proceso
    for(int i = 0; i < 8; i++){     
        for(int j = 0; j < 8; j++){    // Recorro la matriz imprimiendo los elementos
            numero = Factorial(tab[i][j]);
            while((int)(numero) != 0){
                numero = numero / 10.0;
                contador++;    
            }
            printf("%0.0lf", Factorial(tab[i][j])); // Imprimo los elementos 
             for(int k = 0; k < 15 - contador; k++){printf(" ");} // Hago un pequeño truco para organizar bien en columnas.
            contador = 0;
        }
        printf("\n");
    }    
} // Fin de la funcion 

// 5

void Promedios_Filas_Columnas(float tab[8][8]){
    float promedio_Filas= 0.0;
    float promedio_Columnas = 0.0;  // Variables para guardar mas vainas.
    float Mayor_actual = 0.0;
    for(int i=0; i< 8; i++){
        for(int j = 0; j < 8; j++)
            if(Mayor_actual < tab[i][j])
                Mayor_actual = tab[i][j]; // Calculo los valores mayores de cada fila y los voy sumando para al final dividirlos entre 8
        promedio_Filas += Mayor_actual;
        Mayor_actual = 0;
    }
    Mayor_actual = 0.0;

    for(int i=0; i< 8; i++){
        for(int j = 0; j < 8; j++)
            if(Mayor_actual < tab[j][i]) // Calculo los valores mayores de cada columna y los voy sumando para al final dividirlos entre 8
                Mayor_actual = tab[j][i];
        promedio_Columnas += Mayor_actual;
        Mayor_actual = 0;
    }
    printf("\n\n-> G) El valor del promedio de los valores mas altos de cada fila es %0.1f", promedio_Filas / 8);  // Imprimo el resultado de las filas
    printf("\n-> G) El valor del promedio de los valores mas altos de cada columna es %0.1f", promedio_Columnas / 8); // Imprimo el resultado de las columnas
} // fin de la funcion

void llenar(float tab[8][8]){  // Funcion que utilizo para llenar la matriz
    srand(time(0)); // Cambio la semilla para poder tener valores aleatorios.
    float numero = 0.0, numero_decimal = 0.0; // Dos variables que las utilizare para los valores aleatorios.
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++){ // recorro la matriz poniendo numeros alazares entre el 0.0 al 15.0
            numero = rand() % 15;
            numero_decimal = (rand() % 10) / 10.0;
            if(numero_decimal >= 15.0)
                tab[i][j] = numero;   // Coloco los numeros
            else
                tab[i][j] = numero + numero_decimal; // Coloco los numeros.
        }
} // Fin de la funcion

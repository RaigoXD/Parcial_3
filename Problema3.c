/*
    Ing(c) Jhoan Esteban Raigoza Agudelo
    Universidad Tecnologica de Pereira
    Proferos Phd Ricardo Moreno Laverde.
    Fehca de creacion : 31/10/2020 

*/
#include <stdio.h> // importo la libreria de entrada y salida.
#include <stdlib.h>// Importo esta libreria para poder hacer uso de la funcion srand()
#include <time.h>  // Importo esta libreria para poder hacer uso de la funcion time()

// Prototipo de las funciones utilizadoas;
void llenar(int tab[30][30]); // prototipo de la funcion, toma como parametros solamente el arreglo
void revisar_QR(int tab[30][30]); // Prototipo de lA funcion, toma como parametros solamente el arreglo

int main()
{
    int QR[30][30]; // Arreglo donde simularemos de forma aleatoria un QR
    llenar(QR);     // llamo a la funcion llenar() para generar de forma aleatoria los datos en el arreglo QR
    revisar_QR(QR); // Llamo a la funcion revisar_QR() para revisar los puntos clases 
    printf("\n\n"); // imprimo varios espacios.

    for(int i = 0; i < 30; i++){ 
        for(int j = 0; j < 30; j++)   // Bucle para imprimr el arreglo
            if( QR[i][j] == 1)
                printf("%c", 219);
            else
                printf("%c", 32);
        printf("\n");
    }
    return 0;
}
void revisar_QR(int tab[30][30]){  // Funcio para revisar_QR tiene como parametro el arreglo que simula el QR
    int contador_negros = 0;  // Variable donde guardare la cantidad de puntos negros en el cuadrado 7x7 y tambien los errores en la septima linea
    for(int i = 0; i < 7; i++)
        for(int j = 0;j < 7; j++)   // Bucle para revisar el cuadrado
            if(tab[1+i][22+j] == 1)
                contador_negros++; // Sumo cada vez que encuentre un punto negro
        
    if(contador_negros == 25)  // Si es la cantidad exacta lo digo
        printf("\n-> El cuadrado de 7x7 cumple con la cantidad de puntos negros");
    else
        printf("\nNo cumple el cuadrado 7x7 de la esquina"); 

    contador_negros = 0; // Vuelve a 0 para contar ahora el numero de errores en la septima linea 

    if(tab[7][1] == 0)
        contador_negros++;
    if(tab[7][3] == 0)        // Reviso los 3 puntos 
        contador_negros++;
    if(tab[7][24] == 0)
        contador_negros++;

    if(contador_negros == 0)  // Si no hubo errores 
        printf("\n-> Este codigo QR cumple.");
    else{
        printf("\n-> Hay %i errores en la septima fila", contador_negros); // si existen errores.
        printf("\n-> Falsificado");
    }
}

void llenar(int tab[30][30]){  // Funcion para llenar de forma aleatoria, para crear el codigo Qr
    srand(time(0)); // Cambio la semilla con el tiempo para tener valores aleatorios
    int rand1 = 0;  // Variable para guardar los valores aleatorios 
    for(int fil = 0; fil < 30; fil++)  
            for(int col = 0; col < 30; col++){
                rand1 = rand() % 4;
                if(rand1 == 1){
                   tab[fil][col] = 1;    // Recorro todo el arreglo poniendo 0 o 1 con una probabilidad de 1/4.
                }else if(col == 0 || col == 29 || fil == 0 || fil == 29){  // Si es la periferia coloco 1 para hacer una espacia de region
                    tab[fil][col] = 1;
                }else{
                    tab[fil][col] = 0;
                }
            }
} // Fin de la funcion llenar
/*
    Ing(c) Jhoan Esteban Raigoza Agudelo
    Universidad Tecnologica de Pereira
    Proferos Phd Ricardo Moreno Laverde.
    Fehca de creacion : 04/10/2020 

*/
#include <stdio.h> // importo la libreria de entrada y salida.
#include <string.h> // importa la libreria string para utilizar algunas de sus funciones.
#include <stdlib.h> //  importo la libreria para usar algunas funciones utilez como atoi
#include <math.h> // importo la funcion math para poder usar funciones como pow().

// Prototipos de la funciones.
long identificador(char *funcion, int numero);  // La Prototipo de la funcion, recibe como paramatros la funcion analizar y el numero a remplaxar por X
long analiza_termino(char *termino, int len, int numero);
int tabulacion(long tabulaciones[30][2], int inicio, int final, int incremento, char *funcion);
void escalado(long tabulaciones[30][2], int cantidad_tab, int X_Y[30][2]);
void graficar(long tabulaciones[30][2], int cantidad_tab, int X_Y[30][2]);

// Funciones antes del main
int buscarX_Y(int X_Y[30][2], int numeroX,int numero_Y, int cantidad_tab){
    for(int i = 0; i < cantidad_tab; i++)
        if(numeroX == X_Y[i][0])
            if(numero_Y == X_Y[i][1])
                return 1;     
    return 0;
}

int main(){
    long tabulaciones[30][2]; // Arreglo donde guardare las tabulaciones de la funcion
    int X_Y[30][2];  // Arreglo donde guardare los datos de X y Y ya escalados
    char funcion[30];  // Arreglo donde guardare la funcion ingresada por el usuario
    int Rango_inicial = 0; // Rando inicial dado por el usuario
    int Final = 0; int incremento = 0; // punto final e incremento dado por el usuario 
    int numero_elementos = 0; // numero de elementos a la hora de tabular
    printf("\nBienvenido  **Graficador de funciones**  \n->Ingrese la funcion: ");
    scanf("\n%s", &funcion); // Pido la funcion
    printf("\n Ingresa el inicio: ");    scanf("%i", &Rango_inicial);
    printf("Incresa el final: ");        scanf("%i", &Final);   // Pido los datos
    printf("Ingresa el incremento: ");   scanf("%i", &incremento);
    numero_elementos = tabulacion(tabulaciones, Rango_inicial, Final, incremento, funcion);  // creo el tabulado del rango.
    printf("\n Tabla de tabulacion");
     for(int i = 0; i < numero_elementos; i++)
       printf("\n|X:%li\t|Y:%li\t|", tabulaciones[i][0], tabulaciones[i][1]); // Imprimo la tabla  

    escalado(tabulaciones, numero_elementos,X_Y); // Escalo los valores para poder graficas

     for(int i = 0; i < numero_elementos; i++)
       printf("\nX: %li\tY: %li", X_Y[i][0], X_Y[i][1]);

    printf("\n\n");
    graficar(tabulaciones, numero_elementos,X_Y); // por ultimo grafico
    return 0;
} // Fin de la funcion main


void graficar(long tabulaciones[30][2], int cantidad_tab, int X_Y[30][2]){ // La funcion graficar, es para crear nuestro plano de 80 * 24 y colocar los puntos que ya hemos hallado
    for(int i = 12; i >= -11; i--){
        for(int j = -40; j <= 39; j++){// Voy creando el grafico
            if(buscarX_Y(X_Y, j,i,cantidad_tab) == 1) // llamo a la funcion BuscarX_Y para preguntar si en este punto del grafico existe un punto de nuetra grafica final
                printf("X"); // Si es asi coloco una X
            else if(i == 0)  // Si la fila es la 0, imprimo -
                printf("-");
            else if(j == 0)  // Si la columna es la 0, imprimo |
                printf("|");
            else
                printf(" "); // Si no es nada, es el espacio de la grafica, espacio vacio
        }
        printf("\n"); // Saltos entre filas.
    }
} // fin de la funcion

void escalado(long tabulaciones[30][2], int cantidad_tab, int X_Y[30][2]){ // Esta funcion se encargar de calcular y hacer el escalado de nuestros valores de X y Y a la escala de 80 columnas y 24 filas. 
    int mayorX = 0; int mayorY = 0;  // Variables que me ayudaran en el proceso, son mayorX es el valor mas grande de X, el mayorY es el valor mas grande de Y.
    int factor = 0;                  // Factor es el numero por el cual voy a multiplicar, este va a veriar de cual es el mas grande de los x y Y.
    for(int i = 0; i < cantidad_tab; i++){
        if(fabs(mayorX) < fabs(tabulaciones[i][0])) // Busco el mas grande de X con el valor abosluto recorriendo la matriz X_Y 
            mayorX = tabulaciones[i][0];  
        
        if(fabs(mayorY) < fabs(tabulaciones[i][1])) // Busco el mas grande de Y con el valor abosluto recorriendo la matriz X_Y 
            mayorY = tabulaciones[i][1];
    }

    printf("\nEl mayor del eje X es %li", mayorX);
    printf("\nEl mayor del eje Y es %li", mayorY);

    if(mayorX < 0)
        factor = -40;  // Si el mas grande de X es negativo, significa que debe ir en la posicion -40 y ese sera mi factor
    else
        factor = 39; // Si el mas grande de X es positivo, significa que debe ir en la posicion 39 y ese sera mi factor

    for(int i = 0; i < cantidad_tab; i++)
        X_Y[i][0] = ceil((tabulaciones[i][0] * factor) / mayorX);   // Hago una regla de 3 para X de esta forma determino la posicion en X de todos los valores.

    if(mayorY < 0)   // Si el mas grande de Y es negativo, significa que debe ir en la posicion -11 y ese sera mi factor
        factor = -11;
    else
        factor = 12;  // Si el mas grande de Y es positivo, significa que debe ir en la posicion 12 y ese sera mi factor

    for(int i = 0; i < cantidad_tab; i++)
        X_Y[i][1] = ceil((tabulaciones[i][1] * factor) / mayorY);   // Hago una regla de 3 para Y de esta forma determino la posicion en Y de todos los valores.
} // Fin de la funcion

int tabulacion( long tabulaciones[30][2], int inicio, int final, int incremento,char *funcion){ // Esta funcion, realiza el tabulado, es decir evalua la funcion ingresada por el usurio en todos los elementos deseados y retorna el numero de elementos
    int posicion = 0;  // Numero de elementos- contador
    for(int i = inicio; i <= final; i += incremento){   // voy recorriendo de inicio a fin dependiento del ingremento.
        tabulaciones[posicion][0] = i;      // Voy guardando el X y Y de la funcion en el arreglo tabulaciones.
        tabulaciones[posicion][1] = identificador(funcion, i);
        posicion++;
    }
    return posicion; // Retorno la cantidad de elementos 
} // Fin de la funcion

long identificador(char *funcion, int numero){ // La funcion identificador, analiza la funcion entregada como parametro y las separa en terminos, remplaza la X por numero y retorna el resultado.
    int longitud = strlen(funcion);   //  La longitud de la funcion 
    int longitud_ter = 0;   long resultado = 0;   // Variable como la longitud de cada termino y la variable donde guardare el resultado.
    char termino[30];       int pos_ter = 0;      // Variable Termino donde guardare cada termino, con un limite de 30 elementos y la variable pos_ter, es un contador para ir guardando cada elemento del termino.
    for(int i = 0; i <= longitud ; i++){   // Recorro la funcion
        if(funcion[i] != '-' && funcion[i] != '+' && i != 0 && funcion[i] != '\0'){  // un separador de termino puede ser el + o el -
            termino[pos_ter] = funcion[i]; // Voy llenando el termino
            pos_ter++;
        }
        else{
            termino[pos_ter] = '\0'; // Cierro la cadena.
            longitud_ter = strlen(termino);    // La longitud del termino
            //printf("\n%s", termino);
            resultado += analiza_termino(termino, longitud_ter, numero); // llamo a la funcion analiza termino, para ver su coeficiente y potencia y retorna ya evaluda la X
            termino[0] = funcion[i];  // Coloco el + o - que sigue
            pos_ter = 1; // Empiezo con otro termino.
        }    
    }
    return resultado;  // Retorno el resultado.
} // Fin de la funcion

long analiza_termino(char *termino, int len, int numero){  // Funcion analiza_termino, sirve para determinar el coeficiente y la pontencia del termino y lo evaluo el numero como X
    long coeficiente = 1; char coeficiente_c[30];
    int potencia = 1;     char potencia_c[30];  // Variables, para guardar ciertas cosas como el coeficiente, la potencia, el resultado y la posicion de la X en el termino
    int pos_X = 50;       long resultado = 0;

    for(int i = 0; i < len; i++)  // Busco la posicion de la X
        if(termino[i] == 'X') pos_X = i;

    if(pos_X != 50){   // Si la posicion de la X es 50 significa que no existe X.
        if(((termino[0] == '+' || termino[0] == '-') && termino[1] == 'X')  || termino[0] == 'X') // Si la x esta de primer elemento el coeficiente es 1;
            coeficiente_c[0] = '1';
        else{
            for(int i = 0; i < pos_X; i++){coeficiente_c[i] = termino[i];}   // guardo todos los numeros hasta encontrar la X
            coeficiente_c[pos_X] = '\0'; // Cierro la cadena  
        }

        if(termino[len-1] == 'X')  // Si la x esta en la ultima posicion la potencia es 1
            potencia_c[0] = '1';
        else{
            for(int j = pos_X+1; j < len; j++){potencia_c[j-(pos_X+1)] = termino[j];} // GUardo todos los elementos hasta llegar al final del termino desde la posicion de la X
            potencia_c[len- pos_X] = '\0';
        }
        coeficiente = atoi(coeficiente_c);   // Con la funcion atoi convierno numeros literales o caracters a numeros.
        potencia = atoi(potencia_c);           
        resultado = coeficiente * pow(numero, potencia);  // Calculo el coeficiente multiplicado por el numero elevado la potencia 
    }else
    {
        resultado = atoi(termino); // Si no existe X solo convierto el termino a numero y lo guardo
    }
    return resultado; // Retorno resultado.
} // Fin de la funcion
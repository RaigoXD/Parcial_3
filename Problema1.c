/*
    Ing(c) Jhoan Esteban Raigoza Agudelo
    Universidad Tecnologica de Pereira
    Proferos Phd Ricardo Moreno Laverde.
    Fehca de creacion : 31/10/2020 

*/
#include <stdio.h> // importo la libreria de entrada y salida.
#include <stdlib.h> // Importo esta libreria para poder hacer uso de la funcion srand()
#include <time.h>   // Importo esta libreria para poder hacer uso de la funcion time()

void llenar(int tab[30][30]);   // Prototipo de la funcion llenar, que tendra como parametros unicamente el arreglo o laberinto 
int solve(int tab[30][30], int fil_A, int Col_A, int Solve);  // Prototipo de la funcion Solve, tiene como parametros el laberinto a resolver, fila actual y columna actual en el laberinto y una variable llamada solve la cual tendre en cuenta para definir si el laberinto tiene solucion o no.
void imprimir(int lab[30][30]){ // Funcion para imprimir el labarinto, tiene como parametros el arreglo o laberinto
    for(int fil = 0; fil < 30; fil++){    
        for(int col = 0; col < 30; col++){
            if(lab[fil][col] == 1)
                printf("%c", 219);        // Lo que hace es imprimir fila por fila y dependiendo de lo que su encuentre en un posicion determinada
            else if(lab[fil][col] == 0)   // Se imprimira o una pared (caracter ascii: 219) o un espacio vacio (caracter ascii: 32) o un simbolo (caracter ascii: 169)
                printf("%c", 32);
            else if(lab[fil][col] == 9)
                printf("%c", 169);
        }
        printf("\n");
    }
} // Fin de la funcion imprimir. 

int main(){  // Funcion main 
    int lab[30][30];  // Un arreglo de 30 * 30 donde se generara el laberinto de forma aleatoria por medio de la funcion llenar.
    llenar(lab);      // llamo a la funcion llenar para generar el laberinto
    imprimir(lab);    // llamo a la funcion imprimir para mostrar el labarinto sin resolver.
    if(solve(lab, 0,0,0) == 0)    // Si la funcion solve retorna un cero significa que este laberinto no tiene solucion.
        printf("\n SIN SOLUCION");  
    return 0;
} // Fin de la funcion main

int solve(int tab[30][30], int fil_A, int Col_A, int Solve){  // Funcion Solve, la funcion solve define si el laberinto tiene solucion o no y imprime el camino en caso de existir.
    if(Col_A < 29){  // Como la salida siempre esta en la columan 29, mientras mi columna actual sea menor a 29 no se termina.
        if(Col_A+1 <= 29 &&  tab[fil_A][Col_A+1] == 0 && tab[fil_A][Col_A+1] != 9 && tab[fil_A][Col_A+1] != 8){ // Mover a la derecha.
            tab[fil_A][Col_A] = 9;  // Coloco un nueve que significa que me pude mover
            Solve = solve(tab, fil_A, Col_A+1,Solve); // Llamo nuevamente a la funcion pero con la nueva posicion.
        }
        if(fil_A+1 <= 29 && tab[fil_A+1][Col_A] == 0 && tab[fil_A+1][Col_A] != 9 && tab[fil_A+1][Col_A] != 8){ // Mover abajo
            tab[fil_A][Col_A] = 9;  // Coloco un nueve que significa que me pude mover
            Solve = solve(tab, fil_A+1, Col_A,Solve); // Llamo nuevamente a la funcion pero con la nueva posicion.
        }
        if(Col_A-1 <= 0 && tab[fil_A][Col_A-1] == 0 && tab[fil_A][Col_A-1] != 9 && tab[fil_A][Col_A-1] != 8){ // Mover a la izquierda
            tab[fil_A][Col_A] = 9;  // Coloco un nueve que significa que me pude mover
            Solve = solve(tab, fil_A, Col_A-1,Solve);// Llamo nuevamente a la funcion pero con la nueva posicion.
        }
        if(fil_A-1 >= 0 &&tab[fil_A-1][Col_A] == 0 && tab[fil_A-1][Col_A] != 9 && tab[fil_A-1][Col_A] != 8){ // Mover a la arriba
            tab[fil_A][Col_A] = 9;  // Coloco un nueve que significa que me pude mover
            Solve = solve(tab, fil_A-1, Col_A,Solve); // Llamo nuevamente a la funcion pero con la nueva posicion.
        }
        tab[fil_A][Col_A] = 8;  // Si ninguna de las anteriores preguntas con verdad, significa que estoy en algun callejon o un lugar por donde ya he pasado, por tanto me devuelvo y coloco una señal antes de hacerlo
    }else{  // Si existe solucion entonces hago las siguientes instruciones.
        printf("\n\n");  // Imprimo varios saltos de linea para que no quede pegado
        imprimir(tab);   // Llamo a la funcion imprimir
        return 1;        // Retorno un 1, significa que encontre solucion
    }
    return Solve;    //Como funcion en general necesito retornar Solve.
}  // Fin de la funcion Solve

void llenar(int tab[30][30]){  // Funcion para llenar de forma aleatoria, para crear el laberinto.
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

    tab[0][0] = 0;
    tab[0][1] = 0;
    tab[1][0] = 0;  // Entrada del laberinto.
    tab[1][1] = 0;

    rand1 = (rand() % 25) + 2;     
    tab[rand1][29] = 0;  // Creo la salida del laberinto aleatoria
} // Fin de la funcion llenar


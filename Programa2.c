/*
    Ing(c) Jhoan Esteban Raigoza Agudelo
    Universidad Tecnologica de Pereira
    Proferos Phd Ricardo Moreno Laverde.
    Fehca de creacion : 02/10/2020 

*/
#include <stdio.h> // importo la libreria de entrada y salida.
#include <stdlib.h> // Importo esta libreria para poder hacer uso de la funcion srand()
#include <time.h>   // Importo esta libreria para poder hacer uso de la funcion time()

// Prototipos de las funciones utilizadas.
void Crear_valores(int arreglo[30][30][30]); //Prototipo de la funcion, la cual toma como parametros solamente el arreglo el cual llenaremos de valores.
int Revisar_punto(int arreglo[30][30][30], int x, int y, int z); // prototipo de la funcion, toma como valores el arreglo al cual revisaremos el punto, y las cordenadas en x y z del punto a evaluar.
int Revisar_imagen(int arreglo[30][30][30]); // protopipo de la funcion, solo toma como parametro el arreglo

int main() // funcion main
{
    int Libro[30][30][30];  // Arreglo el cual utilizaremos para la resonancia 
    Crear_valores(Libro);   // llamo a la funcion Crear_valores y le paso la matriz como parametro
    int plano_mas_lineas = Revisar_imagen(Libro);  // Creo una variable y le doy el valor que retorne la funcion Revisas_imagen
    if(plano_mas_lineas == 0) // Si el contenido de la variable es 0 significa que no existen lineas en ninguna parte del arreglo
        printf("No existe plano con lineas");
    else{                     // Si es diferente de 0, ese valor es el plano con mas lineas.
        printf("\nEl plano con mas lineas es el %i\n", plano_mas_lineas);  
        for(int i = 0; i < 30; i++){        
            for(int j = 0; j < 30; j++)  // Con estas instrucciones muestro la imagen con mas linea.
                printf("%i,", Libro[plano_mas_lineas][i][j]);
            printf("\n");
        }
    }
    return 0;
} // fin de la funcion main.

int Revisar_imagen(int arreglo[30][30][30])  // La funcion revisar imagenes, revisa todas las hojas buscando lineas y las hojas con mas lineas 
{                                            // al final retorna un 0 si no existen lineas en ninguna parte del arreglo y si existen lineas retorna el plano con mas lineas.
    int tamaño_linea_actual = 0;  // guardo el tamaño de la lineas que voy encontrando en esta variable
    int lineas_actuales = 0;      // el numero de lineas por plano
    int plano_mas_lineas = 0;     // guardo el numero de lineas del plano que mas tenga lineas 
    int plano = 0;                // Guardo el plano que tenga mas lineas

    for(int hoja = 0;hoja < 30; hoja++){    // Recorro cada "hoja" del arreglo.
        for(int fila = 0; fila < 30; fila++)
            for(int columna = 0; columna < 30; columna++){
                if(Revisar_punto(arreglo, columna, fila, hoja) == 1){   // Buscando puntos sospechosos.
                    tamaño_linea_actual++;
                }
                else if(tamaño_linea_actual >= 3){  // Si son mas de 3 consecutivos.
                    lineas_actuales++;
                    tamaño_linea_actual = 0;
                }
            }
        if(lineas_actuales > plano_mas_lineas){ // al terminar la hoja pregunta si las lineas de esta hojas son mayores a la de la hoja con mas lineas que llevamos.
            plano_mas_lineas = lineas_actuales; 
            lineas_actuales = 0;
            plano = hoja;
        }
    }
    return plano;  // retorno el plano con las lineas.
} // fin de la funcion Revisar_imagen();


int Revisar_punto(int arreglo[30][30][30], int x, int y, int z)  // Funcion para revisar puntos sospechos, retorno 1 si el punto es sospechoso y retorno un 0 en caso contrario.
{
    if(z != 0 && z != 29 && y != 0 && y != 29 && x != 0 && x != 29){  // condicion para saber si el punto esta en la periferia. 
        if(arreglo[z][y][x] >= 20 && arreglo[z][y][x] <= 40 && // punto central de la pagina del z 
           arreglo[z][y][x+1] >= 20 && arreglo[z][y][x+1] <= 40 && // punto de la derecha de la pagina z
           arreglo[z][y][x-1] >= 20 && arreglo[z][y][x-1] <= 40 && // punto de la izquierda de la pagina z
           arreglo[z][y+1][x] >= 20 && arreglo[z][y+1][x] <= 40 && // punto de abajo de la pagina z
           arreglo[z][y-1][x] >= 20 && arreglo[z][y-1][x] <= 40 && // punto de arriba de la pagina z
           arreglo[z][y-1][x+1] >= 20 && arreglo[z][y-1][x+1] <= 40 && // punto de la diagonal superior derecha de la pagina z
           arreglo[z][y+1][x+1] >= 20 && arreglo[z][y+1][x+1] <= 40 && // punto de la diagonal inferior derecha de la pagina z
           arreglo[z][y-1][x-1] >= 20 && arreglo[z][y-1][x-1] <= 40 && // punto de la diagonal superior izquierda de la pagina z
           arreglo[z][y+1][x-1] >= 20 && arreglo[z][y+1][x-1] <= 40 && // punto de la diagonal inferior izquierda de la pagina z
           // pagina z+1
           arreglo[z+1][y][x] >= 20 && arreglo[z+1][y][x] <= 40 && // punto central de la pagina del z+1
           arreglo[z+1][y][x+1] >= 20 && arreglo[z+1][y][x+1] <= 40 && // punto de la derecha de la pagina z+1
           arreglo[z+1][y][x-1] >= 20 && arreglo[z+1][y][x-1] <= 40 && // punto de la izquierda de la pagina z+1
           arreglo[z+1][y+1][x] >= 20 && arreglo[z+1][y+1][x] <= 40 && // punto de abajo de la pagina z+1
           arreglo[z+1][y-1][x] >= 20 && arreglo[z+1][y-1][x] <= 40 && // punto de arriba de la pagina z+1
           arreglo[z+1][y-1][x+1] >= 20 && arreglo[z+1][y-1][x+1] <= 40 && // punto de la diagonal superior derecha de la pagina z+1
           arreglo[z+1][y+1][x+1] >= 20 && arreglo[z+1][y+1][x+1] <= 40 && // punto de la diagonal inferior derecha de la pagina z+1
           arreglo[z+1][y-1][x-1] >= 20 && arreglo[z+1][y-1][x-1] <= 40 && // punto de la diagonal superior izquierda de la pagina z+1
           arreglo[z+1][y+1][x-1] >= 20 && arreglo[z+1][y+1][x-1] <= 40 && // punto de la diagonal inferior izquierda de la pagina z+1
           // pagina z-1
           arreglo[z-1][y][x] >= 20 && arreglo[z-1][y][x] <= 40 && // punto central de la pagina del z-1 
           arreglo[z-1][y][x+1] >= 20 && arreglo[z-1][y][x+1] <= 40 && // punto de la derecha de la pagina z-1
           arreglo[z-1][y][x-1] >= 20 && arreglo[z-1][y][x-1] <= 40 && // punto de la izquierda de la pagina z-1
           arreglo[z-1][y+1][x] >= 20 && arreglo[z-1][y+1][x] <= 40 && // punto de abajo de la pagina z-1
           arreglo[z-1][y-1][x] >= 20 && arreglo[z-1][y-1][x] <= 40 && // punto de arriba de la pagina z-1
           arreglo[z-1][y-1][x+1] >= 20 && arreglo[z-1][y-1][x+1] <= 40 && // punto de la diagonal superior derecha de la pagina z-1
           arreglo[z-1][y+1][x+1] >= 20 && arreglo[z-1][y+1][x+1] <= 40 && // punto de la diagonal inferior derecha de la pagina z-1
           arreglo[z-1][y-1][x-1] >= 20 && arreglo[z-1][y-1][x-1] <= 40 && // punto de la diagonal superior izquierda de la pagina z-1
           arreglo[z-1][y+1][x-1] >= 20 && arreglo[z-1][y+1][x-1] <= 40    // punto de la diagonal inferior izquierda de la pagina z
           ) // fin de la conficion - es una unica condicion evaluando si alguno de esos puntos no esta en ese rango.
            return 1;
        else
            return 0;
    }else
        return 0;
} // fin de la funcion Revisar_punto();

void Crear_valores(int arreglo[30][30][30])
{
    srand(time(0));   // Cambio la semilla con la funcion time() que siempre sera un valor diferente por tanto valores aleatorios.
    for(int hoja_A = 0; hoja_A < 30; hoja_A++)
        for(int fila = 0; fila < 30; fila++)
            for(int columna = 0; columna < 30; columna++){
                arreglo[hoja_A][fila][columna] = rand() % 256; // pongo de manera aleatoria valores de 0 a 256 en los elementos del arreglo.
            }
}  // Fin de la funcion Crear_valores();
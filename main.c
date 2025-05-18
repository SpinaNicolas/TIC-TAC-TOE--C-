#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

/// prototipados

void inicializarTablero(char tateti[3][3]);
void mostrarTablero(char tateti[3][3]);
void cargarTableroJ1(char tateti [3][3]);
void cargarTableroJ2(char tateti [3][3]);
int validaFilaYColumna (int *dato);
int checkTerminaJuegoj1 (char tateti[3][3]);
int checkTerminaJuegoj2 (char tateti[3][3]);


int main()
{
    char tateti[3][3];
    inicializarTablero(tateti);
    mostrarTablero(tateti);
    int fin = 0;
    //int jugador1 = 0;
    //int jugador2 = 0;
    int contador = 0;

    while(fin == 0)
    {
        if(fin ==0)
        {
            printf("\t \t JUGADOR NR 1 \n \n");
            cargarTableroJ1(tateti);
            fin = checkTerminaJuegoj1(tateti);

            mostrarTablero(tateti);
        }
        if (fin == 0)
        {
            printf("\t \t JUGADOR NR 2 \n \n");
            cargarTableroJ2(tateti);
            fin = checkTerminaJuegoj2(tateti);

            mostrarTablero(tateti);
        }
        contador++;

    }


    if(fin == 1)
    {
        printf("\n \t \t ******GANO EL JUGADOR 1******");
    }
    else
    {
        printf("\n \t \t ******GANO EL JUGADOR 2******");
    }
}


void inicializarTablero(char tateti[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tateti[i][j] = ' ';
}

void mostrarTablero(char tateti[3][3])
{
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" %c ", tateti[i][j]);
            if (j < 3 - 1) printf("|");
        }
        printf("\n");
        if (i < 3 - 1) printf("---+---+---\n");
    }
    printf("\n");
}

void cargarTableroJ1(char tateti [3][3]) /// carga el tablero validando los datos
{
    int fila = 0;
    int colu = 0;
    int flag ;
    int fin = 1;

    while (fin == 1)
    {
        flag = 0;

        do
        {
            printf("\n J1 ingrese (x) en la para  fila (0-2): ");
            fflush(stdin);
            scanf("%d",&fila);

            flag = validaFilaYColumna(&fila);
            if (flag != 1)
            {
                printf("ERROR ingrese una fila entre 0-2 \n");
            }

        }
        while(flag != 1);  ///validaFilaYColumna devuelve 1 si el dato fue ingresado correctamente

        do
        {
            printf("\n y columna (0-2): ");
            fflush(stdin);
            scanf("%d",&colu);
            flag = validaFilaYColumna(&colu);
            if (flag != 1)
            {
                printf("ERROR ingrese una fila entre 0-2 \n");
            }

        }
        while(flag != 1); ///validaFilaYColumna devuelve 1 si el dato fue ingresado correctamente

        if(tateti[fila][colu] != ' ')
        {
            printf("lugar ocupado , intenta con otro \n ");

        }
        else
        {
            fin = 0;
        }
    }

    tateti[fila][colu] = 'X';

}

void cargarTableroJ2(char tateti [3][3]) /// carga el tablero validando los datos
{
    int fila = 0;
    int colu = 0;
    int flag ;
    int fin = 1;

    while (fin == 1)
    {
        flag = 0;

        do
        {
            printf("\n J1 ingrese (O) en la para  fila (0-2): ");
            fflush(stdin);
            scanf("%d",&fila);
            flag = validaFilaYColumna(&fila);
            if (flag != 1)
            {
                printf("ERROR ingrese una fila entre 0-2 \n");
            }

        }
        while(flag != 1);  ///validaFilaYColumna devuelve 1 si el dato fue ingresado correctamente

        do
        {
            printf("\n y columna (0-2): ");
            fflush(stdin);
            scanf("%d",&colu);
            flag = validaFilaYColumna(&colu);
            if (flag != 1)
            {
                printf("ERROR ingrese una fila entre 0-2 \n");
            }

        }
        while(flag != 1); ///validaFilaYColumna devuelve 1 si el dato fue ingresado correctamente

        if(tateti[fila][colu] != ' ')
        {
            printf("lugar ocupado , intenta con otro \n ");

        }
        else
        {
            fin = 0;
        }
    }

    tateti[fila][colu] = 'O';

}

int validaFilaYColumna (int *dato) /// valida que el dato de la fila o columna este entre 1 y 3
{
    int flag = 0 ;
    if(*dato < 3 && *dato >= 0)
    {
        flag = 1;
    }
    return flag;
}

int checkTerminaJuegoj1 (char tateti[3][3])
{

    int fin = 0 ;

    for(int filas = 0 ; filas < 3 ; filas++)
    {
        ///chequea fila x fila a ver si hay 3 en linea
        if( ( tateti[filas][0]!= ' ') &&(tateti[filas][0]==tateti[filas][1]) && (tateti[filas][0]==tateti[filas][2]) )
        {
            fin = 1;
        }
    }

    for(int colu = 0 ; colu < 3 ; colu++)
    {
        ///chequea columna x columna a ver si hay 3 en linea
        if( ( tateti[0][colu]!= ' ') &&(tateti[0][colu]==tateti[1][colu]) && (tateti[0][colu]==tateti[2][colu]) )
        {
            fin = 1;
        }
    }



    ///chequea la diagonal principal a ver si hay 3 en linea
    if( ( tateti[0][0]!= ' ') &&(tateti[0][0]==tateti[1][1]) && (tateti[0][0]==tateti[2][2]) )
    {
        fin = 1;

    }


    ///chequea la diagonal secundaria a ver si hay 3 en linea
    if( ( tateti[0][2]!= ' ') &&(tateti[0][2]==tateti[1][1]) && (tateti[0][2]==tateti[2][0]) )
    {
        fin = 1;

    }

    return fin;

}

int checkTerminaJuegoj2 (char tateti[3][3])
{

    int fin = 0 ;

    for(int filas = 0 ; filas < 3 ; filas++)
    {
        ///chequea fila x fila a ver si hay 3 en linea
        if( ( tateti[filas][0]!= ' ') &&(tateti[filas][0]==tateti[filas][1]) && (tateti[filas][0]==tateti[filas][2]) )
        {
            fin = 'o';
        }
    }

    for(int colu = 0 ; colu < 3 ; colu++)
    {
        ///chequea columna x columna a ver si hay 3 en linea
        if( ( tateti[0][colu]!= ' ') &&(tateti[0][colu]==tateti[1][colu]) && (tateti[0][colu]==tateti[2][colu]) )
        {
            fin = 2;
        }
    }



    ///chequea la diagonal principal a ver si hay 3 en linea
    if( ( tateti[0][0]!= ' ') &&(tateti[0][0]==tateti[1][1]) && (tateti[0][0]==tateti[2][2]) )
    {
        fin = 2;

    }


    ///chequea la diagonal secundaria a ver si hay 3 en linea
    if( ( tateti[0][2]!= ' ') &&(tateti[0][2]==tateti[1][1]) && (tateti[0][2]==tateti[2][0]) )
    {
        fin = 2;

    }

    return fin;

}

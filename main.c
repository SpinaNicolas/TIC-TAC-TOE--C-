

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define jugadores_ar "jugadores.dat"
#define partidas_ar "partidas.dat"
#define partiXjugadores_ar "partidaXjugador.dat"

typedef struct {
    int idJugador;
    char nombre[30];
    char apellido[30];
    char email[50];
    char username[30];
    char password[20];
    char dni[10];
    int ptsTotales;
    int eliminado; // 0 = activo, 1 = eliminado
} stJugador;

typedef struct {
    int idPartida;
    int dificultad;
    int esContraCpu;
} stPartida;

typedef struct {
    int idPartidaJugador;
    int idPartida;
    int idJugador;
    int resultado;
    int puntosJugador;
} stPartidaXJugador;

// Prototipados
void inicializarTablero(char tateti[3][3]);
void mostrarTablero(char tateti[3][3]);
void cargarTablero(char tateti[3][3], char simbolo, char nombre[]);
void cargarTableroPC(char tateti[3][3], char simbolo);
int validaFilaYColumna(int *dato);
int checkTerminaJuego(char tateti[3][3], char simbolo);
int menu();
void reglas();
void iniciarJuego(char tateti[3][3], int idJugador);
void cargaArchivoJugadores(char archivoJugadores[]);
void muestraArchivoJugadores(char archivoJugadores[]);
void muestraUnJugador(stJugador dato);
stJugador cargaUnJugador(char archivoJugadores[]);
stJugador iniciarSesion(char archivoJugadores[]);
void mostrarEstadisticas(char archivoJugadores[], char archivoPartidasXJugador[], int idJugador);
stJugador modificarUsername(char archivoJugadores[], stJugador jugador);
void eliminarJugador(char archivoJugadores[], stJugador jugador);
stJugador eleccionOpcionMenu(char tateti[3][3],int opcion, char archivoJugadores[], stJugador jugador);
stJugador menuUsuario(char tateti[3][3], stJugador jugador);
int ultIdArchivo(char archivoJugadores[]);
int validarEmail(char email[], char archivoJugadores[]);
int validarUsername(char username[], char archivoJugadores[]);
int validarPassword(char password[]);
int validarDNI(char dni[], char archivoJugadores[]);

int main() {

        char tateti[3][3];
    int opcion = 0;
    stJugador jugadorActual = {0};

    while (opcion != 5) {
        opcion = menu();
        jugadorActual = eleccionOpcionMenu(tateti, opcion, jugadores_ar, jugadorActual);
    }

    return 0;
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
            if (j < 2)
                printf("|");
        }
        printf("\n");
        if (i < 2)
            printf("---+---+---\n");
    }
    printf("\n");
}

void cargarTablero(char tateti[3][3], char simbolo, char nombre[])
{
    int fila = 0, colu = 0, flag;

    while (1)
    {
        do
        {
            printf("\n %s, ingrese (%c) en la fila (0-2): ", nombre, simbolo);
            if (scanf("%d", &fila) != 1)
            {
                printf("ERROR: Debe ingresar un número.\n");
                while(getchar() != '\n');
                continue;
            }
            flag = validaFilaYColumna(&fila);
            if (!flag)
                printf("ERROR: Ingrese una fila entre 0 y 2.\n");
        }
        while (!flag);

        do
        {
            printf("\nIngrese la columna (0-2): ");
            if (scanf("%d", &colu) != 1)
            {
                printf("ERROR: Debe ingresar un número.\n");
                while(getchar() != '\n');
                continue;
            }
            flag = validaFilaYColumna(&colu);
            if (!flag)
                printf("ERROR: Ingrese una columna  entre 0 y 2.\n");
        }
        while (!flag);

        if (tateti[fila][colu] != ' ')
            printf("Lugar ocupado, intenta con otra posición.\n");
        else
        {
            tateti[fila][colu] = simbolo;
            break;
        }
    }
}

void cargarTableroPC(char tateti[3][3], char simbolo)
{
    int fila, colu;
    while (1)
    {
        fila = rand() % 3;
        colu = rand() % 3;
        if (tateti[fila][colu] == ' ')
        {
            tateti[fila][colu] = simbolo;
            printf("La PC pone %c en fila %d, columna %d \n", simbolo, fila, colu);
            break;
        }
    }
}

int validaFilaYColumna(int *dato)
{
    return ((*dato) >= 0 && (*dato) < 3) ? 1 : 0;
}

int checkTerminaJuego(char tateti[3][3], char simbolo)
{
    for (int i = 0; i < 3; i++)
    {
        if (tateti[i][0] == simbolo && tateti[i][1] == simbolo && tateti[i][2] == simbolo)
            return 1;
        if (tateti[0][i] == simbolo && tateti[1][i] == simbolo && tateti[2][i] == simbolo)
            return 1;
    }

    if (tateti[0][0] == simbolo && tateti[1][1] == simbolo && tateti[2][2] == simbolo)
        return 1;
    if (tateti[0][2] == simbolo && tateti[1][1] == simbolo && tateti[2][0] == simbolo)
        return 1;

    return 0;
}

int menu()
{
    int opcion;

    printf("\t\t\t||======================================||\n");
    printf("\t\t\t||             Bienvenidos!             ||\n");
    printf("\t\t\t||         Tateti Los Argento           ||\n");
    printf("\t\t\t||======================================||\n");
    printf("\t\t\t||      1. Iniciar sesion               ||\n");
    printf("\t\t\t||      2. Registrarse (nuevo jugador)  ||\n");
    printf("\t\t\t||      3. Jugar                        ||\n");
    printf("\t\t\t||      4. Ver Reglas                   ||\n");
    printf("\t\t\t||      5. Salir                        ||\n");
    printf("\t\t\t||======================================||\n");
    do
    {
        printf("\n\nSeleccione una opcion (1-5): ");
        scanf("%d", &opcion);
fflush(stdin);

    }
    while (opcion < 1 || opcion >5);
    return opcion;
}

stJugador eleccionOpcionMenu(char tateti[3][3],int opcion, char archivoJugadores[], stJugador jugador) {
    switch (opcion) {
        case 1:
            jugador = iniciarSesion(archivoJugadores);
            if (jugador.idJugador != 0) {
                jugador = menuUsuario(tateti, jugador);
            }
            break;
        case 2:
            cargaArchivoJugadores(archivoJugadores);
            muestraArchivoJugadores(archivoJugadores);
            break;
        case 3:
            iniciarJuego(tateti,0);
            break;
        case 4:
            reglas();
            break;
        case 5:
        printf("Saliendo... presione una tecla y la consola se cerrara. \n");
            break;
    }
    return jugador;
}

stJugador iniciarSesion(char archivoJugadores[]) {
    FILE *archi = fopen(archivoJugadores, "rb");
    stJugador aux, jugador = {0};
    char email[50], password[20];

    if (!archi) {
        printf("\nError al abrir el archivo de jugadores.\n");
        return jugador;
    }

    printf("\nIngrese su email: ");
    fflush(stdin);
    gets(email);
    printf("Ingrese su contrasena: ");
    fflush(stdin);
    gets(password);

    while (fread(&aux, sizeof(stJugador), 1, archi) > 0) {
        if (strcmp(aux.email, email) == 0 && strcmp(aux.password, password) == 0 && aux.eliminado == 0) {
            jugador = aux;
            break;
        }
    }
    fclose(archi);

    if (jugador.idJugador == 0) {
        printf("\n Email o contrasena incorrectas o cuenta eliminada.\n");
    } else {
        printf("\n Bienvenido, %s!\n", jugador.nombre);
    }

    return jugador;
}

stJugador menuUsuario(char tateti[3][3], stJugador jugador) {
    int opcion;

    do {
    printf("\t\t\t||======================================||\n");
    printf("\t\t\t||             Bienvenido!              ||\n");
    printf("\t\t\t||      Menu de usuario (%s)            ||\n", jugador.username);
    printf("\t\t\t||======================================||\n");
    printf("\t\t\t||      1. Ver perfil                   ||\n");
    printf("\t\t\t||      2. Modificar username           ||\n");
    printf("\t\t\t||      3. Jugar                        ||\n");
    printf("\t\t\t||      4. Ver estadisticas             ||\n");
    printf("\t\t\t||      5. Eliminar cuenta              ||\n");
    printf("\t\t\t||      6. Cerrar sesion                ||\n");
    printf("\t\t\t||======================================||\n");
    printf("\nSeleccione una opcion (1-6): ");
        scanf("%d", &opcion);
fflush(stdin);
        switch (opcion) {
            case 1:
                muestraUnJugador(jugador);
                break;
            case 2:
                jugador = modificarUsername(jugadores_ar, jugador);
                break;
            case 3:
                iniciarJuego(tateti,jugador.idJugador);
                break;
            case 4:
                mostrarEstadisticas(jugadores_ar, partiXjugadores_ar, jugador.idJugador);
                break;
            case 5:
                eliminarJugador(jugadores_ar, jugador);
                jugador.idJugador = 0;
                break;
            case 6:
                printf("\nCerrando sesión...\n");
                break;
            default:
                printf("\n opcion no valida, ingrese nuevamente opcion\n");
        }
    } while (opcion != 6 && jugador.idJugador != 0);

    return jugador;
}

stJugador modificarUsername(char archivoJugadores[], stJugador jugador) {
    FILE *archi = fopen(archivoJugadores, "rb+");
    stJugador aux;

    if (!archi) {
        printf("\nError al abrir el archivo de jugadores.\n");
        return jugador;
    }

    printf("\nIngrese su nuevo username: ");
    fflush(stdin);
    gets(jugador.username);

    while (fread(&aux, sizeof(stJugador), 1, archi) > 0) {
        if (aux.idJugador == jugador.idJugador) {
            strcpy(aux.username, jugador.username);
            fseek(archi, -sizeof(stJugador), SEEK_CUR);
            fwrite(&aux, sizeof(stJugador), 1, archi);
            printf("\nUsername actualizado correctamente.\n");
            break;
        }
    }
    fclose(archi);
    return jugador;
}

void mostrarEstadisticas(char archivoJugadores[], char archivoPartidasXJugador[], int idJugador) {
    FILE *archi = fopen(archivoPartidasXJugador, "rb");
    stPartidaXJugador aux;
    int jugadas = 0, ganadas = 0, empates = 0, derrotas = 0;

    if (!archi) {
        printf("\nError al abrir el archivo de estadísticas.\n");
        return;
    }

    while (fread(&aux, sizeof(stPartidaXJugador), 1, archi) > 0) {
        if (aux.idJugador == idJugador) {
            jugadas++;
            if (aux.resultado == 1) ganadas++;
            else if (aux.resultado == 2) empates++;
            else derrotas++;
        }
    }

    fclose(archi);

    printf("\n=== Estadísticas del Jugador ===\n");
    printf("Partidas jugadas: %d\n", jugadas);
    printf("Ganadas: %d\n", ganadas);
    printf("Empates: %d\n", empates);
    printf("Derrotas: %d\n", derrotas);
    float porcentajeV;
    float porcentajeD;
    float porcentajeE;
    porcentajeV= (ganadas*100)/jugadas;
    porcentajeD= (derrotas*100)/jugadas;
    porcentajeE= (empates*100)/jugadas;
    printf("Porcentaje de victorias: %.2f%%\n", porcentajeV);
    printf("Porcentaje de derrotas: %.2f%%\n", porcentajeD);
    printf("Porcentaje de empates: %.2f%%\n", porcentajeE);
}

void eliminarJugador(char archivoJugadores[], stJugador jugador) {
    FILE *archi = fopen(archivoJugadores, "rb+");
    stJugador aux;

    if (!archi) {
        printf("\nError al abrir el archivo de jugadores.\n");
        return;
    }

    while (fread(&aux, sizeof(stJugador), 1, archi) > 0) {
        if (aux.idJugador == jugador.idJugador) {
            aux.eliminado = 1;
            fseek(archi, -sizeof(stJugador), SEEK_CUR);
            fwrite(&aux, sizeof(stJugador), 1, archi);
            printf("\nCuenta eliminada correctamente.\n");
            break;
        }
    }
    fclose(archi);
}

void reglas()
{
    printf("\t\t||===============================================||\n");
    printf("\t\t||              Tateti Los Argento               ||\n");
    printf("\t\t||===============================================||\n");
    printf("\t\t||  1. Tablero: 3x3                              ||\n");
    printf("\t\t||  2. Jugadores: X y O                          ||\n");
    printf("\t\t||  3. Turnos: Los jugadores se alternan         ||\n");
    printf("\t\t||  4. Objetivo: Colocar tres marcas en linea    ||\n");
    printf("\t\t||  5. Empate: Si se llena el tablero sin ganar  ||\n");
    printf("\t\t||===============================================||\n");
}
void iniciarJuego(char tateti[3][3], int idJugador) {
    char continuar = 's';
    int modo = 0;
    srand(time(NULL));

    while (continuar == 's' || continuar == 'S') {
        modo = modoJuego();

        char jugador1[50] = "Jugador 1";
        char jugador2[50] = "Jugador 2";

        if (idJugador == 0) {
            printf("Jugador 1 ingrese su nombre: \n");
            fflush(stdin);
            gets(jugador1);
        } else {
            // Podés recuperar nombre desde el struct usando idJugador si querés
            strcpy(jugador1, "Usuario Logueado");
        }

        if (modo == 1) {
            if (idJugador == 0) {
                printf("Jugador 2 ingrese su nombre: \n");
                gets(jugador2);
            } else {
                strcpy(jugador2, "Jugador 2");
            }
        } else {
            strcpy(jugador2, "PC");
        }

        inicializarTablero(tateti);
        system("cls");
        mostrarTablero(tateti);

        int fin = 0, contador = 0, turno = 1;

        while (fin == 0 && contador < 9) {
            if (turno == 1) {
                printf("\n\t\tTURNO - %s (X)\n\n", jugador1);
                cargarTablero(tateti, 'X', jugador1);
                if (checkTerminaJuego(tateti, 'X')) fin = 1;
            } else {
                printf("\n\t\tTURNO - %s (O)\n\n", jugador2);
                if (modo == 1)
                    cargarTablero(tateti, 'O', jugador2);
                else
                    cargarTableroPC(tateti, 'O');
                if (checkTerminaJuego(tateti, 'O')) fin = 2;
            }

            contador++;
            mostrarTablero(tateti);
            turno = (turno == 1) ? 2 : 1;
        }

        if (fin == 1) {
            printf("\n\t****** GANA %s ******\n", jugador1);
            // Si hay sesión, guardar estadística
        } else if (fin == 2) {
            printf("\n\t****** GANA %s ******\n", jugador2);
        } else {
            printf("\n\t****** EMPATE ******\n");
        }

        if (idJugador > 0) {
            printf("\n(Estadística registrada para el jugador con ID %d)\n", idJugador);
            // guardarResultado(idJugador, fin);
        }

        printf("\n\tPresiona 's' para jugar otra vez o cualquier otra tecla para salir: ");
        while(getchar() != '\n');
        scanf("%c", &continuar);
    }
}

int modoJuego()
{
    int modo;
    system("cls");
    printf("Seleccione el modo de juego:\n");
    printf("1. Jugador vs Jugador\n");
    printf("2. Jugador vs PC\n");
    do
    {
        printf("Elija (1 o 2): ");
        scanf("%d", &modo);
    }
    while (modo != 1 && modo != 2);

    return modo;
}

stJugador cargaUnJugador (char archivoJugadores[])
{
    stJugador dato;
    printf("\n ingrese su nombre: ");
    gets(dato.nombre);

    printf("\n ingrese su apellido: ");
    gets(dato.apellido);


    do
    {
        printf("\n ingresa su Email: ");
        fflush(stdin);
        gets(dato.email);
    }
    while(validarEmail(dato.email,archivoJugadores) != 0);

    do
    {
        printf("\n ingrese su username ");
        fflush(stdin);
        gets(dato.username);
    }
    while(validarUsername(dato.username,archivoJugadores)== 0);

    do
    {
        printf("\n ingrese su password (1mayuscula y 1 minuscula minimo): ");
        fflush(stdin);
        gets(dato.password);
    }
    while(validarPassword(dato.password)!= 2);

    do
    {
        printf("ingrese su DNI: ");
        scanf("%s",dato.dni);
    }
    while(validarDNI(dato.dni,archivoJugadores) != 1);

    dato.idJugador = ultIdArchivo (archivoJugadores);
    dato.ptsTotales = 0;  // inicializa puntos en 0
    dato.eliminado = 0;  // usuario activo. 1=eliminado


    return dato;
}

void cargaArchivoJugadores(char archivoJugadores[])
{
    FILE *archi = fopen(archivoJugadores,"ab");
    stJugador aux;
    char continuar = 's';
    /**
    printf("\n si quiere ingresar un jugador nuevo ingrese 's': ");
    scanf("%c",&continuar);
    */
    while(continuar=='s')
    {

        if(archi)
        {
            aux = cargaUnJugador(archivoJugadores);
            aux.idJugador = ultIdArchivo(archivoJugadores);
            fwrite(&aux,sizeof(stJugador),1,archi);

            printf("\n s para seguir ingresando jugadores: ");
            fflush(stdin);
            scanf("%c",&continuar);
            fflush(stdin);

        }
        fclose(archi);
    }

}

void muestraUnJugador (stJugador dato)
{

    printf("----------------------\n ");
    printf("\n nombre: %s",dato.nombre);
    printf("\n apellido: %s",dato.apellido);
    printf("\n email: %s ",dato.email);
    printf("\n username: %s",dato.username);
    printf("\n DNI: %s",dato.dni);
    printf("\n ID: %d",dato.idJugador);
    /**
    printf("\n puntos totales: %d",dato.ptsTotales);
    printf("\n estado: %d",dato.eliminado);
    */
    printf("\n----------------------\n ");
}

void muestraArchivoJugadores(char archivoJugadores [])
{
    stJugador dato;
    FILE *archi = fopen(archivoJugadores,"rb");
    if(archi)
    {
        while(fread(&dato,sizeof(stJugador),1,archi)>0)
        {
            muestraUnJugador(dato);
        }
        fclose(archi);
    }
}

int validarDNI(char dni[],char archivoJugadores[]) /// valida dni no repetido
{

    FILE *archi = fopen(archivoJugadores,"rb");
    stJugador aux;
    int flag = 1;
    if(archi != NULL)
    {
        while(fread(&aux,sizeof(stJugador),1,archi)>0)
        {
            if(strcmp(aux.dni, dni) == 0)  /// si se repite el DNI devuelve 0 , ERROR
            {
                flag = 0;
            }
        }
        fclose(archi);
    }
    return flag;
}

int validarPassword(char password[])     /// esta no sabia hacerla ,tube que buscarla , preguntar que onda
{
    int tieneMayus = 0;                        /// No sabia como buscar las mayusculas y minusculas
    int tieneMinus = 0;

    for (int i = 0; password[i] != '\0'; i++)   /// busca pos X pos MAYUSCULAS y minusculas
    {
        if (isupper(password[i]))
        {
            tieneMayus = 1;
        }
        if (islower(password[i]))
        {
            tieneMinus = 1;
        }
    }
    int resultado = 0;
    resultado = tieneMayus + tieneMinus ;

    return resultado;
}

int validarUsername(char username[], char archivoJugadores[])   ///valida username no repetido en jugadores activos
{
    FILE* archi = fopen(archivoJugadores, "rb");
    int flag = 1;
    if (archi != NULL)
    {
        stJugador aux;
        while (fread(&aux, sizeof(stJugador), 1, archi) > 0)                ///recorre archivo
        {
            if (strcmp(aux.username, username) == 0 && aux.eliminado == 0)   ///strcmp compara strings
            {
                /// aux.eliminado == a activo
                flag = 0;  /// User ya en uso
            }
        }
        fclose(archi);
    }

    return flag;  /// user no repetido
}

int validarEmail(char email[], char archivoJugadores[]) /// valida email no repetido y si tiene @ y . desp del @
{

    int flag = 0;
    char *arroba = strchr(email, '@'); /// si hay arroba devuelve 1-//strchr devuelve puntero de la dircDeMemoria de donde esta @
    if (arroba != NULL && strchr(arroba, '.') != NULL)   /// si devolvio !NULL y tiene un . dsp de la @ entra al if
    {
        flag++; // válido
    }

    FILE* archi = fopen(archivoJugadores, "rb");

    if (archi != NULL)
    {
        stJugador aux;
        while (fread(&aux, sizeof(stJugador),1, archi) > 0)
        {
            if (strcmp(aux.email, email) == 0 && aux.eliminado == 0)
            {
                fclose(archi);
                flag++;
            }
        }
        fclose(archi);
    }
    flag--; /// valido las 2 , resto 1 para devolver 1 si es valido o distinto a 1 si es invalido
    return flag; /// si flag vale 1 , se validaron las dos condiciones , sino invalido
}

int ultIdArchivo(char archivoJugadores[])///busca en el archivo el ultimo id registrado, si no hay registros previos asigna 1 al primer jugador
{
    int cant;
    int id;
    stJugador aux;
    FILE *archi =fopen(archivoJugadores,"rb");
    if (archi)
    {
        fseek(archi,0,SEEK_END); /// envio el indicador de posicion al final del achivo
        cant =ftell(archi)/sizeof(stJugador);
        if (cant>0) //el archivo tiene datos
        {
            fseek(archi,(-1)*sizeof(stJugador),SEEK_END); ///pongo el cursor en la posicion de la ultima partida registrada y leo el id
            fread(&aux,sizeof(stJugador),1,archi); ///leo el utlimo jugador cargado
            id = aux.idJugador + 1; //como el id es autoincremental, le sumo 1
        }
        else //el archivo esta vacio
        {
            id = 1; //primer idjugador si el archivo esta vacio
        }
        fclose(archi);
    }
    return id;
}



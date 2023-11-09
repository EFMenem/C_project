#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include "cocineritos.h"
#include "chambuchito.h"

//Personajes en archivo juego.
const char REUBEN_JUEGO = 'R';
const char STITCH_JUEGO = 'S';

//Valores del juego.
const int GANASTE_JUEGO = 1;
const int PERDISTE_JUEGO = -1;
const int SEGUIR_JUEGO = 0;
const int MOVIMIENTO_FUEGO = 15;

// PRE: todos los campos de la estructura juego deben estar inicializados.
// POST: imprime el menu de acciones y cuantos movimientos faltan para que aparezca el fuego.
void imprimir_acciones (juego_t juego) {
    int contador = MOVIMIENTO_FUEGO;
    int hasta_fuego = contador - juego.movimientos;
    if (juego.personaje_activo == STITCH_JUEGO) {
        printf("Estas usando a Stitch. \n -W (arriba)\n -S (abajo)\n -A (izquierda)\n -D (derecha)\n -X (cambiar personaje)\n -Ingrese un movimiento : \n");
        printf("Faltan %i movimientos para que aparezca un fuego !!!!! \n", hasta_fuego);
    } else {
        printf("Estas usando a Reuben. \n -W (arriba)\n -S (abajo)\n -A (izquierda)\n -D (derecha)\n -X (cambiar personaje)\n -Ingrese un movimiento : \n");
        printf("Faltan %i movimientos para que aparezca un fuego !!!!! \n", hasta_fuego);
    }
}

int main (){
    juego_t juego;
    int precio = 0 ;
    char movimiento = ' ';
    
    srand((unsigned)time(NULL));  //esto crea la semilla
    printf("\n");
    printf("Comenzaras siendo Stitch. Todas las preguntas tienen que contestarse como se indican (unicamente con la inicial y en mayuscula).\n");
    printf("Te podes mover en 4 direcciones diferentes (Arriba: W, Abajo: S, Derecha: D, Izquierda: A)\n");
    printf("\n");
    printf("Para jugar tenes que cortar todos los ingredientes que aparezcan en el cuadrante superior y cocinar todos los ingredientes del cuadrante inferior, no vas a poder cortar aquellos que aparezcan en el cuadrante inferior y viceversa.\n");
    printf("Principalmente, te va a aparecer los ingredientes para la ensalada, y dependiendo del precio de tu chambuchito, tendras que hacer mas comidas. Estas apareceran una vez que todos los ingredientes esten, cortados o cocinados, en la puerta de salida. \n");
    printf("\n");
    printf("Para dejar o agarrar el ingrediente en la mesa (con una distancia = 1), apreta 'T'. Para agarrar o soltar el ingrediente, apreta 'R'. Para apagar el fuego (tenes que tener el matafuego en mano y una distancia <= 2) apreta 'M'.\n");
    printf("Mientras que haya un fuego en el terreno, unicamente vas poder soltar algun ingrediente que el personaje tenga en mano, moverte, cambiar de personaje y dejar algun ingrediente, que Reuben tenga en mano, en la salida.\n");
    printf("Si caes en un agujero, perdiste.\n");
    calcular_precio_chambuchito(&precio);
    inicializar_juego(&juego,precio);
    system("clear");
    while (estado_juego(juego)== SEGUIR_JUEGO) {

        imprimir_terreno(juego);
        imprimir_acciones(juego);
        scanf(" %c", &movimiento);
        realizar_jugada(&juego, movimiento);
        system("clear");
    }

    if (estado_juego(juego) == PERDISTE_JUEGO) {
        printf("  #######  ##     ##    ##    ##  #######  #### ####    ########  ######## ########  ########  ####  ######  ######## ######## #### #### \n \
##     ## ##     ##    ###   ## ##     ## #### ####    ##     ## ##       ##     ## ##     ##  ##  ##    ##    ##    ##       #### #### \n \
##     ## ##     ##    ####  ## ##     ## #### ####    ##     ## ##       ##     ## ##     ##  ##  ##          ##    ##       #### #### \n \
##     ## #########    ## ## ## ##     ##  ##   ##     ########  ######   ########  ##     ##  ##   ######     ##    ######    ##   ##  \n \
##     ## ##     ##    ##  #### ##     ##              ##        ##       ##   ##   ##     ##  ##        ##    ##    ##                 \n \
##     ## ##     ##    ##   ### ##     ## #### ####    ##        ##       ##    ##  ##     ##  ##  ##    ##    ##    ##       #### #### \n \
 #######  ##     ##    ##    ##  #######  #### ####    ##        ######## ##     ## ########  ####  ######     ##    ######## #### #### \n");
    } else if (estado_juego(juego) == GANASTE_JUEGO) {
        printf("\
  ######      ###    ##    ##    ###     ######  ######## ######## #### \n \
##    ##    ## ##   ###   ##   ## ##   ##    ##    ##    ##       #### \n \
##         ##   ##  ####  ##  ##   ##  ##          ##    ##       #### \n \
##   #### ##     ## ## ## ## ##     ##  ######     ##    ######    ##  \n \
##    ##  ######### ##  #### #########       ##    ##    ##            \n \
##    ##  ##     ## ##   ### ##     ## ##    ##    ##    ##       #### \n \
 ######   ##     ## ##    ## ##     ##  ######     ##    ######## #### \n");
    }

    return 0;
    
}

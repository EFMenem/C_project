#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cocineritos.h"
#include "chambuchito.h"

//Maximos de la matriz del terreno de juego.
#define MAX_FILAS 21
#define MAX_COLUMNAS 21
const int FILA_MEDIA = 10;
const int FILA_FINAL = 20;
const int FILA_INICIAL = 0;
const int COLUMNA_MEDIA = 10;
const int COLUMNA_FINAL = 20;
const int COLUMNA_INICIAL = 0;
#define FILA_LIMITE 19
#define UNA_FILA 1
#define COLUMNA_LIMITE 19

//Terreno matriz
const char PARED = '#';
const char VACIO = '-';
const int CUADRANTES = 2;

//EMOJIS
#define PARED_EMOJI "\U0001f9f1"
#define VACIO_EMOJI "\u2795"
#define FUEGO_EMOJI "\U0001f525"
#define AGUJERO_EMOJI "\U0001f573\uFE0F"
#define HORNO_EMOJI "\U0001f39b\uFE0F"
#define CUCHILLO_EMOJI "\U0001f52a"
#define SALIDA_EMOJI "\U0001f6aa"
#define MATAFUEGO_EMOJI "\U0001f9ef"
#define MESA_EMOJI "\U0001f37d\uFE0F"
#define LECHUGA_EMOJI "\U0001f96c"
#define TOMATE_EMOJI "\U0001f345"
#define JAMON_EMOJI "\U0001f416"
#define QUESO_EMOJI "\U0001f9c0"
#define MASA_EMOJI "\U0001f35e"
#define MILANESA_EMOJI "\U0001f969"
#define PAN_EMOJI "\U0001f956"
#define CARNE_EMOJI "\U0001f356"



//Obstáculos
#define MAX_FUEGO 1
#define MAX_AGUJEROS 20
const char FUEGO = 'F';
const char AGUJERO = 'A';
const int MOVIMIENTO_PARA_FUEGO = 15;
const int DISTANCIA_CORRECTA_AL_FUEGO = 2;

//Herramientas
const char MESA = '_';
const char HORNO = 'H';
const int MAX_HORNOS = 2;
const char CUCHILLO = 'C';
const char MATAFUEGO = 'M'; 
const int MAX_CUCHILLOS = 2;
const int MAX_MATAFUEGOS = 1;
const int DISTANCIA_A_MESA = 1;
const int DISTANCIA_A_HORNO = 1;
const char PUERTA_DE_SALIDA = 'P';

//Personajes
#define REUBEN 'R'
#define STITCH 'S'
#define REUBEN_EMOJI "\U0001f98f"
#define STITCH_EMOJI "\U0001f98d"

//Comidas y sus maximos de ingredientes.
const char PIZZA = 'P';
const char ENSALADA = 'E';
const char SANDWICH = 'S';
const char HAMBURGUESA = 'H';
const int PRECIO_HASTA_PIZZA = 100;
const int PRECIO_HASTA_HAMBURGUESA = 150;
#define INDICE_ENSALADA 0
#define INDICE_PIZZA 1
#define INDICE_SANDWICH 3
#define INDICE_HAMBURGUESA 2
#define MAX_INGREDIENTES_PIZZA 3
#define MAX_INGREDIENTES_SANDWICH 6
#define MAX_INGREDIENTES_ENSALADA 2
#define MAX_INGREDIENTES_HAMBURGUESA 4

//Ingredientes
const char MASA = 'O';
const char PAN = 'N';
const char CARNE = 'B';
const char JAMON = 'J';
const char QUESO = 'Q';
const char TOMATE = 'T';
const char LECHUGA = 'L' ;
const char MILANESA = 'I';

//Movimientos y cambio de peronsaje
const char ABAJO = 'S';
const char CORTAR = 'C';
const char ARRIBA = 'W';
const char COCINAR = 'H';
const char DERECHA = 'D';
const char IZQUIERDA = 'A';
const char MANOS_VACIAS = 'V';
const char APOYAR_DEJAR = 'T';
const char AGARRAR_SOLTAR = 'R';
const char CAMBIAR_PERSONAJE = 'X';

//Valores del juego
const int GANASTE = 1;
const int PERDISTE = -1;
const int SEGUIR_JUGANDO = 0;


// PRE: --
// POST: inicializar las paredes y el campo paredes de la estructura juego_t agregandolos al vector paredes.
void inicializar_paredes_y_mesa(juego_t *juego) {
    juego->tope_paredes = 0;

    for(int fila = 0 ; fila < MAX_FILAS ; fila++) {
        for(int columna = 0 ; columna < MAX_COLUMNAS ; columna++) {
            if(fila == FILA_INICIAL || fila == FILA_FINAL ) {
                (juego->paredes[juego->tope_paredes]).fil = fila ;
                (juego->paredes[juego->tope_paredes]).col = columna ;
                (juego->tope_paredes)++;
            } else if(fila == FILA_MEDIA && columna != COLUMNA_MEDIA) {
                (juego->paredes[juego->tope_paredes]).fil = fila;
                (juego->paredes[juego->tope_paredes]).col = columna;
                (juego->tope_paredes)++;  
            } else if((columna == COLUMNA_INICIAL) && (fila > FILA_INICIAL) && (fila != FILA_MEDIA) && (fila < FILA_FINAL)) {
                (juego->paredes[juego->tope_paredes]).fil = fila;
                (juego->paredes[juego->tope_paredes]).col = columna;
                (juego->tope_paredes)++; 
            } else if ((columna == COLUMNA_FINAL) && (fila > FILA_INICIAL) && (fila != FILA_MEDIA) && (fila < FILA_FINAL)) {
                (juego->paredes[juego->tope_paredes]).fil = fila;
                (juego->paredes[juego->tope_paredes]).col = columna;
                (juego->tope_paredes)++; 
            }
        }
    }
    juego->mesa.col = COLUMNA_MEDIA ;
    juego->mesa.fil = FILA_MEDIA ;
}

// PRE: ambas coordenadas deben estar inicializadas y estar dentro del conjunto permitido {0...21}
// POST: retorna verdadero si coinciden las posiciones.
bool validar_coordenada(coordenada_t coordenada_1 , coordenada_t coordenada_2) {
    return (coordenada_1.col == coordenada_2.col) && (coordenada_1.fil == coordenada_2.fil);
}

// PRE: coordenada,vector y tope vector deben estar inicializados
// POST: retorna verdadero si coinciden las coordenadas deseadas con el vector herramienta.
bool validar_vector_objeto(coordenada_t coordenada, objeto_t* vector, int tope_vector){
    bool coordenada_es_igual = false;

    for(int i = 0 ; i < tope_vector ; i++){
        if(validar_coordenada(coordenada, vector[i].posicion)) {
            coordenada_es_igual = true;
        }
    }
    return coordenada_es_igual;
}

// PRE: que coordenada este inicializada.
// POST: completa el campo de la estructura coordenada_t con valores para las coordenadas de la fila y columna
coordenada_t obtener_coordenada_aleatoria() {
    coordenada_t coordenada;
    coordenada.col = rand() % COLUMNA_LIMITE + UNA_FILA;
    coordenada.fil = rand() % FILA_LIMITE + UNA_FILA;
    while (coordenada.fil == FILA_MEDIA) {
        coordenada.fil = rand() % FILA_LIMITE + UNA_FILA;
    } 
    
    return coordenada;
}

// PRE: --
// POST: inicializar los agujeros el campo obstaculos de la estructura juego_t agregandolos al vector obstaculos.
void inicializar_agujeros(juego_t* juego) {
    int agujeros_segundo_cuadrante = 0;
    int agujeros_primer_cuadrante = 0;
    juego->tope_obstaculos = 0;
    coordenada_t agujero;

    while ((agujeros_primer_cuadrante < MAX_AGUJEROS / CUADRANTES) || (agujeros_segundo_cuadrante < MAX_AGUJEROS / CUADRANTES)) {
        agujero = obtener_coordenada_aleatoria();
        juego->obstaculos[juego->tope_obstaculos].tipo = AGUJERO;
        
        if (agujero.fil < FILA_MEDIA && (agujeros_primer_cuadrante < MAX_AGUJEROS / CUADRANTES) && !validar_vector_objeto(agujero,juego->obstaculos,juego->tope_obstaculos)) {
            juego->obstaculos[juego->tope_obstaculos].posicion = agujero;
            (juego->tope_obstaculos)++;
            (agujeros_primer_cuadrante)++;
        } else if (agujero.fil > FILA_MEDIA && (agujeros_segundo_cuadrante < MAX_AGUJEROS / CUADRANTES) && 
        !validar_vector_objeto(agujero,juego->obstaculos,juego->tope_obstaculos)) {
            juego->obstaculos[juego->tope_obstaculos].posicion = agujero;
            (agujeros_segundo_cuadrante)++;
            (juego->tope_obstaculos)++;
        }
    }
}

// PRE: los campos de la estructura juego y coordenada deben estar inicializados
// POST: retorna verdadero si coinciden las coordenadas con algun obstaculo o herramienta 
bool validar_obstaculos_y_herramientas(juego_t juego , coordenada_t coordenada){
    bool es_coordenada_igual = false;

    if(validar_vector_objeto(coordenada,juego.obstaculos,juego.tope_obstaculos) || 
       validar_vector_objeto(coordenada, juego.herramientas,juego.tope_herramientas)) {
        es_coordenada_igual = true;
    }
    return es_coordenada_igual;
} 


// PRE: --
// POST: inicializar los cuchillos y  el campo herramientas de la estructura juego_t agregandolos al vector.
void inicializar_cuchillos(juego_t* juego) {
    int cuchillos_en_terreno  = 0;
    juego->tope_herramientas = 0;
    coordenada_t cuchillo;

    while(cuchillos_en_terreno < MAX_CUCHILLOS) {
        juego->herramientas[juego->tope_herramientas].tipo = CUCHILLO;
        cuchillo = obtener_coordenada_aleatoria();

        if (cuchillo.fil < FILA_MEDIA && !validar_obstaculos_y_herramientas(*juego,cuchillo)) {   
            juego->herramientas[juego->tope_herramientas].posicion = cuchillo;  
            (juego->tope_herramientas)++;
            cuchillos_en_terreno++;
        }
    }
}

// PRE: --
// POST: inicializar los hornos y modificar el campo de la estructura juego herramientas agregandolos al vector.
void inicializar_hornos(juego_t* juego){
    int hornos_en_terreno = 0;
    coordenada_t horno;

    while ( hornos_en_terreno < MAX_HORNOS) {
        juego->herramientas[juego->tope_herramientas].tipo = HORNO;
        horno = obtener_coordenada_aleatoria();

        if (!validar_obstaculos_y_herramientas(*juego,horno) && horno.fil > FILA_MEDIA) {
            juego->herramientas[juego->tope_herramientas].posicion = horno;
            (juego->tope_herramientas)++;
            hornos_en_terreno++;
        } 
    }
}

// PRE: tope, juego, vector y coordenada deben estar inicializados
// POST: retorna verdadero si coinciden las coordenadas con algun ingrediente del vector ingredientes.
bool validar_posicion_ingrediente(coordenada_t coordenada , comida_t vector, int tope_vector) {
    bool es_coordenada_igual = false;

    for(int i = 0 ; i < tope_vector ; i++){
        if(validar_coordenada(coordenada, vector.ingrediente[i].posicion)) {
            es_coordenada_igual = true;
        }
    }
    return es_coordenada_igual;
}

// PRE: juego, vector y coordenada deben estar correctamente inicializados.
// POST: retorna verdadero si la posicion es igual a cualquier otro ingrediente, herramienta u obstaculo.
bool validacion_universal(juego_t juego, comida_t vector, coordenada_t coordenada) {
    bool es_coordenada_igual = false;

    if (validar_obstaculos_y_herramientas(juego,coordenada) ||
        validar_posicion_ingrediente(coordenada,vector,vector.tope_ingredientes)) {
        es_coordenada_igual = true;
        }
    return es_coordenada_igual;
}

// PRE: el campo comida actual debe estar inicializado por ende las comidas también.
// POST: devuelve el indice de la comida que se está preparando respecto al vector comida.
int indice_de_la_comida_en_el_vector_comida(juego_t juego) {
    int posicion_comida_actual = 0;

    if (juego.comida_actual == ENSALADA){
        posicion_comida_actual = INDICE_ENSALADA;
    } else if (juego.comida_actual == PIZZA) {
        posicion_comida_actual = INDICE_PIZZA;
    } else if (juego.comida_actual == HAMBURGUESA) {
        posicion_comida_actual = INDICE_HAMBURGUESA;
    } else if (juego.comida_actual == SANDWICH) {
        posicion_comida_actual = INDICE_SANDWICH;
    }
    return posicion_comida_actual;
}

// PRE: --
// POST: inicializar el Fuego y agregarlo al vector obstaculos.
void inicializar_fuego (juego_t* juego){
    coordenada_t fuego;
    int fuego_en_cuadrante = 0;
    int indice_actual = indice_de_la_comida_en_el_vector_comida(*juego);

    while(fuego_en_cuadrante == 0 ) {
        fuego = obtener_coordenada_aleatoria();
        juego->obstaculos[juego->tope_obstaculos].tipo = FUEGO;
        

        if ((!validacion_universal(*juego,juego->comida[indice_actual], fuego)) && !validar_coordenada(juego->salida,fuego) &&
        !validar_coordenada(juego->stitch.posicion,fuego) && !validar_coordenada(juego->reuben.posicion,fuego)) {
            juego->obstaculos[juego->tope_obstaculos].posicion = fuego;
            fuego_en_cuadrante++;
        }
    }
    (juego->tope_obstaculos)++;
}

// PRE: --
// POST: inicializar el matafuego y agregarlo al vector herramientas.
void inicializar_matafuego (juego_t* juego){
    coordenada_t matafuego;
    int matafuego_en_cuadrante = 0;
    int indice_actual = indice_de_la_comida_en_el_vector_comida(*juego);

    while(matafuego_en_cuadrante == 0) {
        juego->herramientas[juego->tope_herramientas].tipo = MATAFUEGO;
        matafuego = obtener_coordenada_aleatoria();
        
        if (juego->obstaculos[juego->tope_obstaculos-1].posicion.fil < FILA_MEDIA && matafuego.fil < FILA_MEDIA &&
           (!validacion_universal(*juego,juego->comida[indice_actual], matafuego)) && !validar_coordenada(juego->stitch.posicion,matafuego)) {
            juego->herramientas[juego->tope_herramientas].posicion = matafuego;
            matafuego_en_cuadrante++;
        } else if (juego->obstaculos[juego->tope_obstaculos-1].posicion.fil > FILA_MEDIA && matafuego.fil > FILA_MEDIA &&
           (!validacion_universal(*juego,juego->comida[indice_actual], matafuego)) && !validar_coordenada(juego->reuben.posicion,matafuego)) {
            juego->herramientas[juego->tope_herramientas].posicion = matafuego;
            matafuego_en_cuadrante++;
           }
    }
    (juego->tope_herramientas)++;
} 

// PRE:--
// POST: inicializar la carne modificando el campo de la estructura juego y agregarla al vector ingredientes respectivo.
void inicializar_ingrediente(juego_t* juego, char ingrediente ){
    coordenada_t coordenada_ingrediente;
    bool ingrediente_inicializado = false;
    juego->comida[juego->tope_comida].ingrediente[juego->comida[juego->tope_comida].tope_ingredientes].tipo = ingrediente;
    juego->comida[juego->tope_comida].ingrediente[juego->comida[juego->tope_comida].tope_ingredientes].esta_cocinado = false;
    juego->comida[juego->tope_comida].ingrediente[juego->comida[juego->tope_comida].tope_ingredientes].esta_cortado = false;
    
    while (ingrediente_inicializado == false){
        coordenada_ingrediente = obtener_coordenada_aleatoria();
        
        if (!validacion_universal(*juego,juego->comida[juego->tope_comida], coordenada_ingrediente) && coordenada_ingrediente.fil < FILA_MEDIA &&
        (ingrediente == JAMON || ingrediente == QUESO || ingrediente == LECHUGA || ingrediente == TOMATE || ingrediente == PAN )) {
            juego->comida[juego->tope_comida].ingrediente[juego->comida[juego->tope_comida].tope_ingredientes].posicion = coordenada_ingrediente;
            (juego->comida[juego->tope_comida].tope_ingredientes)++;
            ingrediente_inicializado = true;
        } else if (!validacion_universal(*juego,juego->comida[juego->tope_comida], coordenada_ingrediente) && coordenada_ingrediente.fil > FILA_MEDIA &&
        (ingrediente == CARNE || ingrediente == MASA || ingrediente == MILANESA )) {
            juego->comida[juego->tope_comida].ingrediente[juego->comida[juego->tope_comida].tope_ingredientes].posicion = coordenada_ingrediente;
            (juego->comida[juego->tope_comida].tope_ingredientes)++;
            ingrediente_inicializado = true;
        } 
    } 
}

// PRE: los ingredientes de la ensalada deben estar inicializados.
// POST: inicializa la ensalada y la agrega al vector comida.
void inicializar_ensalada(juego_t* juego){
    juego->tope_comida = 0;
    juego->comida[juego->tope_comida].tope_ingredientes = 0;
    juego->comida[juego->tope_comida].tipo = ENSALADA;

    inicializar_ingrediente(juego,LECHUGA);
    inicializar_ingrediente(juego,TOMATE);

    (juego->tope_comida)++;
} 

// PRE: los ingredientes de la pizza deben estar inicializadas.
// POST: inicializa la pizza y la agrega al vector comida.
void inicializar_pizza(juego_t* juego){
    juego->comida[juego->tope_comida].tope_ingredientes = 0;
    juego->comida[juego->tope_comida].tipo = PIZZA;

    inicializar_ingrediente(juego,MASA);
    inicializar_ingrediente(juego,JAMON);
    inicializar_ingrediente(juego,QUESO);

    (juego->tope_comida)++;
}

// PRE: los ingredientes de la hamburguesa deben estar inicializados
// POST: inicializa la hamburguesa y la agrega al vector comida.
void inicializar_hamburguesa(juego_t* juego){
    juego->comida[juego->tope_comida].tope_ingredientes = 0;
    juego->comida[juego->tope_comida].tipo = HAMBURGUESA;

    inicializar_ingrediente(juego,TOMATE);
    inicializar_ingrediente(juego,LECHUGA);
    inicializar_ingrediente(juego,CARNE);
    inicializar_ingrediente(juego,PAN);

    (juego->tope_comida)++;
}

// PRE: los ingredientes del sandwich deben estar inicializados.
// POST: iniciliza el sandwich y lo agrega al vector comida.
void inicializar_sandwich(juego_t* juego){
    juego->comida[juego->tope_comida].tope_ingredientes = 0;
    juego->comida[juego->tope_comida].tipo = SANDWICH;

    inicializar_ingrediente(juego,JAMON);
    inicializar_ingrediente(juego,QUESO);
    inicializar_ingrediente(juego,TOMATE);
    inicializar_ingrediente(juego,LECHUGA);
    inicializar_ingrediente(juego,PAN);
    inicializar_ingrediente(juego,MILANESA);

    (juego->tope_comida)++;
}

// PRE: --
// POST: inicializa el personaje stitch y modifica el campo stitch de la estructura juego.
void inicializar_stitch(juego_t* juego){
    coordenada_t personaje;
    juego->stitch.tipo = STITCH;
    juego->stitch.objeto_en_mano = MANOS_VACIAS;
    personaje = obtener_coordenada_aleatoria();

    for(int i = 0 ; i < juego->tope_comida ; i++ ){
        while(validacion_universal(*juego,juego->comida[i],personaje) || personaje.fil > FILA_MEDIA) {
            personaje = obtener_coordenada_aleatoria();
        }
    }
    juego->stitch.posicion = personaje;
}

// PRE: --
// POST: inicializa el personaje reuben y modifica el campo reuben de la estructura juego.
void inicializar_reuben (juego_t* juego){
    coordenada_t personaje;
    juego->reuben.tipo = REUBEN;
    juego->reuben.objeto_en_mano = MANOS_VACIAS;
    personaje = obtener_coordenada_aleatoria();

    for(int i = 0 ; i < juego->tope_comida ; i++ ){
        while(validacion_universal(*juego,juego->comida[i],personaje) || personaje.fil < FILA_MEDIA) {
           personaje = obtener_coordenada_aleatoria();
        }
    }
    juego->reuben.posicion = personaje;
}

// PRE:--
// POST: inicializar la puerta de salida y modifica el campo salida de la estructura juego.
void inicializar_puerta_de_salida (juego_t* juego){
    coordenada_t puerta;
    bool hay_puerta = false;

    while(!hay_puerta) {
        puerta = obtener_coordenada_aleatoria();
        if ((!validacion_universal(*juego,juego->comida[juego->tope_comida],puerta) && 
          !validar_coordenada(puerta,juego->reuben.posicion)) && puerta.fil > FILA_MEDIA){
            juego->salida = puerta;
            hay_puerta = true;
        }
    }
}

// PRE: deben estar inicializados los campos de los personajes y el vector de las comidas.
// POST: determina que jugador se va a mover, que comida se va a cocinar e inicializa el campo movimientos al comienzo del juego.
void iniciador_de_turno(juego_t* juego){
    juego->tope_comida_lista = 0;
    juego->movimientos = 0;
    juego->personaje_activo = STITCH; 
    juego->comida_actual = juego->comida[INDICE_ENSALADA].tipo;
    
}

void inicializar_juego(juego_t* juego, int precio) {
    juego->precio_total = precio;

    inicializar_paredes_y_mesa(juego);
    inicializar_agujeros(juego);

    inicializar_cuchillos(juego);
    inicializar_hornos(juego);

    inicializar_ensalada(juego);
    inicializar_pizza(juego);
    inicializar_hamburguesa(juego);
    inicializar_sandwich(juego);

    inicializar_stitch(juego);
    inicializar_reuben(juego);
    inicializar_puerta_de_salida(juego);
    iniciador_de_turno(juego);
}

// PRE: el personaje y el objeto a comparar deben estar inicializados.
// POST: retorna la distancia a la que se encuentra el personaje respecto a una posicion deseada.
int distancia_manhattan (coordenada_t coordenada_1 , coordenada_t coordenada_2) {
    return abs(coordenada_1.fil - coordenada_2.fil) + abs(coordenada_1.col - coordenada_2.col);
}

// PRE: el tope paredes, las paredes y la nueva posicion deben estar inicializados. La nueva posicion debe ser valida.
// POST: devuelve verdadero si hay una pared en la posicion.
bool es_pared (juego_t juego,coordenada_t nueva_posicion) {
    bool hay_pared = false;
    for (int i = 0 ; i < juego.tope_paredes ; i++) {
        if (juego.paredes[i].col == nueva_posicion.col &&
            juego.paredes[i].fil == nueva_posicion.fil ) {
                hay_pared = true;
            }
    }
    return hay_pared;
}

// PRE: el tope obstaculos, los obstaculos y la nueva posicion deben estar inicializados. La nueva posicion debe ser valida.
// POST: devuelve verdadero si hay un fuego en la posicion
bool es_fuego(juego_t juego, coordenada_t nueva_posicion) {
    bool hay_fuego = false;
    for (int i = 0 ; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].posicion.fil == nueva_posicion.fil &&
            juego.obstaculos[i].posicion.col == nueva_posicion.col &&
            juego.obstaculos[i].tipo == FUEGO) {
            hay_fuego = true; 
        }
    }
    return hay_fuego;
}

// PRE: el tope herramientas, las herramientas y la nueva posicion deben estar inicializados. La nueva posicion debe ser valida.
// POST: devuelve verdadero si hay un horno en la posicion.
bool es_horno (juego_t juego, coordenada_t nueva_posicion) {
    bool hay_horno = false;
    for (int i = 0 ; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].posicion.fil == nueva_posicion.fil &&
            juego.herramientas[i].posicion.col == nueva_posicion.col &&
            juego.herramientas[i].tipo == HORNO) {
            hay_horno = true; 
        }
    }
    return hay_horno;

}

// PRE: la mesa y la nueva posicion (además de ser válida) deben estar inicializadas.
// POST: devuelve verdadero si esta la mesa en la posicion.
bool es_mesa (juego_t juego, coordenada_t nueva_posicion) {
    return juego.mesa.fil == nueva_posicion.fil && juego.mesa.col == nueva_posicion.col;
}

//PRE:la variable movimiento debe estar inicializada.
//POST: retorna verdadero si la respuesta esta dentro del conjunto {W,S,D,A,X,R,T,C,M,H}
bool letra_valida(char movimiento){
    return (movimiento == ARRIBA) || (movimiento == ABAJO) || (movimiento == CAMBIAR_PERSONAJE) || (movimiento == DERECHA) || 
    (movimiento == IZQUIERDA) || (movimiento == AGARRAR_SOLTAR) || (movimiento == CORTAR) || (movimiento == COCINAR) ||
    (movimiento == MATAFUEGO) || 
    (movimiento == APOYAR_DEJAR);
}

// PRE: movimiento debe estar inicializado asi como los campos del personaje stitch.
// POST: modifica los campos del personaje stitch respecto a su posicion
void mover_stitch(juego_t* juego, char movimiento) {
    coordenada_t nueva_posicion;
    nueva_posicion.col = juego->stitch.posicion.col;
    nueva_posicion.fil = juego->stitch.posicion.fil;
    

    if (movimiento == IZQUIERDA ) {
        nueva_posicion.col--;
    } else if (movimiento == DERECHA ) {
        nueva_posicion.col++;
    } else if (movimiento == ABAJO ) {
        nueva_posicion.fil++;
    } else if (movimiento == ARRIBA ) {
        nueva_posicion.fil--;
    } else if (movimiento == CAMBIAR_PERSONAJE) {
        juego->personaje_activo = REUBEN;
    }

    if (letra_valida (movimiento) && !es_pared(*juego, nueva_posicion) && !es_fuego(*juego, nueva_posicion) && 
        !es_mesa(*juego, nueva_posicion) && movimiento != CAMBIAR_PERSONAJE && 
        movimiento != MATAFUEGO && movimiento != AGARRAR_SOLTAR &&
        movimiento != APOYAR_DEJAR && movimiento != CORTAR ) {
        juego->stitch.posicion.col = nueva_posicion.col;
        juego->stitch.posicion.fil = nueva_posicion.fil;
        juego->movimientos++;
    }
}

// PRE: movimiento debe estar inicializado asi como los campos del personaje reuben.
// POST: modifica los campos del personaje reuben respecto a su posicion
void mover_reuben(juego_t* juego, char movimiento) {
    coordenada_t nueva_posicion;
    nueva_posicion.col = juego->reuben.posicion.col;
    nueva_posicion.fil = juego->reuben.posicion.fil;

    if (movimiento == IZQUIERDA ) {
        nueva_posicion.col--;
    } else if (movimiento == DERECHA ) {
        nueva_posicion.col++;
    } else if (movimiento == ABAJO ) {
        nueva_posicion.fil++;
    } else if (movimiento == ARRIBA ) {
        nueva_posicion.fil--;
    } else if (movimiento == CAMBIAR_PERSONAJE) {
        juego->personaje_activo = STITCH;
    }

    if (letra_valida (movimiento) && !es_fuego(*juego, nueva_posicion) && !es_pared(*juego,nueva_posicion) &&
        !es_horno(*juego, nueva_posicion) && !es_mesa(*juego, nueva_posicion) && 
        (movimiento != CAMBIAR_PERSONAJE && movimiento != COCINAR && 
         movimiento != APOYAR_DEJAR && movimiento != MATAFUEGO && 
         movimiento != AGARRAR_SOLTAR) ) {
        juego->reuben.posicion.col = nueva_posicion.col;
        juego->reuben.posicion.fil = nueva_posicion.fil;
        juego->movimientos++;
    }
}

// PRE: ingrediente debe estar inicializado.
// POST: retorna verdadero si el ingrediente esta cortado.
bool esta_cortado(ingrediente_t ingrediente) {
    return ingrediente.esta_cortado;
}

// PRE: ingrediente debe estar inicializado.
// POST: retorna verdadero si el ingrediente esta cocinado.
bool esta_cocinado(ingrediente_t ingrediente) {
   return ingrediente.esta_cocinado;
}

// PRE: los vectores ingrediente deben estar inicializados.
// POST:retorna verdadero si ingrediente esta cortado y listo para ser dejada en la puerta de salida.
bool ingrediente_listo(ingrediente_t ingrediente) {
    return (((ingrediente.tipo == LECHUGA) || (ingrediente.tipo == TOMATE) || (ingrediente.tipo == QUESO) || 
             (ingrediente.tipo == JAMON) || (ingrediente.tipo == PAN)) && (esta_cortado(ingrediente)) &&
             (!esta_cocinado(ingrediente))) || 
            (((ingrediente.tipo == CARNE) || (ingrediente.tipo == MASA) || (ingrediente.tipo == MILANESA)) && 
             (!esta_cortado(ingrediente)) && (esta_cocinado(ingrediente)));
}

// PRE: el precio total debe ser mayor a 0 y juego tope comida lista tambien.
// POST: devuelve verdadero si se gana el juego.
bool ganar_juego(juego_t juego) {
    bool se_gano = false;
    if (juego.precio_total <= PRECIO_HASTA_PIZZA && juego.tope_comida_lista == juego.comida[INDICE_PIZZA].tope_ingredientes) {
        se_gano =  true;
    } else if (juego.precio_total > PRECIO_HASTA_PIZZA && juego.precio_total <= PRECIO_HASTA_HAMBURGUESA &&
    juego.tope_comida_lista == juego.comida[INDICE_HAMBURGUESA].tope_ingredientes) {
        se_gano =  true;
    } else if (juego.precio_total > PRECIO_HASTA_HAMBURGUESA && juego.tope_comida_lista == juego.comida[INDICE_SANDWICH].tope_ingredientes) {
        se_gano = true;

    }
    return se_gano;
}

// PRE: los vectores comida y sus topes deben estar inicializados. 
// POST: pasa de comida una vez que esta lista.
void pasar_a_siguiente_comida(juego_t* juego,int indice) {
    if (juego->tope_comida_lista == juego->comida[indice].tope_ingredientes && 
        indice + 1 < juego->tope_comida && !ganar_juego(*juego)) {
        juego->comida_actual = juego->comida[indice + 1].tipo;
        juego->tope_comida_lista = 0;
    }
}

// PRE: el personaje debe ser Reuben y los ingredientes deben cumplicar con las condiciones necesarias para ser dejados en la puerta de salida.
// POST: Reuben deja los ingredientes en la puerta de salida para completar las comidas.
void emplatar(personaje_t* personaje, juego_t* juego, int indice) {

    for (int i = 0; i < juego->comida[indice].tope_ingredientes; i++) {
        if ((juego->comida[indice].ingrediente[i].tipo == personaje->objeto_en_mano) && 
             ingrediente_listo(juego->comida[indice].ingrediente[i]) && 
             validar_coordenada(juego->salida, personaje->posicion)) {
                juego->comida[indice].ingrediente[i].posicion.fil = juego->salida.fil;
                juego->comida[indice].ingrediente[i].posicion.col = juego->salida.col;
                juego->comida_lista[juego->tope_comida_lista].esta_cocinado = juego->comida[indice].ingrediente[i].esta_cocinado;
                juego->comida_lista[juego->tope_comida_lista].esta_cortado = juego->comida[indice].ingrediente[i].esta_cortado;
                juego->comida_lista[juego->tope_comida_lista].tipo = juego->comida[indice].ingrediente[i].tipo;
                juego->comida_lista[juego->tope_comida_lista].posicion.fil = juego->salida.fil;
                juego->comida_lista[juego->tope_comida_lista].posicion.col = juego->salida.col;
                personaje->objeto_en_mano = MANOS_VACIAS;
                (juego->tope_comida_lista)++;
        } 
    }
}

// PRE: el movimiento debe pertenecer al cojunto {A,X,W,S,D,T,R,H,M,C}, el matafuego inicializado y en terreno, y el personaje debe tener las manos vacias. 
// POST: El personaje agarra el matafuego del terreno solo pasando por encima.
void agarrar_matafuego(personaje_t* personaje, juego_t* juego) {
    for (int i = 0; i < juego->tope_herramientas; i++) {
        if (juego->herramientas[i].tipo == MATAFUEGO && personaje->objeto_en_mano == MANOS_VACIAS &&
            validar_coordenada(personaje->posicion, juego->herramientas[i].posicion)) {
            personaje->objeto_en_mano = juego->herramientas[i].tipo;
            juego->herramientas[i].posicion.fil = personaje->posicion.fil;
            juego->herramientas[i].posicion.col = personaje->posicion.col;
        }
    }
}

// PRE: el movimiento debe pertenecer al cojunto {A,X,W,S,D,T,R,H,M,C}, el fuego inicializado y en terreno, y el personaje debe tener el matafuego en mano.
// POST: Apaga el fuego y lo elimina tanto del vector herramienta como del obstáculo.
void apagar_fuego(personaje_t* personaje, char movimiento, juego_t* juego) {
    for (int i = 0; i < juego->tope_herramientas; i++) {
        if (juego->herramientas[i].tipo == MATAFUEGO && personaje->objeto_en_mano == juego->herramientas[i].tipo &&
            movimiento == MATAFUEGO && 
            distancia_manhattan(personaje->posicion,juego->obstaculos[juego->tope_obstaculos-1].posicion) <= DISTANCIA_CORRECTA_AL_FUEGO) {
                juego->tope_herramientas--;
                juego->tope_obstaculos--;
                personaje->objeto_en_mano = MANOS_VACIAS;
        }
    }
}

// PRE: el movimiento debe pertenecer al cojunto {A,X,W,S,D,T,R,H,M,C}, los personajes no deben tener nada en mano y los ingredientes deben estar en terreno.
// POST: El personaje agarra ingredientes del terreno.
void agarrar_ingredientes(personaje_t* personaje, char movimiento, juego_t* juego, int indice) {
    if (personaje->objeto_en_mano == MANOS_VACIAS && movimiento == AGARRAR_SOLTAR) {
        for (int i = 0; i < juego->comida[indice].tope_ingredientes; i++) {
            if (validar_coordenada(personaje->posicion, juego->comida[indice].ingrediente[i].posicion)) {
                personaje->objeto_en_mano = juego->comida[indice].ingrediente[i].tipo;
                // juego->comida[indice_actual].ingrediente[i].posicion.col = personaje->posicion.col;
                // juego->comida[indice_actual].ingrediente[i].posicion.fil = personaje->posicion.fil;
            }
        }
    }
}

// PRE: movimiento debe pertenecer al cojunto {A,X,W,S,D,T,R,H,M,C}, los vectores comida deben estar inicializados y personaje debe tener las manos con ingrediente.
// POST: el personaje deja ingredientes en el terreno.
void dejar_ingredientes(personaje_t* personaje, char movimiento, juego_t* juego, int indice) {

    if (personaje->objeto_en_mano != MANOS_VACIAS && movimiento == AGARRAR_SOLTAR){
        for (int i = 0; i < juego->comida[indice].tope_ingredientes; i++) {
            if (!validar_posicion_ingrediente(personaje->posicion, juego->comida[indice],juego->comida[indice].tope_ingredientes) &&
                juego->comida[indice].ingrediente[i].tipo == personaje->objeto_en_mano  &&
                !validar_vector_objeto(personaje->posicion,juego->herramientas,juego->tope_herramientas) &&
                !validar_coordenada(juego->salida, personaje->posicion)) {
                    juego->comida[indice].ingrediente[i].posicion.col = personaje->posicion.col;
                    juego->comida[indice].ingrediente[i].posicion.fil = personaje->posicion.fil;
                    personaje->objeto_en_mano = MANOS_VACIAS;
            }
        }
    }
}

// PRE: la mesa y los ingredientes deben estar inicializados.
// POST: devuelve verdadero si hay un ingrediente en la mesa.
bool mesa_ocupada (juego_t juego,int indice) {
    bool esta_ocupada = false;
    for (int i = 0 ; i < juego.comida[indice].tope_ingredientes ; i++) {
        if (validar_coordenada (juego.comida[indice].ingrediente[i].posicion, juego.mesa)) {
            esta_ocupada = true;
        }
    }
    return esta_ocupada;
}

// PRE: los ingredientes, personaje y la mesa deben estar inicializados.
// POST: permite que el personaje agarre o deje ingredientes en la mesa.
void obtener_o_dejar_ingredientes_en_mesa(personaje_t* personaje, char movimiento, juego_t* juego, int indice) {
    if (movimiento == APOYAR_DEJAR) {
        if (personaje->objeto_en_mano != MANOS_VACIAS && distancia_manhattan(personaje->posicion,juego->mesa) == DISTANCIA_A_MESA &&
         !mesa_ocupada(*juego,indice)) {
            for (int i = 0; i < juego->comida[indice].tope_ingredientes; i++) {
                if (juego->comida[indice].ingrediente[i].tipo == personaje->objeto_en_mano ) {
                    juego->comida[indice].ingrediente[i].posicion.fil = juego->mesa.fil;
                    juego->comida[indice].ingrediente[i].posicion.col = juego->mesa.col;
                    personaje->objeto_en_mano = MANOS_VACIAS;
                }
            }
        } else if (personaje->objeto_en_mano == MANOS_VACIAS && distancia_manhattan(personaje->posicion,juego->mesa) == DISTANCIA_A_MESA) {
            for (int i = 0; i < juego->comida[indice].tope_ingredientes; i++) {
                if (juego->comida[indice].ingrediente[i].posicion.fil == juego->mesa.fil &&
                    juego->comida[indice].ingrediente[i].posicion.col == juego->mesa.col) {
                    personaje->objeto_en_mano = juego->comida[indice].ingrediente[i].tipo;
                    juego->comida[indice].ingrediente[i].posicion.col = personaje->posicion.col;
                    juego->comida[indice].ingrediente[i].posicion.fil = personaje->posicion.fil;
                }
            }
        }
    }
}

// PRE: el movimiento debe pertenecer al cojunto {A,X,W,S,D,T,R,H,M,C}, las herramientas y los ingredientes deben estar inicializados.
// POST: El personaje corta los ingredientes que tiene en la mano.
void cortar_ingredientes(personaje_t* personaje, char movimiento, juego_t* juego, int indice) {
    if (personaje->objeto_en_mano != MANOS_VACIAS && movimiento == CORTAR &&
        validar_vector_objeto(personaje->posicion,juego->herramientas,juego->tope_herramientas)) {
        for (int i = 0; i < juego->comida[indice].tope_ingredientes; i++) {
            if (juego->comida[indice].ingrediente[i].tipo == personaje->objeto_en_mano) {
                juego->comida[indice].ingrediente[i].esta_cortado = true;
                printf("El %c esta cortado",juego->comida[indice].ingrediente[i].tipo);
            }
        }
    }
}

// PRE: los hornos y los personaje deben estar inicializados.
// POST: Devuelve verdadero si la distancia al horno es correcta para usarlo.
bool distancia_al_horno(personaje_t personaje, juego_t juego) {
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (distancia_manhattan(personaje.posicion, juego.herramientas[i].posicion) <= DISTANCIA_A_HORNO) {
            return true;
        }
    }
    return false;
}

// PRE: el movimiento debe pertenecer al cojunto {A,X,W,S,D,T,R,H,M,C}, las herramientas y los ingredientes deben estar inicializados.
// POST: El personaje cocina los ingredientes que tiene en la mano.
void cocinar_ingredientes(personaje_t* personaje, char movimiento, juego_t* juego, int indice) {
    if (personaje->objeto_en_mano != MANOS_VACIAS && movimiento == COCINAR &&
        distancia_al_horno(*personaje, *juego)) {
        for (int i = 0; i < juego->comida[indice].tope_ingredientes; i++) {
            if (juego->comida[indice].ingrediente[i].tipo == personaje->objeto_en_mano) {
                juego->comida[indice].ingrediente[i].esta_cocinado = true;
                printf("EL %c esta cocinado",juego->comida[indice].ingrediente[i].tipo);
            }
        }
    }
}
 
// PRE: los obstaculos deben estar inicializados en especial el fuego.
// POST: Devuelve verdadero si hay un fuego en el terreno.
bool hay_fuego(juego_t juego) {
    bool fuego_existe = false;
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == FUEGO) {
            fuego_existe = true;
        }
    }
    return fuego_existe;
}

// PRE: los obstaculos deben estar inicializados en especial el fuego.
// POST: Devuelve verdadero si hay un fuego en el cuadrante de stitch.
bool hay_fuego_cuadrante_stitch(juego_t juego) {
    bool fuego_existe = false;
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == FUEGO && juego.obstaculos[i].posicion.fil < FILA_MEDIA) {
            fuego_existe = true;
        }
    }
    return fuego_existe;
}

// PRE: los obstaculos deben estar inicializados en especial el fuego.
// POST: Devuelve verdadero si hay un fuego en el cuadrante de reuben.
bool hay_fuego_cuadrante_reuben(juego_t juego) {
    bool fuego_existe = false;
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == FUEGO && juego.obstaculos[i].posicion.fil > FILA_MEDIA) {
            fuego_existe = true;
        }
    }
    return fuego_existe;
}

// PRE: movimiento y todos los campos del juego relacionado al personaje deben estar correctamente inicializados.
// POST: llama a las funcionas para poder mover al personaje Stitch.
void realizar_jugada_stitch(juego_t* juego , char movimiento,int indice_actual) {
    if(!hay_fuego_cuadrante_stitch(*juego)){
        mover_stitch(juego,movimiento);
        agarrar_ingredientes(&(juego->stitch), movimiento,juego,indice_actual);
        dejar_ingredientes(&(juego->stitch), movimiento,juego,indice_actual);
        cortar_ingredientes(&(juego->stitch), movimiento,juego,indice_actual);
        obtener_o_dejar_ingredientes_en_mesa(&(juego->stitch), movimiento,juego,indice_actual);
    } else{
        mover_stitch(juego,movimiento);
        apagar_fuego(&(juego->stitch), movimiento,juego);
        agarrar_matafuego(&(juego->stitch), juego);
        dejar_ingredientes(&(juego->stitch), movimiento,juego,indice_actual);
    }
}

// PRE: movimiento y todos los campos del juego relacionado al personaje deben estar correctamente inicializados.
// POST: llama a las funciones para poder mover al personaje Reuben.
void realizar_jugada_reuben(juego_t* juego , char movimiento, int indice_actual) {
    if(!hay_fuego_cuadrante_reuben(*juego)) {
        mover_reuben(juego,movimiento);
        emplatar(&(juego->reuben),juego,indice_actual); 
        dejar_ingredientes(&(juego->reuben), movimiento,juego,indice_actual);
        agarrar_ingredientes(&(juego->reuben),movimiento, juego,indice_actual);
        cocinar_ingredientes(&(juego->reuben), movimiento, juego,indice_actual);
        obtener_o_dejar_ingredientes_en_mesa(&(juego->reuben), movimiento, juego,indice_actual);
    }  else {
        mover_reuben(juego,movimiento);
        apagar_fuego(&(juego->reuben), movimiento,juego);
        agarrar_matafuego(&(juego->reuben), juego);
        dejar_ingredientes(&(juego->reuben), movimiento,juego,indice_actual);
    }
}


void realizar_jugada(juego_t* juego, char movimiento) {
    int contador = juego->movimientos;
    int flamas_en_terreno = 0;
    int indice = indice_de_la_comida_en_el_vector_comida(*juego);
    
    if (juego->personaje_activo == STITCH) {
        realizar_jugada_stitch(juego, movimiento,indice);
    } else  {
        realizar_jugada_reuben(juego, movimiento,indice);
    }
    if (hay_fuego(*juego)) {
        juego->movimientos = 0;
    }
    while (flamas_en_terreno == 0 && contador == MOVIMIENTO_PARA_FUEGO) {
        inicializar_fuego(juego);
        inicializar_matafuego(juego);
        juego->movimientos = 0;
        flamas_en_terreno = hay_fuego(*juego) ? 1 : 0;
    }
    pasar_a_siguiente_comida(juego,indice);
}

// PRE: --
// POST: asigna a cada coordenada de la matriz un espacio vacio.
void crear_matriz(char terreno[MAX_FILAS][MAX_COLUMNAS]) {
    for (int fila = 0; fila < MAX_FILAS; fila++) {
        for (int columna = 0; columna < MAX_COLUMNAS; columna++) {
            terreno[fila][columna] = VACIO;
        }
    }
}

// PRE: la matriz terreno, las paredes y su tope deben estar correctamente inicializados  
// POST: asigna las paredes a la matriz.
void asignar_paredes_a_matriz(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego) {
    for (int paredes = 0; paredes < juego.tope_paredes; paredes++) {
        terreno[juego.paredes[paredes].fil][juego.paredes[paredes].col] = PARED;
    }
}

// PRE: la matriz terreno, los obstaculos y su tope deben estar correctamente inicializados.
// POST: asigna los obstaculos a la matriz.
void asignar_obstaculos_a_matriz(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego) {
    for (int obstaculos = 0; obstaculos < juego.tope_obstaculos; obstaculos++) {
        terreno[juego.obstaculos[obstaculos].posicion.fil][juego.obstaculos[obstaculos].posicion.col] =
        juego.obstaculos[obstaculos].tipo;
    }
}

// PRE: la matriz terreno, las herramientas y su tope deben estar correctamente inicializados. 
// POST: asigna las herramientas a la matriz.
void asignar_herramientas_a_matriz(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego) {
    for (int herramienta = 0; herramienta < juego.tope_herramientas; herramienta++) {
        terreno[juego.herramientas[herramienta].posicion.fil][juego.herramientas[herramienta].posicion.col] =
        juego.herramientas[herramienta].tipo;
    }
}

// PRE: la matriz terreno, la mesa y la puerta de salida deben estar inicializados
// POST: asigna la mesa y la puerta de salida a la matriz.
void asignar_mesa_y_puerta_de_salida_a_matriz(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego) {
    terreno[juego.mesa.fil][juego.mesa.col] = MESA;
    terreno[juego.salida.fil][juego.salida.col] = PUERTA_DE_SALIDA;
}

// PRE: la matriz terreno, los ingredientes y las comidas deben estar correctamente inicializadas. 
// POST:asigna los ingredientes de las comidas que se esta preparando a la matriz.
void asignar_comida_a_matriz(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego,int indice) {
    for (int i = 0; i < juego.comida[indice].tope_ingredientes; i++) {
        if( (juego.reuben.objeto_en_mano != juego.comida[indice].ingrediente[i].tipo)  && (juego.stitch.objeto_en_mano != juego.comida[indice].ingrediente[i].tipo ) ) {
        terreno[juego.comida[indice].ingrediente[i].posicion.fil][juego.comida[indice].ingrediente[i].posicion.col] = juego.comida[indice].ingrediente[i].tipo;
        }
    }
}

// PRE: la matriz terreno, y los personajes deben estar correctamente inicializados
// POST: asigna los personajes a la matriz.
void asignar_personajes_a_matriz(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego) {
    terreno[juego.stitch.posicion.fil][juego.stitch.posicion.col] = juego.stitch.tipo;
    terreno[juego.reuben.posicion.fil][juego.reuben.posicion.col] = juego.reuben.tipo;
}

// PRE: la matriz terreno debe estar inicializada y los personajes deben poder agarrar el matafuego.
// POST: desaparece el matafuego del terreno
void desaparecer_matafuego_de_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego) {
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.stitch.objeto_en_mano == MATAFUEGO && juego.herramientas[i].tipo == MATAFUEGO) {
            terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = VACIO;
            terreno[juego.stitch.posicion.fil][juego.stitch.posicion.col] = STITCH;
        } else if (juego.reuben.objeto_en_mano == juego.herramientas[i].tipo) {
            terreno[juego.herramientas[i].posicion.fil][juego.herramientas[i].posicion.col] = VACIO;
            terreno[juego.reuben.posicion.fil][juego.reuben.posicion.col] = REUBEN;
        }
    }
}

// PRE: la matriz terreno, los ingredientes, la mesa deben estar inicializados y los personajes deben poder dejar los ingredientes en la mesa.
// POST: muestra el ingrediente que esta en la mesa.
void ingredientes_en_mesa(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego,int indice) {
    bool mesa_ocupada = false;
    for(int i = 0 ; i < juego.comida[indice].tope_ingredientes ; i++) {
        if(juego.comida[indice].ingrediente[i].posicion.col == juego.mesa.col &&
           juego.comida[indice].ingrediente[i].posicion.fil == juego.mesa.fil) {
            terreno[juego.mesa.fil][juego.mesa.col] = juego.comida[indice].ingrediente[i].tipo;
            mesa_ocupada = true;
        }
    }

    if(!mesa_ocupada) {
        terreno[juego.mesa.fil][juego.mesa.col] = MESA;
    } 
}
// PRE: tope comida lista debe ser mayor a 0.
// POST: imprime por pantalla los ingredientes en el vector comida lista.
void imprimir_vector(juego_t juego) {
    printf("(6) Los ingredientes listos son  = {");
    for (int i = 0 ; i < juego.tope_comida_lista ; i++) {
        printf("%c,",juego.comida_lista[i].tipo);
    }
    printf("}\n");
}

void imprimir_terreno(juego_t juego) {
    int indice_actual = indice_de_la_comida_en_el_vector_comida(juego);
    char terreno[MAX_FILAS][MAX_COLUMNAS];
    crear_matriz(terreno);
    asignar_paredes_a_matriz(terreno, juego);
    asignar_obstaculos_a_matriz(terreno, juego);
    asignar_herramientas_a_matriz(terreno, juego);
    asignar_comida_a_matriz(terreno, juego,indice_actual);
    asignar_mesa_y_puerta_de_salida_a_matriz(terreno, juego);
    asignar_personajes_a_matriz(terreno, juego);
    ingredientes_en_mesa(terreno, juego,indice_actual);
    desaparecer_matafuego_de_terreno(terreno, juego);

    for(int fila = 0 ; fila < MAX_FILAS ; fila++) {
        for (int columna = 0 ; columna < MAX_COLUMNAS  ; columna++) {
            if (terreno[fila][columna] == STITCH) {
                printf(" %s",STITCH_EMOJI);
            }else if (terreno[fila][columna] == REUBEN) {
                printf(" %s",REUBEN_EMOJI);
            }else if (terreno[fila][columna] == PARED) {
                printf(" %s",PARED_EMOJI);
            }else if (terreno[fila][columna] == VACIO) {
                printf(" %s",VACIO_EMOJI);
            }else if (terreno[fila][columna] == HORNO) {
                printf(" %s ",HORNO_EMOJI);
            } else if (terreno[fila][columna] == CUCHILLO) {
                printf(" %s",CUCHILLO_EMOJI);
            } else if (terreno[fila][columna] == PUERTA_DE_SALIDA) {
                printf(" %s",SALIDA_EMOJI);
            } else if (terreno[fila][columna] == AGUJERO) {
                printf(" %s ",AGUJERO_EMOJI);
            }else if (terreno[fila][columna] == FUEGO) {
                printf(" %s",FUEGO_EMOJI);
            }else if (terreno[fila][columna] == MATAFUEGO) {
                printf(" %s",MATAFUEGO_EMOJI);
            }else if (terreno[fila][columna] == MESA) {
                printf(" %s ",MESA_EMOJI);
            }  else if (terreno[fila][columna] == LECHUGA) {
                printf(" %s",LECHUGA_EMOJI);
            }else if (terreno[fila][columna] == TOMATE) {
                printf(" %s",TOMATE_EMOJI);
            }else if (terreno[fila][columna] == MASA) {
                printf(" %s",MASA_EMOJI);
            }else if (terreno[fila][columna] == JAMON) {
                printf(" %s",JAMON_EMOJI);
            }else if (terreno[fila][columna] == QUESO) {
                printf(" %s",QUESO_EMOJI);
            }else if (terreno[fila][columna] == MILANESA) {
                printf(" %s",MILANESA_EMOJI);
            }else if (terreno[fila][columna] == PAN) {
                printf(" %s",PAN_EMOJI);
            }else {
            printf(" %c",terreno[fila][columna]);
            }
        }
        printf("\n \n");
    }

    printf("(1) El precio total es : %i \n", juego.precio_total);
    printf("(2) El indice de la comida actual es : %i   \n", indice_de_la_comida_en_el_vector_comida(juego));
    printf("(3) La comida actual es : %c \n", juego.comida_actual);
    printf("(4) El indice del tope de la comida lista es : %i   \n", juego.tope_comida_lista);
    printf("(5) El tope comida es : %i \n", juego.tope_comida);
    imprimir_vector(juego);
    if (mesa_ocupada(juego,indice_actual)){
        printf("(7) La mesa esta ocupada.\n");
    }else{
        printf("(7) La mesa esta libre. \n");
    }
    if (juego.personaje_activo == REUBEN && juego.reuben.objeto_en_mano != MANOS_VACIAS){
        printf("(8) El personaje tiene  %c en la mano \n ",juego.reuben.objeto_en_mano);
    } else if (juego.personaje_activo == STITCH && juego.stitch.objeto_en_mano != MANOS_VACIAS) {
        printf("(8) El personaje tiene  %c en la mano \n",juego.stitch.objeto_en_mano);
    }
    for (int i = 0 ; i < juego.comida[indice_actual].tope_ingredientes; i ++) {
        if (juego.reuben.objeto_en_mano == juego.comida[indice_actual].ingrediente[i].tipo ||
        juego.stitch.objeto_en_mano == juego.comida[indice_actual].ingrediente[i].tipo) {
            printf("(9) las coordenadas del ingrediente son %i y %i \n",juego.comida[indice_actual].ingrediente[i].posicion.fil,juego.comida[indice_actual].ingrediente[i].posicion.col);
        }
    }

}


int estado_juego(juego_t juego) {
    if(validar_vector_objeto(juego.stitch.posicion, juego.obstaculos,juego.tope_obstaculos) || 
       validar_vector_objeto(juego.reuben.posicion,juego.obstaculos,juego.tope_obstaculos)) {
        return PERDISTE;
    } else if(ganar_juego(juego)) {
        return GANASTE;
    } else {
        return SEGUIR_JUGANDO;
    }   
}
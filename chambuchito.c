#include<stdio.h>
#include<stdbool.h>
#include "chambuchito.h"

//Tipos de panes
const char PAN_BLANCO = 'B';
const char PAN_INTEGRAL = 'I';
const char PAN_AVENA_Y_MIEL = 'A';
const char PAN_QUESO_Y_OREGANO = 'Q';

//Minimo y máximo de la medida
const int MEDIDA_MINIMO = 15;
const int MEDIDA_MAXIMO = 30;

//Tipos de quesos
const char DAMBO = 'D';
const char CHEDDAR = 'C';
const char GRUYERE = 'G';
const char SIN_QUESO = 'S';

//Tipos de proteinas
const char ROAST_BEEF = 'R';
const char ATUN = 'A';
const char SOJA = 'S';
const char POLLITO = 'P';
const char SIN_PROTE = 'N';

//Si o No
const char SI = 'S';
const char NO = 'N';

//Precios:
const float PRECIO_MEDIDA = 0.3f;
const int PRECIO_PAN_BASICO = 5;
const int PRECIO_PAN_ESPECIAL = 8;
const int PRECIO_QUESO_BASICO = 5;
const int PRECIO_QUESO_ESPECIAL = 8;
const int PRECIO_NADA = 0;
const int PRECIO_RB = 7;
const int PRECIO_ATUN = 9;
const int PRECIO_POLLO = 5;
const int PRECIO_SOJA = 3;


//PRE: Recibir una respuesta valida entre 15 y 30
//POST: Retornar si la variable es verdadera o falsa.
bool medida_valida(int medida) {
    return (medida >= 15) && (medida <=30);
}

//PRE:-
//POST: Guarda la respuesta en la variable medida será un valor entre 15 y 30 cm.

void preguntar_medida_del_chambuchito(int* medida) {

    printf("¡BIENVENIDO A CHAMBUCHITO!\n¿De qué medida desea su chambuchito?\nPuede ser desde 15 hasta 30[cms]\n");
    scanf("%i", medida);

    while( medida_valida(*medida) == false ) {
        printf("La respuesta debe ser un numero entre el 15 y el 30\n¿De qué medida desea su chambuchito?\n");
        scanf("%i", medida);
        }
}
//PRE: Recibir una respuesta valida dentro del conjunto {Blanco [B], Integral [I], Avena y Miel [A], Queso y Orégano [Q]}
//POST: Retornar si la variable esta dentro del conjunto o no.
bool tipo_de_pan_valido(char tipo_de_pan) {
    return ((tipo_de_pan == PAN_BLANCO) || (tipo_de_pan ==  PAN_INTEGRAL) || (tipo_de_pan ==  PAN_AVENA_Y_MIEL) || (tipo_de_pan ==  PAN_QUESO_Y_OREGANO));
}

//PRE:-
//POST: Guarda la respuesta en la variable tipo_de_pan. Ese valor estara dentro del conjunto {Blanco [B], Integral [I], Avena y Miel [A], Queso y Orégano [Q]}


void preguntar_tipo_de_pan(char* tipo_de_pan) {

    printf("¿Qué pan desea en su chambuchito?\nMENU:\n-Blanco [B]\n-Integral [I]\n-Avena y Miel [A]\n-Queso y Orégano [Q]\n");
    scanf(" %c", tipo_de_pan);

    while(tipo_de_pan_valido(*tipo_de_pan) == false) {
        printf("Por favor, elija la opción correcta del MENU\n");
        printf("MENU:\n-Blanco [B]\n-Integral [I]\n-Avena y Miel [A]\n-Queso y Orégano [Q]\n");
        scanf(" %c", tipo_de_pan);
        }
}

//PRE: Recibir una respuesta valida dentro del conjunto {Dambo [D], Cheddar [C], Gruyere [G], Sin Queso [S]}
//POST: Retornar si la variable esta dentro del conjunto o no.
bool tipo_de_queso_valido(char tipo_de_queso) {
    return ((tipo_de_queso == DAMBO) || (tipo_de_queso ==  CHEDDAR )|| (tipo_de_queso ==  GRUYERE) || (tipo_de_queso ==  SIN_QUESO));
}

//PRE:-
//POST: Guarda la respuesta en la variable tipo_de_queso.Ese valor estará dentro del conjunto{Dambo [D], Cheddar [C], Gruyere [G], Sin Queso [S]}


void preguntar_tipo_de_queso(char* tipo_de_queso) {

    printf("¿Qué queso querés en tu chambuchito?\nMENU: \n-Dambo [D]\n-Cheddar [C]\n-Gruyere [G]\n-Sin Queso [S]\n");
    scanf(" %c", tipo_de_queso);

    while( tipo_de_queso_valido(*tipo_de_queso) == false) {
        printf("Por favor, elija la opción correcta del MENU\n");
        printf("MENU: \n-Dambo [D]\n-Cheddar [C]\n-Gruyere [G]\n-Sin Queso [S]\n");
        scanf(" %c", tipo_de_queso);
}
}

//PRE: Recibir una respuesta valida dentro del conjunto {Roast Beef [R], Atún [A], Soja [S], Pollito [P], Nada de prote [N]}
//POST: Retornar si la variable esta dentro del conjunto o no.
bool tipo_de_proteina_valido(char tipo_de_proteina) {
    return ((tipo_de_proteina == ROAST_BEEF )|| (tipo_de_proteina ==  SOJA) || (tipo_de_proteina ==  ATUN) || (tipo_de_proteina ==  POLLITO) || (tipo_de_proteina ==  SIN_PROTE));
}

//PRE:-
//POST: Guarda la respuesta en la variable tipo_de_proteina. Ese valor estará dentro del conjunto{Roast Beef [R], Atún [A], Soja [S], Pollito [P], Nada de prote [N]}



void preguntar_tipo_de_proteina(char* tipo_de_proteina) {
    printf("¿Qué proteína querés en tu chambuchito?\n");
    printf("MENU:\n-Roast Beef [R]\n-Atún [A]\n-Soja [S]\n-Pollito [P]\n-Nada de prote [N]\n");
    scanf(" %c", tipo_de_proteina);

    while( tipo_de_proteina_valido(*tipo_de_proteina) == false) {
        printf("Por favor, elija la opción correcta del MENU\n");
        printf("MENU:\n-Roast Beef [R]\n-Atún [A]\n-Soja [S]\n-Pollito [P]\n-Nada de prote [N]\n");
        scanf(" %c", tipo_de_proteina);
}
}

//PRE: La variable tipo_de_proteína debe ser un valor valido dentro del conjunto {Roast Beef , Atún , Soja , Pollito , Nada de prote }
//POST: Guarda la respuesta en la variable temperatura_chambuchit. Estas opciones son S o N dependiendo del tipo de proteina elegido


void preguntar_temperatura(char* temperatura_chambuchito,char* tipo_de_proteina) {
    if (*tipo_de_proteina != ATUN){ 
        printf("¿Deseás tu chambuchito caliente?\n");
        scanf(" %c", temperatura_chambuchito);

    while( (*temperatura_chambuchito != SI) && (*temperatura_chambuchito != NO) ) {
        printf("La respuesta puede ser [S] para sí y [N] para no.\n");
        scanf(" %c", temperatura_chambuchito);
    }
    }
}

//PRE: Medida sera un valor valido dentro el conjunto {[15,30]}.
//POST:  Retornará el costo de la medida acorde al tamaño recibido.

float calcular_precio_de_medida ( int medida) {
    float total_medida =  PRECIO_MEDIDA * (float) medida;
    return total_medida;
}

//PRE:tipo_de_pan va a ser un valor valido del conjunto {BLANCO,INTEGRAL,AVENA_Y_MIEL o QUESO_Y_OREGANO.}
//POST: Retornará el costo del pan acorde al tipo recibido.

int calcular_precio_de_panes (char tipo_de_pan ) {
    int precio_pan;
    if (tipo_de_pan == PAN_BLANCO || tipo_de_pan == PAN_INTEGRAL){
        precio_pan = PRECIO_PAN_BASICO;
    }else{
        precio_pan = PRECIO_PAN_ESPECIAL;
    }
    return precio_pan;
}

//PRE:tipo_de_queso va a ser un valor valido del conjunto{DAMBO,CHEDDAR,GRUYERE o SIN_QUESO}
//POST: Retornará el costo del queso acorde al tipo recibido.

int calcular_precio_de_queso (char tipo_de_queso ) {
    int precio_queso;
    if (tipo_de_queso == DAMBO || tipo_de_queso == CHEDDAR){
        precio_queso = PRECIO_QUESO_BASICO;
    }else if(tipo_de_queso == SIN_QUESO){
        precio_queso = PRECIO_NADA;

    }else {
        precio_queso = PRECIO_QUESO_ESPECIAL;
    }
    return precio_queso;
}

//PRE:tipo_de_proteina va a ser un valor valido del conjunto {ROAST_BEEF,ATUN,POLLITO,SOJA o SIN_PROTE}.
//POST: Retorna el costo de la proteina acorde al tipo recibido.

int calcular_precio_de_proteina (char tipo_de_proteina ) {
    int precio_proteina;
    switch (tipo_de_proteina){
        case 'R':
                precio_proteina = PRECIO_RB;
                break;
        case 'A':
                precio_proteina = PRECIO_ATUN;
                break;
        case 'P':
                precio_proteina = PRECIO_POLLO;
                break;
        case 'S':
                precio_proteina = PRECIO_SOJA;
                break;
        default:
                precio_proteina = PRECIO_NADA;
                break;
        }
    return precio_proteina;
}
//PRE: Las variables a sumar deben estar inicializadas.
//POST:Retornará el valor completo de lo que sale el chambuchito.
float suma_final (float valor_medida,int valor_panes,int valor_queso, int valor_proteina ) {
    float suma_total =  valor_medida * ((float) valor_panes + (float )valor_queso + (float) valor_proteina);
    return suma_total;
}
void mostrar_precio_chambuchito (int total_chambuchito){
    printf("El valor del chambuchito es -%i- . \n", total_chambuchito);
}



void calcular_precio_chambuchito(int *precio){
    int medida = 0;
    char tipo_de_pan = ' ';
    char tipo_de_queso = ' ';
    char tipo_de_proteina = ' ';
    char temperatura_chambuchito = ' ';

    preguntar_medida_del_chambuchito(&medida);
    preguntar_tipo_de_pan(&tipo_de_pan);
    preguntar_tipo_de_queso(&tipo_de_queso);
    preguntar_tipo_de_proteina(&tipo_de_proteina);
    preguntar_temperatura(&temperatura_chambuchito,&tipo_de_proteina);

    float valor_medida =  calcular_precio_de_medida(medida);
    int valor_panes =  calcular_precio_de_panes(tipo_de_pan);
    int valor_queso =  calcular_precio_de_queso(tipo_de_queso);
    int valor_proteina =  calcular_precio_de_proteina(tipo_de_proteina);


    int total_chambuchito = (int) suma_final(valor_medida,valor_panes,valor_queso, valor_proteina);
    *precio = total_chambuchito;
    mostrar_precio_chambuchito(total_chambuchito);
}
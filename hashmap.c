#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    unsigned long position = hash(key,map->capacity);
    unsigned long orPosition = position;

    while (map->buckets[position] != NULL && (map->buckets[position]->key != NULL)) {
        // Verificar si la clave ya existe en la casilla actual
        if (is_equal(map->buckets[position]->key, key))return;
        // Avanzar al siguiente índice 
        position = (position + 1) % map->capacity;
        if (position == orPosition)return;
    }
    
    Pair* nuevoElemento = malloc(sizeof(HashMap));
    map->buckets[position] = nuevoElemento;
    nuevoElemento->value = value;
    nuevoElemento->key = key;
    map->current = position;
    map->size++;
    
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {// Crear mapa
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (map == NULL)exit(EXIT_FAILURE);
    
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;
    map->buckets = (Pair **)malloc(sizeof(Pair *) * capacity);

    if (map->buckets == NULL) {
        // Manejo de errores si no se puede asignar memoria
        free(map); 
        exit(EXIT_FAILURE);
    }
    // Inicializar cada bucket a NULL (lista vacía)
    for (long i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }
    return map;
}

void eraseMap(HashMap * map,  char * key) {  
    Pair *pair = searchMap(map, key);
    if (pair != NULL) {
        pair->key = NULL;
        
        map->size--;
    }
}

Pair * searchMap(HashMap * map,  char * key) {   
    unsigned long position = hash(key, map->capacity);
    unsigned long orPosition = position;

    // Buscar la clave
    while (map->buckets[position] != NULL) {
        if (is_equal(map->buckets[position]->key, key)) {
            map->current = position;
            return map->buckets[position];
        }
        // Avanzar al siguiente índice 
        position = (position + 1) % map->capacity;
        if (position == orPosition)return NULL;
    }

    // La clave no se encontró 
    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}

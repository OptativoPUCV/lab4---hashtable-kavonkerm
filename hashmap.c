#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"
#include <stdbool.h>


typedef struct HashMap HashMap;
int enlarge_called=0;

typedef struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
} HashMap;

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
  //long pos = hash(key,map->capacity);
  
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *map = (HashMap *) malloc(sizeof(HashMap));
  if (map == NULL){
    return NULL;
  }
  map->capacity = capacity;
  map->buckets = (Pair **) calloc(capacity,sizeof(Pair *));
  if (map->buckets == NULL){
    return NULL;
  }
  map->size = 0;
  map->current = -1;
  return map;
}

void eraseMap(HashMap * map,  char * key) {    
  
}

Pair * searchMap(HashMap * map,  char * key) {   
  int aux = hash(key,map->capacity);
  while(true){
    if(map->buckets[aux] == NULL || map->buckets[aux]->key == NULL)
      return NULL;

    if(is_equal(map->buckets[aux]->key , key)){
      map->current = aux;
      return map->buckets[aux];
    }
    else{
      aux++;
      if(aux > map->capacity)
        aux = 0;
    }
  }
  return NULL;
}

Pair * firstMap(HashMap * map) {
  for(long i = 0; i < map->capacity; i++){
    if(*(map->buckets+i) ==  NULL) continue;
    if( (*(map->buckets+i))->key != NULL ){
      map->current = i;
      return *(map->buckets+i);
    }
  }
  return NULL;
}

Pair * nextMap(HashMap * map) {
  for(long it = map->current+1; it < map->capacity; it++){

    if(*(map->buckets+it) ==  NULL) continue;

    if( (*(map->buckets+it))->key != NULL ){
      map->current = it;
      return *(map->buckets+it);
    }
  }
  return NULL;
}

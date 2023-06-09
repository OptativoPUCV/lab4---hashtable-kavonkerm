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
  long pos = hash(key,map->capacity);
  if( *(map->buckets+pos) == NULL){
    *(map->buckets+pos) = createPair(key, value);
  }else{
    for(long i = 0, it = pos+1; i < map->capacity; i++, it++){
      it = it%map->capacity;
      if(*(map->buckets+it) ==  NULL){
        *(map->buckets+it) = createPair(key, value);
        break;
      } else if((*(map->buckets+it))->key == NULL){
        *(map->buckets+it) = createPair(key, value);
        break;
      }
    }
  }
  map->size++;
  
}

void enlarge(HashMap * map) {
  enlarge_called = 1; //no borrar (testing purposes)
  map->capacity*=2;
  Pair** oldBuckets = map->buckets; 
  map->buckets = (Pair**) calloc(map->capacity, sizeof(Pair));
  map->size = 0;
  for(long it = 0; it < map->capacity/2; it++){
    if(*(oldBuckets+it) ==  NULL) continue;
    insertMap(map, (*(oldBuckets+it))->key, (*(oldBuckets+it))->value ); 
  }
}


HashMap * createMap(long capacity) {
  HashMap *mapa = (HashMap *) malloc(sizeof(HashMap));
  if (mapa == NULL){
    return NULL;
  }
  mapa->capacity = capacity;
  mapa->buckets = (Pair **) calloc(capacity,sizeof(Pair *));
  if (mapa->buckets == NULL){
    return NULL;
  }
  mapa->size = 0;
  mapa->current = -1;
  return mapa;
}

void eraseMap(HashMap * map,  char * key) {    
  long pos = hash(key, map->capacity);

  if(is_equal(key, (*(map->buckets+pos))->key)){
    map->current =  pos;
    (*(map->buckets+pos))->key = NULL;
  }else{
    for(long i = 0, j = pos+1; i < map->capacity; i++, j++){
      j = j % map->capacity;

      if(*(map->buckets+j) ==  NULL) continue;
      
      if(is_equal(key, (*(map->buckets+j))->key)){
        map->current = j;
        (*(map->buckets+j))->key = NULL;
      }
    }
  }
  if(map->size > 0) map->size--;
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

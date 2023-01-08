#if !defined(PoulpiHashMap)
#define PoulpiHashMap


#include "hashSet.h"
struct pair
{
    void* key;
    void* value;
}
typedef map_pair_t;

struct hashMap_fields{
    P_hashSet_t* table;
};
struct hashMap_methods{
};

struct hashMap
{
    struct hashMap_fields fields;
    struct hashMap_methods methods;
}
typedef P_hashMap_t;

typedef int (*compType)(void*,void*);
typedef void (*freeType)(void*);
typedef void (*printType)(void*);
typedef size_t (*hashType)(void*);
// GLOBAL VARIABLE
compType userCompare = NULL;
freeType userFree_key = NULL;
freeType userFree_value = NULL;
hashType userHash = NULL;
printType userPrint_key = NULL;
printType userPrint_value = NULL;

int comparePair(void* pair1_,void* pair2_){
    map_pair_t* pair1 = (map_pair_t*)pair1_, *pair2 = (map_pair_t*)pair2_;
    assert(userCompare != NULL);
    return userCompare(pair1->key,pair2->key);
}


size_t hashPair(void* pair_){
    map_pair_t* pair = (map_pair_t*)pair_;
    assert(userHash != NULL);
    return userHash(pair->key);
}

void freePair(void* pair_){
    map_pair_t* pair = (map_pair_t*)pair_;
    if (userFree_key != NULL)
        userFree_key(pair->key);
    if (userFree_value != NULL)
        userFree_value(pair->value);
    free(pair);
}

void printPair(void* pair_){
    map_pair_t* pair = (map_pair_t*)pair_;
    printf("\"");
    if (userPrint_key != NULL)
        userPrint_key(pair->key);
    printf("\" : '");
    if (userPrint_value != NULL)
        userPrint_value(pair->value);
    printf("'");
}

P_hashMap_t* hashMap_create(
    void (*freeKey)(void*),
    void (*printKey)(void*),
    void (*freeValue)(void*),
    void (*printValue)(void*),
    size_t (*hashFunction)(void*),
    int (*compareFunction)(void*,void*),
    size_t cap)
{
    userCompare = compareFunction;
    userFree_key = freeKey;
    userFree_value = freeValue;
    userHash = hashFunction;
    userPrint_key = printKey;
    userPrint_value = printValue;

    P_hashMap_t* hashMap = (P_hashMap_t*) malloc(sizeof(P_hashMap_t));
    hashMap->fields.table = hashSet_create(freePair,printPair,hashPair,comparePair,cap);
    return hashMap;
}
void hashMap_put(P_hashMap_t* hashMap,void* key,void* value){
    map_pair_t* pair = (map_pair_t*) malloc(sizeof(map_pair_t));
    pair->key = key;
    pair->value = value;
    hashSet_insert(hashMap->fields.table,pair);
}

void hashMap_print(P_hashMap_t* hashMap){
    hashSet_print(hashMap->fields.table);
}

void hashMap_destroy(P_hashMap_t* hashMap){
    hashSet_destroy(hashMap->fields.table);
    free(hashMap);
}

#endif // PoulpiHashMap
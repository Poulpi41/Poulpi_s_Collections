#if !defined(PoulpiHashSet)
#define PoulpiHashSet

#include "vector.h"
#include <stdbool.h>
#include <assert.h>
#include <string.h>
struct hashSet_fields{
    P_vector_t* table;
    size_t numberOfCollisions;
    size_t numberOfElements;
};
struct hashSet_methods{
    size_t (*hashFunction)(void*);
    int (*compareFunction)(void*,void*);
};
struct hashSet_container
{
    struct hashSet_fields fields;
    struct hashSet_methods methods;
}
typedef P_hashSet_t;


void vector_destroyWrap(void* elem){
    vector_destroy((P_vector_t*)elem);
}
void vector_printWrap(void* elem){
    vector_print_((P_vector_t*)elem,"[ "," , "," ]");
}

void integrityCheck(size_t cap, P_hashSet_t* hashSet){
    assert(hashSet->fields.table->fields.size == cap);
    assert(hashSet->fields.table->fields.capacity != 0);
    assert(hashSet->fields.table->fields.datas != NULL);
    for (size_t i = 0; i < cap; i++)
    {
        assert(hashSet->fields.table->fields.datas[i] != NULL);
    }
}



P_hashSet_t* hashSet_create(
    void (*freeElem)(void*),
    void (*printElem)(void*),
    size_t (*hashFunction)(void*),
    int (*compareFunction)(void*,void*),
    size_t cap)
{
    P_hashSet_t* hashSet = (P_hashSet_t*) malloc(sizeof(P_hashSet_t));
    hashSet->fields.numberOfCollisions = 0;
    hashSet->fields.numberOfElements = 0;
    hashSet->fields.table = vector_create(cap,vector_destroyWrap,vector_printWrap);
    hashSet->methods.hashFunction = hashFunction;
    hashSet->methods.compareFunction = compareFunction;
    for (size_t i = 0; i < cap; i++)
    {
        vector_pushBack(hashSet->fields.table,vector_create(2,freeElem,printElem));
    }
    integrityCheck(cap,hashSet);
    return hashSet;
}

P_vector_t* hashSet_listAll(P_hashSet_t* hashSet){
    P_vector_t* first = (P_vector_t*)vector_get(hashSet->fields.table,0);
    typedef void (printType)(void*);
    printType* printElem = first->methods.printElem;
    P_vector_t* list = vector_create(hashSet->fields.numberOfElements,NULL,printElem);
    for (size_t i = 0; i < hashSet->fields.table->fields.size; i++)
    {
        P_vector_t* bucket = (P_vector_t*)vector_get(hashSet->fields.table,i);
        vector_addAll(list,bucket);
    }
    return list;
}

void hashSet_print_(P_hashSet_t* hashSet){    
    vector_print_(hashSet->fields.table,"{\n\t","\n\t","\n}\n");
}
void hashSet_print(P_hashSet_t* hashSet){
    P_vector_t* list = hashSet_listAll(hashSet);
    vector_print_(list,"{ "," , "," }\n");
    vector_destroy(list);
}
bool hashSet_exist(P_hashSet_t* hashSet,void* elem){
    size_t hash = hashSet->methods.hashFunction(elem);
    size_t index = hash % hashSet->fields.table->fields.capacity;
    P_vector_t* bucket = (P_vector_t*)vector_get(hashSet->fields.table,index);

    for (size_t i = 0; i < bucket->fields.size; i++)
    {
        //assert(bucket->fields.datas[i] != NULL);
        if (hashSet->methods.compareFunction(elem,&bucket->fields.datas[i]) == 0){
            return true;
        }
    }
    return false;
}


void hashSet_insert(P_hashSet_t* hashSet,void* elem);
void hashSet_destroy(P_hashSet_t* hashSet);
void rehash(P_hashSet_t* hashSet){
    void* arrayOfElement[hashSet->fields.numberOfElements];
    memset(arrayOfElement,0,sizeof(void*)*hashSet->fields.numberOfElements);
    size_t counter = 0;
    for (size_t i = 0; i < hashSet->fields.table->fields.capacity; i++)
    {
        P_vector_t* bucket = (P_vector_t*)vector_get(hashSet->fields.table,i);
        for (size_t j = 0; j < bucket->fields.size; j++)
        {
            void* elem = vector_get(bucket,j);
            //assert(elem != NULL);
            if (elem != NULL)
                memmove(arrayOfElement+counter,&elem,sizeof(void*));
            //bucket->methods.freeElem(elem);
            vector_set(bucket,j,NULL);
            counter++;
        }
        bucket->fields.size = 0;
        vector_setCap(bucket,2);
    }
    P_vector_t* first = (P_vector_t*)vector_get(hashSet->fields.table,0);
    // while (hashSet->fields.table->fields.size > 0)
    // {
    //     vector_popBack(hashSet->fields.table);
    // }
    hashSet->fields.numberOfCollisions = 0;
    size_t newCap = hashSet->fields.table->fields.capacity,tmp_num = hashSet->fields.numberOfElements;
    hashSet->fields.numberOfElements = 0;
    for (size_t i = 0; i < newCap; i++)
    {
        vector_pushBack(hashSet->fields.table,vector_create(2,first->methods.freeElem,first->methods.printElem));
    }

    for (size_t i = 0; i < tmp_num; i++)
    {
        //assert(arrayOfElement[i] != NULL);
        hashSet_insert(hashSet,arrayOfElement[i]);
    }
    // printf("\n");
    // hashSet_print(hashSet);
    // printf("\n");
}


void hashSet_insert(P_hashSet_t* hashSet, void* toInsert){
    size_t index = hashSet->methods.hashFunction(toInsert) % hashSet->fields.table->fields.capacity;
    P_vector_t* bucket = (P_vector_t*)vector_get(hashSet->fields.table,index);
    if (bucket->fields.size == 0){
        vector_pushBack(bucket,toInsert);
        hashSet->fields.numberOfElements++;
    }
    else{
        if (hashSet_exist(hashSet,toInsert)){
            return;
        }
        vector_pushBack(bucket,toInsert);
        hashSet->fields.numberOfCollisions++;
        hashSet->fields.numberOfElements++;
        if (hashSet->fields.numberOfCollisions > hashSet->fields.numberOfElements/2){
            rehash(hashSet);
        }
        //integrityCheck(hashSet->fields.table->fields.capacity,hashSet);
    }
}
void hashSet_remove(P_hashSet_t* hashSet, void* toRemove){
    size_t index = hashSet->methods.hashFunction(toRemove) % hashSet->fields.table->fields.capacity;
    P_vector_t* bucket = (P_vector_t*)vector_get(hashSet->fields.table,index);
    for (size_t i = 0; i < bucket->fields.size; i++)
    {
        if (hashSet->methods.compareFunction(toRemove,&bucket->fields.datas[i]) == 0){
            vector_remove(bucket,i);
            hashSet->fields.numberOfElements--;
            return;
        }
    }
}
void hashSet_destroy(P_hashSet_t* hashSet){
    vector_destroy(hashSet->fields.table);
    free(hashSet);
}

#endif // PoulpiHashSet

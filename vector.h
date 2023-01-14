#if !defined(PoulpiVector)
#define PoulpiVector

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
struct vector_fields
{
    void** datas;
    size_t size,capacity;
};
struct vector_methods
{
    void (*freeElem)(void*);
    void (*printElem)(void*);
};
struct vector_container
{
    struct vector_fields fields;
    struct vector_methods methods;
}
typedef P_vector_t;

P_vector_t* vector_create(
    size_t capacity,
    void (*freeElem)(void*),
    void (*printElem)(void*))
{
    P_vector_t* vector = (P_vector_t*) malloc(sizeof(P_vector_t));
    vector->fields.datas = (void**)malloc(capacity*sizeof(void*));
    vector->fields.size = 0;
    vector->fields.capacity = capacity;
    vector->methods.freeElem = freeElem;
    vector->methods.printElem = printElem;
    return vector;
}
void vector_pushBack(P_vector_t* vec, void* data){
    if(vec->fields.size == vec->fields.capacity){
        vec->fields.capacity *= 2;
        vec->fields.datas = (void**)realloc(vec->fields.datas, vec->fields.capacity*sizeof(void*));
    }
    vec->fields.datas[vec->fields.size] = data;
    vec->fields.size++;
}
void vector_print_(P_vector_t* vec,char* beg,char* sep,char* end){
    printf("%s",beg);
    if (vec->fields.size > 0){
        if (vec->methods.printElem != NULL)
            vec->methods.printElem(vec->fields.datas[0]);
    }
    if (vec->methods.printElem != NULL)
        for(size_t i = 1; i < vec->fields.size; i++){
            printf("%s",sep);
            vec->methods.printElem(vec->fields.datas[i]);
        }
    printf("%s",end);
}
void vector_print(P_vector_t* vec){
    vector_print_(vec,"[ "," , "," ]\n");
}
void vector_addAll(P_vector_t* dest, P_vector_t* source){
    for (size_t i = 0; i < source->fields.size; i++)
    {
        vector_pushBack(dest,source->fields.datas[i]);
    }
}

P_vector_t* listAll(P_vector_t* vec){
    return vec;
}

void* vector_get(P_vector_t* vec, size_t index){
    if (index >= vec->fields.size)
        return NULL;
    return vec->fields.datas[index];
}
void vector_set(P_vector_t* vec, size_t index, void* data){
    assert(index < vec->fields.size);
    vec->fields.datas[index] = data;
}
void vector_popBack(P_vector_t* vec){
    assert(vec->fields.size > 0);
    if (vec->methods.freeElem != NULL)
        vec->methods.freeElem(vector_get(vec,vec->fields.size-1));
    vec->fields.size--;
}
void vector_remove(P_vector_t* vec, size_t index){
    assert(index < vec->fields.size);
    if (vec->methods.freeElem != NULL)
        vec->methods.freeElem(vector_get(vec,index));
    for(size_t i = index; i < vec->fields.size-1; i++)
        vec->fields.datas[i] = vec->fields.datas[i+1];
    vec->fields.size--;
}

void vector_setCap(P_vector_t* vec, size_t capacity){
    vec->fields.capacity = capacity;
    vec->fields.datas = (void**)realloc(vec->fields.datas, vec->fields.capacity*sizeof(void*));
    if (vec->fields.size > vec->fields.capacity)
        vec->fields.size = vec->fields.capacity;
}

void vector_destroy(P_vector_t* vec){
    if (vec->methods.freeElem != NULL)
        for(size_t i = 0; i < vec->fields.size; i++)
            vec->methods.freeElem(vec->fields.datas[i]);
    free(vec->fields.datas);
    free(vec);
}

#endif // PoulpiVector

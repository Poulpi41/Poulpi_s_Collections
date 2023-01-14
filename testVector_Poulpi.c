#include "vector.h"

struct I
{
    int i;
};
struct I* createI(int val){
    struct I* i = (struct I*)malloc(sizeof(struct I));
    i->i = val;
    return i;
}
void printElem(void *elem){
    printf("%d",((struct I*)elem)->i);
}
int main(int argc, char const *argv[])
{
    P_vector_t *v = vector_create(8,free,printElem);
    vector_pushBack(v,createI(1));
    vector_pushBack(v,createI(2));
    vector_pushBack(v,createI(3));
    vector_pushBack(v,createI(4));
    vector_pushBack(v,createI(5));
    vector_pushBack(v,createI(6));
    vector_pushBack(v,createI(7));
    vector_pushBack(v,createI(8));
    vector_pushBack(v,createI(9));
    vector_pushBack(v,createI(10));
    vector_pushBack(v,createI(11));
    vector_remove(v,3);
    vector_print(v);
    vector_destroy(v);
    return 0;
}

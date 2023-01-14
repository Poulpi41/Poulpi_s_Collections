#include "hashSet.h"
#include <string.h>
char* numbersStr[] = {
    "zero","one","two","three","four","five","six","seven","eight","nine",
    "ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen",
    "twenty","twenty-one","twenty-two","twenty-three","twenty-four","twenty-five","twenty-six","twenty-seven","twenty-eight","twenty-nine",
    "thirty","thirty-one","thirty-two","thirty-three","thirty-four","thirty-five","thirty-six","thirty-seven","thirty-eight","thirty-nine",
    "forty","forty-one","forty-two","forty-three","forty-four","forty-five","forty-six","forty-seven","forty-eight","forty-nine",
    "fifty","fifty-one","fifty-two","fifty-three","fifty-four","fifty-five","fifty-six","fifty-seven","fifty-eight","fifty-nine",
    "sixty","sixty-one","sixty-two","sixty-three","sixty-four","sixty-five","sixty-six","sixty-seven","sixty-eight","sixty-nine",
    "seventy","seventy-one","seventy-two","seventy-three","seventy-four","seventy-five","seventy-six","seventy-seven","seventy-eight","seventy-nine",
    "eighty","eighty-one","eighty-two","eighty-three","eighty-four","eighty-five","eighty-six","eighty-seven","eighty-eight","eighty-nine",
    "ninety","ninety-one","ninety-two","ninety-three","ninety-four","ninety-five","ninety-six","ninety-seven","ninety-eight","ninety-nine",
    "hundred","hundred-one","hundred-two","hundred-three","hundred-four","hundred-five","hundred-six","hundred-seven","hundred-eight","hundred-nine",
    "hundred-ten","hundred-eleven","hundred-twelve","hundred-thirteen","hundred-fourteen","hundred-fifteen","hundred-sixteen","hundred-seventeen","hundred-eighteen","hundred-nineteen"
};

/**
 * @brief djb2 algorith excelent with strings
 * 
 * @param elem a string
 * @return size_t the hash for the given element
 */
size_t djb2(void* elem){
    char *str = (char*)elem;
    size_t hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;

}

void printStr(void *str_){
    char *str = (char*)str_;
    printf("%s",str);
}
void* createStr(char* str){
    char *newStr = (char*)malloc(strlen(str)+1);
    strcpy(newStr,str);
    return newStr;
}
int wrapCmp(void* a,void* b){
    return strcmp((const char*)a,(const char*)b);
}

int main(int argc, char const *argv[])
{
    P_hashSet_t* hashSet = hashSet_create(free,printStr,djb2,wrapCmp,8);
    hashSet_print_(hashSet);
    for (size_t i = 0; i < 16; i++)
    {
        hashSet_insert(hashSet,(void*)createStr(numbersStr[i]));
        hashSet_print_(hashSet);
    }
    printf("\n");
    hashSet_destroy(hashSet);
    return 0;
}

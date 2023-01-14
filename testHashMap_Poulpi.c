#include "hashMap.h"

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
int numbers[] = {
    0,1,2,3,4,5,6,7,8,9,
    10,11,12,13,14,15,16,17,18,19,
    20,21,22,23,24,25,26,27,28,29,
    30,31,32,33,34,35,36,37,38,39,
    40,41,42,43,44,45,46,47,48,49,
    50,51,52,53,54,55,56,57,58,59,
    60,61,62,63,64,65,66,67,68,69,
    70,71,72,73,74,75,76,77,78,79,
    80,81,82,83,84,85,86,87,88,89,
    90,91,92,93,94,95,96,97,98,99,
    100,101,102,103,104,105,106,107,108,109,
    110,111,112,113,114,115,116,117,118,119
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
void printInt(void *num_){
    int *num = (int*)num_;
    printf("%d",*num);
}
int wrapCmp(void* a,void* b){
    return strcmp((char*)a,(char*)b);
}
int main(int argc, char const *argv[])
{
    P_hashMap_t* map = hashMap_create(NULL,printStr,NULL,printInt,djb2,wrapCmp,8);
    for (size_t i = 0; i < 120; i++)
    {
        hashMap_put(map,numbersStr[i],&numbers[i]);
    }
    

    hashMap_print(map);
    hashMap_destroy(map);
    return 0;
}

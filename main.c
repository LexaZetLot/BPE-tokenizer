#include "BPE.h"
#define SIZE_TABLE 20

int main(int arhc, char** argv){
    char* path = "/home/lexa/Desktop/text/";
    char** file = arrFullPathFile(path);
    int len = lenFilesPath(path);
    struct ListTextASCII* listTextASCII = fabricListTextASCII();   
    struct HashTable* hashTable = fabricHashTable(SIZE_TABLE);
      
    printf("%d\n", len);
    for(int i = 0; i < len; i++)
        printf("%s\n", file[i]); 

    fillingListTextASCII(path, listTextASCII);
    
    printListTextASCII(listTextASCII);
    
    printf("%lu\n", SimpleCityHash64cons("ll", 2, 15));
    printf("%lu\n", SimpleCityHash64cons("le", 2, 15));
    printf("%lu\n", SimpleCityHash64cons("hp", 2, 15));
    
    fillingHashTable(listTextASCII, hashTable, SIZE_TABLE);    
    printHashTable(hashTable, SIZE_TABLE);
    
    printf("token -> %s\n", getMaxStrToHashTable(hashTable));
    return 0;
}

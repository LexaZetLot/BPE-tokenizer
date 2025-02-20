#include "BPE.h"

void parserSetToFile(struct Set* set, size_t sizeHashTable){
    FILE* fp = fopen("tokin.txt", "w");
    size_t numerTokens = 0;
    
    for(int i = 0; i < sizeHashTable; i++){
        struct NodeSet* nodeSet = set->table[i];
        while(nodeSet != NULL){
            fprintf(fp, "token %lu -> %s\n", numerTokens, nodeSet->str);
            numerTokens++;
            nodeSet = nodeSet->next;
        }
    }
}

void bytePairEncodingTokinazer(char* path, size_t sizeTable, size_t num){
    struct ListTextASCII* listTextASCII = fabricListTextASCII();
    struct HashTable* hashTable;
    struct Set* set;
    size_t numTokens;
    char ch;

    fillingListTextASCII(path, listTextASCII);
    do{
        hashTable = fabricHashTable(sizeTable);
        set = fabricSet(sizeTable);

        fillingHashTable(listTextASCII, hashTable, sizeTable);
        if(getMaxStrToHashTable(hashTable) == NULL){
            fillingSet(listTextASCII, set, sizeTable);
            freeHashTable(hashTable, sizeTable);
            break;
        }
        mergeListTextASCII(listTextASCII, getMaxStrToHashTable(hashTable));
         
        fillingSet(listTextASCII, set, sizeTable);
        numTokens = getNumTokens(set);
        
        printf("tokens -> %lu\n", numTokens);
        
        freeHashTable(hashTable, sizeTable);
        if(numTokens == num)
            break;
        else
            freeSet(set, sizeTable);
    }while(numTokens != num); 
    freeListTextASCII(listTextASCII);
    parserSetToFile(set, sizeTable);
    freeSet(set, sizeTable);
}

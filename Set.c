#include "BPE.h"

struct Set* fabricSet(size_t sizeHashTable){
    struct Set* set = (struct Set*)malloc(sizeof(struct Set));
    set->table = (struct NodeSet**)calloc(sizeHashTable, sizeof(struct NodeSet*));
    set->numTockens = 0;    

    return set;
}

void fillingSet(struct ListTextASCII* listTextASCII, struct Set* set, size_t sizeHashTable){
    struct ListTextASCII* listTextASCIIBuf = listTextASCII;
    struct Set* setBuf = set;
    struct NodeSet* nodeSet;
    uint64_t indexHashTable = 0;

    while(listTextASCIIBuf != NULL){
        indexHashTable = SimpleCityHash64cons(listTextASCIIBuf->str, strlen(listTextASCIIBuf->str), sizeHashTable);
        
        nodeSet = setBuf->table[indexHashTable];
        while(nodeSet != NULL){
            if(!strcasecmp(listTextASCIIBuf->str, nodeSet->str))
                break;
            nodeSet = nodeSet->next;            
        }

        if(nodeSet == NULL){
            nodeSet = (struct NodeSet*)malloc(sizeof(struct NodeSet));
            nodeSet->str = strdup(listTextASCIIBuf->str);
            nodeSet->next = setBuf->table[indexHashTable];
            setBuf->table[indexHashTable] = nodeSet;
            
            setBuf->numTockens++;
            
        }
    
        listTextASCIIBuf = listTextASCIIBuf->listNext;
    }
}

void printSet(struct Set* set, size_t sizeHashTable){
    struct Set* setBuf = set;
    struct NodeSet* nodeSet;

    for(int i = 0; i < sizeHashTable; i++){
        printf("%d ", i);
        if(setBuf->table[i] == NULL)
            printf("NULL");
        else{
            nodeSet = setBuf->table[i];
            while(nodeSet != NULL){
                printf("{str->%s}", nodeSet->str);
                nodeSet = nodeSet->next;
            }
        }
        printf("\n");
    }
}

size_t getNumTokens(struct Set* set){
    return set->numTockens;
}

void freeListSet(struct NodeSet* node){
    while(node){
        struct NodeSet* temp = node;
        node = node->next;
        free(temp->str);
        free(temp);
    }
}

void freeSet(struct Set* set, size_t sizeHashTable){
    for(int i = 0; i < sizeHashTable; i++)
        freeListSet(set->table[i]);
    free(set->table);
    free(set);
}

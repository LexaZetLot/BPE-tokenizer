#include "BPE.h" 

struct HashTable* fabricHashTable(size_t sizeHashTable){
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));    
    hashTable->table = (struct Node**)malloc(sizeHashTable * sizeof(struct Node*));
    hashTable->maxNode = 0;
    hashTable->maxStr = NULL;
        
    for(int i = 0; i < sizeHashTable; i++){
        hashTable->table[i] = (struct Node*)malloc(sizeof(struct Node));
        hashTable->table[i]->key = NULL;
        hashTable->table[i]->count = 0;
        hashTable->table[i]->next = NULL;
    }
    return hashTable;
}

struct Node* fabricNode(){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->key = NULL;
    node->count = 0;
    node->next = NULL;
    
    return node;
}

void insertNode(struct Node* nodeTable, char* str, struct HashTable* hashTable){
    struct Node* node = nodeTable;
    while(node->next != NULL){
        if(!(strcasecmp(node->key, str))){
            node->count++;
            break;    
        }  
        node = node->next;
    }
    if(node->next == NULL){
        if(!(strcasecmp(node->key, str)))
            node->count++;
        else {
            node->next = fabricNode();
            node->next->key = str;
            node->next->count = 1;
        }
    }       
    if(node->count > hashTable->maxNode){
        hashTable->maxStr = node->key;
        hashTable->maxNode = node->count;
    }
 
}

void fillingHashTable(struct ListTextASCII* listTextASCII, struct HashTable* hashTable, size_t sizeHashTable){
    struct ListTextASCII* listTextASCIIBuf = listTextASCII;
    struct HashTable* hashTableBuf = hashTable;    
    char* one = NULL;
    int count = 0;
    
    while(listTextASCIIBuf != NULL){
        
        if((listTextASCIIBuf->listNext != NULL) && 
            isalpha(listTextASCIIBuf->str[0]) &&
            isalpha(listTextASCIIBuf->listNext->str[0])){
            
            char* buf = (char*)malloc((strlen(listTextASCIIBuf->str) + 
                                       strlen(listTextASCIIBuf->listNext->str) + 1) * 
                                       sizeof(char));
            strcpy(buf, listTextASCIIBuf->str);
            strcat(buf, listTextASCIIBuf->listNext->str);
            
            uint64_t indexHashTable = SimpleCityHash64cons(buf, strlen(buf), sizeHashTable); 
            
            if(hashTableBuf->table[indexHashTable]->key == NULL){
                hashTableBuf->table[indexHashTable]->key = buf;
                hashTableBuf->table[indexHashTable]->count++;
                if(hashTableBuf->table[indexHashTable]->count > hashTableBuf->maxNode){
                        hashTableBuf->maxStr = hashTableBuf->table[indexHashTable]->key;
                        hashTableBuf->maxNode = hashTableBuf->table[indexHashTable]->count;
                }

            } else{
                if(!(strcasecmp(hashTableBuf->table[indexHashTable]->key, buf))){
                    hashTableBuf->table[indexHashTable]->count += 1;
                    if(hashTableBuf->table[indexHashTable]->count > hashTableBuf->maxNode){
                        hashTableBuf->maxStr = hashTableBuf->table[indexHashTable]->key;
                        hashTableBuf->maxNode = hashTableBuf->table[indexHashTable]->count;
                    }
                    free(buf);
                } else{
                    insertNode(hashTableBuf->table[indexHashTable], buf, hashTableBuf); 
                }
            }    
        }
        
    listTextASCIIBuf = listTextASCIIBuf->listNext;
    }
}

void printHashTable(struct HashTable* hashTable, size_t sizeHashTable){
    struct HashTable* hashTableBuf = hashTable;    
    struct Node* node;    

    for(int i = 0; i < sizeHashTable; i++){
        printf("%d ", i);
        node = hashTableBuf->table[i];
        while(node != NULL){
            printf("{key->%s count->%lu}", node->key, node->count);
            node = node->next;    
        }
        printf("\n");
    }
    printf("maxNode -> %lu maxStr -> %s\n", hashTableBuf->maxNode, hashTableBuf->maxStr);
}  

char* getMaxStrToHashTable(struct HashTable* hashTable){
    char* str = (char*)malloc((strlen(hashTable->maxStr) + 1) * sizeof(char));
    strcpy(str, hashTable->maxStr);
    return str;
}

void freeHashTable(struct HashTable* hashTable, size_t sizeHashTable){
    for(int i = 0; i < sizeHashTable; i++){
        struct Node* node = hashTable->table[i];
        struct Node* buf;
        while(node != NULL){
            buf = node->next;
            free(node->key);
            free(node);
            node = buf;
        }
    }
 
    free(hashTable->table);
    free(hashTable);
} 

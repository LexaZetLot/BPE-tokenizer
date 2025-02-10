#include "BPE.h"

#define BIG_CONSTANT(x) (x##ULL) 

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

uint64_t RotateRight(uint64_t value, int shift){
    return (value >> shift) | (value << (64 - shift));
}

uint64_t Mix(uint64_t a, uint64_t b){
    a ^= RotateRight(b, 37);
    a *= BIG_CONSTANT(0x9ddfea08eb382d69);
    b ^= RotateRight(a, 27);
    b *= BIG_CONSTANT(0xc6a4a7935bd1e995);
    return a ^ b;
}

uint64_t SimpleCityHash64cons(const char *data, size_t len, size_t sizeHashTable){
    const uint64_t seed = BIG_CONSTANT(0xdeadbeefdeadbeef);
    uint64_t hash = seed ^ len;
    
    const uint64_t *blocks = (const uint64_t *)data;
    size_t num_blocks = len / 8;

    for(int i = 0; i < num_blocks; i++){
        uint64_t k = blocks[i];
        hash = Mix(hash, k);
    }
    
    const uint8_t *tail = (const uint8_t *)(data + num_blocks * 8);
    uint64_t tailValue = 0;
    for (size_t i = 0; i < len % 8; i++) {
        tailValue |= ((uint64_t)tail[i]) << (8 * i);
    }

    hash = Mix(hash, tailValue);
    return hash % sizeHashTable;
}

void insertNode(struct Node* nodeTable, char* str){
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
}

void insertHashTable(struct HashTable* hashTable, size_t indexHashTable ,char* str){
    struct HashTable* hashTableBuf = hashTable;
    if(hashTableBuf->table[indexHashTable]->key == NULL){
        hashTableBuf->table[indexHashTable]->key = str;
        hashTableBuf->table[indexHashTable]->count++;
    } else{
        if(!(strcasecmp(hashTableBuf->table[indexHashTable]->key, str))){
            free(str);
            hashTableBuf->table[indexHashTable]->count++;
        } else
            insertNode(hashTableBuf->table[indexHashTable], str); 
    }
}

void fillingHashTable(struct ListTextASCII* listTextASCII, struct HashTable* hashTable, size_t sizeHashTable){
    struct ListTextASCII* listTextASCIIBuf = listTextASCII;
    struct HashTable* hashTableBuf = hashTable;    
   
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
            } else{
                if(!(strcasecmp(hashTableBuf->table[indexHashTable]->key, buf))){
                    hashTableBuf->table[indexHashTable]->count += 1;
                    if(hashTableBuf->table[indexHashTable]->count > hashTableBuf->maxNode){
                        hashTableBuf->maxStr = hashTableBuf->table[indexHashTable]->key;
                        hashTableBuf->maxNode = hashTableBuf->table[indexHashTable]->count;
                    }
                    free(buf);
                } else{
                    insertNode(hashTableBuf->table[indexHashTable], buf); 
                }
            }
        } else if((listTextASCIIBuf->listNext != NULL) &&
                  isalpha(listTextASCIIBuf->str[0]) && 
                  !isalpha(listTextASCIIBuf->listNext->str[0])){
            char* buf = (char*)malloc((strlen(listTextASCIIBuf->str) + 1) * sizeof(char));
            strcpy(buf, listTextASCIIBuf->str);
            uint64_t indexHashTable = SimpleCityHash64cons(buf, strlen(buf), sizeHashTable);
            
             
            insertHashTable(hashTable, indexHashTable, buf);
            
        } else if((listTextASCIIBuf->listNext != NULL) &&
                   ((!isalpha(listTextASCIIBuf->str[0]) &&
                   isalpha(listTextASCIIBuf->listNext->str[0])) || 
                   (!isalpha(listTextASCIIBuf->str[0]) &&
                   !isalpha(listTextASCIIBuf->listNext->str[0])))){
            char* buf = (char*)malloc((strlen(listTextASCIIBuf->str) + 1) * sizeof(char));
            
            strcpy(buf, listTextASCIIBuf->str);
            
            uint64_t indexHashTable = SimpleCityHash64cons(buf, strlen(buf), sizeHashTable);
            
            insertHashTable(hashTable, indexHashTable, buf);
        } else{
            char* buf = (char*)malloc((strlen(listTextASCIIBuf->str) + 1) * sizeof(char));
            strcpy(buf, listTextASCIIBuf->str);
            uint64_t indexHashTable = SimpleCityHash64cons(buf, strlen(buf), sizeHashTable);
            
            insertHashTable(hashTable, indexHashTable, buf);
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

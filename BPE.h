#ifndef BPE
#define BPE

#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <ctype.h>
#include <strings.h>

struct ListTextASCII{
    struct ListTextASCII* listNext;
    char* str;
};


struct Node{
    char* key;
    size_t count;
    struct Node* next;
};

struct HashTable{
    struct Node **table;
    size_t maxNode;
    char* maxStr;
};


size_t lenFilesPath(char* path);
char** arrFullPathFile(char* path);
void freeListPath(char** listPath, size_t len);
void initializationStr(char** str, int ch);


struct ListTextASCII* fabricListTextASCII(void);
void fillingListTextASCII(char* path, struct ListTextASCII* listTextASCII);
void printListTextASCII(struct ListTextASCII* listTextASCII);


struct HashTable* fabricHashTable(size_t sizeHashTable);
struct Node* fabricNode();
uint64_t RotateRight(uint64_t value, int shift);
uint64_t Mix(uint64_t a, uint64_t b);
uint64_t SimpleCityHash64cons(const char *data, size_t len, size_t sizeHashTable);
void insertNode(struct Node* nodeTable, char* str);
void insertHashTable(struct HashTable* hashTable, size_t indexHashTable ,char* str);
void fillingHashTable(struct ListTextASCII* listTextASCII, struct HashTable* hashTable, size_t sizeHashTable);
void printHashTable(struct HashTable* hashTable, size_t sizeHashTable);
char* getMaxStrToHashTable(struct HashTable* hashTable);
#endif

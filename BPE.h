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


struct NodeSet{
    char* str;
    struct NodeSet* next;
};

struct Set{
    struct NodeSet **table;
    size_t numTockens;
};


size_t lenFilesPath(char* path);
char** arrFullPathFile(char* path);
void freeListPath(char** listPath, size_t len);
void initializationStr(char** str, int ch);
char* stringСoncantation(const char* const str1, const char* const str2);


struct ListTextASCII* fabricListTextASCII(void);
void fillingListTextASCII(char* path, struct ListTextASCII* listTextASCII);
void printListTextASCII(struct ListTextASCII* listTextASCII);
void freeListNode(struct ListTextASCII* listTextASCII);
void mergeListTextASCII(struct ListTextASCII* listTextASCII, char* str);
void freeListTextASCII(struct ListTextASCII* listTextASCII);


uint64_t RotateRight(uint64_t value, int shift);
uint64_t Mix(uint64_t a, uint64_t b);
uint64_t SimpleCityHash64cons(const char *data, size_t len, size_t sizeHashTable);


struct HashTable* fabricHashTable(size_t sizeHashTable);
struct Node* fabricNode();
void insertNode(struct Node* nodeTable, char* str, struct HashTable* hashTable);
void fillingHashTable(struct ListTextASCII* listTextASCII, struct HashTable* hashTable, size_t sizeHashTable);
void printHashTable(struct HashTable* hashTable, size_t sizeHashTable);
char* getMaxStrToHashTable(struct HashTable* hashTable);
void freeList(struct Node* node);
void freeHashTable(struct HashTable* hashTable, size_t sizeHashTable);


struct Set* fabricSet(size_t sizeHashTable);
void fillingSet(struct ListTextASCII* listTextASCII, struct Set* set, size_t sizeHashTable);
void printSet(struct Set* set, size_t sizeHashTable);
size_t getNumTokens(struct Set* set);
void freeListSet(struct NodeSet* node);
void freeSet(struct Set* set, size_t sizeHashTable);


void parserSetToFile(struct Set* set, size_t sizeHashTable);
void bytePairEncodingTokinazer(char* path, size_t sizeTable, size_t num);


int utf8CharLength(unsigned char ch);
char* readUtf8Char(FILE* file);
#endif

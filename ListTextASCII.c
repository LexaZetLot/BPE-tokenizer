#include "BPE.h"

struct ListTextASCII* fabricListTextASCII(void){
    struct ListTextASCII* list = (struct ListTextASCII*)malloc(sizeof(struct ListTextASCII));
    list->listNext = NULL;    
    list->str = NULL;

    return list;
}

void fillingListTextASCII(char* path, struct ListTextASCII* listTextASCII){
    FILE* fp;
    char** listPath = arrFullPathFile(path);
    size_t len = lenFilesPath(path);
    
    struct ListTextASCII* listTextASCIIBuf = listTextASCII;
    int ch = 0;    

    for(int i = 0; i < len; i++){
        fp = fopen(listPath[i], "r");
        if(fp == NULL)
            freeListPath(listPath, len);
        
        if((i == 0) && ((ch = fgetc(fp)) != EOF))
            initializationStr(&listTextASCIIBuf->str, ch);  
        

        while((ch = fgetc(fp)) != EOF){
            listTextASCIIBuf->listNext = fabricListTextASCII();
            listTextASCIIBuf->listNext->listNext = NULL;
            listTextASCIIBuf->listNext->str = NULL;

            listTextASCIIBuf = listTextASCIIBuf->listNext;
            initializationStr(&listTextASCIIBuf->str, ch); 
        }
        fclose(fp);
    }
}

void printListTextASCII(struct ListTextASCII* listTextASCII){
    struct ListTextASCII* listTextASCIIBuf = listTextASCII;
    int i = 0;    
    
    while(listTextASCIIBuf != NULL){
        printf("%d{%s}\n", i, listTextASCIIBuf->str);
        listTextASCIIBuf = listTextASCIIBuf->listNext;
        i++;
    }
}

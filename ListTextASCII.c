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
    freeListPath(listPath, len);
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

void freeListNode(struct ListTextASCII* listTextASCII){
    free(listTextASCII->str);
    free(listTextASCII);
}

void mergeListTextASCII(struct ListTextASCII* listTextASCII, char* str){
    struct ListTextASCII* listTextASCIIBuf = listTextASCII;
    char* bufStr;    

    while(listTextASCIIBuf->listNext != NULL){
        bufStr = stringСoncantation(listTextASCIIBuf->str, listTextASCIIBuf->listNext->str);
        
        if(!strcasecmp(bufStr, str)){
            struct ListTextASCII* buf = listTextASCIIBuf->listNext;
            listTextASCIIBuf->listNext = listTextASCIIBuf->listNext->listNext;
            freeListNode(buf);
            free(listTextASCIIBuf->str);
            listTextASCIIBuf->str = (char*)malloc((strlen(str) + 1) * sizeof(char));
            strcpy(listTextASCIIBuf->str, str);
        }
        
        free(bufStr);
        listTextASCIIBuf = listTextASCIIBuf->listNext;
    }
}

void freeListTextASCII(struct ListTextASCII* listTextASCII){
    struct ListTextASCII* listTextASCIIBuf = listTextASCII;
    struct ListTextASCII* buf;
    while(listTextASCIIBuf != NULL){
        buf = listTextASCIIBuf->listNext;
        freeListNode(listTextASCIIBuf);
        listTextASCIIBuf = buf;
    }

}

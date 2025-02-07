#include "BPE.h"

size_t lenFilesPath(char* path){
    size_t len = 0;
    DIR *dp = opendir(path);
    struct dirent* entry;    
  
    if(dp == NULL)
        return -1;
  
    while((entry = readdir(dp)) != NULL)
        if(entry->d_type == DT_REG)
            len++;
    
    free(dp);
    free(entry);    
    return len;
}

char** arrFullPathFile(char* path){
    DIR *dp = opendir(path);
    struct dirent* entry;    
    size_t lenPath = strlen(path);    

    char** arrStr = (char**)malloc(lenFilesPath(path) * sizeof(char *));
    
    int i = 0;

    if(dp == NULL){
        free(arrStr);
        return NULL;
    }
    if(arrStr == NULL){
        free(dp);
        return NULL;
    }

    while((entry = readdir(dp)) != NULL)
        if(entry->d_type == DT_REG){
            arrStr[i] = (char *)malloc((strlen(entry->d_name) + lenPath + 1) * sizeof(char));
            if(arrStr[i] == NULL){
                free(dp);
                free(entry);
                
                for(int j = 0; j < i; j++)
                    free(arrStr[i]);
                free(arrStr);                

                return NULL;
            }

            strcpy(arrStr[i], path);
            strcat(arrStr[i], entry->d_name);
            i++;
        }    

    return arrStr;
}

void freeListPath(char** listPath, size_t len){
    for(int i = 0; i < len; i++)
        free(listPath[i]);
    free(listPath);
}

void initializationStr(char** str, int ch){
    *str = (char*)malloc(2 * sizeof(char));
    (*str)[0] = (char)ch;
    (*str)[1] = '\0';
}

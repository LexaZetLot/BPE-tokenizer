#include "BPE.h"

int utf8CharLength(unsigned char ch){
    if((ch & 0x80) == 0) return 1;
    if((ch & 0xE0) == 0xC0) return 2;
    if((ch & 0xF0) == 0xE0) return 3;
    if((ch & 0xF8) == 0xF0) return 4;
    
    return -1;
}

char* readUtf8Char(FILE* file){
    int firstByte = fgetc(file);
    if(firstByte == EOF)
        return NULL;

    int len = utf8CharLength((unsigned char)firstByte);
    if(len == -1)
        return NULL;

    char* buffer = (char*)malloc((len + 1) * sizeof(char));
    buffer[0] = (char)firstByte;
    
    int nextByte;
    for(int i = 1; i < len; i++){
        nextByte = fgetc(file);
        if(nextByte == EOF || (nextByte & 0xC0) != 0x80)
            return NULL;
        buffer[i] = (char)nextByte;
    }
    buffer[len] = '\0';
    return buffer;
}

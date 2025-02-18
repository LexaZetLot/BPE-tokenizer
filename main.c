#include "BPE.h"
#define SIZE_TABLE 20

int main(int arhc, char** argv){
    char* path = "/home/lexa/Desktop/text/";
        
    bytePairEncodingTokinazer(path, SIZE_TABLE, 30);
    return 0;
}

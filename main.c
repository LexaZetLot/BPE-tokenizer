#include "BPE.h"
#define SIZE_TABLE 3000

int main(int arhc, char** argv){
    char* path = "/home/lexa/Desktop/text/";
        
    bytePairEncodingTokinazer(path, SIZE_TABLE, 2000);
    return 0;
}

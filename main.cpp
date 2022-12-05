/**
 * @file main.cpp
 * @author Majdi Rhim
 * @brief 
 * @version 0.1
 * @date 2022-11-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "cCompression.h"
#include "cHuffman.h"
int main(){
    char data[]={'a','b','c','d','e','f'};
    unsigned int freq[]={5,3,7,1,10,2};
    cHuffman h = cHuffman();
    h.HuffmanCodes(data,freq,6);
    h.AfficherHuffman();
return 0;
}



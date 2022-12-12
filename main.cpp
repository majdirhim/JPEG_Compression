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
//#include "cCompression.h"
#include "cHuffman.h"
int main(){
    int data[]={55,66,77,88,90,56};
    unsigned int freq[]={5,3,7,1,10,2};
    cHuffman h = cHuffman(data,freq,6);
    h.HuffmanCodes();
    h.Generatecodes();
    h.decode("00010");
return 0;
}



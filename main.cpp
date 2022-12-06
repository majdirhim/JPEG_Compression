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
  /*  char data[]={'a','b','c','d','e','f'};
    unsigned int freq[]={5,3,7,1,10,2};
    cHuffman h = cHuffman();
    h.HuffmanCodes(data,freq,6);
    h.AfficherHuffman();
    */
int cpltTrame[128*128];
int Donne[128*128];
unsigned int Freq[128*128];
cCompression test("lenna.txt");
test.RLE(cpltTrame);
test.Histogramme(cpltTrame,test.get_cpltTrameSize(),Donne,Freq);
cHuffman h=cHuffman();
h.HuffmanCodes(Donne,Freq,test.get_HistoSize());
h.AfficherHuffman();
/*int data[]={0,5,4,3,2,1};
unsigned int freq[]={5,3,7,1,10,2};
cHuffman h = cHuffman();
h.HuffmanCodes(data,freq,6);
h.AfficherHuffman();*/
return 0;
}



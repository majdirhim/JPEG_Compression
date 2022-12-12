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
    int cpltTrame[128*128];
    int Donne[128*128];
    unsigned int Freq[128*128];
    cCompression test("lenna.txt");
    test.RLE(cpltTrame);
    test.Histogramme(cpltTrame,test.get_cpltTrameSize(),Donne,Freq);    
    cHuffman h = cHuffman(Donne,Freq,test.get_HistoSize());
    h.HuffmanCodes();
    h.Generatecodes();
    h.decode("1011100");
return 0;
}



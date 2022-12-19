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
    cCompression test("lenna.txt");
    test.Compress();
return 0;
}



/**
 * @file cCompression.h
 * @author Majdi Rhim
 * @brief This class Handles image reading and all JPEG's operation such as the DCT , the inverse DCT, the quantifiaction, the inverse quantification and also \n 
 * it handles the Run-length encoding for 128*128 image.  
 * @version 0.1
 * @date 2022-11-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <queue>
#include "cHuffman.h"
#define Bloc8 8 /*Single Bloc size*/

/**
 * @brief Reference table for jpeg quantification
 * 
 */
const uint8_t RefTable[Bloc8][Bloc8]={{16,11 ,10 ,16 ,24 ,40, 51, 61},
                                {12 ,12 ,14 ,19 ,26 ,58 ,60 ,55},
                                {14 ,13 ,16 ,24 ,40 ,57 ,69 ,56},
                                {14 ,17 ,22 ,29 ,51 ,87 ,80 ,62},
                                {18 ,22 ,37 ,56 ,68 ,109 ,103 ,77},
                                {24 ,35 ,55 ,64 ,81 ,104 ,113 ,92},
                                {49 ,64 ,78 ,87 ,103 ,121 ,120 ,101},
                                {72 ,92 ,95 ,98 ,112 ,100 ,103 ,99}
                                };

/**
 * @brief cCompression Class definition
 * 
 */
class cCompression{

unsigned int mLargeur=128 , mHauteur=128;/*Image Resolution*/
uint8_t *mBuffer; /*Image buffer*/
unsigned int mQualite=50;
unsigned int cpltTrameSize=0; /*Complete trame size*/
unsigned int TrameSize=0; /*Single Bloc's trame size*/ 
float Trame_average=0; /*Average Current Trame*/ 
int m_DC_precedent=0; /* Average previous Trame*/
unsigned int HistoSize=0; /*Histogram tables size*/

/**
 * @note Different zigzag states for RLE 
 * 
 */
enum State{
    Strate_H,
    Down,
    Strate_V,
    UP,
    Exit
};

double coeff(unsigned int u)const;
void toSigned(uint8_t (*Block8x8)[Bloc8])const;
double lambda(unsigned int Quality)const;
double QTable(unsigned int i , unsigned j)const;
void State_Machine_RLE(int (*Qimg)[Bloc8],int *Trame);
public:
    cCompression(const char *filename);
    ~cCompression();
    unsigned int get_mLargeur(void)const;
    unsigned int get_mHauteur(void)const;
    unsigned int get_mQualite(void)const;
    unsigned int get_cpltTrameSize()const;
    unsigned int get_HistoSize()const;
    void set_mLargeur(unsigned int Lar );
    void set_mHauteur(unsigned int HAU);
    void set_mQualite(unsigned int Q);

    void Calcul_DCT_Block(uint8_t (*Block8x8)[Bloc8],double(*DCT_Img)[Bloc8])const;
    void Calcul_iDCT(double(*DCT_Img)[Bloc8],uint8_t  (*Block8x8)[Bloc8])const;
    void quant_JPEG(double(*DCT_Img)[Bloc8],int (*Img_Quant)[Bloc8])const;
    void dequant_JPEG(int (*Img_Quant)[Bloc8],double(*DCT_Img)[Bloc8])const;

    double EQM(uint8_t (*Bloc8x8)[Bloc8],uint8_t (*IDCT)[Bloc8])const;
    double Taux_Compression(uint8_t (*Bloc8x8)[Bloc8],int (*Qimg)[Bloc8])const;
    
    void RLE_Block(int (*Qimg)[Bloc8],int DC_precedent ,int *Trame);
    void RLE(int* CpltTrame);
    void TConcatenate(int* CpltTrame,int* Trame);

    void Histogramme(int* Trame, unsigned int Longueur_Trame, int* Donnee , unsigned int* Frequence);

    void Ecriture_Flot( int* Trame, const char* filename="Flow.txt");
};
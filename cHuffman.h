/**
 * @file cHuffman.h
 * @author Majdi
 * @brief 
 * @version 0.1
 * @date 2022-12-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "cCompression.h"
#include <queue>
#include <string>  
struct sNoeud {
int mdonnee ; // code
unsigned int mfreq ; // frequence du code
sNoeud *mgauche ; // fils gauche
sNoeud *mdroit ; // fils droit
std::string mcode;
sNoeud ( char d , unsigned int f ) {
    mgauche = NULL;
    mdroit = NULL;
    this->mdonnee = d ;
    this->mfreq = f ;
    }
};

struct compare{
    bool operator()(sNoeud* gauche,sNoeud *droit){
        return gauche->mfreq > droit->mfreq;
    }
};
class cHuffman{
    int* mTrame;
    unsigned int* mFrequence;
    unsigned int mLongueur;
    sNoeud *mRacine;
    void Generatecodes( sNoeud* Racine,std::string code="");
public:
cHuffman(const int* Trame,const unsigned int* Frequence,const unsigned int& Longueur);
~cHuffman();
int* getTrame()const;
unsigned int getLongueur()const;
sNoeud* getRacine()const;

void setTrame();
void setLongueur();
void setRacine();


void HuffmanCodes();
void Generatecodes();
void decode(const std::string& input,const char* file_name="Decoded.txt")const;
};

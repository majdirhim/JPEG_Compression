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
struct sNoeud {
char mdonnee ; // code
unsigned int mfreq ; // frequence du code
sNoeud *mgauche ; // fils gauche
sNoeud *mdroit ; // fils droit
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
    int *mTrame;
    uint8_t mLongueur;
    sNoeud *mRacine;

    void AfficherHuffman(sNoeud* Racine)const;
public:
cHuffman();
~cHuffman();
int* getTrame()const;
uint8_t getLongueur()const;
sNoeud* getRacine()const;

void setTrame();
void setLongueur();
void setRacine();


void HuffmanCodes(char* Donnee ,unsigned int* Frequence ,unsigned int Taille );
void AfficherHuffman()const;
};

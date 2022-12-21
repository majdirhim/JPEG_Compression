/**
 * @file cHuffman.h
 * @author Majdi
 * @brief This class handles the lossless part of compressing, it creates the Humffman Tree\n
 * generates Huffman codes for each node and store them in a file by code length to achieve maximum entropy\n 
 * and finaly it decodes an encoded string.   
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
#include <unordered_map>
/**
 * @brief Huffman tree node's struct
 * 
 */
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
/**
 * @brief Overloading the () operator for the huffman Tree priority Queue comparision\n
 * it prioritize low frequencies
 * 
 */
struct compare_less{
    bool operator()(sNoeud* gauche,sNoeud *droit){
        return gauche->mfreq > droit->mfreq;
    }
};
/**
 * @brief Overloading the () operator for the for huffman Code generator priority Queue comparision\n 
 * it prioritize high frequencies
 * 
 */
struct compare_great{
    bool operator()(sNoeud* gauche,sNoeud *droit){
        return gauche->mfreq < droit->mfreq;
    }
}; 
/**
 * @brief CHuffman Class definition
 * 
 */
class cHuffman{
    int* mTrame;
    unsigned int* mFrequence;
    unsigned int mLongueur; /*data length*/
    sNoeud *mRacine;
    void Generatecodes( sNoeud* Racine,std::priority_queue<sNoeud*, std::vector<sNoeud*>,compare_great>& Q,std::string code="");
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
std::priority_queue<sNoeud*, std::vector<sNoeud*>,compare_great> Generatecodes();
void decode(const std::string& input,const char* file_name="Decoded.txt")const;
};

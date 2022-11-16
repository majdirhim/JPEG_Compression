#include "cCompression.h"

class cHuffman{
    int *mTrame;
    uint8_t mLongueur;
    int *mRacine;
public:
cHuffman(int* Trame,uint8_t longueur,int* rac);
~cHuffman();
int* getTrame()const;
uint8_t getLongueur()const;
int* getRacine()const;

void setTrame();
void setLongueur();
void setRacine();


};
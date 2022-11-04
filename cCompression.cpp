#include "cCompression.h"

cCompression::cCompression(){

}
cCompression::~cCompression(){
    
}

unsigned int cCompression::get_mHauteur(void)const{
    return mHauteur;
}

unsigned int cCompression::get_mLargeur(void)const{
    return mLargeur;
}

void cCompression::set_mHauteur(unsigned int Lar){
     mHauteur=Lar;
}

void cCompression::set_mLargeur(unsigned int HAU){
    mLargeur=HAU;
}

void cCompression::Calcul_DCT_Block(double **DCT_Img,unsigned char **Block8x8){

}

void cCompression::Calcul_iDCT(unsigned char **Block8x8,double **DCT_Img){

}


void cCompression::quant_JPEG(double **Img_DCT,int **Img_Quant){

}
void cCompression::dequant_JPEG(double **Img_Quant,int **Img_DCT){

}
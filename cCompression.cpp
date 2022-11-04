#include "cCompression.h"
/**
 * @brief cCompresssion constructor
 * 
 */
cCompression::cCompression(){

}
/**
 * @brief cCompresssion deconstructor
 * 
 */
cCompression::~cCompression(){
    
}
/**
 * @brief getter for mHauteur
 * 
 * @return unsigned int 
 */
unsigned int cCompression::get_mHauteur(void)const{
    return mHauteur;
}
/**
 * @brief getter for mLargeur
 * 
 * @return unsigned int 
 */

unsigned int cCompression::get_mLargeur(void)const{
    return mLargeur;
}
/**
 * @brief setter for mHauteur
 * 
 * @param Lar 
 */

void cCompression::set_mHauteur(unsigned int Lar){
     mHauteur=Lar;
}
/**
 * @brief setter for mLargeur
 * 
 * @param HAU 
 */
void cCompression::set_mLargeur(unsigned int HAU){
    mLargeur=HAU;
}

double cCompression::coeff(char u)const{
    return u==0?(1.0/sqrt(2)):(u>1 && u<7);
}
double cCompression::DCT_Sum(int Block8x8[][Bloc8])const{
    double s =0.0;

    return s;
}
/**
 * @brief Apply the Discrete cosine transform function to a block of image 8x8
 * 
 * @param DCT_Img : pointer
 * @param Block8x8 : pointer
 */

void cCompression::Calcul_DCT_Block(char (*Block8x8)[Bloc8],double(*DCT_Img)[Bloc8])const{
    double s=0.0;
    for(unsigned int u=0;u<Bloc8;u++){
        for(unsigned int v=0;v<Bloc8;v++){
            s=0.0;
            for(unsigned int x=0;x<Bloc8;x++)
                for(unsigned int y=0;y<Bloc8;y++)
                    s+=*(*(Block8x8+x)+y)*cos((2*x+1)*M_PI*u/16.0)*cos((2*y+1)*M_PI*v/16.0);
            *(*(DCT_Img+u)+v)=(coeff(u)*coeff(v)/4.0)*s;
        }
    }      

}
/**
 * @brief Apply the inverse discrete cosine transform to a DCT encoded image 8x8
 * 
 * @param DCT_Img 
 * @param Block8x8 
 */

void cCompression::Calcul_iDCT(double(*DCT_Img)[Bloc8],char (*Block8x8)[Bloc8])const{
    double s=0.0;
    for(unsigned int x=0;x<Bloc8;x++){
        for(unsigned int y=0;y<Bloc8;y++){
            s=0.0;
            for(unsigned int u=0;u<Bloc8;u++)
                for(unsigned int v=0;v<Bloc8;v++)
                    s+=*(*(DCT_Img+u)+v)*coeff(u)*coeff(v)*cos((2*x+1)*M_PI*u/16.0)*cos((2*y+1)*M_PI*v/16.0);
            *(*(Block8x8+x)+y)=s/4.0;
        }
    }
}


void cCompression::quant_JPEG(double **Img_DCT,int **Img_Quant){

}
void cCompression::dequant_JPEG(double **Img_Quant,int **Img_DCT){

}



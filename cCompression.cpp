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
 * @brief getter for mQualite
 * 
 * @return unsigned int 
 */
unsigned int cCompression::get_mQualite(void)const{
    return mQualite;
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

void cCompression::set_mQualite(unsigned int Q){
    mQualite=Q;
}

double cCompression::coeff(unsigned int u)const{
    return u==0?(1.0/sqrt(2)):(u>=1 && u<=7);
}

/**
 * @brief scale the values to be between -127 and 128 
 * @param Block8x8
 */
void cCompression::toSigned(uint8_t (*Block8x8)[Bloc8])const{
    for(unsigned int i=0;i<Bloc8;i++){
        for(unsigned int j=0;j<Bloc8;j++){
            *(*(Block8x8+i)+j)-=128;
        }
    }
}

/**
 * @brief Apply the Discrete cosine transform function to a block of image 8x8
 * 
 * @param DCT_Img : pointer
 * @param Block8x8 : pointer
 */

void cCompression::Calcul_DCT_Block(uint8_t (*Block8x8)[Bloc8],double(*DCT_Img)[Bloc8])const{
    double s;
    toSigned(Block8x8);
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

void cCompression::Calcul_iDCT(double(*DCT_Img)[Bloc8],uint8_t  (*Block8x8)[Bloc8])const{
    long double s;
    for(unsigned int x=0;x<Bloc8;x++){
        for(unsigned int y=0;y<Bloc8;y++){
            s=0.000;
            for(unsigned int u=0;u<Bloc8;u++)
                for(unsigned int v=0;v<Bloc8;v++)
                    s+=*(*(DCT_Img+u)+v)*coeff(u)*coeff(v)*cos((2*x+1)*M_PI*u/16.000)*cos((2*y+1)*M_PI*v/16.000);
            *(*(Block8x8+x)+y)=(uint8_t)lround(s/4.0); //Convert the double to nearest uint8_t value
        }
    }
}


double cCompression::lambda(unsigned int Quality)const{
    return ( Quality<50 ? 5000.0/Quality : 200.0-(2.0*Quality) );
}

double cCompression::QTable(unsigned int i , unsigned j)const{
    double res=(lambda(mQualite)*(*(*(RefTable+i)+j))+50)/100;
    if(res<1)
        return 1;
    else if (res>255)
        return 255;
    else
        return res;
}

/**
 * @brief Quantify a matrix depending on Fq factor and a reference table
 * 
 * @param Img_DCT 
 * @param Img_Quant 
 */
void cCompression::quant_JPEG(double(*DCT_Img)[Bloc8],int (*Img_Quant)[Bloc8]){
    for(unsigned int u=0 ; u<Bloc8 ;u++)
        for(unsigned int v=0 ; v<Bloc8 ;v++)
            *(*(Img_Quant+u)+v)=round((*(*(DCT_Img+u)+v))/QTable(u,v));
}
void cCompression::dequant_JPEG(int (*Img_Quant)[Bloc8],double(*DCT_Img)[Bloc8])const{
for(unsigned int u=0 ; u<Bloc8 ;u++)
        for(unsigned int v=0 ; v<Bloc8 ;v++)
            (*(*(DCT_Img+u)+v))=round(*(*(Img_Quant+u)+v)*QTable(u,v));
}



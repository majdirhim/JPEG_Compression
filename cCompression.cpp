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
/**
 * @brief calculate the coefficient c(k)
 * 
 * @param u 
 * @return double 
 */
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
    toSigned(Block8x8);// return to 0-255
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
    toSigned(Block8x8); // return to 0-255
}


double cCompression::lambda(unsigned int Quality)const{
    return ( Quality<50 ? 5000.0/Quality : 200.0-(2.0*Quality) );
}
/**
 * @brief return Quantification table value in [i][j] coordinates
 * 
 * @param i :lignes
 * @param j :colonnes
 * @return double 
 */
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
/**
 * @brief Dequantifying 
 * @param Img_Quant : Quantified image
 * @param DCT_Img : Dequantification result 
 * 
 */
void cCompression::dequant_JPEG(int (*Img_Quant)[Bloc8],double(*DCT_Img)[Bloc8])const{
for(unsigned int u=0 ; u<Bloc8 ;u++)
        for(unsigned int v=0 ; v<Bloc8 ;v++)
            (*(*(DCT_Img+u)+v))=round(*(*(Img_Quant+u)+v)*QTable(u,v));
}

/**
 * @brief root mean square deviation
 * 
 */
double cCompression::EQM(uint8_t (*Bloc8x8)[Bloc8],uint8_t (*IDCT)[Bloc8])const{
    double Ecart =0 , somme=0.0;
    for(unsigned int u=0 ; u<Bloc8 ;u++)
        for(unsigned int v=0 ; v<Bloc8 ;v++)
            somme+=((*(*(Bloc8x8+u)+v))-(*(*(IDCT+u)+v)))*((*(*(Bloc8x8+u)+v))-(*(*(IDCT+u)+v)));            
return(somme/(Bloc8*Bloc8));
}

/**
 * @brief Compression Ratio (%)
 * 
 * @return double 
 */
double cCompression::Taux_Compression(uint8_t (*Bloc8x8)[Bloc8],int (*Qimg)[Bloc8])const{
    uint8_t zeros=0, elements=64;
    for(unsigned int u=0 ; u<Bloc8 ;u++)
        for(unsigned int v=0 ; v<Bloc8 ;v++)
            if(*(*(Qimg+u)+v)==0)
                zeros++;
    elements-=zeros;
    return (100-((double)elements*100/(Bloc8*Bloc8)));
    
}

/**
 * @brief 
 * 
 * @param Qimg : Quantified Image
 * @param DC_precedent  : Qimg[0] - Average previous Trame
 * @param Trame : compressed (lossless) quantified Image
 */
void cCompression::State_Machine_RLE(int (*Qimg)[Bloc8],int DC_precedent,int *Trame)const{
unsigned int i =0 , j=0 , t=0;
State state=Strate_H;
Trame[0]=Qimg[i][j];
do{
switch(state){
    case Strate_H:
        j++;
        if(j%2!=0 && i!=7)
            state=Down;
        else if(i==7 && j%2!=0 && j!=7)
            state=UP;
        else if(i==7 && j==7)
            state=Exit;
        else 
            state=Strate_H;
        break;
    case Down:
        i++;
        j--;
        if(i%2!=0 && j==0 && i!=7 )
            state=Strate_V;
        else if (i==7)
            state=Strate_H;
        else 
            state=Down;
        break;
    case Strate_V:
        i++;
        if(i%2==0 && j==7)
            state=Down;
        else if(i%2==0 && j==0)
            state=UP;
        else 
            state=Strate_V;
        break;
    case UP:
        i--;
        j++;
        if(i==0)
            state=Strate_H;
        else if(i%2!=0 &&j==7)
            state=Strate_V;
        else 
            state=UP;
        break;
    default:
        state=Exit;

}
t++;
Trame[t]=Qimg[i][j];
printf("state : %d\t i=%d\t j=%d\t t=%d\r\n",state,i,j,t);
}while(state!=Exit);

}

void cCompression::RLE_Block(int (*Qimg)[Bloc8],int DC_precedent ,int *Trame)const{
unsigned int zeros=0;
int tab[64];
State_Machine_RLE(Qimg,DC_precedent,tab);
Trame[0]=DC_precedent;
for(unsigned int i=1,j=0;i<Bloc8*Bloc8;i++){
    if(tab[i]==0){
        zeros++;
    }
    else{
        Trame[++j]=zeros;
        Trame[++j]=tab[i];
        zeros=0;
    }
    if(tab[i]==0 && i==Bloc8*Bloc8-1){
        Trame[++j]=0;
        Trame[++j]=0;
    }
}
}

void cCompression::RLE(int* Trame)const{
    
}
#include <iostream>
#define Bloc8x8 8
class cCompression{

unsigned int mLargeur , mHauteur;
unsigned char **mBuffer;
unsigned int mQualite;
unsigned char Bloc[8][8]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};

void Calcul_DCT_Block(double **DCT_Img,unsigned char **Block8x8);
void Calcul_iDCT(unsigned char **Block8x8,double **DCT_Img);
void quant_JPEG(double **Img_DCT,int **Img_Quant);
void dequant_JPEG(double **Img_Quant,int **Img_DCT);
public:
    cCompression();
    ~cCompression();

    unsigned int get_mLargeur(void)const;
    unsigned int get_mHauteur(void)const;
    unsigned int get_mQualite(void)const;

    void set_mLargeur(unsigned int Lar );
    void set_mHauteur(unsigned int HAU);
    void set_mQualite(unsigned int Q);


};
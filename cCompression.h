#include <iostream>
#include <cmath>
/**
 * @brief Bloc size
 * 
 */
#define Bloc8 8
const int m = 8, n = 8;
/**
 * @brief cCompression Class definition
 * 
 */
class cCompression{

unsigned int mLargeur , mHauteur;
char **mBuffer;
unsigned int mQualite;
double coeff(char u)const;
double DCT_Sum(int Block8x8[][Bloc8])const;
public:
    cCompression();
    ~cCompression();

    unsigned int get_mLargeur(void)const;
    unsigned int get_mHauteur(void)const;
    unsigned int get_mQualite(void)const;

    void Calcul_DCT_Block(char (*Block8x8)[Bloc8],double(*DCT_Img)[Bloc8])const;
    void Calcul_iDCT(double(*DCT_Img)[Bloc8],char (*Block8x8)[Bloc8])const;
    void quant_JPEG(double **Img_DCT,int **Img_Quant);
    void dequant_JPEG(double **Img_Quant,int **Img_DCT);

    void set_mLargeur(unsigned int Lar );
    void set_mHauteur(unsigned int HAU);
    void set_mQualite(unsigned int Q);


};
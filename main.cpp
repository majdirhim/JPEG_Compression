#include "cCompression.h"

int main(){
//exemple of block
uint8_t Bloc[8][8] = {      {139,144,149,153,155,155,155,155},
                            {144,151,153,156,159,156,156,156},
                            {150,155,160,163,158,156,156,156},
                            {159,161,162,160,160,159,159,159},
                            {159,160,161,162,162,155,155,155},
                            {161,161,161,161,160,157,157,157},
                            {162,162,161,163,162,157,157,157},
                            {162,162,161,161,163,158,158,158}
                        };

int  Qimg[8][8];
double DCT_img[8][8] ;
int Trame[64];
cCompression test;
test.RLE(Trame);
for(int i=0;i<13*3;i++)
    printf("%d\t",Trame[i]);
printf("\n");


/* //DCT
test.Calcul_DCT_Block(Bloc,DCT_img);

for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        printf("%.2lf\t",DCT_img[i][j]);
    }
    printf("\n");
}

test.set_mQualite(50); // qualité 50%

//Quantification
test.quant_JPEG(DCT_img,Qimg);
std::cout<<"\n";
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        printf("%d\t",Qimg[i][j]);
    }
printf("\n");
}

printf("\n");

//Dequantification
test.dequant_JPEG(Qimg,DCT_img);
std::cout<<"\n";
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        printf("%.2lf\t",DCT_img[i][j]);
    }
printf("\n");
}
uint8_t IBloc[8][8];
printf("\n");

//IDCT
test.Calcul_iDCT(DCT_img,IBloc);
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        printf("%d\t",(int)IBloc[i][j]);
    }
printf("\n");
}

// EQM
std::cout <<"\n";
std::cout <<test.EQM(Bloc,IBloc)<<"\n";

//Taux
std::cout <<"\n";
std::cout <<test.Taux_Compression(Bloc,Qimg)<<"\n";

//RLE
std::cout<<"\nRLE\n";

test.RLE_Block(Qimg,14,Trame);
printf("Trame= [");
for(int i=0;i<13;i++)
    printf("%d, ",Trame[i]);
printf("]\n"); */


return 0;
}



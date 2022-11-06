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

uint8_t  IBloc[8][8];
double img[8][8];
cCompression test;
test.Calcul_DCT_Block(Bloc,img);

for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        printf("%.2lf\t",img[i][j]);
    }
    printf("\n");
}


test.Calcul_iDCT(img,IBloc);
std::cout<<"\n";
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        printf("%hhu\t",IBloc[i][j]);
    }
    printf("\n");
}
return 0;
}
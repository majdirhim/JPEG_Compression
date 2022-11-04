#include "cCompression.h"

int main(){
//exemple of block
char Bloc[8][8] = { { 127, 127, 3, 5, 127, 18, 127, 9 },
                     { 127, 4, 127, 6, 127, 30, 127, 127 },
                     { 10, 70, 127, 0, 2, -1, 127, -128 },
                     { 127, 0, 127, 55, 90, 70, 127, 127 },
                     { 55, -10, 127, 100, 127, 127, 127, -90 },
                     { -120, 127, 127, 127, 40, 127, 127, 120 },
                     { 127, -128, 127, 127, 127, 127, 127, 127 },
                     { 127, 8, 127, 10, 127, 1, 1, 15 } };
char IBloc[8][8];
double img[8][8];
cCompression test;
test.Calcul_DCT_Block(Bloc,img);

for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        printf("%lf\t", img[i][j]);
    }
    printf("\n");
}


test.Calcul_iDCT(img,IBloc);
std::cout<<"\n";
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        printf("%lf\t", IBloc[i][j]);
    }
    printf("\n");
}
return 0;
}
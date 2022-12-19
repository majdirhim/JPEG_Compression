/**
 * @file cCompression.cpp
 * @author Majdi Rhim
 * @brief 
 * @version 0.1
 * @date 2022-11-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "cCompression.h"
/**
 * @brief Construct a new c Compression::c Compression object
 * 
 * @param imagePath : Path to the image to compress
 */
cCompression::cCompression(const char *imagePath){
    mBuffer=new uint8_t[mLargeur*mHauteur];
    FILE *img;
    img=fopen(imagePath,"r");
    rewind(img); // Begining of the file 
    for(unsigned int i=0;i<mLargeur*mHauteur;i++)
        fscanf(img, "%hhu",&mBuffer[i]);
    fclose(img);
}
/**
 * @brief cCompresssion deconstructor
 * 
 */
cCompression::~cCompression(){
    delete [] mBuffer;
}
/**
 * @brief getter for mQualite : Compression quality \n 
 * It is between 0 and 100, by default it is set to 50
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
 * @brief getter for complete Trame Size
 * 
 * @return unsigned int 
 */
unsigned int cCompression::get_cpltTrameSize()const{
    return cpltTrameSize;
}
/**
 * @brief Getter for HistoSize
 * 
 * @return unsigned int 
 */
unsigned int cCompression::get_HistoSize()const{
    return HistoSize;
}
/**
 * @brief setter for mHauteur
 * 
 * @param HAU : height of the image
 */

void cCompression::set_mHauteur(unsigned int HAU){
     mHauteur=HAU;
}
/**
 * @brief setter for mLargeur
 * 
 * @param Lar : width of the image
 */
void cCompression::set_mLargeur(unsigned int Lar){
    mLargeur=Lar;
}
/**
 * @brief Setter for mQuality :  Compression quality \n 
 * It is between 0 and 100, by default it is set to 50
 * 
 * @param Q : Quality (0-100)
 */
void cCompression::set_mQualite(unsigned int Q){
    /*checking for quality, it must be between 0 and 100*/
    assert(Q>=0 && Q<=100); 
    mQualite=Q;
}
/**
 * @brief calculate the coefficient c(k)
 * 
 * @param u :value between 1--->7
 * @return double 
 */
double cCompression::coeff(unsigned int u)const{
    /*checking if u is between 1 and 7*/
    assert(u>=0 && u<=7);
    return u==0?(1.0/sqrt(2)):(u>=1 && u<=7); /* return (1/sqrt(2)) if (u == 0) else return 1 */ 
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
 * @param DCT_Img : pointer to array of double
 * @param Block8x8 : pointer to array of uint8_t
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
    toSigned(Block8x8); /*rescaling to 0-255*/ 
}
/**
 * @brief Apply the inverse discrete cosine transform to a DCT encoded image 8x8
 * 
 * @param DCT_Img : pointer to array of double
 * @param Block8x8 : pointer to array of uint8_t
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
    toSigned(Block8x8); /*rescaling to 0-255*/
}

/**
 * @brief calculate lambda value
 * 
 * @param Quality : quality between 0-100
 * @return double 
 */
double cCompression::lambda(unsigned int Quality)const{
    return ( Quality<50 ? 5000.0/Quality : 200.0-(2.0*Quality) );
}
/**
 * @brief return Quantification table value in each [i][j] coordinates
 * 
 * @param i :row index
 * @param j :column index
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
 * @param Img_DCT : pointer to array of double
 * @param Img_Quant : pointer to array of int
 */
void cCompression::quant_JPEG(double(*DCT_Img)[Bloc8],int (*Img_Quant)[Bloc8])const{
    for(unsigned int u=0 ; u<Bloc8 ;u++)
        for(unsigned int v=0 ; v<Bloc8 ;v++)
            *(*(Img_Quant+u)+v)=round((*(*(DCT_Img+u)+v))/QTable(u,v));
}
/**
 * @brief Dequantifying a JPEG image
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
 * @brief Determine the root mean square deviation 
 * 
 */
double cCompression::EQM(uint8_t (*Bloc8x8)[Bloc8],uint8_t (*IDCT)[Bloc8])const{
    double somme=0.0;
    for(unsigned int u=0 ; u<Bloc8 ;u++)
        for(unsigned int v=0 ; v<Bloc8 ;v++)
            somme+=((*(*(Bloc8x8+u)+v))-(*(*(IDCT+u)+v)))*((*(*(Bloc8x8+u)+v))-(*(*(IDCT+u)+v)));            
return(somme/(Bloc8*Bloc8));
}

/**
 * @brief Determine the compression ratio (%)
 * @param Bloc8x8 : pointer to array of uint8_t
 * @param Img_Quant : pointer to array of int
 * @return double : (%)
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
 * @brief Apply a state machine to iterate between elements in ZigZag
 * 
 * @param Qimg : Quantified Image
 * @param Trame : compressed (lossless) quantified Image (output)
 */
void cCompression::State_Machine_RLE(int (*Qimg)[Bloc8],int *Trame){
unsigned int i =0 , j=0 , t=0;
State state=Strate_H;
Trame[0]=Qimg[i][j]; // Trame[0]=Qimg[0][0]
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
t++; //increment
Trame[t]=Qimg[i][j];
Trame_average+=Trame[t]; /*somme of the trame's values*/ 
//printf("state : %d\t i=%d\t j=%d\t t=%d\r\n",state,i,j,t); /*debug*/
}while(state!=Exit);
}
/**
 * @brief Caclulate the RLE Trame for one Bloc8X8
 * @param Qimg : Quantified Block8x8
 * @param DC_precedent  : Average previous Trame
 * @param Trame : compressed (lossless) quantified Block8x8
 */
void cCompression::RLE_Block(int (*Qimg)[Bloc8],int DC_precedent ,int *Trame){
unsigned int zeros=0;
int temp[64]; //temporary array
TrameSize=0;
Trame_average=0.0;  //reinitialize for the next trame calculation      
State_Machine_RLE(Qimg,temp);
Trame[0]=temp[0]-DC_precedent; //Qimg[0] - Average previous Trame
/*Trame formatting*/
for(unsigned int i=1,j=0;i<Bloc8*Bloc8;i++){
    if(temp[i]==0){
        zeros++;
    }
    else{
        Trame[++j]=zeros;
        Trame[++j]=temp[i];
        zeros=0;
    }
    if(temp[i]==0 && i==Bloc8*Bloc8-1){
        Trame[++j]=0;
        Trame[++j]=0;
        TrameSize=j+1;
        m_DC_precedent=(Trame_average/TrameSize); /*Determine the average */
       // printf("average :%d\n\r",(int)m_DC_precedent);
    }
}
}
/**
 * @brief Apply RLE for all image's blocks and Concatenate all the trames
 * 
 * @param CpltTrame :[OUT] Complete Image's Trame
 */
void cCompression::RLE(int* CpltTrame){
    int  Qimg[8][8];
    double DCT_img[8][8] ;
    int Trame[64];
    uint8_t Bloc[8][8];
    unsigned int offsetIndex=0;
    for(unsigned int k =0;k<(mLargeur*mHauteur)/(Bloc8*Bloc8);k++){
        /*Extracting 8x8 Block from the image*/   
        for(unsigned int i=0;i<Bloc8;i++){
            for(unsigned j=0;j<Bloc8;j++){
                Bloc[i][j]=mBuffer[(j+i*Bloc8)+offsetIndex]; //8x8 1D to 8x8 2D
               // printf("%u\t",Bloc[i][j]); //debug
            }
        //printf("\n");
        }
        //printf("\r\n");
        offsetIndex+=Bloc8*Bloc8;
        Calcul_DCT_Block(Bloc,DCT_img);     
        quant_JPEG(DCT_img,Qimg);
        RLE_Block(Qimg,m_DC_precedent,Trame);
        TConcatenate(CpltTrame,Trame);
    }
}
/**
 * @brief Concatenate all 8x8 block's trames in a single complete image trame
 * 
 * @param CpltTrame : complete image trame
 * @param Trame : 8x8 block trame
 */
void cCompression::TConcatenate(int* CpltTrame,int* Trame){
    unsigned int lastSize=cpltTrameSize;
    cpltTrameSize+=TrameSize;
    for(unsigned int i =lastSize;i<cpltTrameSize;i++){
        CpltTrame[i]=Trame[i-lastSize];
    }
}
/**
 * @brief Returns the data table and it's corresponding frequency table 
 * 
 * @param Trame : RLE Trame
 * @param Longueur_Trame : Size of RLE Trame
 * @param Donnee : pointer to the data table to return 
 * @param Frequence : pointer to the frequency table to return
 */
void cCompression::Histogramme(int* Trame, unsigned int Longueur_Trame, int* Donnee , unsigned int* Frequence){
    std::priority_queue<int, std::vector<int>, std::greater<int> > Q;
    int temp,extemp;
    unsigned int Freq=0;
    for(unsigned int i=0;i<Longueur_Trame;i++)
        Q.push(Trame[i]);
    while(!Q.empty()){
        temp=Q.top();
        Q.pop();
        do{
            Donnee[HistoSize]=temp;
            Freq++;
            Frequence[HistoSize]=Freq;
            extemp = Q.top();
            Q.pop();
        }while(temp==extemp);
        HistoSize++;
        Freq=0;
    }
}

/**
 * @brief Determine data Trame frequencies, create huffman tree,\n generate huffman codes and store them in a file
 * accoriding to their length
 * 
 * @param Trame : pointer to the complete image Trame
 * @param filename : the file name, by default it is set to Flow.txt
 */
void cCompression::Ecriture_Flot(int* Trame, const char* filename){
    FILE* file;
    int Donne[128*128];
    unsigned int Freq[128*128];
    Histogramme(Trame,get_cpltTrameSize(),Donne,Freq);
    cHuffman h = cHuffman(Donne,Freq,get_HistoSize());
    h.HuffmanCodes(); //create the tree
    std::unordered_map<unsigned int ,std::string > freq_code = h.Generatecodes(); //generate huffman codes
    std::priority_queue<unsigned int> Q;
    for(unsigned int i = 0; i<get_HistoSize();i++)
        Q.push(Freq[i]);
    file=fopen(filename,"w");
    while(!Q.empty()){
        fprintf(file,"%s",freq_code[Q.top()].c_str()); //write shortest code first
        Q.pop();
    }
    fclose(file);
    
}

/**
 * @brief Compressing a luminance image
 * 
 */
void cCompression::Compress(){
    int cpltTrame[128*128];
    RLE(cpltTrame); // The Lossy part compression (DCT-Quantification ...)
    Ecriture_Flot(cpltTrame); //The Lossless part compression (Huffman)
}
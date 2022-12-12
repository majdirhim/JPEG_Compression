#include "cHuffman.h"

/**
 * @brief Construct a new cHuffman::cHuffman object
 * 
 */
cHuffman::cHuffman(const int* Trame,const unsigned int* Frequence,const unsigned int& Longueur){
    assert(Longueur>0); /*must not be null*/
    mLongueur=Longueur;
    mFrequence=new unsigned int[Longueur];
    mTrame=new int[Longueur];
    for(unsigned int i=0;i<mLongueur;i++){
        mFrequence[i]=Frequence[i];
        mTrame[i]=Trame[i];
    }
}
/**
 * @brief Destroy the cHuffman::cHuffman object
 * 
 */
cHuffman::~cHuffman(){
delete[] mFrequence;
delete[] mTrame;
} 
/**
 * @brief Getter for mTrame
 * 
 * @return int* 
 */
int* cHuffman::getTrame()const{
    return mTrame;
}
/**
 * @brief Getter for mLongueur
 * 
 * @return uint8_t 
 */
unsigned int cHuffman::getLongueur()const{
    return mLongueur;
}
/**
 * @brief Getter for mRacine
 * 
 * @return sNoeud* 
 */
sNoeud* cHuffman::getRacine()const{
    return mRacine;
}

/**
 * @brief Private function to Create the Huffman Tree
 * 
 * @param Donnee :pointer to array of data
 * @param Frequence :pointer array of data frequency occurence
 * @param Taille : size of arrays
 */
void cHuffman::HuffmanCodes(){
    std::priority_queue<sNoeud*, std::vector<sNoeud*>,compare> Q;
    for(unsigned int i =0;i<mLongueur;i++)
        Q.push(new sNoeud(mTrame[i],mFrequence[i]));
    while(Q.size()!=1){
        sNoeud* gauche = Q.top();
        Q.pop();
        sNoeud* droit = Q.top();
        Q.pop();
        sNoeud* top =new sNoeud('~',gauche->mfreq+droit->mfreq);
        top->mdroit=droit;
        top->mgauche=gauche;
        //printf("data = %c \t freq=%d\n\r",top->mdonnee,top->mfreq); //debug
        Q.push(top);
    }
    mRacine=Q.top(); //root node
    Q.pop();
}
/**
 * @brief Public function to Generate the Huffman codes for each node and print the Tree
 * 
 */
void cHuffman::Generatecodes(){
    Generatecodes(this->mRacine);
}


/**
 * @brief Private function to Generate Huffman codes for each node and print the Tree
 * 
 * @param Racine : root node address
 * @param code : node code, by default it's set to ""
 */
void cHuffman::Generatecodes( sNoeud* Racine , std::string code){
    if(Racine!=NULL){
        Racine->mcode=code; //store codes in each node
        Generatecodes(Racine->mgauche,code+"0");
        Generatecodes(Racine->mdroit,code+"1");
        if(Racine->mdonnee!='~'){
            /**Print the Tree*/
            printf("Data= %d\tcode=%s\r\n",Racine->mdonnee,Racine->mcode.c_str());
        }
    }
}


/**
 * @brief Decodes the given encoded string and store the result in a file
 * 
 * @param input : encoded string
 * @param file_name : file name by debault it's set to Decoded.txt
 */
void cHuffman::decode(const std::string& input,const char* file_name )const{
  FILE* file;
  file=fopen(file_name,"w");

  sNoeud* node=this->mRacine;
  for(unsigned int i = 0;i<input.size();i++){
    if(input[i]=='0'){
      node=node->mgauche;
    }
    else if (input[i]=='1')
      node=node->mdroit;
    if(node->mgauche == NULL && node->mdroit == NULL){
      printf("%d\n\r",node->mdonnee);
      fprintf(file,"%d",node->mdonnee);
      node=this->mRacine;
    }
  }
  fclose(file);
}


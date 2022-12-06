#include "cHuffman.h"

/**
 * @brief Construct a new cHuffman::cHuffman object
 * 
 */
cHuffman::cHuffman(){

}
/**
 * @brief Destroy the cHuffman::cHuffman object
 * 
 */
cHuffman::~cHuffman(){

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
uint8_t cHuffman::getLongueur()const{
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
 * @brief Create the Huffman Tree
 * 
 * @param Donnee :array of data
 * @param Frequence :array of data frequency occurence
 * @param Taille : size of arrays
 */
void cHuffman::HuffmanCodes(int* Donnee ,unsigned int* Frequence ,unsigned int Taille ){
    std::priority_queue<sNoeud*, std::vector<sNoeud*>,compare> Q;
    for(unsigned int i =0;i<Taille;i++)
        Q.push(new sNoeud(Donnee[i],Frequence[i]));
    uint8_t t=0;
    while(Q.size()!=1){
        sNoeud* gauche = Q.top();
        Q.pop();
        sNoeud* droit = Q.top();
        Q.pop();
        sNoeud* top =new sNoeud('\0',gauche->mfreq+droit->mfreq);
        top->mdroit=droit;
        top->mgauche=gauche;
        //printf("data = %c \t freq=%d\n\r",top->mdonnee,top->mfreq);
        Q.push(top);
    }
    mRacine=Q.top();
    Q.pop();
}
/**
 * @brief Public Function to print Huffman Tree
 * 
 */
void cHuffman::AfficherHuffman()const{
    AfficherHuffman(this->mRacine,"");
}


/**
 * @brief Private function to print Huffman Tree
 * 
 * @param Racine : First node in huffman tree
 */
void cHuffman::AfficherHuffman(sNoeud* Racine , std::string code)const{
    if(Racine!=nullptr){
        if(Racine->mdonnee!='\0')
            printf("Data= %d\t\tcode=%s\t\r\n",Racine->mdonnee,code.c_str());
        AfficherHuffman(Racine->mdroit,code+"1");
        AfficherHuffman(Racine->mgauche,code+"0");
    }
}

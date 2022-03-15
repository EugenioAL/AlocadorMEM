#include <iostream>
#include <cstdlib>
#include <list>
#include "aloca.h"

using namespace std;
meualoc::meualoc(int tamanhoMemoria,int politicaMem){
		setMeuAloc(tamanhoMemoria, politicaMem);
}

char *meualoc::getMemoriaPointer(){
		return memoria;
	}

int meualoc::getMemoriaTam(){
		return tamanhoMemoria;
}

void meualoc::setMeuAloc(int tamanho,int politica){
	list<Node> lista;
	memoria = (char*) malloc (tamanho*sizeof(char));
	listaLivres = lista;
	tamanhoMemoria = tamanho;
	politicaMem = politica;
	posLista = lista.begin();
	initListaDeVazia();
	fillMemory();
}
void meualoc::initListaDeVazia(){
    Node tmp(memoria,tamanhoMemoria);
    insertListaDeVazias(tmp);
	posLista = listaLivres.begin();
}

void meualoc::insertListaDeVazias(Node tmp){
	list<Node>::iterator it;
	Node novo = tmp;
	it = listaLivres.begin();
	int flag = 0;
	if(listaLivres.size() <=1){
		if(listaLivres.size() == 0){
			listaLivres.push_front(novo);
			cout << "0\n";
		}
		else if(listaLivres.size() == 1){
			
			if(&(novo.addr) > &(it->addr)){
				listaLivres.push_front(novo);
			}
			else{
				listaLivres.push_back(novo);
			}
		}
	}
	else{
		int i = 0;
		while(flag == 0 && i < (int)listaLivres.size()){
			if(novo.addr < it->addr){
				listaLivres.insert(it,novo);
				flag =1;
			}
			it++;
			i++;
		}
		if(flag == 0){
			listaLivres.insert(it,novo);
		}
	}
}


void meualoc::fillMemory(){
	for(int i = 0; i < tamanhoMemoria; i++){
		memoria[i] = 65 + i/10;
	}
}

void meualoc::coalesce(){
	list<Node>::iterator it1,it2,it3;
	it3 = listaLivres.end();
	if(listaLivres.size() >= 2){
		it2 = it1 = listaLivres.begin();
		it2++;
		int i = 0;
		while( i < (int)listaLivres.size()){
			if(it2->addr == it1->addr + it1->tamanho){
				it1->tamanho = it1->tamanho + it2->tamanho;
				if(posLista == it2){
					posLista = it1;
				}
				listaLivres.erase(it2);
				it2 = it1++;
			}
			else{
				it1++;
				it2++;
				i++;
			}
		}
	}
}

//Pega um pedaco da variavel memoria e aloca, retornando o ponteiro para o comeco dessa regiao e atualizando a lista de livres.
char *meualoc::aloca(unsigned short int tamanho){
	unsigned short int espaco = tamanho+4; 
	list<Node>::iterator it,it2,tmp;
	char *ini,flag = 'f',flag1 = 'f';
	if(espaco >= CEIL){
		cout << "Tamanho indisponivel!" << endl;
		return NULL;
	}
	else{
		coalesce();
		if(politicaMem == BESTFIT){
			for(it = listaLivres.begin(); it != listaLivres.end();it++){
				if(it->tamanho >= espaco){
					if(flag == 'f'){
						tmp = it;
						flag1 = flag = 't';
						}
					else{
						if(((it->tamanho)-espaco) < (tmp->tamanho) - espaco){
						tmp = it;
						flag1 = 't';
						}
					}
				}	
			}
		}
		else if(politicaMem == FIRSTFIT){
			it = listaLivres.begin();
			while(it != listaLivres.end() && flag == 'f'){
				if((it->tamanho) >= espaco){
					tmp = it;
					flag1 = 't';
					cout << "tam lista " << it->tamanho << endl;
				}
				it++;
			}
		}
		else if(politicaMem == NEXTFIT){
			int i = 0;
			it2 = posLista;
			while(i < (int)listaLivres.size() && flag1 == 'f'){
				cout << "it tam " << it2->tamanho << endl;
				if(it2->tamanho >= espaco){
					tmp = it2;
					flag1 = 't';
				}
				if(it2 == listaLivres.end()){
					it2 = listaLivres.begin();
				}
				it2++;
				i++;
			}
		}
		else{
			cout << "ERRO" << endl;
			return NULL;
		}

	if(flag1 == 't'){
			tmp->addr[0] = tamanho >> 8;
			tmp->addr[1] = tamanho;
			tmp->addr[2] = (char)(MAGICVAR >> 8);
			tmp->addr[3] = (char)MAGICVAR;
			ini = tmp->addr;
			tmp->addr += espaco;
			tmp->tamanho-=espaco;
			if(tmp->tamanho == 0){
				listaLivres.erase(tmp);
			}
			return ini + 4;
		}
		else{
			return NULL;
		}
	}
}

//Verifica se a posicao dada pelo ponteiro esta alocada
char* meualoc::verifica(char* ponteiro,int posicao){
	unsigned short int val1,val2,val3;
	char mByte,lByte;
	if(ponteiro != NULL){
		mByte = ponteiro[posicao-2];
		lByte = ponteiro[posicao-1];
		val1 = mByte;
		val2 = lByte;
		val3 = (val1 << 8) + val2; 
		if((val3 == MAGICVAR)){
			return ponteiro;
		}
		else{
			return NULL;
		}
	}
	else{
		return NULL;
	}
}

		
		
		//Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
int meualoc::libera(char* ponteiro){
	cout << &ponteiro << endl;
	cout << ponteiro-4 << endl;
    char* tmp = ponteiro - 4;
	unsigned short int mval,lval;
	if(verifica(ponteiro,0) != NULL){
		mval = tmp[0] << 8;
		lval = tmp[1];
		for(int i = 0; i< 4; i++){
			tmp[i] = 'F';
		}
		cout << &tmp << endl;
		Node novo(tmp,mval+lval + 4);
		insertListaDeVazias(novo);
		return 1;
	}
	else{
		cout << "Este endereco nao esta alocado.\n";
		return 0;
	}
}

		//Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
void meualoc::imprimeDados(){
	list<Node>::iterator it;
	it = listaLivres.begin();
	int i = 0;
	for(it = listaLivres.begin(); it!=listaLivres.end();it++){
		//printa os numeros os valores da lista
		cout << "Tamanho: " << it->tamanho <<"\t" << "Cont: "<< it->addr << endl;
		cout <<"Posicao: " << i << "\tTamanho: " << it->tamanho <<"\t" << "Cont: "<< &(it->addr) << endl;
		i++;
	}
}

meualoc::~meualoc(){
	free(memoria);
	cout << "Alocador destruido"<< endl;
}
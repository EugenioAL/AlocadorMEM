#ifndef _meualoc
#define _meualoc
#define BESTFIT 0
#define FIRSTFIT 1
#define NEXTFIT 2
#define MAGICVAR 20299

using namespace std;

//TAMANHO MÁXIMO DE ALOCACAO: 65535 (maior unsigned short)

class Node{
	public:
		char* addr;
		int tamanho;

		Node(char* addre, int tam){
				addr = addre;
				tamanho = tam;
			}
};

class meualoc{
	char* memoria; //char* pois eh byte a byte
	list<Node> listaLivres;
	int tamanhoMemoria;
	int politicaMem;
	int posLista;

	public:
		//tamanhoMemoria vai definir o tamanho da memória que o alocador vai utilizar
		//politicaMem define como escolher o bloco de onde saira a memória
		meualoc(int tamanhoMemoria,int politicaMem){
			setMeuAloc(tamanhoMemoria, politicaMem);
		}

		char *getMemoriaPointer(){
			return memoria;
		}

		void setMeuAloc(int tamanho,int politica){
			list<Node> lista;
			memoria = (char*) malloc (tamanho*sizeof(char));
			listaLivres = lista;
			tamanhoMemoria = tamanho;
			politicaMem = politica;
			posLista = 0;
			cout <<"pointerMem11: " << &memoria << endl;
			initListaDeVazia();
			fillMemory();
		}

		void initListaDeVazia(){
			Node tmp(memoria,tamanhoMemoria);
			insertListaDeVazias(tmp);
		}

		void insertListaDeVazias(Node tmp){
			list<Node>::iterator it;
			if(listaLivres.size() == 0){
					listaLivres.push_front(tmp);
			}
			else{
				for(it = listaLivres.begin(); it != listaLivres.end(); it++){
					cout << "Errado!!" << endl;
				}
			}
		}

		void fillMemory(){
			for(int i = 0; i < tamanhoMemoria; i++){
				memoria[i] = 48 + i/10;
			}
		}

		//Pega um pedaco da variavel memoria e aloca, retornando o ponteiro para o comeco dessa regiao e atualizando a lista de livres.
		char *aloca(unsigned short int tamanho){
			if(tamanho >= 65532){
				cout << "Tamanho indisponivel!" << endl;
				return NULL;
			}
			list<Node>::iterator it;
			list<Node>::iterator tmp ;
			char flag = 'f';
			char* a,*tmpp;
			ofstream myfile;
			unsigned short int espaco = tamanho+4;
			switch (politicaMem)
			{
			case 0:
				for(it = listaLivres.begin(); it != listaLivres.end();it++){
					if(it->tamanho >= espaco){
						if(flag == 'f'){
							tmp = it;
						}
						else{
							if(((it->tamanho)-espaco) < (tmp->tamanho) - espaco){
								tmp = it;
							}
						}
					}
				}
				tmpp = tmp->addr;
				cout << "Memoria antes: "<< memoria << endl;
				tmp->addr[0] = tamanho >> 8;
				tmp->addr[1] = tamanho;
				tmp->addr[2] = 'O';
				tmp->addr[3] = 'K';
				cout << "Memoria depois: "<< memoria[0] << endl;
				myfile.open ("example.txt");
				myfile << memoria;
				myfile.close();
				a=tmp->addr+4;
				cout << a << endl;
				cout << &a << endl;
				tmp->tamanho -=espaco;
				tmp->addr += espaco;
				break;
			case 1:
				for(it = listaLivres.begin(); it != listaLivres.end();it++){
					if(it->tamanho >= espaco){
					}
				}
				break;
			case 2:
				/* code */
				break;
			
			default:
				break;
			}
			return a;
		}

		//Verifica se a posicao dada pelo ponteiro esta alocada
		char* verifica(char* ponteiro,int posicao=0);

		
		
		//Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
		int libera(char* ponteiro);

		//Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
		void imprimeDados(){
			char** ptmp;
			list<Node>::iterator it;
			it = listaLivres.begin();
			for(it = listaLivres.begin(); it!=listaLivres.end();it++){
				//printa os numeros os valores da lista
				ptmp = &(it->addr);
				cout << "Tamanho: " << it->tamanho <<"\t" << "Endereço: "<< &(it->addr) << endl;
				cout << "Tamanho: " << it->tamanho <<"\t" << "Endereço: "<< ptmp << endl;
			}
		}

		~meualoc(){
			free(memoria);
			cout << "Alocador destruido"<< endl;
		}
};

#endif

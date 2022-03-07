#ifndef _meualoc
#define _meualoc
#define BESTFIT 0
#define FIRSTFIT 1
#define NEXTFIT 2

using namespace std;

//TAMANHO MÁXIMO DE ALOCACAO: 65535 (maior unsigned short)

class node{
	unsigned short int addr;
	unsigned short int tamanho;
};

class meualoc{
	char* memoria; //char* pois eh byte a byte
	list<node> listaLivre;
	int tamanhoMemoria;
	int politicaMem;

	public:
		//tamanhoMemoria vai definir o tamanho da memória que o alocador vai utilizar
		//politicaMem define como escolher o bloco de onde saira a memória
		meualoc(int tamanhoMemoria,int politicaMem){
			cout << tamanhoMemoria << endl;
			cout << politicaMem << endl;
		}

		//Pega um pedaco da variavel memoria e aloca, retornando o ponteiro para o comeco dessa regiao e atualizando a lista de livres.
		char *aloca(unsigned short int tamanho);

		//Verifica se a posicao dada pelo ponteiro esta alocada
		char* verifica(char* ponteiro,int posicao=0);
		
		//Libera o espaco ocupado na posicao, de forma analoga ao free. Ou seja, liberar toda a memoria alocada para este ponteiro na funcao aloca.
		int libera(char* ponteiro);

		//Imprime o numero de elementos na lista de vazios, o maior e a media de tamanhos dos blocos vazios
		void imprimeDados();


};

#endif

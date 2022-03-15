#include <iostream>
#include <cstdlib>
#include <list>
#include "aloca.h"

using namespace std;


int main(){
    int tamMem,politicaMem,var = 0,criado = 0;
    unsigned short int alocTam;
    cout << sizeof(Node) << endl;
    meualoc *tmp;
    tmp = NULL;
    char option,*pont;
    pont = NULL;
    while(var==0){
        cout << "Escolha uma ação: " << endl;
        cout << "1-Criar o alocador." << "\t2-Alocar memória." << "\t3-Consultar endereço." << "\t4-Liberar memoria."<<"\t5-Imprimir"<<"\t6-Destruir alocador." << "\t7-Sair" << endl;
        cin >> option;
        switch (atoi(&option))
        {
        case 1:
            if(criado == 1){
                cout << "Apenas um alocador é permitido por vez, por favor delete o alocador já criado." << endl;
                break;
            }
            cout << "Entre com o valor em Bytes para o tamanho da memoria:" << endl;
            cin >> tamMem;
            cout << "Entre com a politica de alocação para memoria(0-BESTFIT,1-FIRSTFIT,2-NEXTFIT):" << endl;
            cin >> politicaMem;
            if (politicaMem == BESTFIT || politicaMem == FIRSTFIT || politicaMem == NEXTFIT)
            {
                tmp = new meualoc(tamMem,politicaMem);
            }
            else{
                cout << "valor inválido" << endl;
            }
            criado = 1;

            break;
        case 2:
            cout << "Entre com o tamanho da memoria de ate 65531" << endl;
            cin >> alocTam;
            pont = tmp->aloca(alocTam);
            if(pont == NULL){
                cout << "Não tem espaço." << endl;
            }
            else{
                cout <<"Conteudo pont: " << pont-4 << endl;
            }
            break;
        case 3:
            if(pont != NULL){
                if(tmp->verifica(pont,0) != NULL){
                    cout << "Este ponteiro está alocado.\n";
                }
            }
            else{
                cout << "Este ponteiro não está alocado.\n";
            }
            break;
        case 4:
            if(tmp->libera(pont) == 1){
                cout << "Memoria Liberada.\n"; 
            }
            else{
                cout << "Essa memoria não pode ser liberada.\n";
                pont = NULL;
            }
            break;
        case 5:
            if(criado){
                tmp->imprimeDados();
            }
            else{
                cout << "Não há nenhum alocado criado!";
            }
            break;
        case 6:
            cout << "destruiu" << endl;
            delete tmp;
            criado = 0;
            break;
        case 7:
        cout << "Bye" << endl;
            var = 1;
            break;
        
        default:
        cout << "opção inválida" << endl;
            break;
        }
    }
}
#include <iostream>
#include <cstdlib>
#include "aloca.h"

using namespace std;

Node::Node(char* addre, unsigned short int tam){
		addr = addre;
		tamanho = tam;
		prox = NULL;
}

void Node::criarLista(Node **p){
	*p=Node(getMemoriaPointer(),meualoc::getMemoriaTam());
}

void Node::insereListaCircular(Node **p){
	Node *aux;
	aux = (Node*) malloc(sizeof(Node));
	if(aux==NULL){
		exit(2);
	}
	aux->dado = d;
	if(*p == NULL){
		*p=aux;
		aux->prox = aux;
	}
	else{
		aux->prox = (*p)->prox;
		(*p)->prox = aux;
		*p = aux;
	}
}

void Node::removerListaCircular(Node **p){
	Node *aux;
	aux = *p;
	if(aux){
		if(aux == aux->prox){
			free(aux);
			*p = NULL;
		}
		else{
			aux = aux->prox;
			(*p)->prox = aux->prox;
			*p = (*p)->prox;
			free(aux);
		}
	}
	else{
		printf("A lista esta vazia.\n");
	}
}

void Node::mostrarListaCircular(Node **p){
	Node *aux;
	aux = *p;
	if(aux){
		do{
			printf("\t%s %s %d\n",aux->addr,aux->tamanho);
			aux = aux->prox;
		}while(aux != *p);
		printf("\n");
	}
	else{
		printf("A lista esta vazia.\n");
	}
}
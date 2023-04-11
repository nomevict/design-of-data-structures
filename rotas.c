#include <stdio.h>
#include <stdlib.h>
#include "rotas.h"
#include "cliente.h"

struct rota{
    int idRota, nTentativas;
    Cliente *cliente;
    Rota *proximo;
};

struct fila{
    Rota *inicio, *fim;
};

struct pilha{
    Rota *inicio;
};

Fila *criarFilaRotas(){
    Fila *new = (Fila *) malloc(sizeof(Fila));
    new->inicio = NULL; new->fim = NULL;
    return new;
}

Pilha *criarPilhaNaoEntregue(){
    Pilha *new = (Pilha *) malloc(sizeof(Pilha));
    new->inicio = NULL;
    return new;
}

int filaRotaVazia(Fila *filaRotas){
    return filaRotas->inicio == NULL && filaRotas->fim == NULL? 1 : 0;
}

int pilhaVazia(Pilha *pilha){
    return pilha->inicio == NULL ? 1 : 0;
}

Fila *cadastrarRota(Fila *filaRotas, Cliente *cliente){
    Rota *new = (Rota *) malloc(sizeof(Rota));

    new->idRota = rand() % 100000;
    new->nTentativas = 0;
    new->cliente = cliente;
    new->proximo = NULL;

    if(filaRotaVazia(filaRotas)){
        filaRotas->inicio = new;
        filaRotas->fim = new;

    }else{
        filaRotas->fim->proximo = new;
        filaRotas->fim = new;
    }

    return filaRotas;
}

void mostrarRotas(Fila *filaRotas){
    Rota *aux = filaRotas->inicio;

    if(filaRotaVazia(filaRotas)){
        printf("\nFila de rotas vazia!\n");
        return;
    }

    printf("\n------------Todas as rotas------------");
    while(aux != NULL){
        printf("\nID da entrega: %d", aux->idRota);
        mostrarUnicoCliente(aux->cliente);

        aux = aux->proximo;
    }
}

Fila *fazerRota(Fila *filaRotas, Pilha *pilhaEntregaFalha, float *pontos, int *nEntregas){
    Rota *aux, *entregas; 
    int size, status;

    if(filaRotaVazia(filaRotas)){
        printf("\nNao ha rotas!\n");
        return filaRotas;
    }

    entregas = filaRotas->inicio;
    filaRotas->inicio = filaRotas->inicio->proximo;
    entregas->proximo = NULL;
    entregas->nTentativas++;

    size = contaRotas(filaRotas->inicio, entregas);

    for(int i = 0; i < size; i++){
        filaRotas->inicio = permuta(filaRotas->inicio, entregas);
    }

    aux = filaRotas->inicio;
    if(aux){
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }

        filaRotas->fim = aux;

    }else{
        filaRotas->fim = NULL;
    }

    printf("\nO cliente recebeu a(s) entrega(s)? 1 - S/0 -N >>> "); scanf("%d", &status);
    *nEntregas = *nEntregas + 1;
    if(status){
        aux = entregas;

        while(aux != NULL){
            *pontos = *pontos + 5;

            aux = aux->proximo;
            free(entregas);
            entregas = aux;
        }

        printf("\n----------Entregas feitas com sucesso!--------\n");

    }else{
        if(pilhaEntregaFalha->inicio){
            status = 1;

        }else{
            status = 0;
        }

        falhaEntrega(&pilhaEntregaFalha, entregas, status);
    }
    
    return filaRotas;
}

void falhaEntrega(Pilha **pilhaDestino, Rota *itens, int status){
    Rota *aux;

    if(status){
        aux = itens;

        while(aux->proximo != NULL){
            aux = aux->proximo;
        }

        aux->proximo = (*pilhaDestino)->inicio;
    }
        
    (*pilhaDestino)->inicio = itens;
}

Rota *permuta(Rota *origem, Rota *destino){
    Rota *aux = origem, *aux2 = destino;

    if(!origem){
        printf("\nNenhuma rota para fazer!\n");
        return origem;
    }

    if(aux->cliente == destino->cliente){

        while(aux2->proximo != NULL){
            aux2 = aux2->proximo;
        }

        aux2->proximo = aux;
		origem = origem->proximo;
		aux->proximo = NULL;
        aux->nTentativas++;

        return origem;
    }

    while(aux->proximo != NULL && aux->proximo->cliente != destino->cliente){
		aux = aux->proximo;
	}

    if(aux->proximo == NULL){
		return origem;
	}

    while(aux2->proximo != NULL){
		aux2 = aux2->proximo;
	}

    aux->proximo->nTentativas++;
    aux2->proximo = aux->proximo;
	aux->proximo = aux->proximo->proximo;
	aux2->proximo->proximo = NULL;

    return origem;
}

int contaRotas(Rota *rotas, Rota *destino){
    Rota *aux = rotas; int cont = 0;

    if(rotas){
        while(aux != NULL){
            if(aux->cliente == destino->cliente){
                cont++;
            }
            aux = aux->proximo;
        }
    }

    return cont;
}

void mostrarEntregasFalhas(Pilha *entregas){
    Rota *aux = entregas->inicio;

    printf("\n------------Entregas nao efetuadas------------");
    while(aux != NULL){
        printf("\nID da entrega: %d", aux->idRota);
        mostrarUnicoCliente(aux->cliente);

        aux = aux->proximo;
    }
    printf("\n---------------------------------------\n");
}

Pilha *entregarPilha(Pilha *entregasFalhas, int *nTentativas, float *pontos, Fila *devolucao){
    Rota *aux, *novaEntrega;
    int size, status, remove = 0;

    if(pilhaVazia(entregasFalhas)){
        printf("\nNao entregas na pilha de entregas nao efetuadas!\n");
        return entregasFalhas;

    }else{
        novaEntrega = entregasFalhas->inicio;
        entregasFalhas->inicio = entregasFalhas->inicio->proximo;
        novaEntrega->proximo = NULL;
        novaEntrega->nTentativas++;

        size = contaRotas(entregasFalhas->inicio, novaEntrega);

        for(int i = 0; i < size; i++){
            entregasFalhas->inicio = permuta(entregasFalhas->inicio, novaEntrega);
        }

        printf("\nCliente recebeu a(s) entrega(s) ? 1 - Sim/0 - Nao >>> "); scanf("%d", &status);
        *nTentativas = *nTentativas + 1;
        if(status){
            aux = novaEntrega;

            while(aux != NULL){
                if(aux->nTentativas == 1){
                    *pontos = *pontos + 3;
                }else{
                    *pontos = *pontos + 2;
                }

                aux = aux->proximo;
                free(novaEntrega);
                novaEntrega = aux;
            }

        }else{

            if(novaEntrega->nTentativas == 3){
                filaDevolucao(&devolucao, novaEntrega);
                
            }else{
                if(entregasFalhas->inicio){
                    status = 1;

                }else{
                    status = 0;
                }

                falhaEntrega(&entregasFalhas, novaEntrega, status);
            }
        }   
    }

    return entregasFalhas;
}

void filaDevolucao(Fila **devolucao, Rota *itens){
    Rota *aux;

    while(aux->proximo != NULL){
        aux = aux->proximo;
    }
    
    aux->proximo = (*devolucao)->inicio;
    (*devolucao)->inicio = itens;

    aux = (*devolucao)->inicio;

    while(aux->proximo != NULL){
        aux = aux->proximo;
    }

    (*devolucao)->fim = aux;
}

void mostrarDevolucoes(Fila *devolucoes){
    Rota *aux = devolucoes->inicio;

    printf("\n------------Fila de devolucao----------");
    while(aux != NULL){
        printf("\nID da entrega: %d", aux->idRota);
        mostrarUnicoCliente(aux->cliente);

        aux = aux->proximo;
    }
    printf("\n---------------------------------------\n");
}
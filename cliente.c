#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "rotas.h"

struct endereco {
    char estado[10];
    char cidade[30];
    char logradouro[100];
};

struct cliente {
    int id;
    char nome[100];
    Endereco localizacao;
    Cliente *proximo;
};

Cliente *criarListaClientes(){
    return NULL;
}

Cliente *cadastrarClienteOrdenado(Cliente *listaClientes){
    Cliente *new = (Cliente *) malloc(sizeof(Cliente)), *aux = listaClientes;

    new->id = rand() % 100000;
    printf("\n-------------Cadastro--------------\n");
    printf("Insira seu Nome: "); scanf("%s", new->nome); setbuf(stdin, NULL);
    printf("Insira seu Estado: "); scanf("%s", new->localizacao.estado); setbuf(stdin, NULL);
    printf("Insira sua Cidade: "); scanf("%s", new->localizacao.cidade); setbuf(stdin, NULL);
    printf("Insira seu logradouro: "); scanf("%s", new->localizacao.logradouro); setbuf(stdin, NULL);
    printf("-------------------------------------\n");

    if(listaVaziaClientes(listaClientes) || listaClientes->id > new->id){
        new->proximo = listaClientes;
        listaClientes = new;

    }else{
        while(aux->proximo != NULL && aux->proximo->id < new->id){
            aux = aux->proximo;
        }

        new->proximo = aux->proximo;
        aux->proximo = new;
    }

    return listaClientes;
}

int listaVaziaClientes(Cliente *listaClientes){
    return listaClientes == NULL ? 1 : 0;
}

void mostrarClientes(Cliente *listaClientes){
    Cliente *aux = listaClientes;

    if(listaVaziaClientes(listaClientes)){
        printf("\nNao ha clientes cadastrados!\n");

    }else{
        printf("\n------------Lista de clientes----------\n");
        while(aux){
            printf("\nID: %d\n", aux->id);
            printf("Nome: %s\n", aux->nome);
            printf("Estado: %s\n", aux->localizacao.estado);
            printf("Cidade: %s\n", aux->localizacao.cidade);
            printf("Logradouro: %s\n", aux->localizacao.logradouro);

            aux = aux->proximo;
        }
        printf("\n---------------------------------------\n");
    }
}

void liberarListaClientes(Cliente *listaClientes){
    Cliente *aux = listaClientes;

    if(listaVaziaClientes(listaClientes)){
        printf("\nLista esvaziada!\n");

    }else{
        while(aux){
            aux = aux->proximo;
            free(listaClientes);
            listaClientes = aux;
        }

        printf("\nLista Esvaziada!\n");
    }
}

Cliente *buscarCliente(Cliente *listaCliente, int id){
    Cliente *aux = listaCliente;

    while(aux != NULL && aux->id != id && aux->id < id){
        aux = aux->proximo;
    }

    return aux->id == id ? aux : NULL;
}

void mostrarUnicoCliente(Cliente *cliente){
    printf("\nNome: %s\n", cliente->nome);
    printf("Estado: %s\n", cliente->localizacao.estado);
}
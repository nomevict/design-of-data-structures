#include <stdio.h>
#include <stdlib.h>
#include "rotas.h"
#include "cliente.h"
#include "transportadora.h"

struct transportadora{
    int rotasFeitas;
    float pontosAcumulados, score;
    Cliente *clientes;
    Fila *rotas;
    Pilha *entregasNaoEfetuadas;
    Fila *devolucao;
};

Transportadora *criar(){
    Transportadora *new = (Transportadora *) malloc(sizeof(Transportadora));
    new->clientes = criarListaClientes();
    new->rotas = criarFilaRotas();
    new->entregasNaoEfetuadas = criarPilhaNaoEntregue();
    new->rotasFeitas = 0; new->pontosAcumulados = 0; new->score = 0;
    new->devolucao = criarFilaRotas();
    return new;
}

void cadastrarClienteTransportadora(Transportadora *transportadora){
    transportadora->clientes = cadastrarClienteOrdenado(transportadora->clientes);
}

void cadastrarRotaTransportadora(Transportadora *transportadora){
    int id; Cliente *cliente;
    printf("\n--------Cadastro de entrega---------\n");
    printf("Insira o ID do cliente: "); scanf("%d", &id);
    printf("------------------------------------\n");

    cliente = buscarCliente(transportadora->clientes, id);
    if(cliente){
        transportadora->rotas = cadastrarRota(transportadora->rotas, cliente);

    }else{
        printf("\nCliente inexistente!\n");
    }
}

void mostrarClientesTransportadora(Transportadora *transportadora){
    mostrarClientes(transportadora->clientes);
}

void mostrarRotasTransportadora(Transportadora *transportadora){
    mostrarRotas(transportadora->rotas);
}

void fazerEntrega(Transportadora *transportadora){
    transportadora->rotas = fazerRota(transportadora->rotas, transportadora->entregasNaoEfetuadas, &transportadora->pontosAcumulados, &transportadora->rotasFeitas);
}

void mostrarPilhaEntregasFalhas(Transportadora *transportadora){
    mostrarEntregasFalhas(transportadora->entregasNaoEfetuadas);
}

void mostrarEstatisticas(Transportadora *transportadora){
    float score;
    if(!transportadora->rotasFeitas){
        score = 0;
    }else{
        score = transportadora->pontosAcumulados/transportadora->rotasFeitas;
    }
    printf("\n----------Estatisticas-----------\n");
    printf("Rotas feitas: %d\n", transportadora->rotasFeitas);
    printf("Score: %.2f\n", score);
    printf("----------------------------------\n");
}

void entregarPilhaFalhas(Transportadora *transportadora){
   transportadora->entregasNaoEfetuadas = entregarPilha(transportadora->entregasNaoEfetuadas, &transportadora->rotasFeitas, &transportadora->pontosAcumulados, transportadora->devolucao);
}

void mostrarFilaDevolucao(Transportadora *transportadora){
    mostrarDevolucoes(transportadora->devolucao);
}
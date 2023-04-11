#include "cliente.h"
typedef struct rota Rota;
typedef struct fila Fila;
typedef struct pilha Pilha;

Fila *criarFilaRotas();
Pilha *criarPilhaNaoEntregue();
Fila *cadastrarRota(Fila *filaRotas, Cliente *cliente);
int filaRotaVazia(Fila *filaRotas);
void mostrarRotas(Fila *filaRotas);
Fila *fazerRota(Fila *filaRotas, Pilha *pilhaEntregaFalha, float *pontos, int *nEntregas);
void falhaEntrega(Pilha **pilhaDestino, Rota *itens, int status);
Rota *permuta(Rota *origem, Rota *destino);
int contaRotas(Rota *rotas, Rota *destino);
void mostrarEntregasFalhas(Pilha *entregas);
Pilha *entregarPilha(Pilha *entregasFalhas, int *nTentativas, float *pontos, Fila *devolucao);
void filaDevolucao(Fila **devolucao, Rota *itens);
void mostrarDevolucoes(Fila *devolucoes);
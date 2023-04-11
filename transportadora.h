typedef struct transportadora Transportadora;


Transportadora *criar();
void cadastrarClienteTransportadora(Transportadora *transportadora);
void cadastrarRotaTransportadora(Transportadora *transportadora);
void mostrarClientesTransportadora(Transportadora *transportadora);
void mostrarRotasTransportadora(Transportadora *transportadora);
void fazerEntrega(Transportadora *transportadora);
void mostrarPilhaEntregasFalhas(Transportadora *transportadora);
void mostrarEstatisticas(Transportadora *transportadora);
void entregarPilhaFalhas(Transportadora *transportadora);
void mostrarFilaDevolucao(Transportadora *transportadora);



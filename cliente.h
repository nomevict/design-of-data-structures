typedef struct endereco Endereco;
typedef struct cliente Cliente;

Cliente *criarListaClientes();
Cliente *cadastrarClienteOrdenado(Cliente *listaClientes);
int listaVaziaClientes(Cliente *listaClientes);
void mostrarClientes(Cliente *listaClientes);
void liberarListaClientes(Cliente *listaClientes);
Cliente *buscarCliente(Cliente *listaCliente, int id);
void mostrarUnicoCliente(Cliente *cliente);
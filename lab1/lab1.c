// lista estática sequencial: é um arranjo de dados ou registros onde estão
// estabelecidos regras de precedencia entre seus elementos ou é uma coleção
// ordenada de componentes do mesmo tipo.

// lab -> inserção e remoção em ordem

// Inserir 1 a 1 (10 valores na lista) -> inserção em ordem crescente
// le valores inseridos e diz em que posição os valores estão (mostra todas as
// posições) remove valores e mostra a lista

//@brief -> descricao
//@param -> parametro da funcao
//@return-> retorno da funcao

// encontra posicao-> recebe lista e valor e devolve inteiro q eh posicao do
// valor na lista (retorna -1 se nao encontrar) deslocar a direta, abre espaço
// em posicao especifica (para inserir valor) -> recebe indice a partir do qual
// vai deslocar desloca a esquerda nao permite que hajam buracos no arranjo
// inserir valor na lista -> recebe lista e valor e insere na lista (verifica se a lista nao ta cheia e ai insere)
//remover-> remove indice e faz deslocamento
// a esquerda

//Lista lista = { .n = 0 }; //seta membro n em 0  (ou lista.n = 0)

#include <stdio.h>

#define TAMANHO 10

typedef struct {
    int valores[TAMANHO];
    int n;
} Lista;

/**
 * @brief Verifica se a lista está cheia.
 * 
 * @param lista Ponteiro para a lista.
 * @return int Retorna 1 se a lista estiver cheia, caso contrário, retorna 0.
 */
int esta_cheia(Lista *lista) {
    if (lista->n == TAMANHO) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Verifica se a lista está vazia.
 * 
 * @param lista Ponteiro para a lista.
 * @return int Retorna 1 se a lista estiver vazia, caso contrário, retorna 0.
 */
int esta_vazia(Lista *lista) {
    if (lista->n == 0) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Encontra a posição onde um valor deve ser inserido na lista ordenada.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser inserido.
 * @return int Retorna o índice onde o valor deve ser inserido.
 */
int encontrar_posicao(Lista *lista, int valor) {
    if (lista->n < TAMANHO) {
        for (int i = 0; i < lista->n; i++) {
            if (valor == lista->valores[i]) {
                return i;
            }
        }
        return -1;  
    }
}

/**
 * @brief Move os elementos da lista para a direita a partir de um índice, criando espaço para um novo valor.
 * 
 * @param lista Ponteiro para a lista.
 * @param indice O índice a partir do qual os elementos serão movidos.
 */
void deslocar_direita(Lista *lista, int indice) {
    for (int i = lista->n; i > indice; i--) {
        lista->valores[i] = lista->valores[i - 1];
    }
}

/**
 * @brief Move os elementos da lista para a esquerda a partir de um índice, removendo um valor.
 * 
 * @param lista Ponteiro para a lista.
 * @param indice O índice a partir do qual os elementos serão movidos.
 */
void deslocar_esquerda(Lista *lista, int indice) {
    for(int i = indice; i< lista->n; i++){
        lista->valores[i-1] = lista->valores[i];
    }
  lista->n--;
 
//     for (int i = indice; i < lista->n - 1; i++) {
//         lista->valores[i] = lista->valores[i + 1];
//     }
//     lista->n--; 
 }

/**
 * @brief Insere um valor na lista em sua posição ordenada.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser inserido.
 * @return int Retorna 1 se a inserção for bem-sucedida, ou 0 se a lista estiver cheia.
 */
// int inserir(Lista *lista, int valor) {
//     if(esta_cheia(lista)){
//         return 0;
//     }
//     int posicao = encontrar_posicao(lista, valor);
//     if(posicao<0){
//         lista->valores[lista->n] = valor;
//         lista->n++;
//         return 1;
//      }else{
//         deslocar_direita(lista, posicao);
//         lista->valores[posicao] = valor;
//         lista->n++;  // Increment the size of the list
//         return 1;
//         }
//     }
/*encontrar_posicao retorna a posição onde o valor já existe ou a posição onde o valor deve ser inserido, mas não garante que essa posição é a correta para a inserção se a lista ainda não estiver ordenada ou se a posição for negativa. Isso causa problemas se a posição for -1.*/
//chat
int inserir(Lista *lista, int valor) {
    if (esta_cheia(lista)) {
        return 0;
    }

    int posicao = 0;
    // Encontrar a posição correta para inserir o valor
    while (posicao < lista->n && lista->valores[posicao] < valor) {
        posicao++;
    } //pq while? linha  211

    // Desloca para a direita para criar espaço na posição correta
    deslocar_direita(lista, posicao);

    // Insere o valor na posição encontrada
    lista->valores[posicao] = valor;

    // Incrementa o tamanho da lista
    lista->n++;

    return 1;
}

/*encontrar a Posição Correta: A função agora encontra a posição onde o valor deve ser inserido. Isso é feito com o loop while que verifica se o valor atual é menor do que o valor a ser inserido.

Deslocar os Elementos: Se for necessário deslocar os elementos para abrir espaço, a função deslocar_direita é chamada para criar esse espaço na posição correta.

Inserir o Valor: Após deslocar os elementos, o valor é inserido na posição correta.
*/

/**
 * @brief Remove um valor da lista.
 * 
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser removido.
 * @return int Retorna o valor removido se a remoção for bem-sucedida, ou -1 se a lista estiver vazia.
 */
int remover(Lista *lista, int valor) {
    if (!esta_vazia(lista)) {
        int posicao = encontrar_posicao(lista, valor);
        deslocar_esquerda(lista, posicao); //sobrescreve o valor a ser removido
        return valor;
    } else {
        return -1;
    }
}

int remover_ordem(Lista *lista){
    for(int posicao = 0; posicao < lista->n; posicao++){
        deslocar_esquerda(lista,posicao);
        return lista->valores[posicao];
    }

}

/**
 * @brief Exibe todos os valores da lista.
 * 
 * @param lista Ponteiro para a lista.
 */
void exibir_lista(const Lista *lista) {
    for (int i = 0; i < lista->n; i++) {
        printf("%d ", lista->valores[i]);
    }
    printf("\n");
}

int main() {
    Lista lista = { .n = 0 };
    Lista *pl = &lista;
    int valores[] = {21, 14, 13, 10, 87, 35, 27, 56, 85, 29};

    for (int i = 0; i < TAMANHO; i++) {
        inserir(pl, valores[i]);
        exibir_lista(pl);
    }

    for (int i = 0; i < TAMANHO; i++) {
        printf("O valor %d está na posição %d\n", valores[i], encontrar_posicao(pl, valores[i]));
    }

    for (int i = 0; i < TAMANHO; i++) {
        remover(pl, valores[i]);
        exibir_lista(pl);
    }
     // for (int i = 0; i < TAMANHO; i++) {
    //     remover_ordem(pl);
    //     exibir_lista(pl);
    // }

    return 0;
}

//for:
//O loop for é usado quando você sabe antecipadamente quantas vezes deseja repetir um bloco de código.
//Ele combina três partes: inicialização, condição de parada, e incremento. Todas essas partes são geralmente colocadas na mesma linha.

//while;
//O loop while é usado quando a repetição de um bloco de código depende de uma condição que pode mudar de forma imprevisível ou
// quando não se sabe quantas vezes o loop precisará ser repetido.
//O while verifica a condição antes de executar o bloco de código, e o loop continua enquanto a condição for verdadeira.
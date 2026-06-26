#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int valor;
    struct Celula *proximo;
} Celula;

typedef struct Lista {
    int qtde;
    Celula *primeiro;
} Lista;


Celula *criarCelula(int valor){//retorna endereço(ponteiro) para uma celula e uso valor para setar a celula
  Celula *celula = malloc(sizeof(Celula)); //tipo de dado é celula, aloca espaço para celula (sizeof descobre quantos bytes alocar)
  celula->proximo = NULL;
  celula->valor = valor;
  return celula;//retorno endereço da celula
}

/**
 * @brief Insere um valor na lista de forma ordenada.
 *
 * @param l Ponteiro para a lista onde o valor será inserido.
 * @param valor O valor inteiro a ser inserido na lista.
 */
void inserir(Lista *l, int valor) {
    Celula *novo = criarCelula(valor); 
  Celula *atual = l->primeiro;
  Celula *anterior = NULL;
  if(l->primeiro == NULL){
    l->primeiro = novo;
    l->qtde++;
  }else{
    while(atual != NULL && novo->valor >= atual->valor){
      //movimentação 
      anterior = atual; //endereço do anterior vai pro endereço do atual
      atual = atual->proximo; //atual vai para o proximo
    }
    if(anterior == NULL){ //para se atal for nulo
      novo->proximo = l->primeiro;
      l->primeiro = novo;
      l->qtde++;
    }else{
      if(atual == NULL){
        anterior->proximo = novo;
        l->qtde++;
      }else{ //inserção no meio      //inserir valor no meio da lista não vazia
        anterior->proximo = novo;    //sabe que é meio pois anterior não é nulo e atual nao é nulo
        novo->proximo = atual;
        l->qtde++;
      }
    }
  }
}


/**
 * @brief Remove um valor da lista, se ele estiver presente.
 *
 * @param l Ponteiro para a lista de onde o valor será removido.
 * @param valor O valor inteiro a ser removido da lista.
 */
void remover(Lista *l, int valor) {
    Celula *atual = l->primeiro;
    Celula *anterior = NULL;
    while(atual != NULL && atual->valor != valor){
        anterior = atual;
        atual = atual->proximo;
  }
  if(atual == NULL){
    printf("Valor não encontrado\n");
  }else{
    if(anterior == NULL){
      l->primeiro = atual->proximo;
      l->qtde--;
    }else{
      anterior->proximo = atual->proximo;
      l->qtde--;
    }
  }
}

/**
 * @brief Inicializa uma nova lista vazia.
 *
 * @return Ponteiro para a nova lista inicializada.
 */
Lista *inicializa_lista() {
    Lista *l = malloc(sizeof(Lista)); //maloc aloca memoria para lista correspondente ao valor do tipo de dado
    l->primeiro = NULL; //seta primeiro elemento da lista  
    l->qtde = 0; //seta qtde, inicializa quantidade de elementos da lista
    return l;
}


/**
 * @brief Imprime todos os valores da lista na ordem.
 *
 * @param l Ponteiro para a lista a ser impressa.
 */
void imprimir(Lista *l) {
    Celula *atual = l->primeiro;
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo; //caminhar na lista
  }
  printf("\n");
}

int main(void) {
    Lista *l = inicializa_lista();
    int valores[] = {2, 1, 0, 9, 3, 8, 5, 7, 6, 4};

    // Inserção
    for (int i = 0; i < 10; i++) {
        inserir(l, valores[i]);
        imprimir(l);
    }

    // Remoção
    for (int i = 0; i < 10; i++) {
        remover(l, valores[i]);
        imprimir(l);
    }

    free(l); // Liberar memória alocada para a lista
    return 0;
}

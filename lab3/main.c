#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó na lista duplamente encadeada
typedef struct no {
  int valor;
  struct no *anterior;
  struct no *proximo;
} No;

// Definição da estrutura da lista duplamente encadeada
typedef struct lista_duplamente_encadeada {
  int quantidade;
  No *inicio;
} ListaDuplamenteEncadeada;

/**
 * Cria uma nova lista duplamente encadeada e a inicializa.
 *
 * @return Um ponteiro para a nova lista criada.
 */
ListaDuplamenteEncadeada *criar_lista() {
  ListaDuplamenteEncadeada *lista = malloc(sizeof(ListaDuplamenteEncadeada));
  lista->inicio = NULL;
  lista->quantidade = 0;
  return lista;
}

/**
 * Cria um novo nó contendo o valor especificado.
 *
 * @param valor O valor a ser armazenado no nó.
 * @return Um ponteiro para o novo nó criado.
 */
No *criar_no(int valor) {
  No *novo_no = malloc(sizeof(No));
  novo_no->valor = valor;
  novo_no->anterior = NULL;
  novo_no->proximo = NULL;
  return novo_no;
}

/**
 * Insere um valor na lista de forma ordenada.
 *
 * @param lista Ponteiro para a lista onde o valor será inserido.
 * @param valor O valor a ser inserido na lista.
 */
void inserir_valor(ListaDuplamenteEncadeada *lista, int valor) {
  No *novo_no = criar_no(valor);
  No *atual = lista->inicio;
  No *anterior = NULL;
  if (lista->inicio == NULL) {
    lista->inicio = novo_no;
  } else {
    while (atual != NULL && atual->valor < valor) {
      anterior = atual;
      atual = atual->proximo;
    }
    if (anterior == NULL) {
      lista->inicio = novo_no;
      novo_no->proximo = atual;
      atual->anterior = novo_no;
    } else if (atual == NULL) {
      anterior->proximo = novo_no;
      novo_no->anterior = anterior;
    } else {
      anterior->proximo = novo_no;
      novo_no->anterior = anterior;
      atual->anterior = novo_no;
      novo_no->proximo = atual;
    }
  }
  lista->quantidade++;
}

/**
 * Exibe os valores da lista em ordem crescente.
 *
 * @param lista Ponteiro para a lista a ser exibida.
 */
void exibir_lista(ListaDuplamenteEncadeada *lista) {
  printf("Início -> ");
  No *atual = lista->inicio;
  while (atual != NULL) {
    printf("%d ", atual->valor);
    atual = atual->proximo;
  }
  printf("<- Final\n");
}

/**
 * Exibe os valores da lista em ordem decrescente.
 *
 * @param lista Ponteiro para a lista a ser exibida.
 */
void exibir_lista_invertida(ListaDuplamenteEncadeada *lista) {
  No *celulaAnterior = NULL;
  printf("Final -> ");
  No *atual = lista->inicio;
  //vai para final da lista para depois voltar mostrando invertido 
  while (atual != NULL) {
    celulaAnterior = atual;
    atual = atual->proximo;
  }
  while (celulaAnterior != NULL) {
    printf("%d ", celulaAnterior->valor);
    celulaAnterior = celulaAnterior->anterior;
  }
  printf("<- Início\n");
}

/**
 * Remove o nó que contém o valor especificado da lista.
 *
 * @param lista Ponteiro para a lista de onde o valor será removido.
 * @param valor O valor a ser removido da lista.
 */
void remover_valor(ListaDuplamenteEncadeada *lista, int valor) {
  No *atual = lista->inicio;
  No *anterior = NULL;
  //(while mexe na posicao do anterior e atual para comparar e achar valor p remover
  while (atual != NULL && atual->valor < valor) { //valor da celula atual for < que valor que quero remover
    anterior = atual; //celula anterior vira celula atual
    atual = atual->proximo; //celula atual vira celula proxima da atual (celula para qual ponteiro proximo da celula atual aponta)
  }
  if (atual == NULL) { //chego no fim da lista e só tem valores menores que o q quero remover
    return;
    // remover do inicio
  } else if (anterior == NULL) { // remover primeiro da lista
    lista->inicio = atual->proximo; //primeiro elemento da lista passa a ser o eleento para o qual o ponteiro proximo da celula atual ta apontando (mudo o apontamento do ponteiro da lista para o proximo elemento))
    if (atual->proximo != NULL) { //tem + de 1 elemento na lista
      atual->proximo->anterior = NULL; // tem mais elementos na lista
    }
    lista->quantidade--; //(sempre decrementa, tenho ou n mais elementos, mas
                         //qnd so tem o elemento sozinho tira ele
    // remover do meio 
          //cel anterior
  } else if(anterior != NULL && atual->proximo != NULL){  
    anterior->proximo = atual->proximo; //cel anterior aponta para o proximo do atual
    atual->proximo->anterior = anterior;
  }//remover do final
  else if(atual->proximo == NULL){ //atual é o ultimo elemento
    anterior->proximo = NULL; //proximo da n celua anterior
  }
}
// atual->proximo->anterior != NULL,  o anterior do proximo (o proprio numero)
    int main(void) {
      ListaDuplamenteEncadeada *lista = criar_lista();

      inserir_valor(lista, 10);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      inserir_valor(lista, 5);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      inserir_valor(lista, 20);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      inserir_valor(lista, 15);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      remover_valor(lista, 5);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      remover_valor(lista, 15);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      remover_valor(lista, 20);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      remover_valor(lista, 10);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      for (int i = 1; i <= 10; i++) {
        inserir_valor(lista, i);
      }
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      for (int i = 1; i <= 10; i++) {
        remover_valor(lista, i);
      }
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      remover_valor(lista, 100);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      inserir_valor(lista, 10);
      inserir_valor(lista, 10);
      inserir_valor(lista, 10);
      exibir_lista(lista);
      exibir_lista_invertida(lista);

      return 0;
    }

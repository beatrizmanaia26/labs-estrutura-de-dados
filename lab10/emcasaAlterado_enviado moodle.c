#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice{
  int valor;
  struct Vertice* esq;
  struct Vertice* dir;
  struct Vertice* pai;
} Vertice;

typedef struct Arvore{
  Vertice* raiz;
  int qtde;
} Arvore;

void in_ordem(Vertice *raiz) {
  if(raiz != NULL){
    in_ordem(raiz->esq);
    printf("%d ", raiz->valor);
    in_ordem(raiz->dir);
  }
}

void pre_ordem(Vertice *raiz) {
  if(raiz != NULL){
    printf("%d ", raiz->valor);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
  }
}

void pos_ordem(Vertice *raiz) {
  if(raiz != NULL){
    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%d ", raiz->valor);
  }
}

Vertice *cria_vertice(int valor){
  Vertice* novo = malloc(sizeof(Vertice));
  novo->dir = NULL;
  novo->esq = NULL;
  novo->pai = NULL;
  novo->valor = valor;

  return novo;
}

Arvore *cria_arvore(){
  Arvore* arvore = malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  arvore->qtde = 0;

  return arvore;
}
void inserir(Arvore* arvore, int valor){
  Vertice *novo = cria_vertice(valor);
  if(arvore->raiz == NULL){//arvore vazia
    arvore->raiz = novo;
  }else{//arvore não vazia
    Vertice *anterior = NULL;
    Vertice *atual = arvore->raiz;
    while(atual != NULL){//itera(caminha)
      anterior = atual;
        //arruma ponteiros para inserção
      if(valor < atual->valor){
           atual = atual->esq;
      }
      else if (valor > atual->valor){
        atual = atual->dir;
      }
    }
    //insere
    novo->pai = anterior; //faz pai do novo ser o anterior 
    if(valor > anterior->valor){//valor a ser inserido > valor do pai
      anterior->dir = novo;
      novo->valor = valor; 
    }else{
      anterior->esq = novo;
      novo->valor = valor; 
    }
  }
  arvore->qtde++;
}

int remover_vertice(Arvore* arvore, Vertice* vertice) {
  int valor_removido = vertice->valor; //pro return
  if(vertice->esq == NULL && vertice->dir == NULL){//vertice nao tem filhos
    if(vertice->pai == NULL){ // vertice é raiz
      arvore->raiz = NULL;
    }
        //antigo da erro
    // if(arvore->qtde == 1){ // vertice é raiz
    //     arvore->raiz = NULL;
    // }
    else{//verifica se vertice é filho
      if(vertice->pai->esq == vertice){//é filho esquerdo
        vertice->pai->esq = NULL;
      }
      else if(vertice->pai->dir == vertice){//é filho direito
        vertice->pai->dir = NULL;
      }
        // if(vertice->pai->valor > vertice->valor){ //é filho esquerdo
        // vertice->pai->esq = NULL;
        // }
        // else if(vertice->pai->valor < vertice->valor){//é filho direito
        //     vertice->pai->dir = NULL;
        // }
    }
  }
  else if (vertice->esq != NULL && vertice->dir == NULL){ //vertice tem filho a esquerda
    if(vertice->pai == NULL){//vertice é raiz
      arvore->raiz = vertice->esq; //raiz passa a ser o filho a esquerda
      vertice->esq->pai = NULL; //pai do filho a esquerda é NULL (removo a raiz)
   }else{//nao é raiz  
      if(vertice->pai->esq == vertice){//verifica se vertice é filho esquerdo
        vertice->pai->esq = vertice->esq; //vertice esqeurdo do pai é o filho a esquerda do vertice que vo remover
        vertice->esq->pai = vertice->pai; //pai do filho a esquerda é o pai do vertice que vo remover
       }
      else{//verifica se vertice é filho direito 
        vertice->pai->dir = vertice->esq; //vertice direito do pai é o filho a esquerda do vertice que vo remover
        vertice->esq->pai = vertice->pai; //pai do filho a esquerda é o pai do vertice que vo remover
        }
    }
    //antigo 
    // else{//nao é raiz 
    //     vertice->pai->esq = vertice->esq; //vertice esqeurdo do pai é o filho a esquerda do vertice que vo remover
    //     vertice->esq->pai = vertice->pai; //pai do filho a esquerda é o pai do vertice que vo remover
    // }
  }
  else if(vertice->esq == NULL && vertice->dir != NULL){ //vertice tem filho a direita
    if(vertice->pai == NULL){//vertice é raiz
        arvore->raiz = vertice->dir; //raiz passa a ser o filho a direita
       // vertice->dir->pai = NULL; //pai do filho a direita é NULL (removo a raiz)
      arvore->raiz->pai = NULL;
    }else{//nao é raiz 
       if(vertice->pai->esq == vertice){
            vertice->pai->esq = vertice->dir; //vertice esqeurdo do pai é o filho a direita do vertice que vo remover
            vertice->dir->pai = vertice->pai; //pai do filho a direita é o pai do vertice que vo remover
       }else{
            vertice->pai->dir = vertice->dir; //vertice direito do pai é o filho a direita do vertice que vo remover
            vertice->dir->pai = vertice->pai; //pai do filho a direita é o pai do vertice que vo remover
       }
    }
    //antigo errado (nao verificava se vertice era filho esquerdo ou direito)
    // else{//nao é raiz
    //     vertice->pai->dir = vertice->dir; //vertice direito do pai é o filho a direita do vertice que vo remover
    //     vertice->dir->pai = vertice->pai; //pai do filho a direita é o pai do vertice que vo remover
    // }
    // arvore->qtde--;
    // return valor_removido;
  }
  else{ //tem 2 filhos
      Vertice *atual = vertice->esq; 
      while(atual->dir != NULL){//pega vertice mais a esquerda
        atual = atual->dir;
      }
      //troca de lugar o vértice "pai" com o vertice mais a esquerda para remover vertice "pai"
      vertice->valor = atual->valor;
      atual->valor = valor_removido; 
      remover_vertice(arvore, atual); //pq chamar? pq troque valores do vertice a ser removido com valor do vertice encontrado, chamo funcao de remocao passando referencia do vertice mais baixo (passo o anterior)
      //na função de remocao faz de novo ate n ter filho, ai pega o pai do que quero remover, seta pai como null e da free no vertice,chama recursivamente ate que vire um dos casos mais faceis mencionados acima
  }
  arvore->qtde--;
  return valor_removido;
}

Vertice *buscar_valor(Arvore* arvore, int valor){
  Vertice* atual = arvore->raiz;
  while(atual != NULL){
    if(valor < atual->valor){
      atual = atual->esq;
    }else if(valor > atual->valor){
      atual = atual->dir;
    }else{
      return atual;
    }
  }
  return NULL;
}

void liberar_arvore(Vertice* vertice) {
    if (vertice != NULL) {
        liberar_arvore(vertice->esq);
        liberar_arvore(vertice->dir);
        free(vertice);
    }
}

int main(void) {
  int dados[] = {5, 3, 8, 2, 4, 7, 9, 1, 6, 10};
    Arvore *arvore = cria_arvore();

  for(int i = 0; i < 10; i++){
    inserir(arvore, dados[i]);
    printf("Inseriu %d mostra em ordem -> ", dados[i]);
    in_ordem(arvore->raiz);
    printf("\n");
    printf("Inseriu %d mostra em pré-ordem -> ", dados[i]);
    pre_ordem(arvore->raiz);
    printf("\n");
    printf("Inseriu %d mostra em pós-ordem -> ", dados[i]);
    pos_ordem(arvore->raiz);
    printf("\n");
  }

  for(int i = 0; i < 10; i++){
    Vertice *vertice = buscar_valor(arvore, dados[i]);
    if(vertice != NULL){
      remover_vertice(arvore, vertice);
    }
    printf("Removeu %d mostra em ordem -> ", dados[i]);
    in_ordem(arvore->raiz);
    printf("\n");
    printf("Removeu %d mostra em pré-ordem -> ", dados[i]);
    pre_ordem(arvore->raiz);
    printf("\n");
    printf("Removeu %d mostra em pós-ordem -> ", dados[i]);
    pos_ordem(arvore->raiz);
    printf("\n");
  }

  liberar_arvore(arvore->raiz);
  free(arvore);

    return 0;
}

output

Inseriu 5 mostra em ordem -> 5 
Inseriu 5 mostra em pré-ordem -> 5 
Inseriu 5 mostra em pós-ordem -> 5 
Inseriu 3 mostra em ordem -> 3 5 
Inseriu 3 mostra em pré-ordem -> 5 3 
Inseriu 3 mostra em pós-ordem -> 3 5 
Inseriu 8 mostra em ordem -> 3 5 8 
Inseriu 8 mostra em pré-ordem -> 5 3 8 
Inseriu 8 mostra em pós-ordem -> 3 8 5 
Inseriu 2 mostra em ordem -> 2 3 5 8 
Inseriu 2 mostra em pré-ordem -> 5 3 2 8 
Inseriu 2 mostra em pós-ordem -> 2 3 8 5 
Inseriu 4 mostra em ordem -> 2 3 4 5 8 
Inseriu 4 mostra em pré-ordem -> 5 3 2 4 8 
Inseriu 4 mostra em pós-ordem -> 2 4 3 8 5 
Inseriu 7 mostra em ordem -> 2 3 4 5 7 8 
Inseriu 7 mostra em pré-ordem -> 5 3 2 4 8 7 
Inseriu 7 mostra em pós-ordem -> 2 4 3 7 8 5 
Inseriu 9 mostra em ordem -> 2 3 4 5 7 8 9 
Inseriu 9 mostra em pré-ordem -> 5 3 2 4 8 7 9 
Inseriu 9 mostra em pós-ordem -> 2 4 3 7 9 8 5 
Inseriu 1 mostra em ordem -> 1 2 3 4 5 7 8 9 
Inseriu 1 mostra em pré-ordem -> 5 3 2 1 4 8 7 9 
Inseriu 1 mostra em pós-ordem -> 1 2 4 3 7 9 8 5 
Inseriu 6 mostra em ordem -> 1 2 3 4 5 6 7 8 9 
Inseriu 6 mostra em pré-ordem -> 5 3 2 1 4 8 7 6 9 
Inseriu 6 mostra em pós-ordem -> 1 2 4 3 6 7 9 8 5 
Inseriu 10 mostra em ordem -> 1 2 3 4 5 6 7 8 9 10 
Inseriu 10 mostra em pré-ordem -> 5 3 2 1 4 8 7 6 9 10 
Inseriu 10 mostra em pós-ordem -> 1 2 4 3 6 7 10 9 8 5 
Removeu 5 mostra em ordem -> 1 2 3 4 6 7 8 9 10 
Removeu 5 mostra em pré-ordem -> 4 3 2 1 8 7 6 9 10 
Removeu 5 mostra em pós-ordem -> 1 2 3 6 7 10 9 8 4 
Removeu 3 mostra em ordem -> 1 2 4 6 7 8 9 10 
Removeu 3 mostra em pré-ordem -> 4 2 1 8 7 6 9 10 
Removeu 3 mostra em pós-ordem -> 1 2 6 7 10 9 8 4 
Removeu 8 mostra em ordem -> 1 2 4 6 7 9 10 
Removeu 8 mostra em pré-ordem -> 4 2 1 7 6 9 10 
Removeu 8 mostra em pós-ordem -> 1 2 6 10 9 7 4 
Removeu 2 mostra em ordem -> 1 4 6 7 9 10 
Removeu 2 mostra em pré-ordem -> 4 1 7 6 9 10 
Removeu 2 mostra em pós-ordem -> 1 6 10 9 7 4 
Removeu 4 mostra em ordem -> 1 6 7 9 10 
Removeu 4 mostra em pré-ordem -> 1 7 6 9 10 
Removeu 4 mostra em pós-ordem -> 6 10 9 7 1 
Removeu 7 mostra em ordem -> 1 6 9 10 
Removeu 7 mostra em pré-ordem -> 1 6 9 10 
Removeu 7 mostra em pós-ordem -> 10 9 6 1 
Removeu 9 mostra em ordem -> 1 6 10 
Removeu 9 mostra em pré-ordem -> 1 6 10 
Removeu 9 mostra em pós-ordem -> 10 6 1 
Removeu 1 mostra em ordem -> 6 10 
Removeu 1 mostra em pré-ordem -> 6 10 
Removeu 1 mostra em pós-ordem -> 10 6 
Removeu 6 mostra em ordem -> 10 
Removeu 6 mostra em pré-ordem -> 10 
Removeu 6 mostra em pós-ordem -> 10 
Removeu 10 mostra em ordem -> 
Removeu 10 mostra em pré-ordem -> 
Removeu 10 mostra em pós-ordem -> 
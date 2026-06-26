#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11

typedef struct Celula{
    int valor;
    struct Celula *proximo;
  // struct Celula *anterior;
}Celula;

typedef struct {
    int qtde;
    Celula *primeiro;
}Lista;

typedef struct {
  Lista *lista[tam_hash];
}Hash;

Hash* start_hash(){
  Hash *hash = malloc(sizeof(Hash));
  for(int i = 0; i < tam_hash; i++){
    Lista *lista = malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->qtde = 0;
    hash->lista[i] = lista;
  }
  return hash;
}

void inserir_hash(Hash* hash, int valor){
  int posicao = valor % tam_hash;
  Celula *novaCelula = malloc(sizeof(Celula));
  novaCelula->valor = valor;
  if(hash->lista[posicao] == NULL){
    //novacelula na primeira posicao da lista que ta dentro da osicao especifica do hash
    hash->lista[posicao]->primeiro = novaCelula;
  }else{
    // novo prox = 1
    // 1 = novo
    novaCelula->proximo = hash->lista[posicao]->primeiro;
    hash->lista[posicao]->primeiro = novaCelula; 
    //insere na primeira posicao vazia da lista
  }
}

 void remover_hash(Hash* hash, int valor){
  int posicao = valor % tam_hash;

  if(hash->lista[posicao]->primeiro == NULL){//hash vazio
    return;
  }else{
    Celula *aux = hash->lista[posicao]->primeiro;
      if(aux->valor == valor){
        hash->lista[posicao]->primeiro = aux->proximo;
        //aux = aux->proximo;
        return;
      }
    else{
      while(aux->proximo != NULL){
        aux = aux->proximo;
      }
      if(aux->proximo->valor == valor){
        aux->proximo = aux->proximo->proximo;
      }
    }
  }

   //   Celula *novaCelula = malloc(sizeof(Celula));
    //   int posicao = valor % tam_hash;
    // //  REMOVER: pego valor a ser removido, vejo em que posicao deve ta, percorro lista procurando valor, se encontra retiro ele
    //   if(hash->lista[posicao]->primeiro->valor == valor){
    //     hash->lista[posicao]->primeiro = hash->lista[posicao]->primeiro->proximo; //substitui primeiro pelo prox
    //   }else{
    //     Celula *aux = hash->lista[posicao]->primeiro;
    //     while(aux->proximo != NULL && aux->proximo->valor != valor){
    //       aux = aux->proximo;
    //       if(aux->valor == valor){
    //         aux->proximo = aux->proximo->proximo;
    //       }
    //     }
    //   }


    /*chat! FAZER SOZINHA E SEM 2 PONTEIROS (lu fez com 2 ponteiros)*/
  //  int posicao = valor % tam_hash; //para achar posicao do valor a ser removido na hash
  //  if (hash->lista[posicao]->primeiro == NULL) { //lista vazia, se o valor nao tive na primeira posicao das listas da hash retorna 
  //      return;
  //  }
  //  Celula *aux = hash->lista[posicao]->primeiro; //auxiliar para percorrer a lista de cada posicao da hash 
  //  Celula *anterior = NULL;
  //  if (aux->valor == valor) { //se o valor a ser removido estiver na primeira posicao da lista
  //      hash->lista[posicao]->primeiro = aux->proximo; //faz primeiro valor ser o prox (remoe primeiro valor)
  //      return;
  //  }
  //  while (aux != NULL && aux->valor != valor) { //se o primeiro valor nao for o valor a ser removido ou nao for nulo (negacao dos casos de cima)
  //      anterior = aux; //anterior recebe o primeiro valor da lista
  //      aux = aux->proximo; //o primeiro valor da lista recebe o proximo valor
  //  }
  //  if (aux != NULL) {
  //      anterior->proximo = aux->proximo;
  //  } else {
  //      return;
  //  }

 }

//lu
//  void remover_hash(Hash* hash, int valor){
//   int posicao = valor % tam_hash;
//   Celula *celula = hash->lista[posicao].primeiro;
//   if(celula == NULL){
//     return;
//   }else{
//     if(celula->valor == valor){ 
//       if(celula->proximo == NULL){//se apenas tiver um termo na lista
//         hash->lista[posicao].primeiro = NULL;
//       }else{
//         celula->proximo->anterior = NULL;
//         hash->lista[posicao].primeiro = celula->proximo;
//       }
//     }else{
//       Celula *atual = hash->lista[posicao].primeiro;
//       while(atual!= NULL){
//         if(atual->valor == valor){
//           atual->anterior->proximo = atual->proximo;
//           if(atual->proximo != NULL){
//             atual->proximo->anterior = atual->anterior;
//           }
//           break;
//         }
//         atual = atual->proximo;
//       }
//     }
//   }
  
// }

void imprimir(Hash* hash){
  printf("---------------------\n");
  for(int i = 0; i < tam_hash; i++){
    Celula *novaCelula = hash->lista[i]->primeiro;
    //posicao que o hash esta, hash se move
    printf("%d -> ", i);
    while( novaCelula != NULL){
        printf("%d ", novaCelula->valor);
        novaCelula = novaCelula->proximo;
    }
     printf("\n");
  }
  printf("---------------------\n");
}

int main(void) {
  Hash* hash = start_hash();
  int valor;
  while(1){
    scanf("%d", &valor);
    if(valor == 0)
      break;
    inserir_hash(hash, valor);
  }
  imprimir(hash);
  while(1){
    scanf("%d", &valor);
    if(valor == 0)
      break;
     remover_hash(hash, valor);
  }
  imprimir(hash);
  return 0;
}
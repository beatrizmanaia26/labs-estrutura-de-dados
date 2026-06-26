#include <stdio.h>
#include <stdlib.h> //usar malloc
#define V 8
#define E 20

typedef struct Celula{ 
    struct Celula *anterior; //primeiro membro
    struct Celula *proximo;
    int valor;
} Celula;

typedef struct {
    Celula *head;
    Celula *tail;
    int qtde;
}Fila;

Fila *criarFila(){
    Fila *fila = malloc(sizeof(Fila)); //alocar variavel do tipo fila
    //inicializar membros da fila
    fila->head = NULL; //head é ponteiro ent NULL de inicio
    fila->tail = NULL;
    fila->qtde = 0;
    return fila;
}

Celula *criarCelula(int valor){
    //instanciar variaveis
    Celula *celula = malloc(sizeof(Celula));
    celula->anterior = NULL;
    celula->proximo = NULL;
    celula->valor = valor;
    return celula;
}

void enqueue(Fila *fila, int valor){
  Celula *novo = criarCelula(valor);
  if (fila->qtde == 0) { // fila vazia
    fila->head = novo;
  } else {
    fila->tail->proximo = novo;
    novo->anterior = fila->tail;
  }
  fila->tail = novo;
  fila->qtde++;

}

int dequeue(Fila *fila){
  if(fila->qtde > 0){
    int valor = fila->head->valor; //valor da fila é valor do head
    Celula *temp = fila->head; //para poder dar free (desalocar memoria)
    //quando tem mais de um elemento, fila->head passa a ser o proximo
    fila->head = fila->head->proximo; //para tirar o primeiro elemento, falo que o head eh o proximo
    if(fila->qtde == 1){ //quando tiver um só, o fila->proximo ja vai ser null
        fila->tail = NULL;
    }else{
        fila->head->anterior = NULL;
      }
      fila->qtde--;
      free(temp);
      return valor;
    }//fila vazia
    return -1; 
}

//dado no lab 
int get_index(char x) {
  return x - 114; // corrige rotulo alfabético pra ordem na matriz
}

void inicia_arestas(int arestas[V][V]) {
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      arestas[i][j] = 0;
    }
  }
}

void cria_arestas(int arestas[V][V], int v, int u) { // cria aresta recebe vertice de origem v e destino u
  arestas[v][u] = 1;
}

void mostra_arestas(int arestas[V][V]) {//copiei código slide
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      printf("%d ", arestas[i][j]);
    }
    printf("\n");
  }
}

void mostra_adjacentes(int arestas[V][V], char v) {
  for (int j = 0; j < V; j++) {
      if(arestas[get_index(v)][j] == 1) {
        char letra = j + 114;
        printf("%c -> %c\n", v, letra);
     }
  }
}

void mostra_distancias(int arestas[V][V], char v) {//baseado no sldie que tem branco cinza e preto
  int distancia[] = {-1,-1,-1,-1,-1,-1,-1,-1}; //pra distancia ser -1 (brancos)
  distancia[get_index(v)] = 0; //disttancia dele pra ele mesmo
  Fila *filaQ = criarFila();
  enqueue(filaQ, get_index(v));
  while(filaQ->qtde > 0){//fila nao vazia
    int removido = dequeue(filaQ);
    //funcao adjacente
    for (int j = 0; j < V; j++) {
       if(arestas[removido][j] == 1) { //existe aresta
         // printf("cheguei");
        if(distancia[j] == -1) { //se for branco
          distancia[j] = distancia[removido] + 1; //somando com a primeira aresta
          enqueue(filaQ, j); //colocar na fila
        }
      }
    }
  }
}

    //ANTIGO
    // int lista[v]; //pra guardar cor
    // for (int j = 0; j < V; j++){
    //   // arestas[get_index(v)][j] = -1;  //distancia
    //   // lista[j] = -1; //guardar elementos brancos
    // }
    // //so o especifico é cinza
    // arestas[get_index(v)][get_index(v)] = 0; //cinza se for get_index(v) 
    // lista[get_index(v)] = 0; //começo desse vertice
    // Fila *filaQ = criarFila();
    // enqueue(filaQ, get_index(v));
    // while(filaQ->qtde > 0){//fila nao vazia
    //   int removido = dequeue(filaQ);
    //   //funcao adjacente
    //   for (int j = 0; j < V; j++) {
    //     // if(arestas[get_index(v)][j] == -1) {
    //        // printf("cheguei");
    //       if(lista[j] == -1) { //se for branco
    //         arestas[get_index(v)][j] = arestas[removido][j] + 1; //somando com a primeira aresta
    //         lista[j] = 0; //é cinza
    //         enqueue(filaQ, j); //colocar na fila
    //       // }
    //     }
    //   }

  // implementar
  // chama busca em largura
  //(obter pela implementação do busca em largura e cham busca em largura para cada um dos vértices
// }
//   //print
//   for (int j = 0; j < V; j++) {
//     printf("%d ", distancia[j]);
//   }
//   printf("\n");
// }
int main(void) {
  char lista_de_vertices[V] = {'r', 's', 't', 'u', 'v', 'w', 'x', 'y'};
  char lista_de_arestas[E][2] = {"vr", "rv", "rs", "sr", "sw", "ws", "wt",
                                 "tw", "wx", "xw", "tx", "xt", "tu", "ut",
                                 "xu", "ux", "xy", "yx", "uy", "yu"};
  int arestas[V][V];
  inicia_arestas(arestas);
  printf("Matriz de adjacências\n");
  for (int i = 0; i < E; i++) {
    cria_arestas(arestas, get_index(lista_de_arestas[i][0]),
                 get_index(lista_de_arestas[i][1]));
  }
  mostra_arestas(arestas);
  printf("Lista de adjacências\n");
  for (int i = 0; i < V; i++) {
    mostra_adjacentes(arestas, lista_de_vertices[i]);
  }
  printf("Matriz de distâncias\n");
  for (int i = 0; i < V; i++) {
    mostra_distancias(arestas, lista_de_vertices[i]);
  }
  return 0;
}
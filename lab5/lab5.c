#include <stdio.h>

#define LEN 100

typedef struct {
	char data[LEN];
	int head;
	int tail;
	int qtde;
} Queue;

//se for parenteses aberto adiciono na fila, se for parenteses fechado desisnfilero fila de checagem, quando termina 
//coloca caracteres dentro de uma fila e se na hr que for desenfileirar e n tivr nd ta errado, se chega no final e parentesis aberto tive vazio ta certo, se nao ta errado

int is_full(Queue *queue){
    return queue->qtde == LEN; //se for vdd é 1
}
        
int is_empty(Queue *queue){
    return queue->qtde == 0;
}

void enqueue(Queue *queue, char caracter) {
    if(!is_full(queue)){
        queue->data[queue->tail% LEN] = caracter;
        queue->tail++;
        queue->qtde++;
    }
}

char dequeue(Queue *queue) {
    if(!is_empty(queue)){
        char caracter = queue->data[queue->head % LEN];
        queue->head++; //incrementa head 
        queue->qtde--; 
        return caracter;
    }
    return 0;
}

void show(Queue *queue) {
    for(int i = queue->head; i < queue->tail; i++){
        printf("%c", queue->data[i % LEN]);
    }
   // printf("\n");
}

void start_queue(Queue *queue) {
    queue->head = 0; 
    queue->tail = 0;
    queue->qtde = 0;
}

int main(void) {
    char s[LEN];
    int contadorAbrir = 0;
    int contadorFechar = 0;
    //int validacaoIncorreto = 0;//chat pediu p add isso
    Queue queue;
   // Queue parentesis; jeito q sor pediu p fazer
    fgets(s, sizeof(s), stdin); //le string

   for(int i = 0; s[i] != '\0'; i++){
       enqueue(&queue, s[i]); //enquanto nao acaba coloca caracteres na fila
   }
//desenfileirar, usar segunda fila para verificar () esta correto se para todo ( que abriu fechou 

    //NAO PODE FECHA ) SEM TER ABERTO
    for(int i = 0; s[i] != '\0'; i++){
        char decremento = dequeue(&queue); //para pegar o return da funcao
        if(decremento == '('){ //cada vez que chama o dequeue(&queue) ele desenfileira por isso output ta diferente
            contadorAbrir = contadorAbrir+1;
        }
         else if(decremento == ')'){
             contadorFechar = contadorFechar+1;
         }
         if(contadorAbrir < contadorFechar){
            printf("incorreto");
          //  validacaoIncorreto = 1;
             break;
        }
       show(&queue);
   }
   // if(validacaoIncorreto != 1){
        if(contadorAbrir == contadorFechar){
          printf("correto");
    }
        if(contadorAbrir > contadorFechar){
            printf("incorreto");
        }
   // }
    // printf("abrir %d", contadorAbrir);
    //   printf("fechar %d", contadorFechar);
    return 0;
}

//ou
//   for(int i = 0; s[i] != '\0'; i++){
//         char decremento = dequeue(&queue);
//         if(decremento == '('){ //cada vez que chama o dequeue(&queue) ele desenfileira por isso output ta diferente
//             contadorAbrir = contadorAbrir+1; //tava fznd assim na sala mas coloquei isso depois do if e elseif e antes do show(&queue)
//         }
//          else if(decremento == ')'){
//               contadorFechar = contadorFechar+1;
//              if(contadorAbrir < contadorFechar){
//             printf("incorreto");
//              break;
//         }
//          }
         
//        show(&queue);
//    }

//tira mostra e compara o que tiro, se for (faço que contado valor 1
//se contagem de ( for par retorna verdadeiro
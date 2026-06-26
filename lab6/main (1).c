#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
	int valor;
	struct Celula *proximo;
	struct Celula *anterior;
} Celula;

typedef struct {
	Celula *head;
	Celula *tail;
	int qtde;
} Queue;

Celula *cria_celula(int valor){
	Celula *celula = malloc(sizeof(Celula));
	celula->proximo = NULL;
	celula->anterior = NULL;
	celula->valor = valor;

	return celula;
}

Queue *cria_queue(){
	Queue *queue = malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail = NULL;
	queue->qtde = 0;

	return queue;
}

void enqueue(Queue *queue, int valor){
	 Celula *novo = cria_celula(valor); //colocar valor na celula 
    if(queue->qtde == 0){
        queue->head = novo;
        novo->anterior = queue->tail;
    }else{//fila nao vazia
        queue->tail->proximo = novo;//ponteiro proximo da ultima celula tem que aponta pro novo 
        novo->anterior = queue->tail;
    }
    queue->tail = novo;
    queue->qtde++;
	}

int dequeue(Queue *queue){
	 if(queue->qtde > 0){  
        int valor = queue->head->valor; //valor da fila é valor do head
        Celula *temp = queue->head; //para poder dar free (desalocar memoria)
        //quando tem mais de um elemento, fila->head passa a ser o proximo
        queue->head = queue->head->proximo; //para tirar o primeiro elemento, falo que o head eh o proximo
        if(queue->qtde == 1){ //quando tiver um só, o fila->proximo ja vai ser null
            queue->tail = NULL;
        }else{
            queue->head->anterior = NULL;
        }
        queue->qtde--;
        free(temp);
        return valor;
    }//fila vazia
    return -1; 
}

void show(Queue *queue){
	Celula *atual = queue->head;
    while(atual != NULL){
        printf("%d", atual->valor);
        atual = atual->proximo;
    }
}

//fiz show_invertido igual show mas comecando da tail e pegando anterior
void show_invertido(Queue *queue){
    Celula *atual = queue->tail;
    while(atual != NULL){
        printf("%d", atual->valor);
        atual = atual->anterior;
    }
}

int main(void) {
   
	Queue *qnum1 = cria_queue();
	Queue *qnum2 = cria_queue();
	Queue *res = cria_queue();
	
	char num1[100];
	char num2[100];
	fgets(num1, sizeof(num1), stdin);
	fgets(num2, sizeof(num2), stdin);

	int i = 0;
	while(num1[i] != '\n'){		
		enqueue(qnum1, (int)(num1[i]) - 48);
		enqueue(qnum2, (int)(num2[i]) - 48);
		i++;
		}
	//implementei a partir daqui

    int carry = 0;
    //peguei filas do fim para ir somando os elementos, igual show invertido mas sem o print
    
    Celula *atual1 = qnum1->tail;
    Celula *atual2 = qnum2->tail;
    while(atual1 != NULL){ 
        int soma = atual1->valor + atual2->valor + carry;
        if(soma > 9){
            carry = 1;
            int valorInserido = soma - 10; //-10 pq o 1 vai pro carry e o valor vai ser enqueue na fila
            enqueue(res,valorInserido); //soma valores das 2 filas e coloca na terceira
        }else{
            enqueue(res,soma);
            carry = 0;
        }
        atual1 = atual1->anterior;
        atual2 = atual2->anterior;
    }
    
      if(carry==1){
        enqueue(res,1);
    }
    
    show_invertido(res);

}
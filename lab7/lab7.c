//jeito do sor

//de coloca ler string, quando aparece abertos coloca dentro da pilha e quando aparece fechados faz 
//o decremento(pop) e coloca ele em uma variavel e compara se essa variavel é diferente dos fechados de ) ] e } ou seja,
//se quando chega no fechado de um tipo, o topo da pilha for o aberto do mesmo tipo ta certo, se nao, ta errado 
//tambem verifica se quando aparece [ ja apareceu (, ou seja, quantidade de colchete nao pode ser > que de parentese e 
//assim por diante, ordem de hierarquia

#include <stdio.h>
#include <stdlib.h> ///para malloc

typedef struct Celula{ 
    struct Celula *anterior;
    char valor;
    struct Celula *proximo;
}Celula; //eiras

typedef struct{
    Celula *topo; 
    int qtd;
}Stack;

//inicializar celula
Celula *criar_celula(char valor){
    Celula *celula = malloc(sizeof(Celula));
    celula->anterior = NULL;
    celula->proximo = NULL;
    celula->valor = valor;
    return celula;
}

Stack *start_stack(){
    Stack *stack = malloc(sizeof(Stack));
    stack->qtd = 0;
    stack->topo = NULL;
    return stack; //return no endereço que fez a locacao
}


void push(Stack *pilha, char valor){ 
    Celula *novo = criar_celula(valor);
    if(pilha->qtd > 0){
        novo->anterior = pilha->topo;
        pilha->topo->proximo = novo;
    }
    pilha->topo = novo;
    pilha->qtd++;
}

char pop(Stack *pilha){
    if(pilha->qtd == 0){
        return -1;
    }
    char valor = pilha->topo->valor;
    Celula *temp = pilha->topo;
    pilha->topo = pilha->topo->anterior;
    if(pilha->qtd > 1){
        pilha->topo->proximo = NULL;
    }
    free(temp);
    pilha->qtd--;
    return valor;
}

void mostra(Stack *pilha){
    Celula *atual = pilha->topo;
    while(atual != NULL){
        printf("%c", atual->valor);
        atual = atual->anterior;
    }
    printf("\n");
}

int main(void){
    int chaves = 0;
    int colchete = 0;
    int parenteses = 0;
    
    Stack *stack = start_stack();
    char expr[100]; 
    fgets(expr, sizeof(expr), stdin);

      for(int i = 0; expr[i] != '\0'; i++){
        if(expr[i] == '('){
             push(stack, expr[i]);
             parenteses = parenteses + 1;
        }else if(expr[i] == '['){
            if(colchete>parenteses){
                printf("incorreto");
                return 0;
            }else{
                push(stack, expr[i]);
                colchete = colchete + 1;
            }
        }else if(expr[i] =='{'){
            if(colchete>chaves || parenteses>chaves){
                printf("incorreto");
                return 0;
            }else{
                push(stack, expr[i]);
                chaves = chaves + 1;
            }
         }else if(expr[i] == ')'){
            char abertoParen = pop(stack);
            if(abertoParen != '('){
                printf("incorreto");
                return 0;
            }
        }else if(expr[i] == ']'){
            char abertoCol = pop(stack);
            if(abertoCol != '['){
                printf("incorreto");
                return 0;
            }
        }else if(expr[i] == '}'){
            char abertoChave = pop(stack);
            if(abertoChave != '{'){
                printf("incorreto");
                return 0; 
                /*
                break: interrompe o loop atual e continua a execução do código que vem depois do loop.
                após sair do laço for, o programa continua executando as instruções seguintes, c
                omo a verificação da pilha e o printf final.

                return 0: Finaliza a execução da função onde está inserido. No caso da função main,
                encerra o programa completamente. Portanto, ao usar return 0, o programa termina imediatamente
                */
            }
        }
          //verificar se lista nao ta vazia ta errado
    //contador controla hierarquia nao pode ( fora de [ e [ fora da {
          //nao pode chave dentro de parenteses e parenteses dentro de colchete
          //se abre chave e colcehte < 0 errado
        //     parenteses = parenteses - 1;
        // }else if(expr[i] == ']'){
        //     colchete = colchete - 1;
        // else if(expr[i] == '}'){
        //     chaves = chaves - 1;
        // }
          
       }
        if(stack->qtd == 0){
            printf("correto");
            
        }else{
            printf("incorreto");
        }
     mostra(stack);
    
    
	return 0;
}

/*
todo parenteses, colchete e chave que abre tem que fecha
ordem certa {[()]}

le  qualquer simbulo abet ocoloca na pilha, le fechado tira da pilha 
se nao vier nada ou 
*/
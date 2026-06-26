/*LAB

insere mostra o heap, remove mostrs o heap, ultimo pai recebe heap como paremtro (prestaa tencao no que recebe como parametro)
*/

#include <stdio.h>
#include <stdlib.h>

#define LEN 10

typedef struct {
  int valores[LEN];
  int qtde;
} heap;

int filho_esq(int pai) { //passa indice do pai retorna indice do filho
    //verificar se existe esse filho
    return 2*pai + 1;
}

int filho_dir(int pai) { 
    return 2*pai + 2;
    }

int Pai(int filho) { 
   //passa indice do filho devolve indice do pai
   return filho-1/2;
    }

int ultimo_pai(heap *h) { 
  return (h->qtde/2) - 1;
}

void peneirar(heap *h, int pai) { 
    int maior_indice = pai;    
            //ve se filho esquerdo é maior que pai && ve se filho esq existe (indice do filho < qtde)
    if(h->valores[maior_indice] < h->valores[filho_esq(pai)] && filho_esq(pai) < h->qtde){
         maior_indice = filho_esq(pai); //atribui o índice do filho esquerdo a maior_indice
    }
    if(h->valores[maior_indice] < h->valores[filho_dir(pai)] && filho_dir(pai) < h->qtde){
        maior_indice = filho_dir(pai);
    }
    if(maior_indice > pai){
        int temp = h->valores[pai]; //valor do pai
        h->valores[pai] = h->valores[maior_indice]; //valor do pai passa a ser o do maior filho 
        h->valores[maior_indice] = temp; //valor do maior filho passa a ser o valor do pai
        peneirar(h, maior_indice); //chama o peneirar para ver se o novo pai continua sendo maior que os filhos
    }
    //antes
    //  if (h->valores[filho_esq(pai)] > h->valores[pai]) {

    //     h->valores[pai] = h->valores[filho_esq(pai)];
    //     h->valores[filho_esq(pai)] = h->valores[pai];
    //     peneirar(h, filho_esq(pai));


    // } else if(h->valores[filho_dir(pai)] > h->valores[pai]) {
    //     h->valores[pai] = h->valores[filho_dir(pai)];
    //     h->valores[filho_dir(pai)] = h->valores[pai];
    //     peneirar(h, filho_dir(pai));
    // }

}
/*
-IDENTIFCAR QUE NAO TEM PROPRIEDADE ESTRUTURAL
  -> se pai for > que algum dos filhos n tem propriedade estrutural
  -identifico que ta errado, troco pai com maior filho
  **sempre que inserir algm no heap ou remover alguem do heap tem que verificar se propriedade estrutural ta ok
  -na hora de consturir o peneirar verifica qual é o maior filho e ve se o maior filho é maior que o pai, ai troca (chama funcao que faz isso recursivamente)
  (no final verifica se os filhos do pai sao folhas(nao tem filhos) ou se tem filhos, se tiver compara neles tb)
   *se filhos forem iguais troca com o da esquerda
*/

void mostrar(heap *h) {
    for(int i = 0; i<h->qtde; i++){
        printf("%d ", h->valores[i]); 
    }
    printf("\n");
}

void construir(heap *h) {
    //comeca do ultimo pai, for inverso
    //posicoes 0 e (n/2)-1, ou seja, todos os nos quesao pais
    //indice maior é 0 menor é do ultimo pai
    for(int i = ultimo_pai(h); i >= 0; i--){
        peneirar(h,i);
    }
    //antes
    //  for(int i = 0; i< ultimo_pai(h); i++){
    //     peneirar(h,ultimo_pai(h));
    // }
/*
uncao construir percorre todos os pais e fchama peneirr pra todo pai
-se peneirar trocou elemento chama o peneirar pro filho 
-algoritmo construir transforma qualquer vetor em um HEAP. Como os indices i,[n/2]<=i<n sao folhas, basta aplicar o sift entre
as posicoes 0 e (n/2)-1, ou seja, todos os nos quesao pais
*/

}

void inserir(heap *h, int valor) {
  if(h->qtde < LEN){ //nao ta vazio
    h->valores[h->qtde] = valor; //insere sempre no indice da qtde
    h->qtde++;
    construir(h);
  }
}

 void remover(heap *h) {
 if(h->qtde > 0){
     int maior_valor = h->valores[0];
     h->valores[0] = h->valores[h->qtde - 1]; //coloca ultimo valor do heap ( o na posicao qtde-1) no topo do heap
     h->valores[h->qtde - 1] = maior_valor;
     h->qtde-- ; //remove o maior d=valor da heap ao diminuir seu tamanho
     construir(h);
     }
    else{
        return; 
    }
 }

/*
EXCLUSAO:

-retorna quem ta na posicao 0 (raiz), que é o maior numero
-para remover pego primeiro valor do arranjo, troco com ultimo, reduzo o tamanho do arranjo,
faço troca e decremento quantidade do arranjo e pego oarrano reduzido e mando pro constuir 1:6
-depois de remover, construir pega ultimo pai e mando pro peneirar que ve se precisa peneirar, pega o prox pai e mando pro peneirar... 
*/

int main(void) {
  heap *h = malloc(sizeof(heap));
  int valor;
  h->qtde = 0;
  for (int i = 0; i < LEN; i++) {
    scanf("%d", &valor);
    inserir(h, valor);
    mostrar(h);
  }
   for (int i = 0; i < LEN; i++) {
     remover(h);
     mostrar(h);
   }

  return 0;
}
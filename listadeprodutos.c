#include "listadeprodutos.h"

PLISTA criarLista(){
  PLISTA res = (PLISTA) malloc(sizeof(LISTADEPRODUTOS));
  int x;
  for (x=0;x<NUMTIPOS;x++){
    res->LISTADELISTAS[x]=(PONT) malloc(sizeof(REGISTRO));
    res->LISTADELISTAS[x]->id=-1;
    res->LISTADELISTAS[x]->quantidade=0;
    res->LISTADELISTAS[x]->valorUnitario=0;
    res->LISTADELISTAS[x]->proxProd=NULL;
  }
  return res;
}


int tamanho(PLISTA l){
  int tam = 0;
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      atual = atual->proxProd;
      tam++;
    }
  }
  return tam;
}

PONT buscarID(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual;
      atual = atual->proxProd;
    }
  }
  return NULL;
}

PONT buscarIDTipo(PLISTA l, int id, int tipo){
  if (tipo<0 || tipo>=NUMTIPOS) return NULL;
  PONT atual = l->LISTADELISTAS[tipo]->proxProd;
  while (atual) {
    if (atual->id == id) return atual;
    atual = atual->proxProd;
  }
  return NULL;
}

void exibirLog(PLISTA f){
  int numElementos = tamanho(f);
  printf("Log lista [elementos: %i]\n", numElementos);
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    printf("  #TIPO: %i -> ", x);
    atual = f->LISTADELISTAS[x]->proxProd;
    while (atual){
      printf(" [%i;%i;%i;$%i]", atual->id, atual->quantidade, atual->valorUnitario, atual->quantidade*atual->valorUnitario);
      atual = atual->proxProd;
    }
    printf("\n");
  }
  printf("\n");
}

int consultarValorUnitario(PLISTA l, int id){
  int x;
  PONT atual;
  for (x=0;x<NUMTIPOS;x++){
    atual = l->LISTADELISTAS[x]->proxProd;
    while (atual) {
      if (atual->id == id) return atual->valorUnitario;
      atual = atual->proxProd;
    }
  }
  return 0;
}

PONT buscaValorTotalINS(PLISTA l, int tipo, int valorTotal, PONT* ant){
  PONT atual;
  int i;

  *ant = l -> LISTADELISTAS[tipo];
  atual = l->LISTADELISTAS[tipo]->proxProd;

  for(i = 0; i < NUMTIPOS; i++){
    atual = l -> LISTADELISTAS[i] -> proxProd;
    while(atual){
      if(atual -> quantidade * atual -> valorUnitario == valorTotal) return atual;
      *ant = atual;
      atual = atual -> proxProd;
    }
  }

  return NULL;
}



bool inserirNovoProduto(PLISTA l, int id, int tipo, int quantidade, int valor){
  PONT novo, ant;

  /* Testa se os valores recebidos são positivos e se o TIPO esta no intervalo correto */
  if(id <= 0 || quantidade <= 0 || valor <= 0 || tipo < 0 || tipo > NUMTIPOS-1) return false;

  /* Busca o id e analisa se ja existe um produto com o mesmo id */
  novo = buscarID(l, id);
  if(novo != NULL) return false;

  /* Busca a posição certa do REGISTRO */
  novo = buscaValorTotalINS(l, tipo, quantidade*valor, &ant);
  if(novo != NULL) return false;

  novo = (PONT) malloc(sizeof(REGISTRO));
  novo -> id = id;
  novo -> quantidade = quantidade;
  novo -> valorUnitario = valor;

  novo -> proxProd = ant -> proxProd;
  ant -> proxProd = novo;

  return true;
}



bool removerItensDeUmProduto(PLISTA l, int id, int quantidade){

  /* COMPLETAR */

  return false;
}


bool atualizarValorDoProduto(PLISTA l, int id, int valor){

  /* COMPLETAR */

  return false;
}

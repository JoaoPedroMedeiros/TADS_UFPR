#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct aviao {
  int id;
  char nome[30];
  char origem[30];
  char destino[30];
} Aviao;

typedef struct item {
  Aviao aviao;
  struct item *before;
  struct item *next;
} Item;

typedef struct fila {
  Item *first;
  Item *last;
  int size;
} Fila;

/**
 * Aloca um item de uma fila.
 */
Item* newItem(Aviao aviao) {
  Item *item = (Item*) malloc(sizeof(Item));
  item->aviao = aviao;
  item->before = NULL;
  item->next = NULL; 
  return item;
}

/**
 * Preenche as informações iniciais de uma nova fila.
 */
void new(Fila *fila) {
  fila->first = NULL;
  fila->last = NULL;
  fila->size = 0;
}

/**
 * Adiciona um item no fim da fila.
 */
void push(Fila *fila, Aviao aviao) {
  Item *item = newItem(aviao);
  
  // Se a fila não estiver vazia, diz que o
  // próximo do último é o novo item.
  if (fila->size > 0)
    fila->last->next = item;
    
  // Diz que o anterior do novo item é o antigo
  // último.
  item->before = fila->last;
  
  // Diz que o último é o novo item.
  fila->last = item;
    
  // Incrementa o número de itens.
  fila->size++;
  
  // Se esse foi o primeiro elemento a ser adicionado,
  // então diz que ele é o primeiro também.
  if (fila->size == 1)
    fila->first = fila->last;
}

/**
 * Remove um item do início da fila.
 */
int pop(Fila *fila) {
  if (fila->size > 0) {
    
    // Marca o primeiro como desalocado.
    Item *desalocado = fila->first;
    
    // Se tiver mais de um item na fila, diz que o anterior
    // do segundo é nulo.
    if (fila->size > 1)
      desalocado->next->before = NULL;
    
    // Aponta o segundo como novo primeiro
    fila->first = desalocado->next;
    
    // Decrementa o tamanho.
    fila->size--;
    
    // Se esse foi o último item desalocado,
    // marca o último como nulo.
    if (fila->size == 0)
      fila->last = NULL;
    
    // Desaloca o item que foi removido.
    free(desalocado);
    
    // Retorna sucesso.
    return 1;  
  }
  
  // Se a fila estiver vazia, retorna erro.
  return 0;
}

int op(int min, int max) {
  int op;
  
  printf("Opcao: ");
  do {
    scanf("%d", &op);
    fflush(stdin);
  }
  while (op < min || op > max);
  return op;
}

int menu() {
  printf("1. Adicionar aviao na fila de decolagem \n");
  printf("2. Adicionar aviao na fila de pouso     \n");
  printf("3. Autorizar decolagem                  \n");
  printf("4. Autorizar pouso                      \n");
  printf("5. Exibir fila de decolagem             \n");
  printf("6. Exibir fila de pouso                 \n");
  printf("0. Sair                                 \n");
  return op(0, 6);
}

void desenha_painel_aviao(Aviao aviao) {
  printf("================================\n");
  printf("IDENTIFICADOR: %d               \n", aviao.id);
  printf("NOME.........: %s               \n", aviao.nome);
  printf("ORIGEM.......: %s               \n", aviao.origem);
  printf("DESTINO......: %s               \n", aviao.destino);
  printf("================================\n");
}

void substitui_espaco(char texto[], char csub) {
  int i;
  for (i = 0; i < strlen(texto); i++)
    if (texto[i] == ' ')
      texto[i] = csub;
}

void recupera_aviao_usuario(Aviao *aviao) {
  desenha_painel_aviao(*aviao);

  printf("Identificador: ");
  scanf("%d", &(aviao->id));
  fflush(stdin);

  system("cls");
  desenha_painel_aviao(*aviao);

  printf("Nome: ");
  gets(aviao->nome);
  fflush(stdin);
  substitui_espaco(aviao->nome, '_');

  system("cls");
  desenha_painel_aviao(*aviao);

  printf("Origem: ");
  gets(aviao->origem);
  fflush(stdin);
  substitui_espaco(aviao->origem, '_');

  system("cls");
  desenha_painel_aviao(*aviao);
  
  printf("Destino: ");
  gets(aviao->destino);
  fflush(stdin);
  substitui_espaco(aviao->destino, '_');

  system("cls");
  desenha_painel_aviao(*aviao);
}

char vazio[] = " ";

void inicializa_aviao(Aviao *aviao) {
  aviao->id = 0;
  strcpy(aviao->nome, vazio);
  strcpy(aviao->origem, vazio);
  strcpy(aviao->destino, vazio);
}

void adiciona_aviao(Fila *fila) {
  //Recupera um novo avião.
  Aviao aviao;
  do {
    system("cls");
    inicializa_aviao(&aviao);
    recupera_aviao_usuario(&aviao);
    
    printf("Confirma os dados?\n");
    printf("1. Sim; 2. Nao    \n");
  }
  while (op(1, 2) == 2);
  
  //Adiciona o avião na fila.
  push(fila, aviao);
}

void autorizar(Fila *fila) {
  if (fila->size > 0) {
    printf("O seguinte aviao sera autorizado.\n");
    desenha_painel_aviao(fila->first->aviao);
    
    printf("\nConfirma?\n");
    printf("1. Sim; 2. Nao    \n");
    
    if (op(1, 2) == 1) {
      pop(fila);
      printf("Operacao efetuada com sucesso!\n");
    }
    else
      printf("A operacao nao foi efetuada!\n");
  }
  else
    printf("Nenhum aviao na fila.\n");
  printf("\n");
  system("pause");
}

void mostrar_fila(Fila *fila) {
  int i = 0;
  Item *atual = fila->first;
  while (atual != NULL) {
    printf("AVIAO %d:\n", ++i);
    desenha_painel_aviao(atual->aviao);
    atual = atual->next;
  }
  printf("TOTAL DE AVIOES: %d\n\n", i);
  system("pause");
}

void main() {
  Fila pouso;
  Fila decolagem;
   
  new(&pouso);
  new(&decolagem);
  
  int op;
  while (1) {
    system("cls");
    
    op = menu();
    
    switch (op) {
      case 1:
        system("cls");
        adiciona_aviao(&decolagem);
        break;
      case 2:
        system("cls");
        adiciona_aviao(&pouso);
        break;
      case 3:
        system("cls");
        printf("DECOLAGEM:\n\n");
        autorizar(&decolagem);
        break;
      case 4:
        system("cls");
        printf("POUSO:\n\n");
        autorizar(&pouso);
        break;
      case 5:
        system("cls");
        printf("FILA DE DECOLAGEM:\n\n");
        mostrar_fila(&decolagem);
        break;
      case 6:
        system("cls");
        printf("FILA DE POUSO:\n\n");
        mostrar_fila(&pouso);
        break;
      case 0:
        exit(0);
        break;
    }
  }
  
}











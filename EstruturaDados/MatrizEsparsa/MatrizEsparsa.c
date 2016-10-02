#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <locale.h>

/**
 * Definição do tipo de dado que representa o valor que será armazenado na lista.
 * A princípio está declarado como inteiro, entretanto, se for preciso alterá-lo,
 * a mudança será feita somente aqui.
 */
typedef int Value;

/**
 * Constante estática utilizada para guardar a string de entrada de dados do valor.
 * Caso seja necessário alterar o tipo de dado de Value, só é preciso alterar seu
 * leitor aqui.
 */
static const char SCANNER_ITEM[] = "%d";
static const char PRINTER_ITEM[] = "%d";

/**
 * Definição de um tipo de dado que representa uma posição XY dentro de
 * uma matriz.
 */
typedef struct pos2D {
  int x;
  int y;

} Pos2D;

/**
 * Item de que será armazenado na lista que contém o valor esparso diferente de 0
 * bem como sua posição na matriz.
 */
typedef struct item {
  Pos2D pos;
  Value value;
} Item;

/**
 * Nó da lista.
 */
typedef struct node {
  Item item;
  struct node *before;
  struct node *next;

} Node;

/**
 * Definição da lista que representa uma matriz.
 */
typedef struct positions {
  int lenX;
  int lenY;
  int size;
  Node *first;
  Node *last;

} Positions;

/*========================================================================*/
/* 1.0_dec - Funções referentes à manipulação da lista.
/*========================================================================*/
// 1.1_dec - Função que faz a alocação de memória para cada nodo criado na lista;
Node* newNode(Value value, int x, int y);
// 1.2_dec - Função que faz a alocação de memória para uma lista.
void new(Positions *positions, int x, int y);
// 1.3_dec - Função que insere na lista um nodo alocado;
int add(Positions *positions, Node *node);
// 1.4_dec - Função que lê (busca) os dados de uma lista por posição.
Item* findByPos(Positions *positions, int x, int y);
// 1.5_dec - Função que lê (busca) os dados de uma lista por valor.
Positions* findByValue(Positions *positions, Value value);
// 1.6_dec - Função que libera a memória alocada para a lista;
void freePositions(Positions *positions);
/*========================================================================*/
/* 2.0_dec - Funções referentes à manipulação da matriz
/*========================================================================*/
// 2.1_dec - Função que soma duas matrizes;
Positions* soma_matriz(Positions *matriz1, Positions *matriz2);
// 2.2_dec - Função que subtrai duas matrizes;
Positions* subtrai_matriz(Positions *matriz1, Positions *matriz2);
// 2.3_dec - Função que multiplica duas matrizes;
Positions* multiplica_matriz(Positions *matriz1, Positions *matriz2);
// 2.4_dec - Função que gera a matriz transposta;
Positions* aplica_transposta(Positions *matriz);
// 2.5_dec - Função que imprime todos os dados da matriz, inclusive os zeros;
int imprime_matriz(Positions *matriz);
// 2.6_dec - Função que imprime os elementos da diagonal principal, inclusive os zeros caso existam.
int imprime_diagonal_principal(Positions *matriz);

/*========================================================================*/
/* Funções assistentes
/*========================================================================*/
int op(int min, int max, char mensagem[]) {
  int op;
  if (mensagem != NULL)
    printf(mensagem);
  else
    printf("Opcao: ");
  do {
    scanf("%d", &op);
    fflush(stdin);
  }
  while (op < min || op > max);
  return op;
}

int permite_acentuacao() {
  setlocale(LC_ALL, "");
}

/*========================================================================*/
/* Funções de interface com o usuário
/*========================================================================*/
void recupera_node_usuario(int *x, int *y, Value *value) {

  int opcao;

  do {
    printf("Digite a linha...: ");
    do {
      scanf("%d", y);
      fflush(stdin);
    }
    while (*y < 1);

    printf("Digite a coluna..: ");
    do {
      scanf("%d", x);
      fflush(stdin);
    }
    while (*x < 1);

    printf("Digite o valor...: ");
    scanf(SCANNER_ITEM, value);
    fflush(stdin);

    printf("\n");

    printf("Confirma a adição?\n");
    printf("1 - Sim, 2 - Não\n");

    *x = *x - 1;
    *y = *y - 1;

    opcao = op(1, 2, NULL);
  }
  while (opcao == 2);
}

void imprime_menu_principal() {
  printf("Menu:\n");
  printf("1. Adicionar\n");
  printf("2. Mostrar matriz\n");
  printf("3. Mostrar diagonal principal\n");
  printf("4. Buscar item\n");
  printf("5. Somar\n");
  printf("6. Subtrair\n");
  printf("7. Multiplicar\n");
  printf("8. Aplicar transposta\n");
  printf("9. Limpar matriz\n");
  printf("0. Sair\n");
}

void find(Positions *positions) {
  int opBusca;
  Value value;
  int r, i;
  int x;
  int y;

  Node *atual;
  Positions *encontrados;
  Item *encontrado;

  while (1) {
    system("cls");

    printf("Procurar por:\n");
    printf("1. Posição\n");
    printf("2. Valor\n");
    printf("0. Voltar\n\n");

    opBusca = op(0, 2, NULL);

    switch (opBusca) {
      case 1:
        printf("\n");
        y = op(1, positions->lenY, "Digite a linha..: ") - 1;
        x = op(1, positions->lenX, "Digite a coluna.: ") - 1;
        printf("\n");

        encontrado = findByPos(positions, x, y);

        printf("Valor encontrado: ");
        printf(PRINTER_ITEM, encontrado != NULL ? encontrado->value : 0);
        printf("\n\n");
        break;
      case 2:
        printf("Digite o valor: ");
        scanf(SCANNER_ITEM, &value);
        fflush(stdin);
        printf("\n");

        encontrados = findByValue(positions, value);

        if (encontrados->size > 0) {
          atual = encontrados->first;
          while (atual != NULL) {
            printf("Encontrado em linha %d coluna %d.", atual->item.pos.y + 1, atual->item.pos.x + 1);
            printf("\n");
            atual = atual->next;
          }
          printf("\n");
        }
        else
          printf("Nenhum item encontrado com esse valor.\n\n");

        freePositions(encontrados);

        break;
      case 0:
        goto saida_loop;
        break;
    }
    system("pause");
  }
  saida_loop:;
}

void recupera_matriz_operacao(int maxX, int maxY, Positions *nova) {

  int x, y;
  Value value;

  int opcao;

  while (1) {
    system("cls");
    printf("Digite os itens da matriz para efetuar a operação\n");
    printf("Máximo linhas.: %d\n", maxY);
    printf("Máximo colunas: %d\n\n", maxX);

    printf("Opções:\n");
    printf(" 1. Adicionar\n");
    printf(" 2. Mostrar matriz\n");
    printf(" 3. Ver resultado\n\n");

    opcao = op(1, 3, NULL);

    if (opcao == 1) {
      y = op(1, maxY, "Digite a linha.: ");
      x = op(1, maxX, "Digite a coluna: ");

      y--;
      x--;

      printf("Digite o valor.: ");
      scanf(SCANNER_ITEM, &value);
      fflush(stdin);

      add(nova, newNode(value, x, y));
    }
    else if (opcao == 2) {
      imprime_matriz(nova);
      system("pause");
    }
    else
      break;
  }
}

void recupera_numero_colunas_multiplicacao(int *maxX) {
  printf("Digite o número de colunas: ");
  do {
    scanf("%d", maxX);
  }
  while (*maxX < 1);
}

void limpar(Positions *positions) {
  freePositions(positions);
  new(positions, 0, 0);
}

/*========================================================================*/
/* Main                                
/*========================================================================*/
void main() {
  permite_acentuacao();

  Positions positions;
  Positions operada;
  Positions *resultado;

  //Inicializa a matriz.
  new(&positions, 0, 0);

  int x, y, maxX;
  Value value;

  // Entra no menu principal e fica aqui até o usuário decidir sair.
  while (1) {
    system("cls");

    //Desenha o menu
    imprime_menu_principal();

    //Pergunta a opção.
    int opMenu = op(0, 9, NULL);

    system("cls");
 
    //Verifica qual foi a opção.
    switch (opMenu) {
      case 1:
        recupera_node_usuario(&x, &y, &value);
        add(&positions, newNode(value, x, y));
        break;
      case 2:
        imprime_matriz(&positions);
        system("pause");
        break;
      case 3:
        imprime_diagonal_principal(&positions);
        system("pause");
        break;
      case 4:
        find(&positions);
        break;
      case 5:
        new(&operada, positions.lenX, positions.lenY);

        recupera_matriz_operacao(positions.lenX, positions.lenY, &operada);
        resultado = soma_matriz(&positions, &operada);

        system("cls");

        printf("RESULTADO:\n\n");
        imprime_matriz(resultado);

        freePositions(&operada);
        freePositions(resultado);

        system("pause");
        break;
      case 6:
        new(&operada, positions.lenX, positions.lenY);

        recupera_matriz_operacao(positions.lenX, positions.lenY, &operada);
        resultado = subtrai_matriz(&positions, &operada);

        system("cls");

        printf("RESULTADO:\n\n");
        imprime_matriz(resultado);

        freePositions(&operada);
        freePositions(resultado);

        system("pause");
        break;
      case 7:
        recupera_numero_colunas_multiplicacao(&maxX);

        new(&operada, maxX, positions.lenX);
        recupera_matriz_operacao(maxX, positions.lenX, &operada);

        resultado = multiplica_matriz(&positions, &operada);

        system("cls");

        printf("RESULTADO:\n\n");
        imprime_matriz(resultado);

        freePositions(&operada);
        freePositions(resultado);

        system("pause");
        break;
      case 8:
        resultado = aplica_transposta(&positions);
        imprime_matriz(resultado);
        freePositions(resultado);
        system("pause");
        break;
      case 9:
        limpar(&positions);
        printf("Matriz zerada com sucesso!\n\n");
        system("pause");
        break;
      case 0:
        exit(0);
    }
  }
}

/*========================================================================*/
/* 1.0_impl
/*========================================================================*/
// 1.1_impl
Node* newNode(Value value, int x, int y) {
  Node *node = malloc(sizeof(Node));
  node->item.pos.x = x;
  node->item.pos.y = y;
  node->item.value = value;
  node->before = NULL;
  node->next = NULL;
  return node;
}
// 1.2_impl
void new(Positions *positions, int x, int y) {
  positions->first = NULL;
  positions->last = NULL;
  positions->size = 0;
  positions->lenX = x;
  positions->lenY = y;
}

void adiciona_depois(Positions *positions, Node *nodeBase, Node *nodeAdd) {
  if (positions->last == nodeBase)
    positions->last = nodeAdd;

  if (nodeBase->next != NULL)
    nodeBase->next->before = nodeAdd;

  nodeAdd->next = nodeBase->next;
  nodeBase->next = nodeAdd;
  nodeAdd->before = nodeBase;
}

void adiciona_antes(Positions *positions, Node *nodeBase, Node *nodeAdd) {
  if (positions->first == nodeBase)
    positions->first = nodeAdd;

  if (nodeBase->before != NULL)
    nodeBase->before->next = nodeAdd;

  nodeAdd->before = nodeBase->before;
  nodeBase->before = nodeAdd;
  nodeAdd->next = nodeBase;
}

// 1.3_impl
int add(Positions *positions, Node *node) {
  //Se não tiver um primeiro registro, adiciona como primeiro.
  if (positions->size == 0) {
    positions->first = node;
    positions->last = node;
  }
  //Se já existe um registro adicionado, encontra a posição para adicionar.
  else {
    Node *nodeAux = positions->first;

    while (nodeAux != NULL && nodeAux->item.pos.y < node->item.pos.y)
      nodeAux = nodeAux->next;

    // Se o nó auxiliar estiver null, significa que a posição Y do nó que está sendo
    // é a maior entre todos os nós que já existem. Por isso, adiciona no final.
    if (nodeAux == NULL)
      adiciona_depois(positions, positions->last, node);
    // Senão, significa que o nodeAux está apontando para o primeiro item com Y maior
    // ou igual ao Y do item que está sendo adicionado.
    else
      // Se forem iguais, precisa adicionar em relação à posição X
      if (nodeAux->item.pos.y == node->item.pos.y) {

        // Se o x for maior que o x do nó adicionado, adiciona antes.
        if (nodeAux->item.pos.x > node->item.pos.x) {
          adiciona_antes(positions, nodeAux, node);
        }
        // Senão, procura até o fim da linha alguém que tenha o x igual ou maior que o x adicionado.
        else {
          while (nodeAux != NULL && nodeAux->item.pos.x < node->item.pos.x && nodeAux->item.pos.y == node->item.pos.y)
            nodeAux = nodeAux->next;

          // Se o nó auxiliar estiver null, significa que estava na ultima linha e não encontrou
          // ninguém com um x maior, então adiciona depois do último.
          if (nodeAux == NULL)
            adiciona_depois(positions, positions->last, node);
          else {
            // Se tiver saído da busca por chegar na linha seguinte, retorna para o nó anterior
            if (nodeAux->item.pos.y > node->item.pos.y)
              nodeAux = nodeAux->before;

            // Enfim, se o encontrou um x maior que o x adicionado, adiciona antes.
            if (nodeAux->item.pos.x > node->item.pos.x)
              adiciona_antes(positions, nodeAux, node);
         
            // Senão, significa que é pra adicionar em uma posição que já existe,
            // então substitui e aponta o ponteiro passado por parâmetro para o
            // nó antigo com valor substituído.
            else
              if (nodeAux->item.pos.x == node->item.pos.x) {
                nodeAux->item.value = node->item.value;
                //Limpa o node da memória porque ele não foi adicionado na lista.
                free(node);
                //Aponta o node para nodeAux porque ele virou o 'adicionado'
                node = nodeAux;
              }
              else
                // Senão significa que não encontrou nenhum maior, então adiciona
                // depois do último encontrado na linha.
                adiciona_depois(positions, nodeAux, node);
          }
        }
      }
      // Se só encontrou um y maior que o y adicionado, adiciona antes.
      else
        adiciona_antes(positions, nodeAux, node);
  }

  //Altera o máximo de x se precisar
  if (node->item.pos.x + 1 > positions->lenX)
    positions->lenX = node->item.pos.x + 1;

  //Altera o máximo de y se precisar
  if (node->item.pos.y + 1 > positions->lenY)
    positions->lenY = node->item.pos.y + 1;

  positions->size++;
  return 1;
}

// 1.4_impl
Item* findByPos(Positions *positions, int x, int y) {
  int px, py;

  if (positions->size == 0)
    return NULL;

  Node *node = positions->first;
  while (node != NULL) {
    px = node->item.pos.x;
    py = node->item.pos.y;

    if (py < y)
      node = node->next;
    else if (py == y)
      if (px < x)
        node = node->next;
      else if (px == x)
        return &node->item;
      else
        return NULL;
    else
      return NULL;
  }
  return NULL;
}
// 1.5_impl
Positions* findByValue(Positions *positions, Value value) {
  Positions *result = (Positions*) malloc(sizeof(Positions));
  new(result, 0, 0);

  int x, y;

  Node *aux = positions->first;
  if (value != 0)
    while (aux != NULL) {
      if (aux->item.value == value)
        add(result, newNode(value, aux->item.pos.x, aux->item.pos.y));
    
      aux = aux->next;
    }
  else
    for (y = 0; y < positions->lenY; y++)
      for (x = 0; x < positions->lenX; x++)
        if (aux != NULL && aux->item.pos.x == x && aux->item.pos.y == y)
          aux = aux->next;  
        else
          add(result, newNode(value, x, y));  
  
  return result;
}
// 1.6_impl
void freePositions(Positions *positions) {
  Node *node = positions->first;
  Node *next = NULL;
  while (node != NULL) {
    next = node->next;
    free(node);
    node = next;
  }
  free(positions);
}

/*========================================================================*/
/* 2.0_impl
/*========================================================================*/
// 2.1_impl
Positions* soma_matriz(Positions *matriz1, Positions *matriz2) {
  Positions *result = (Positions*) malloc(sizeof(Positions));
  new(result, matriz1->lenX, matriz1->lenY);

  if(matriz1->lenX != matriz2->lenX && matriz1->lenY != matriz2->lenY)
    return result;

  Value value1, value2, valueSoma;
  Node *node1 = matriz1->first;
  Node *node2 = matriz2->first;

  int x, y;
  for (y = 0; y < matriz1->lenY; y++)
    for (x = 0; x < matriz1->lenX; x++) {
      value1 = node1 != NULL && node1->item.pos.x == x && node1->item.pos.y == y ? node1->item.value : 0;
      value2 = node2 != NULL && node2->item.pos.x == x && node2->item.pos.y == y ? node2->item.value : 0;

      valueSoma = value1 + value2;
      if (valueSoma != 0)
        add(result, newNode(valueSoma, x, y));

      if (value1 != 0)
        node1 = node1->next;
      if (value2 != 0)
        node2 = node2->next;
    }

  return result;
}

// 2.2_impl
Positions* subtrai_matriz(Positions *matriz1, Positions *matriz2) {
  Positions *result = (Positions*) malloc(sizeof(Positions));
  new(result, matriz1->lenX, matriz1->lenY);

  if(matriz1->lenX != matriz2->lenX && matriz1->lenY != matriz2->lenY)
    return result;

  Value value1, value2, valueSub;
  Node *node1 = matriz1->first;
  Node *node2 = matriz2->first;

  int x, y;
  for (y = 0; y < matriz1->lenY; y++)
    for (x = 0; x < matriz1->lenX; x++) {
      value1 = node1 != NULL && node1->item.pos.x == x && node1->item.pos.y == y ? node1->item.value : 0;
      value2 = node2 != NULL && node2->item.pos.x == x && node2->item.pos.y == y ? node2->item.value : 0;

      valueSub = value1 - value2;
      if (valueSub != 0)
        add(result, newNode(valueSub, x, y));

      if (value1 != 0)
        node1 = node1->next;
      if (value2 != 0)
        node2 = node2->next;
    }

  return result;
}

Node* firstLin(Positions *positions, int y) {
  Node *node = positions->first;
  while (node != NULL) {
    if (node->item.pos.y == y)
      return node;
    node = node->next;
  }
  return NULL;
}

// 2.3_impl
Positions* multiplica_matriz(Positions *matriz1, Positions *matriz2) {
  Positions *result = (Positions*) malloc(sizeof(Positions));
  new(result, matriz2->lenX, matriz1->lenY);

  Positions *matriz2T = aplica_transposta(matriz2);

  Node *node1 = matriz1->first;
  Node *node2 = matriz2->first;

  Value value1, value2, totalPos;

  int lin1, y, x;
  // Percorre o número de linhas da matriz 1
  for (lin1 = 0; lin1 < matriz1->lenY; lin1++) {
    
    // Dentro de cada linha, percorre todos os itens da matriz 2 transposta.
    for (y = 0; y < matriz2T->lenY; y++) {
    
      node1 = firstLin(matriz1, lin1);
      node2 = firstLin(matriz2T, y);
      
      totalPos = 0;
      for (x = 0; x < matriz2T->lenX; x++) {
        value1 = node1 != NULL && node1->item.pos.x == x && node1->item.pos.y == lin1 ? node1->item.value : 0;
        value2 = node2 != NULL && node2->item.pos.x == x && node2->item.pos.y == y ? node2->item.value : 0;
        
        totalPos += value1 * value2;
        
        if (value1 != 0)
          node1 = node1->next;
        if (value2 != 0)
          node2 = node2->next;
      }
      add(result, newNode(totalPos, y, lin1));
    }
  }
  
  freePositions(matriz2T);
  
  return result;
}

// 2.4_impl
Positions* aplica_transposta(Positions *matriz) {
  Positions *result = (Positions*) malloc(sizeof(Positions));
  new(result, 0, 0);  
  
  Node *nodeAux = matriz->first;
  
  while (nodeAux != NULL) {
    add(result, newNode(nodeAux->item.value, nodeAux->item.pos.y, nodeAux->item.pos.x));
    nodeAux = nodeAux->next;
  }
  
  return result;
}
// 2.5_impl
int imprime_matriz(Positions *matriz) {
  int x, y;
  Node *nodeAux = matriz->first;

  for (y = 0; y < matriz->lenY; y++) {
    for (x = 0; x < matriz->lenX; x++) {
      if (nodeAux != NULL && nodeAux->item.pos.x == x && nodeAux->item.pos.y == y) {
        printf(PRINTER_ITEM, nodeAux->item.value);
        printf(" ");
        nodeAux = nodeAux->next;
      }
      else {
        printf(PRINTER_ITEM, 0);
        printf(" ");
      }
    }
    printf("\n");
  }
  printf("\n");
}
// 2.6_impl
int imprime_diagonal_principal(Positions *matriz) {
  int x, y;
  Node *nodeAux = matriz->first;

  if (matriz->lenY != matriz->lenX) {
    printf("A matriz não é quadrada.\n\n");
    return;
  }
    
  for (y = 0; y < matriz->lenY; y++) {
    for (x = 0; x < matriz->lenX; x++) {
      if (x == y && nodeAux != NULL && nodeAux->item.pos.x == x && nodeAux->item.pos.y == y) {
        printf(PRINTER_ITEM, nodeAux->item.value);
        printf(" ");
      }
      else {
        printf("0");
        printf(" ");
      }

      if (nodeAux != NULL && nodeAux->item.pos.x == x && nodeAux->item.pos.y == y)
        nodeAux = nodeAux->next;
    }
    printf("\n");
  }
  printf("\n");
}

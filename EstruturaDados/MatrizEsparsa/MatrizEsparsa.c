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

/**
 * Definição do ponteiro para função de leitura de dados da matriz.
 */
typedef (*Reader)(Value *value, int x, int y);

/**
 * Função que recebe uma lista de Posições de matriz espersa e uma leitor de dados
 * e preenche a lista com os dados que forem diferentes de 0;
 */
void parse(Positions *positions, Reader reader);

/*========================================================================*/
/* 1.0_dec - Funções referentes à manipulação da lista.
/*========================================================================*/
// 1.1_dec - Função que faz a alocação de memória para cada nodo criado na lista;
Node* newNode(Value value, int x, int y);
// 1.2_dec - Função que faz a alocação de memória para cada nodo criado na lista;
void new(Positions *positions, int x, int y);
// 1.3_dec - Função que insere na lista um nodo alocado;
int add(Positions *positions, Node *node);
// 1.4_dec - Função que lê (busca) os dados de uma lista por posição.
Item* findByPos(Positions *positions, int x, int y);
// 1.5_dec - Função que lê (busca) os dados de uma lista por valor.
Positions* findByValue(Positions *positions, Value value);
// 1.6_dec - Função que libera a memória alocada para a lista;
void freePositions(Positions *positions);
// 1.7_dec - Função que valida se o arquivo tem um formato adequado para a importação.
int isValid(Positions *positions, FILE *file, char **ret);
// 1.8_dec - Função que lê os dados da matriz e insere na lista a partir de um arquivo.
//           Utiliza a função parse passando um leitor de arquivo.
void parseFromFile(Positions *positions, FILE *file);
// 1.9_dec - Função que lê os dados da matriz e insere na lista a partir da entrada do usuário.
//           Utiliza a função parse passando um leitor STDIN.
void parseFromStdin(Positions *positions);
/*========================================================================*/
/* 2.0_dec - Funções referentes à manipulação da matriz
/*========================================================================*/
// 2.1_dec - Função que soma duas matrizes;
int soma_matriz(Positions *matriz1, Positions *matriz2);
// 2.2_dec - Função que subtrai duas matrizes;
int subtrai_matriz(Positions *matriz1, Positions *matriz2);
// 2.3_dec - Função que multiplica duas matrizes;
int multiplica_matriz(Positions *matriz1, Positions *matriz2);
// 2.4_dec - Função que gera a matriz transposta;
int aplica_transposta(Positions *matriz);
// 2.5_dec - Função que imprime todos os dados da matriz, inclusive os zeros;
int imprime_matriz(Positions *matriz);
// 2.6_dec - Função que imprime os elementos da diagonal principal, inclusive os zeros caso existam.
int imprime_diagonal_principal(Positions *matriz);
// 2.7_dec - Função que imprime os elementos da diagonal secundária, inclusive os zeros caso existam.
int imprime_diagonal_secundaria(Positions *matriz);

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

char* copyformat(char **str, const char *format, int arg1, int arg2, int arg3) {
  // Melhorar essa função para alocar um tamanho dinâmico conforme o format
  // e passar um número ilimitado e de tipos diferentes assim como faz o
  // printf() e o sprintf().
  *str = (char *) malloc(128 * sizeof(char));
  sprintf(*str, format, arg1, arg2, arg3);
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

int recupera_tipo_load() {
  int opDimensoes;

  printf("Escolha uma maneira de inicializar a matriz:\n");
  printf("1. Arquivo de texto.\n");
  printf("2. Entrada manual.\n");

  return op(1, 2, NULL);
}

void imprime_informacoes_load_arquivo() {
  printf("O arquivo de importação precisa estar com o nome \"matriz.txt\" no pasta batch criada junto a esse executável.\n");
}

FILE* recupera_arquivo_load_valido(Positions *positions) {
  FILE *file;
  int valido;
  int tentativas = 0;

  // Ponteiro que será passado por referência para receber a mensagem de
  // validação.
  char *mensagem;

  //Cria o diretório batch.
  mkdir("batch");

  // Enquanto o arquivo não for válido fica no loop.
  while (1) {
    tentativas++;
    // Limpa a tela
    system("cls");
    printf("Número de validações: %d\n", tentativas);
    printf("------------------------------------------------------\n");
    // Abre o arquivo matriz.txt
    file = fopen("batch/matriz.txt", "r");
    // Posiciona o cursor no início do arquivo.
    // para que possa ser validado mais de uma vez
    fseek(file, 0, SEEK_SET);
    // Realiza a validação.
    valido = isValid(positions, file, &mensagem);
    //Se não for válido, mostra a mensagem retornada e continua no loop.
    if (!valido) {
      printf("%s", mensagem);
      printf("Altere o arquivo e tente novamente.\n\n");
      system("pause");
    }
    else
      break;
  }

  //Posiciona o cursor no ínicio do arquivo para que ele seja entregue intacto.
  fseek(file, 0, SEEK_SET);
  return file;
}

void imprime_menu_principal() {
  printf("Menu:\n");
  printf("1. Adicionar\n");
  printf("2. Remover\n");
  printf("3. Mostrar matriz\n");
  printf("4. Buscar item\n");
  printf("0. Sair\n");
}

void find(Positions *positions) {
  int opBusca;
  int value;
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

        encontrados = findByValue(positions, value);

        if (encontrados->size > 0) {
          atual = encontrados->first;
          while (atual != NULL) {
            printf("%d / %d: ", atual->item.pos.y, atual->item.pos.x);
            printf(PRINTER_ITEM, atual->item.value);
            printf("\n\n");
          }
        }
        else
          printf("Nenhum item encontrado com esse valor.\n\n");
        break;
      case 0:
        goto saida_loop;
        break;
    }
    system("pause");
  }
  saida_loop:;
}

void main() {
  printf("v1\n");
  system("pause");
  permite_acentuacao();

  Positions positions;

  //Inicializa a matriz.
  new(&positions, 0, 0);

  int x, y;
  Value value;

  // Entra no menu principal e fica aqui até o usuário decidir sair.
  while (1) {
    system("cls");

    //Desenha o menu
    imprime_menu_principal();

    //Pergunta a opção.
    int opMenu = op(0, 4, NULL);

    system("cls");

    //Verifica qual foi a opção.
    switch (opMenu) {
      case 1:
        recupera_node_usuario(&x, &y, &value);
        add(&positions, newNode(value, x, y));
        break;
      case 2:
        find(&positions);
        break;
      case 3:
        imprime_matriz(&positions);
        system("pause");
        break;
      case 4:
        find(&positions);
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

        if (nodeAux->item.pos.x > node->item.pos.x)
          adiciona_antes(positions, nodeAux, node);
        else {
          while (nodeAux != NULL && nodeAux->item.pos.x < node->item.pos.x && nodeAux->item.pos.y == node->item.pos.y)
            nodeAux = nodeAux->next;

          if (nodeAux == NULL)
            adiciona_depois(positions, positions->last, node);
          else {
            if (nodeAux->item.pos.y > node->item.pos.y)
              nodeAux = nodeAux->before;

            if (nodeAux->item.pos.x > node->item.pos.x)
              adiciona_antes(positions, nodeAux, node);

            else
              if (nodeAux->item.pos.x == node->item.pos.x) {
                nodeAux->item.value = node->item.value;
                //Limpa o node da memória porque ele não foi adicionado na lista.
                free(node);
                //Aponta o node para nodeAux porque ele virou o 'adicionado'
                node = nodeAux;
              }
              else
                adiciona_depois(positions, nodeAux, node);
          }
        }
      }
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

  // TODO Ir preenchendo a lista com o que encontrou.

  return result;
}
// 1.6_impl
void freePositions(Positions *positions) {

}

// 1.7_impl
int isValid(Positions *positions, FILE *file, char **ret) {
  //Strings constantes para erros de validação
  const char *err_col = "Arquivo inválido: Erro linha %d. Colunas encontradas %d. Esperado %d\n";
  const char *err_lin = "Arquivo inválido: Linhas encontradas %d. Esperado %d\n";

  //Variáveis assistentes.
  char ch;
  int nlin = 1, ncol = 1;
  int wasCh = 0;

  // Se o arquivo não existir, retorna que não é válido
  if (file == NULL) {
    *ret = "Arquivo não encontrado. \n Crie um arquivo chamado matriz.txt na pasta batch.";
    return 0;
  }

  while ((ch = fgetc(file)) != EOF) {
    // Se encontrar um espaço e se o ultimo caractere não fosse de marcação.
    // incrementa o número de colunas.
    if (wasCh && ch == ' ')
      ncol++;

    // Senão, se encontrar um quebra de linha.
    else if (ch == '\n') {
      // Verifica se o número de colunas contadas até agora é diferente do número
      // de colunas esperadas. Se for, informa que o arquivo está inválido.
      if (positions->lenX != ncol) {
        copyformat(ret, err_col, nlin, ncol, positions->lenX);
        return 0;
      }
      // Incrementa o número de linhas.
      nlin += 1;
      // Volta para 1 o número de colunas.
      ncol = 1;
    }
    // Indica se esse último caractere era ou não um caractere especial.
    wasCh = (ch != '\n' && ch != ' ');
  }

  //Valida o número de linhas do arquivo.
  if (positions->lenY != nlin) {
    copyformat(ret, err_lin, nlin, positions->lenY, 0);
    return 0;
  }

  //Valida o número de colunas para a última linha.
  if (positions->lenX != ncol) {
    copyformat(ret, err_col, nlin, ncol, positions->lenX);
    return 0;
  }
  return 1;
}

// Ponteiro global para arquivo utilizado pelo fileReader.
FILE *fileTemp;

void fileReader(Value *value, int x, int y) {
  int i = 0;
  char ch;
  char numb[16];

  //Pega o número até o espaço.
  while ((ch = fgetc(fileTemp)) != ' ' && ch != '\n' && ch != EOF)
    numb[i++] = ch;

  //Coloca em value o que foi recuperado.
  *value = atoi(numb);
}

// 1.8_impl
void parseFromFile(Positions *positions, FILE *file) {
  fileTemp = file;
  parse(positions, fileReader);
  fclose(file);
}

void stdinReader(Value *value, int x, int y) {
  printf("%d/%d: ", y + 1, x + 1);
  scanf(SCANNER_ITEM, value);
  fflush(stdin);
}

// 1.9_impl
void parseFromStdin(Positions *positions) {
  parse(positions, stdinReader);
}

void parse(Positions *positions, Reader reader) {
  int x, y;
  Value valueAux;
  Node *node;

  for (y = 0; y < positions->lenY; y++)
    for (x = 0; x < positions->lenX; x++) {
      // Coloca na variavel valueAux o conteúdo da posição dos valores x y.
      (*reader)(&valueAux, x, y);
      // Se o valor retornado for diferente de 0, então adiciona ele na lista.
      if (valueAux != 0) {
        // Aloca um nó para adicionar na lista.
        node = newNode(valueAux, x, y);
        // Adiciona o nó na lista.
        add(positions, node);
      }
      printf("Valor ");
      printf(PRINTER_ITEM, valueAux);
      printf(" atribuido à posição %d/%d", y + 1, x + 1);
      printf("\n");
    }
  printf("\nMatriz carregada com sucesso!\n\n");
  system("pause");
}

/*========================================================================*/
/* 2.0_impl
/*========================================================================*/
// 2.1_impl
int soma_matriz(Positions *matriz1, Positions *matriz2) {

}
// 2.2_impl
int subtrai_matriz(Positions *matriz1, Positions *matriz2) {

}
// 2.3_impl
int multiplica_matriz(Positions *matriz1, Positions *matriz2) {

}
// 2.4_impl
int aplica_transposta(Positions *matriz) {

}
// 2.5_impl
int imprime_matriz(Positions *matriz) {
  int x, y;
  Node *nodeAux = matriz->first;

  for (y = 0; y < matriz->lenY; y++) {
    for (x = 0; x < matriz->lenX; x++) {
      if (nodeAux != NULL && nodeAux->item.pos.x == x && nodeAux->item.pos.y == y) {
        printf("%d ", nodeAux->item.value);
        nodeAux = nodeAux->next;
      }
      else
        printf("%d ", 0);
    }
    printf("\n");
  }
  printf("\n");
}
// 2.6_impl
int imprime_diagonal_principal(Positions *matriz) {

}
// 2.7_impl
int imprime_diagonal_secundaria(Positions *matriz) {

}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#define mx 30
#define my 30

/**
 * Estrutura para marcar uma posição.
 */
typedef struct position {
  int x;
  int y;
  int status;
} Pos;

/**
 * Estrutura para identificar um labirinto.
 */
typedef Pos Labirinto[mx][my];

/**
 * Estrutura para identificar um item da pilha que contém
 * uma posição.
 */
typedef struct item {

  Pos *pos;
  struct item *before;
  struct item *next;

} Item;

/**
 * Estrutura que representa a pilha de posições.
 */
typedef struct pilha {

  Item *last;
  int size;

} Pilha;

typedef struct rato {
  Pos ***atual;
} Rato;

Rato rato;

/*===========================================================*/
/* Funções de interação com a pilha                          */
/*===========================================================*/
int pop(Pilha *pilha);
int push(Pilha *pilha, Pos *pos);

/*===========================================================*/
/* Funções de interação com posição                          */
/*===========================================================*/
void setBeco(Pos *pos);
void setLivre(Pos *pos);
void setParede(Pos *pos);
void setVisitado(Pos *pos);

int beco(Pos pos);
int livre(Pos pos);
int parede(Pos pos);
int visitado(Pos pos);

/*===========================================================*/
/* Funções de interação com o labirinto                      */
/*===========================================================*/
void gera_labirinto(Labirinto labirinto, Pos **inicialRato, Pos **saida);
void imprime_labirinto(Labirinto labirinto);
void aloca_labirinto(Labirinto labirinto);
char caractere_posicao(Pos *pos);

/*===========================================================*/
/* Funções auxiliares                                        */
/*===========================================================*/
int seed = 0;

int randomInt(int max) {
  if (!seed) {
    time_t t;
    srand((unsigned) time(&t));
    seed = 1;
  }
  return rand() % (max + 1);
}

Pos* atual() {
  return **rato.atual;
}

Pos* proxima_posicao(Labirinto labirinto, Pos *pos, int proxima) {
  if (pos->y > 0)
    if (livre(labirinto[pos->x][pos->y - 1])) {
      proxima--;
      if (proxima == -1)
        return &labirinto[pos->x][pos->y - 1];
    }
  if (pos->x < mx - 1)
    if (livre(labirinto[pos->x + 1][pos->y])) {
      proxima--;
      if (proxima == -1)
        return &labirinto[pos->x + 1][pos->y];
    }
  if (pos->y < my - 1)
    if (livre(labirinto[pos->x][pos->y + 1])) {
      proxima--;
      if (proxima == -1)
        return &labirinto[pos->x][pos->y + 1];
    }
  if (pos->x > 0)
    if (livre(labirinto[pos->x - 1][pos->y])) {
      proxima--;
      if (proxima == -1)
        return &labirinto[pos->x - 1][pos->y];
    }
}

int andar(Pilha *pilha, Labirinto labirinto, Pos *saida, Pos *inicial) {
  int livres = 0, visitados = 0;
  Pos *vaiPara = 0;
  livres = livres_em_volta(labirinto, *atual());

  setVisitado(atual());

  if (livres > 0) {
    vaiPara = proxima_posicao(labirinto, atual(), randomInt(livres - 1));

    push(pilha, vaiPara);
    setVisitado(atual());

    if (atual() == saida)
      return 0;
  }
  else {
    setBeco(atual());
    pop(pilha);

    if (atual() == inicial)
      return -1;
  }

  return 1;
}

void limpar_pilha(Pilha *pilha) {
  while (pop(pilha));
}

void main() {
  Pilha pilha;
  Labirinto labirinto;
  Pos *inicialRato;
  Pos *saida;
  int op;

  int semSaida;

  while (1) {
    system("cls");
    printf("Opcoes:\n");
    printf("  1 - Iniciar labirinto\n");
    printf("  2 - Sair\n");

    do {
      scanf("%d", &op);
      fflush(stdin);
    }
    while (op < 1 || op > 2);

    if (op == 2)
      exit(0);

    system("cls");

    new(&pilha);
    //Aloca as posições.
    aloca_labirinto(labirinto);
    //Gera o labirinto.
    gera_labirinto(labirinto, &inicialRato, &saida);
    push(&pilha, inicialRato);
    rato.atual = &(pilha.last);

    do {
      system("cls");
      imprime_labirinto(labirinto);

    }
    while ((semSaida = andar(&pilha, labirinto, saida, inicialRato)) > 0);

    if (!semSaida)
      printf("O rato encontrou a saida! \\o/ \\o/\n");
    else
      printf("Labirinto sem saida.\n");

    system("pause");

    limpar_pilha(&pilha);
  }
}
/*===========================================================*/
/* Funções de interação com o labirinto                      */
/*===========================================================*/
int livre(Pos pos) {
  return pos.status == 0;
}
int parede(Pos pos) {
  return pos.status == 1;
}
int visitado(Pos pos) {
  return pos.status == 2;
}
int beco(Pos pos) {
  return pos.status == 3;
}
int disponivel(Pos pos) {
  return pos.status == 0 || pos.status == 2;
}
void setLivre(Pos *pos) {
  pos->status = 0;
}
void setParede(Pos *pos) {
  pos->status = 1;
}
void setVisitado(Pos *pos) {
  pos->status = 2;
}
void setBeco(Pos *pos) {
  pos->status = 3;
}

char caractere_posicao(Pos *pos) {
  if (atual() == pos)
    return 169;

  if (!pos->status)
    return ' ';
  if (pos->status == 2)
    return 250;
  if (pos->status == 3)
    return '#';
  else
    return 219;
}

void aloca_labirinto(Labirinto labirinto) {
  //inicializa as posições.
  int x, y;
  for (x = 0; x < mx; x++)
    for (y = 0; y < my; y++) {
      labirinto[x][y].status = -1;
      labirinto[x][y].x = x;
      labirinto[x][y].y = y;
    }
}
/**
 *
 * Agradecimentos ao salsicha.
 *
 */
void imprime_labirinto(Labirinto labirinto) {
  char *desenho = (char*) malloc(sizeof(char) * (mx + 1) * (my + 2));
  int count = 0;
  int x, y;
  for (y = 0; y <my; y++) {
    for (x = 0; x < mx; x++){
      printf("%c", caractere_posicao(&labirinto[x][y]));
      //desenho[count++] = caractere_posicao(&labirinto[x][y]);
    }
    //desenho[count++] = '\n';
    printf("\n");
  }

  printf("%s", desenho);
}

int posicaoEhBorda(int x, int y) {
  return x == 0 || x == mx - 1 || y == 0 || y == my - 1;
}

int posicaoEhCanto(int x, int y) {
  return (x == 0 && y == 0) || (x == 0 && y == my - 1) || (x == mx - 1 && y == 0) || (x == mx - 1 && y == my - 1);
}

Pos* geraPosicaoInicial() {
  Pos *posicao = (Pos*) malloc(sizeof(Pos));

  int x, y;
  do {
    x = randomInt(mx - 1);
    y = randomInt(my - 1);
  }
  while (!posicaoEhBorda(x, y) || posicaoEhCanto(x, y));

  posicao->x = x;
  posicao->y = y;

  return posicao;
}

Pos* geraPosicaoInicialDiferenteDe(Pos *pos) {
  Pos *ret = NULL;
  do {
    if (ret != NULL)
      free(ret);

    ret = geraPosicaoInicial();
  }
  while (ret->x == pos->x && ret->y == pos->y);
  return ret;
}

int coordenadasDa(int x, int y, Pos pos) {
  return x == pos.x && y == pos.y;
}

int status_em_volta(Labirinto labirinto, Pos pos, int status) {
  int nParedes = 0;
  if (pos.x < mx - 1)
    if (labirinto[pos.x + 1][pos.y].status == status)
      nParedes++;
  if (pos.x > 0)
    if (labirinto[pos.x - 1][pos.y].status == status)
      nParedes++;
  if (pos.y < my - 1)
    if (labirinto[pos.x][pos.y + 1].status == status)
      nParedes++;
  if (pos.y > 0)
    if (labirinto[pos.x][pos.y - 1].status == status)
      nParedes++;
  return nParedes;
}

int livres_em_volta(Labirinto labirinto, Pos pos) {
  return status_em_volta(labirinto, pos, 0);
}

int visitados_em_volta(Labirinto labirinto, Pos pos) {
  return status_em_volta(labirinto, pos, 2);
}

int paredes_em_volta(Labirinto labirinto, Pos pos) {
  return status_em_volta(labirinto, pos, 1);
}

int disponiveis_em_volta(Labirinto labirinto, Pos pos) {
  return status_em_volta(labirinto, pos, 0) + status_em_volta(labirinto, pos, 2);
}

Pos* caminho_da_borda(Pos borda) {
  Pos *caminho = (Pos*) malloc(sizeof(Pos));

  int x, y;
  x = borda.x;
  y = borda.y;

  if (borda.x == 0)
    x++;
  else if (borda.x == mx - 1)
    x--;
  if (borda.y == 0)
    y++;
  else if (borda.y == my - 1)
    y--;

  caminho->x = x;
  caminho->y = y;

  return caminho;
}

void preenche_caminho_como_livre(Pos posborda, Labirinto labirinto) {
  Pos *caminho_borda = caminho_da_borda(posborda);
  labirinto[caminho_borda->x][caminho_borda->y].status = 0;
  free(caminho_borda);
}

void gera_labirinto(Labirinto labirinto, Pos **inicialRato, Pos **saida) {
  *inicialRato = geraPosicaoInicial();
  *saida = geraPosicaoInicialDiferenteDe(*inicialRato);

  int x, y;
  int status;
  int range, nliv;
  for (x = 0; x < mx; x++)
    for (y = 0; y <my; y++)
      if (coordenadasDa(x, y, **inicialRato) || coordenadasDa(x, y, **saida))
        setLivre(&labirinto[x][y]);
      else if (posicaoEhBorda(x, y))
        setParede(&labirinto[x][y]);

  preenche_caminho_como_livre(**inicialRato, labirinto);
  preenche_caminho_como_livre(**saida, labirinto);

  for (x = 0; x < mx; x++)
    for (y = 0; y <my; y++) {
      if (labirinto[x][y].status == -1) {
        range = randomInt(3) + 1;
        nliv = livres_em_volta(labirinto, labirinto[x][y]);
        status = range - nliv;
        if (status > 0)
          labirinto[x][y].status = 0;
        else
          labirinto[x][y].status = 1;
      }
    }

  *inicialRato = &labirinto[(*inicialRato)->x][(*inicialRato)->y];
  *saida = &labirinto[(*saida)->x][(*saida)->y];
}

void new(Pilha *pilha) {
  pilha->size = 0;
}

Item* newItem(Pos *pos) {
  Item *item = (Item*) malloc(sizeof(Item));
  item->before = NULL;
  item->next = NULL;
  item->pos = pos;
  return item;
}

int pop(Pilha *pilha) {
  if (pilha->size > 0) {
    Item *ultimo = pilha->last;
    pilha->last = ultimo->before;

    if (pilha->last != NULL)
      pilha->last->next = NULL;

    free(ultimo);

    pilha->size--;
    return 1;
  }
  return 0;
}

int push(Pilha *pilha, Pos *pos) {
  if (pos != NULL) {
    Item *item = newItem(pos);
    if (pilha->size > 0) {
      pilha->last->next = item;
      item->before = pilha->last;
    }
    pilha->last = item;
    pilha->size++;
    return 1;
  }
  return 0;
}

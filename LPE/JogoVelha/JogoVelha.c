/*=========================================================*/
/* Aluno: João Pedro Medeiros de Farias                    */
/* TADS NOTURNO                                            */
/*=========================================================*/

#include<stdio.h>
#include <string.h>

#define vazio ' '

//Variável global para a velha
char velha[3][3];
//Variáveis de controle do placar
int nrPartidas = 0, vitoriasX = 0, vitoriasO = 0;

//Ponteiro para funções de jogada genéricas
typedef (*jogada)(struct jogador *jog);

//Estrutura de dados para jogador
struct jogador {
  char simbolo;
  char nome[15];
  int isUsuario;
  int nivel;
  jogada fncJogada;
};

//Estrutura de dados para partida
struct Velha {
 int partida;
 char velha[3][3];
 char resultado;
};

//Declaração das funções
char jogar(int op, struct jogador *jog1, struct jogador *jog2);

//Urls dos arquivos
char arq_nomes[] = "nomes.txt";
char arq_velha[] = "velha.dat";

int jogada_usuario(int lin, int col, char jog) {
  if (lin < 0 || lin > 2 || col < 0 || col > 2)
    return 1;
  
  else if (velha[lin][col] != vazio)
    return 2;
  
  else {
  	velha[lin][col] = jog;
  	return 0;
  }
}

int jogada_computador(char jog, int nivel) {
  int linha, coluna;
  
  switch (nivel) {
  	case 1:
  	  recupera_posicao_basico(&linha, &coluna);
  	  break;
  	case 2:
  	  recupera_posicao_intermediario(jog, &linha, &coluna);
  	  break;
  	case 3:
  	  recupera_posicao_avancado(jog, &linha, &coluna);
  	  break;
  }
  
  velha[linha][coluna] = jog;
}

void efetua_jogada_usuario(struct jogador *jog) {
  int linha, coluna, jogada;
  
  do {
  	printf("%s (%c), digite a linha e a coluna: ", (*jog).nome, (*jog).simbolo);
    scanf("%d", &linha);
    scanf("%d", &coluna);
    fflush(stdin);
    
    jogada = jogada_usuario(linha - 1, coluna - 1, (*jog).simbolo);
    
    if (jogada == 1)
      printf("Posicao invalida.\n");
    else if (jogada == 2)
	  printf("Posicao ja preenchida.\n");
  }
  //Enquanto for 1 ou 2 (inválida)
  while (jogada);
}

void efetua_jogada_computador(struct jogador *jog) {
  //Chama a jogada do computador	
  jogada_computador((*jog).simbolo, (*jog).nivel);
  
}

int recupera_possibilidade_por_valores(char valores[2], char jog) {
  
  //Se os dois estiverem preenchidos
  if (valores[0] != vazio && valores[1] != vazio)
	//Se os dois simbolos forem iguais
	if (valores[0] == valores[1])
	  
	  //Se for para ganhar
	  if (valores[0] == jog)
	    return 8;
	  //Se for para defender
	  else
	    return 4;
	
	//Se tiver preenchido com um de cada
	else
	  return 0;
	  
  //Se algum deles estiver vazio
  else 
    //Se tudo estiver vazio
	if (valores[0] == vazio && valores[1] == vazio)
      return 1;
	//Se tiver preenchido somente com o simbolo do jogador atual
    else if (valores[0] == jog || valores[1] == jog)
      return 2;
    //Se tiver preenchido somente com o simbolo do rival
    else
      return 0;  
}

void recupera_possibilidades(int possib[3][3], char jog) {
  int i, j, k, indice;
  char valores_linha[2];
  
  //Zera as possibilidades
  for (i = 0; i < 3; i++)   
	for (j = 0; j < 3; j++)
	  possib[i][j] = 0;
 
  for (i = 0; i < 3; i++)
    
	for (j = 0; j < 3; j++)
	  
	  if (velha[i][j] == vazio) {
	  	
	    //Calcula as possibilidades para linha
	    indice = 0;
		for (k = 0; k < 3; k++) {
	      if (k != j)
	        valores_linha[indice++] = velha[i][k];
	    }
		possib[i][j] += recupera_possibilidade_por_valores(valores_linha, jog);
		
		//Calcula as possibilidades para coluna
		indice = 0;
		for (k = 0; k < 3; k++) {
	      if (k != i)
	        valores_linha[indice++] = velha[k][j];
	    }
		possib[i][j] += recupera_possibilidade_por_valores(valores_linha, jog);
		
		//Calcula as possibilidades para a diagonal principal (A casa faz parte da diagonal principal se i = j)
		if (i == j) {
		  indice = 0;
		  for (k = 0; k < 3; k++) {
	     	if (k != i)
	     	  valores_linha[indice++] = velha[k][k];
	      }
		  possib[i][j] += recupera_possibilidade_por_valores(valores_linha, jog);
		}
		
		//Calcula as possibilidades para a diagonal secundária (A casa faz parte da diagonal secundário se i + j = 2)
		if (i + j == 2) {
		  indice = 0;
		  for (k = 0; k < 3; k++) {
		    if ((k != i) || (2 - k != j))
		      valores_linha[indice++] = velha[k][2 - k];
		  }
		  possib[i][j] += recupera_possibilidade_por_valores(valores_linha, jog);
		}
	  }
	  
	  //Espaço já preenchido
	  else
	    possib[i][j] = 0;
}

void recupera_posicao_basico(int *lin, int *col) {
  do {
    *lin = rand() % 3;
    *col = rand() % 3;
  }
  while (velha[*lin][*col] != vazio);
}

void recupera_melhor_possibilidade(int possib[3][3], int *lin, int *col) {
  int i, j, maior;
  *lin = -1;
  for (i = 0; i < 3; i++)   
	for (j = 0; j < 3; j++)
	  if ((*lin == - 1 && velha[i][j] == vazio) || maior < possib[i][j]) {
	  	maior = possib[i][j];
	    *lin = i;
	    *col = j;
	  }
}

void recupera_posicao_intermediario(char jog, int *lin, int *col) {
  int possib[3][3];
  int i, j = - 1;
  int maior = 0;
  int eh_inicio = 0;
  
  for (i = 0; i < 3; i++)   
    for (j = 0; j < 3; j++)
      if (velha[i][j] != vazio)
      	if (eh_inicio == 1) { 
		  eh_inicio++;
		  goto verifica_inicio;
		}
		else
		  eh_inicio = 1;
  
  verifica_inicio: eh_inicio = eh_inicio < 2;
  
  recupera_possibilidades(possib, jog);
  
  //Impede que o computador jogue no meio
  if (eh_inicio)
    possib[1][1] = 0;
  
  recupera_melhor_possibilidade(possib, lin, col);
}

void recupera_posicao_avancado(char jog, int *lin, int *col) {
  
  int possib[3][3];
  
  recupera_possibilidades(possib, jog);
  
  recupera_melhor_possibilidade(possib, lin, col);
}

void preenche_usuario(struct jogador *usuario, char nom[]) {
  strcpy((*usuario).nome, nom);
  (*usuario).fncJogada = efetua_jogada_usuario;
  (*usuario).isUsuario = 1;
  (*usuario).nivel = -1;
  
}

void preenche_computador(struct jogador *computador) { 
  strcpy((*computador).nome, "Computador");
  (*computador).fncJogada = efetua_jogada_computador;
  (*computador).isUsuario = 0;
  (*computador).nivel = obtem_nivel();
}

void boas_vindas(char nome1[], char nome2[]) {
  printf("==============================================================\n");
  printf(" BEM-VINDO                                                    \n");
  printf(" Como essa eh sua primeira vez, escolha o nome dos jogadores. \n");
  printf("==============================================================\n");
  
  printf("Jogador 1: ");
  scanf("%s", nome1);
  fflush(stdin);
  
  printf("Jogador 2: ");
  scanf("%s", nome2);
  fflush(stdin);
}


int grava_jogadores(char url[], struct jogador jog1, struct jogador jog2) {
  FILE *file;
  file = fopen(url, "w");
  if (file != NULL) {
    fprintf(file, "%s ; %c ; %s ; %c\n", jog1.nome, jog1.simbolo, jog2.nome, jog2.simbolo);
    fclose(file);
    return 1;
  }
  return 0;
}

void copia_matriz(char m[3][3], char m2[3][3]) {
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      m[i][j] = m2[i][j];
}

int arquivo_existe(char arq[]) {
  FILE *file;
  file = fopen(arq, "r");
  int existe = (file != NULL);
  
  if (existe)
    fclose(file);
    
  return existe;
}

int tamanho_arq(FILE *file) {
  int len;
  fseek(file, 0, SEEK_END);
  len = ftell(file);
  fseek(file, 0, SEEK_SET);
  return len;
}

int recupera_partidas(char url[], struct Velha **partidas) {
  int len, n;
  FILE *file;
  
  // Abre o arquivo
  file = fopen(url, "rb");
  
  if (file != NULL) {
    // Recupera o número de bytes dele
    len = tamanho_arq(file);
    // Recupera o numero de Velhas que existem dentro do arquivo
    n = len / sizeof(struct Velha);
    //Aloca o tamanho do vetor
    *partidas = (struct Velha *) malloc(sizeof(struct Velha) * n);
    // Coloca o conteudo da velha dentro da struct
    fread(*partidas, sizeof(struct Velha), n, file);
    //Fecha o arquivo
    fclose(file);
    //Retorna o numero de velhas encontradas no arquivo
    return n;
  }
  return 0;
}

void recupera_partida(char url[], struct Velha *partida) {
  
  struct Velha *partidas;
  int n;
  
  if (!arquivo_existe(url) || !(n = recupera_partidas(url, &partidas)))
    (*partida).partida = 1;
  else
    (*partida).partida = partidas[n - 1].partida + 1;
    
  copia_matriz((*partida).velha, velha);
}

int grava_partida(char url[], struct Velha partida) {
  
  FILE *file;
  
  file = fopen(url, "ab");
  
  if (file != NULL)
    fwrite (&partida, sizeof(struct Velha), 1, file);
  else {
    printf("Desculpe, houve um erro ao abrir o arquivo da partida. :/");
    system("pause");
  }
  fclose(file);
}

void recupera_jogadores(char url[], struct jogador *jog1, struct jogador *jog2) {
  
  char nome1[15], nome2[15];
  char simb1, simb2;
  
  FILE *file;
  file = fopen(url, "r");
  
  if (file != NULL) {
  
    if (tamanho_arq(file) < 13) {
	  printf("Desculpe, o arquivo de nomes está vazio. Abra o jogo novamente.\n\n");
	  fclose(file);
	  remove(arq_nomes);
	  exit(0);
	}
  
    fscanf(file, "%s ; %c ; %s ; %c\n", &nome1, &simb1, &nome2, &simb2);
  
    preenche_usuario(jog1, nome1);
    preenche_usuario(jog2, nome2);
  
    (*jog1).simbolo = simb1;
    (*jog2).simbolo = simb2;
  }
}

void jogadores_campeonato(struct jogador *jog1, struct jogador *jog2) {
  
  char nome1[15], nome2[15];
  
  if (!arquivo_existe(arq_nomes)) {
    system("cls");
    boas_vindas(nome1, nome2);
    
    preenche_usuario(jog1, nome1);
    preenche_usuario(jog2, nome2);
    
	escolha_simb(&(*jog1).simbolo, &(*jog2).simbolo);
	
	if (!(grava_jogadores(arq_nomes, *jog1, *jog2))) {
	  printf("Desculpe, houve um erro ao gravar o nome dos jogadores :/");
	  exit(0);
	}
  }
  else
    recupera_jogadores(arq_nomes, jog1, jog2);
}

void preenche_info_campeonato(int *vitoriasX, int *vitoriasO, int *nrPartidas) {
  
  struct Velha *partidas;
  int n, i;
  
  *nrPartidas = recupera_partidas(arq_velha, &partidas);
  
  for (i = 0; i < *nrPartidas; i++) {
  	*vitoriasX += partidas[i].resultado == 'X' ? 1 : 0; 
  	*vitoriasO += partidas[i].resultado == 'O' ? 1 : 0;
  }
}

void relatorio() {
  
  struct Velha *partidas;
  struct jogador jog1, jog2;
  int vitoriasX, vitoriasO, nrPartidas;
  int i;
  
  vitoriasX = vitoriasO = nrPartidas = 0;
  
  nrPartidas = recupera_partidas(arq_velha, &partidas);
  recupera_jogadores(arq_nomes, &jog1, &jog2);
  
  for (i = 0; i < nrPartidas; i++) {
  	vitoriasX += partidas[i].resultado == 'X' ? 1 : 0; 
  	vitoriasO += partidas[i].resultado == 'O' ? 1 : 0;
  }
  
  system("cls");
  
  printf("|=====================================|\r\n");
  printf("| Numero de partidas: %d               \r\n", nrPartidas);
  printf("| Vitorias de %s (X): %d               \r\n", jog1.simbolo == 'X' ? jog1.nome : jog2.nome, vitoriasX);
  printf("| Vitorias de %s (O): %d               \r\n", jog2.simbolo == 'O' ? jog2.nome : jog1.nome, vitoriasO);
  printf("| Velhas: %d                           \r\n", nrPartidas - vitoriasX - vitoriasO);
  printf("|=====================================|\r\n"); 
 
  for (i = 0; i < nrPartidas; i++) {
	printf("Partida numero %d ", partidas[i].partida);
	if (partidas[i].resultado == 'V')
	  printf("deu velha.\n");
	else if (partidas[i].resultado == 'X')
	  printf("%s ganhou.\n", jog1.simbolo == 'X' ? jog1.nome : jog2.nome);
	else if (partidas[i].resultado == 'O')
	  printf("%s ganhou.\n", jog1.simbolo == 'O' ? jog1.nome : jog2.nome);
  	desenha_painel(partidas[i].velha);
  	printf("\n");
  }
  
  system("pause");
}

int recupera_partida_por_codigo(char url[], struct Velha *partida, int nrPartida) {
  struct Velha *partidas;
  int n, i;
 
  n = recupera_partidas(url, &partidas);
  
  if (nrPartida <= n && nrPartida > 0) {
    *partida = partidas[nrPartida - 1];
    return 1;
  }
  return 0;
}

void pesquisar() {
  
  struct Velha partida;
  struct jogador jog1, jog2;
  int op;
  
  do {
    system("cls");
    
    printf("Nr. da partida \n");
    printf("Opcao: ");
    scanf("%d", &op);
    fflush(stdin);
    
    system("cls");
    
    printf("=========================================\n");
    printf(" Buscando partida...                     \n");
    printf("=========================================\n");
    
    recupera_jogadores(arq_nomes, &jog1, &jog2);
    
    if (recupera_partida_por_codigo(arq_velha, &partida, op)) {
      printf("Partida numero %d ", partida.partida);
      if (partida.resultado == 'V')
        printf("deu velha.\n");
      else if (partida.resultado == 'X')
        printf("%s ganhou.\n", jog1.simbolo == 'X' ? jog1.nome : jog2.nome);
      else if (partida.resultado == 'O')
        printf("%s ganhou.\n", jog1.simbolo == 'O' ? jog1.nome : jog2.nome);
      desenha_painel(partida.velha);
      printf("\n");
    }
    else
      printf("Partida %d nao existe\n\n", op);
      
    printf("Deseja buscar novamente?\n");
    printf("1 - Sim, 2 - Nao\n");
    
    do {
      printf("Opcao: ");
      scanf("%d", &op);
      fflush(stdin);
    }
    while (op < 1 && op > 2);
  }
  while (op == 1);
}

int main() {
  //Variáveis
  int op;
  int control;
  struct jogador jog1;
  struct jogador jog2;
  struct Velha partida;
  char nome_jogador1[] = "Jogador 1";
  char nome_jogador2[] = "Jogador 2";
  
  //Variaveis para contagem do placar
  char vencedor;
  
  do {
  	inicio:
  	
  	system("cls");
  	
    //Recupera a opção de jogo
    //  1 - Player vs Player
    //  2 - Player vs Computador
    //  3 - Campeonato                 
    op = menu();
  
    //Recupera a função de jogada de cada jogador
    //  Se 1, os dois são preenchidos como usuário
    //  Se 2, o jog1 recebe usuário e o jog2 recebe computador
    if (op == 1) {
      preenche_usuario(&jog1, nome_jogador1);
      preenche_usuario(&jog2, nome_jogador2);
      escolha_simb(&jog1.simbolo, &jog2.simbolo);
    }
    else if (op == 2) {
      preenche_usuario(&jog1, nome_jogador1);
      preenche_computador(&jog2);
      escolha_simb(&jog1.simbolo, &jog2.simbolo);
    } 
    else if (op == 3)
      jogadores_campeonato(&jog1, &jog2);
      
    else if (op == 4) {
      if (!arquivo_existe(arq_nomes) || !arquivo_existe(arq_velha)) {
        printf("Inicie um campeonato para acessar essa opcao.\n\n");
        system("pause");
      }
      else	
	    relatorio();
	  goto inicio;
	}
	else if (op == 5) {
	  if (!arquivo_existe(arq_nomes) || !arquivo_existe(arq_velha)) {
        printf("Inicie um campeonato para acessar essa opcao.\n\n");
        system("pause");
      }
      else	
	    pesquisar();
	  goto inicio;
	}
  
    vitoriasX = vitoriasO = nrPartidas = 0;
  
    if (op == 3)
      preenche_info_campeonato(&vitoriasX, &vitoriasO, &nrPartidas);
  
    do {
      //Jogo
      vencedor = jogar(op, &jog1, &jog2);
      
      nrPartidas++;
      if (vencedor == 'X') vitoriasX++;
      if (vencedor == 'O') vitoriasO++;
      
      //Grava no arquivo binario
      if (op == 3) {
        recupera_partida(arq_velha, &partida);
        partida.resultado = vencedor; 
        grava_partida(arq_velha, partida);
      }
      
      printf("Deseja jogar novamente?          \n");
      printf(" 1 - Jogar com as mesmas opcoes. \n");
      printf(" 2 - Voltar ao menu principal.   \n");
      printf(" 0 - Sair.                       \n");
      
      do {
      	printf("Opcao: ");
	    scanf("%d", &control);
	    fflush(stdin);
	  }
	  while (control < 0 || control > 2);
	  
	  system("cls");
    }
    //Enquanto quiser jogar com as mesmas opções
    while (control == 1);
  }
  //Enquanto quiser voltar ao menu principal
  while (control == 2);
}

int verifica_ganhador(char jog) {
  int linha_valida;
  int coluna_valida;
  int diag_maior_valida = 1;
  int diag_menor_valida = 1;
  int i, j;
  for (i = 0; i < 3; i++) {
  	linha_valida = 1;
  	coluna_valida = 1;
  	diag_maior_valida = diag_maior_valida && velha[i][i] == jog;
  	diag_menor_valida = diag_menor_valida && velha[i][2 - i] == jog;
    for (j = 0; j < 3; j++) {
	  linha_valida = linha_valida && velha[i][j] == jog;
	  coluna_valida = coluna_valida && velha[j][i] == jog;
	  if (!linha_valida && !coluna_valida)
	    break;
	}
	if (linha_valida || coluna_valida)
	  return 1;
  }
  return (diag_maior_valida || diag_menor_valida);
}

int velha_completa() {
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      if (velha[i][j] == vazio)
        return 0;
  return 1;
}

void inicializa_velha() {
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      velha[i][j] = vazio;
}

char jogar(int op, struct jogador *jog1, struct jogador *jog2) {
  int completou;
  //Ponteiro para o jogador atual
  struct jogador *jogAtual;
  
  //Inicializa a matriz da velha com valores vazios
  inicializa_velha();
  
  do {
  	system("cls");
  	desenha_placar((*jog1).simbolo == 'X' ? jog1 : jog2, (*jog2).simbolo == 'O' ? jog2 : jog1);
	desenha_painel(velha);
  	
  	//Altera a vez do jogador
    jogAtual = jogAtual == jog1 ? jog2 : jog1;
    
    //Efetua a jogada do jogador
    (*(*jogAtual).fncJogada)(jogAtual);
    
    system("cls");
    desenha_placar((*jog1).simbolo == 'X' ? jog1 : jog2, (*jog2).simbolo == 'O' ? jog2 : jog1);
	desenha_painel(velha);
  }
  //Repete o processo enquanto ninguém ganhar e a velha não estiver completa
  while (!verifica_ganhador((*jogAtual).simbolo) && !(completou = velha_completa()));
  
  if (!completou) {
    printf("%s venceu!\n", (*jogAtual).nome);
    return (*jogAtual).simbolo;
  }
  else {
    printf("Deu velha!\n");
    return 'V';
  }
}

int menu() {
  int op;
  
  printf("Selecione o estilo de jogo:\n");
  printf(" 1. Player vs Player       \n");
  printf(" 2. Player vs Computador   \n");
  printf(" 3. Campeonato             \n");
  printf(" 4. Partidas               \n");
  printf(" 5. Pesquisar partida      \n");
   
  do {
  	printf("Opcao: ");
    scanf("%d", &op);
    fflush(stdin);
  }
  while (op < 1 && op > 5);
  
  return op;
}

void escolha_simb(char *simb1, char *simb2) {
  char auxEntrada;
  
  printf("Selecione o simbolo do jogador 1 (X / O)\n");
  
  do {
  	printf("Opcao: ");
    scanf("%c", &auxEntrada);
    *simb1 = toupper(auxEntrada);
    fflush(stdin);
  }
  while (*simb1 != 'X' && *simb1 != 'O');
  
  *simb2 = *simb1 == 'X' ? 'O' : 'X';
}

int obtem_nivel() {
  int nivel;
  
  printf("Selecione o nivel do computador:\n");
  printf(" 1. Basico.         \n");
  printf(" 2. Intermediario.  \n");
  printf(" 3. Avancado.       \n");
   
  do {
  	printf("Opcao: ");
    scanf("%d", &nivel);
    fflush(stdin);
  }
  while (nivel < 1 || nivel > 3);
  
  return nivel; 
}

void desenha_placar(struct jogador *jogX, struct jogador *jogO) {
  printf("|=====================================|\r\n");
  printf("| Numero de partidas: %d               \r\n", nrPartidas);
  printf("| Vitorias de %s (X): %d               \r\n", (*jogX).nome, vitoriasX);
  printf("| Vitorias de %s (O): %d               \r\n", (*jogO).nome, vitoriasO);
  printf("| Velhas: %d                           \r\n", nrPartidas - vitoriasX - vitoriasO);
  printf("|=====================================|\r\n"); 
}

void desenha_painel(char v[3][3]) {
  int i, j;
  printf("|==============|\r\n");
  for (i = 0; i < 5; i++) {
  	printf("| ");
	for (j = 0; j < 3; j++) {
	  if (i % 2 != 0) {
	    printf("----");
	    continue;
  	  }
	  printf(" ");	
	  printf("%c", v[i/2][j] != vazio ? v[i/2][j] : ' ');
	  if (j < 2)
	    printf(" |");
    }
    printf("\r\n");
  }
  printf("|==============|\r\n");
}


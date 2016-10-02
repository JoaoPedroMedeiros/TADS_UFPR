#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define size 1000

char url[] = "db.txt";
char vazio[] = " ";
char vend[] = "Vendido";
char disp[] = "Disponivel";

typedef struct Carro {
  char modelo[50];
  char placa[8];
  float valor;
  int vend;
} Carro;

typedef (*compara)(Carro car1, Carro car2);
typedef (*valor_valido)(Carro car, float valor);
typedef (*isValido)(Carro car);

void desenha_painel_carro(Carro carro) {
  printf("================================\n");
  printf("INFORMACOES DO NOVO CARRO       \n");
  printf("MODELO: %s                      \n", carro.modelo);
  printf("PLACA : %s                      \n", carro.placa);
  printf("VALOR : R$ %.2f                 \n", carro.valor);
  printf("================================\n");
}

void recupera_info_carro(Carro *car) {

  desenha_painel_carro(*car);

  printf("Modelo: ");
  gets((*car).modelo);
  fflush(stdin);
  substitui_espaco((*car).modelo, '_');

  system("cls");
  desenha_painel_carro(*car);

  printf("Placa: ");
  gets((*car).placa);
  fflush(stdin);
  substitui_espaco((*car).placa, '-');

  system("cls");
  desenha_painel_carro(*car);

  printf("Valor: ");
  scanf("%f", &(*car).valor);
  fflush(stdin);

  system("cls");
  desenha_painel_carro(*car);
}

void salva_carro(FILE *file, Carro car) {
  fputs(car.modelo, file);
  fprintf(file, " | ");
  fputs(car.placa, file);
  fprintf(file, " | ");
  fprintf(file, "%.2f", car.valor);
  fprintf(file, " | ");
  fprintf(file, "%d", car.vend);
  fprintf(file, "\n");
}

void reset_carro(Carro *car) {
  strcpy((*car).modelo, vazio);
  strcpy((*car).placa, vazio);
  (*car).valor = 0;
  (*car).vend = 0;
}

void substitui_espaco(char texto[], char csub) {
  int i;
  for (i = 0; i < strlen(texto); i++)
    if (texto[i] == ' ')
      texto[i] = csub;
}

void novo_carro(FILE *file) {
  int op;
  Carro car;

  while (1) {

    reset_carro(&car);

    system("cls");
    recupera_info_carro(&car);

    printf("=================================================\n");
    printf(" 0 - Redigitar; 1 - Salvar; 2 - Voltar ao menu   \n");
    printf("=================================================\n");

    op = opcao(0, 2);

    if (op)
      break;
  }

  if (op == 1) {
    salva_carro(file, car);
    printf("Salvo com sucesso!\n");
    printf("\n");
    system("pause");
  }
}

void desenha_carro(Carro carro) {
  printf("MODELO: %s      \n", carro.modelo);
  printf("PLACA : %s      \n", carro.placa);
  printf("VALOR : R$ %.2f \n", carro.valor);
  printf("STATUS: %s      \n", carro.vend ? vend : disp);
  printf("\n");
}

int recupera_carros(FILE *file, Carro carros[]) {
  int i = 0;

  fclose(file);
  file = fopen(url, "r");
  
  while (
    (fscanf(file, "%s | %s | %f | %d\n",
      &(carros[i].modelo),
      &(carros[i].placa),
      &(carros[i].valor),
      &(carros[i].vend))) != EOF) i++;

  return i;
}

void listar_carros(Carro carros[], int len) {
  int j;
  int disponiveis, vendidos;
  float totcar, totdisp, totvend;
  
  disponiveis = vendidos = 0;
  totcar = totdisp = totvend = 0;

  for (j = 0; j < len; j++) {
    printf("Carro %d\n", j + 1);
    desenha_carro(carros[j]);
    
    //Informações
    disponiveis += carros[j].vend ? 0 : 1;
    vendidos += carros[j].vend ? 1 : 0;
    totcar += carros[j].valor;
    totdisp += !carros[j].vend ? carros[j].valor : 0;
    totvend += carros[j].vend ? carros[j].valor : 0;
  }

  printf("=================================================\n");
  printf("Tot. carros                : %d carro(s)\n", len);
  printf("Disponiveis                : %d carro(s)\n", disponiveis);
  printf("Vendidos                   : %d carro(s)\n", vendidos);
  printf("Valor total em carros      : R$ %.2f\n", totcar);
  printf("Valor total em disponiveis : R$ %.2f\n", totdisp);
  printf("Valor total em vendidos    : R$ %.2f\n", totvend);
  printf("=================================================\n");
  printf("\n");
  
  system("pause");  
}

void listar_todos(FILE *file) {
  int n;
  Carro carros[size];
  
  n = recupera_carros(file, carros);
  
  printf("=================================================\n");
  printf(" Todos os veiculos\n");
  printf("=================================================\n");
  
  listar_carros(carros, n);
}

void desenha_painel_filtro(int ord, int most, int opvlr, float valor) {
  printf("=================================================\n");
  //Mostrando
  printf("  - Ordenando por: ");
  switch (ord) {
  	case 1:
  	  printf("Modelo");
  	  break;
  	case 2:
  	  printf("Valor");
  	  break;
  }
  printf("\n");
  
  //Listando
  printf("  - Listando     : ");
  switch (most) {
  	case 1:
  	  printf("Disponiveis");
  	  break;
  	case 2:
  	  printf("Vendidos");
  	  break;
  	case 3:
  	  printf("Todos");
  	  break;
  }
  printf("\n");
  
  //Valor
  printf("  - Valor        : ");
  switch (opvlr) {
  	case 1:
  	  printf("Qualquer");
  	  break;
  	case 2:
  	  printf("Maior que R$ %.2f", valor);
  	  break;
  	case 3:
  	  printf("Menor que R$ %.2f", valor);
  	  break;
  	case 4:
  	  printf("Igual a R$ %.2f", valor);
  	  break;
  }
  printf("\n");
  printf("=================================================\n");	
}

int opcao_ordenacao() {
  printf("=================================================\n");
  printf("Ordenar por\n");
  printf(" 1 - Modelo\n");
  printf(" 2 - Valor\n");
  printf("=================================================\n");
  
  return opcao(1, 2);
}

int opcao_listagem() {
  printf("=================================================\n");
  printf("Listar\n");
  printf(" 1 - Disponiveis\n");
  printf(" 2 - Vendidos\n");
  printf(" 3 - Todos\n");
  printf("=================================================\n");
  
  return opcao(1, 3);
}

int opcao_valor(float *valor) {
  int op;
  
  printf("=================================================\n");
  printf("Valor\n");
  printf(" 1 - Qualquer\n");
  printf(" 2 - Maior que\n");
  printf(" 3 - Menor que\n");
  printf(" 4 - igual a\n");
  printf("=================================================\n");
  
  op = opcao(1, 4);
  
  if (op > 1) {
    printf("Valor: ");
    scanf("%f", valor);
  }
  
  return op;
}

int compara_modelo(Carro car1, Carro car2) {
  return strcmp(car1.modelo, car2.modelo);
}

int compara_valor(Carro car1, Carro car2) {
  return car1.valor - car2.valor;
}

int isDisponivel(Carro car) {
  return !car.vend;
}

int isVendido(Carro car) {
  return car.vend;
}

int valor_maior_que(Carro car, float valor) {
  return car.valor > valor;
}

int valor_menor_que(Carro car, float valor) {
  return car.valor < valor;
}

int valor_igual(Carro car, float valor) {
  return car.valor == valor;
}

void listar_avancado(FILE *file) {
  int i, j, n;
  int op, ord, most, opvlr;
  float valor;
  Carro carros[size], aux;
    
  //Ponteiros para funcao
  compara fncComp;
  isValido mostrarPorStatus;
  valor_valido mostrar_valor;
  
  do {
  	system("cls");
  	
    ord = opcao_ordenacao();
    system("cls");
    most = opcao_listagem();
    system("cls");
    opvlr = opcao_valor(&valor);
    system("cls");
    
    n = recupera_carros(file, carros);
    
    // Ordenação
    fncComp = ord == 1 ? compara_modelo : compara_valor;
    
    for (i = 0; i < n - 1; i++)
      for (j = i + 1; j < n; j++)
        if (fncComp(carros[i], carros[j]) > 0) {
          aux = carros[j];
          carros[j] = carros[i];
          carros[i] = aux;
        }
    
    //Listagem
    mostrarPorStatus = most == 1 ? isDisponivel : isVendido;
    
    if (most != 3) {
      reset_carro(&aux);
      i = 0;
      while (i < n) {
        if (!mostrarPorStatus(carros[i])) {
          if (i == n - 1)
        	carros[i] = aux;
          for (j = i; j < n - 1; j++)
	  	    carros[j] = carros[j + 1];
	  	  n--;
	    }
	    else
	      i++;
      }
    }
    
    //Filtro de valor
    if (opvlr > 1) {
      if (opvlr == 2)
        mostrar_valor = valor_maior_que;
      else if (opvlr == 3)
        mostrar_valor = valor_menor_que;
      else if (opvlr == 4)
        mostrar_valor = valor_igual;
        
      reset_carro(&aux);
    	i = 0;
      while (i < n) {
        if (!mostrar_valor(carros[i], valor)) {
          if (i == n - 1)
            carros[i] = aux;
          for (j = i; j < n - 1; j++)
	  	  carros[j] = carros[j + 1];
	  	  n--;
	    }
	    else
	      i++;
      }
    }
    
    desenha_painel_filtro(ord, most, opvlr, valor);
    
    listar_carros(carros, n);
    
    system("cls");
    
    printf("Filtrar novamente?\n");
    printf("1 - Sim, 2 - Nao\n");
    
    op = opcao(1, 2);
  }
  while (op == 1);
}

void pesq_placa(Carro carros[], int len, char placa[], int encont[]) {
  int i, j = 0;
  for (i = 0; i < len; i++) {
    if (!strcmp(carros[i].placa, placa))
      encont[j++] = i;
  }
}

void pesq_modelo(Carro carros[], int len, char modelo[], int encont[]) {
  int i, j = 0;
  for (i = 0; i < len; i++)
    if (!carros[i].vend && !strcmp(carros[i].modelo, modelo))
      encont[j++] = i;
}

void opcao_placa(char pesq[]) {
  printf("Placa: ");
  gets(pesq);
  fflush(stdin);
}

void opcao_modelo(char pesq[]) {
  printf("Modelo: ");
  gets(pesq);
  fflush(stdin);
}

void vender(FILE *file, Carro carros[], int indice, int len) {
  int i;

  carros[indice].vend = 1;

  fclose(file);
  file = fopen(url, "w");

  for (i = 0; i < len; i++)
    salva_carro(file, carros[i]);
}

void pesquisar(FILE *file) {

  char pesq[50];
  int encont[size], n, i, op, ndisp = 0, sel = -1;
  Carro carros[size];
  Carro carrosEncont[size];

  do {
    system("cls");
    
    printf("Pesquisar por:\n");
    printf(" 1 - Placa\n");
    printf(" 2 - Modelo\n");
    printf(" 3 - Voltar\n");
    
    //Inicializa o array dos encontrados
    for (i = 0; i < size; i++)
      encont[i] = -1;
    
    //Recupera a opção do usuário
    op = opcao(1, 3);
    
    system("cls");
    
    //Recupera os carros do arquivo
    n = recupera_carros(file, carros);
    
    switch (op) {
      case 1:
        opcao_placa(pesq);
        printf("\n");
        pesq_placa(carros, n, pesq, encont);
        break;
      case 2:
        opcao_modelo(pesq);
        printf("\n");
        pesq_modelo(carros, n, pesq, encont);
        break;
    }
    
    printf("=====================================\n");
    for (i = 0; i < size; i++) {
      if (encont[i] == -1)
        break;
      printf("Carro %d\n", i + 1);
      desenha_carro(carros[encont[i]]);
      ndisp = ndisp + (carros[encont[i]].vend ? 0 : 1);
    }
    printf("=====================================\n");
    printf("Encontrados: %d\n", i);
    printf("Vendidos   : %d\n", i - ndisp);
    printf("Disponiveis: %d\n", ndisp);
    printf("=====================================\n");
    
    if (i > 0 && ndisp > 0) {
      if (i > 1 && ndisp > 1) {
        printf("Selecione um carro\n");
        do {
          if (sel > -1)
            printf("Carro %d ja foi vendido.\n", sel);
          sel = opcao(1, i);
        }
        while (carros[encont[sel - 1]].vend);
      }
      else
        if (ndisp == 1) {
          //Seleciona o unico carro que esta disponivel
          for (sel = 1; sel <= n; sel++)
            if (!carros[encont[sel - 1]].vend)
              break;
	    }
	    else
          sel = 1;
    
      printf("Deseja vender o carro %d?\n", sel);
      printf("1 - Sim, 2 - Nao\n");
    
      op = opcao(1, 2);
    
      if (op == 1) {
        vender(file, carros, encont[sel - 1], n);
        printf("Vendido com sucesso.\n\n");
      }
    }
    
    printf("Pesquisar novamente?\n", sel);
    printf("1 - Sim, 2 - Nao\n");
    
    op = opcao(1, 2);
  }
  while (op == 1);
}

void relatorio(FILE *file) {
  int i, n, nvend = 0;
  float tot;

  Carro carros[size];

  n = recupera_carros(file, carros);

  printf("Modelo\t\t\tValor\n");
  printf("-------------------------------------------\n");
  for (i = 0; i < n; i++) {
    if (carros[i].vend) {
    	nvend++;
      printf("%s\t\t\tR$ %.2f\n", carros[i].modelo, carros[i].valor);
      tot += carros[i].valor;
    }
  }
  printf("===========================================\n");
  printf("Vendidos: %d carros\n", nvend);
  printf("Total   : R$ %.2f\n", tot);
  printf("\n");
  system("pause");
}

int opcao(int min, int max) {
  int op;

  do {
    printf("Opcao: ");
    scanf("%d", &op);
    fflush(stdin);
  }
  while(op < min || op > max);

  return op;
}

void main() {

  int op;
  FILE *file;

  while (1) {

    file = fopen(url, "a");

    if (file == NULL) {
      printf("Nao foi possivel carregar o arquivo db.txt.\n");
      exit(0);
    }

    system("cls");

    printf("Menu\n");
    printf(" 1. Novo carro\n");
    printf(" 2. Listar todos\n");
    printf(" 3. Listar todos (avancado)\n");
    printf(" 4. Pesquisar carro\n");
    printf(" 5. Relatorio\n");
    printf(" 6. Sair\n");
    
    op = opcao(1, 6);

    system("cls");

    switch (op) {
      case 1:
        novo_carro(file);
        break;
      case 2:
        listar_todos(file);
        break;
      case 3:
        listar_avancado(file);
        break;
      case 4:
        pesquisar(file);
        break;
      case 5:
        relatorio(file);
        break;
      case 6:
        exit(0);
    }

    fclose(file);
  }

}



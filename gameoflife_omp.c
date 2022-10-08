#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <assert.h>
#define m 50000
void aloca_matriz(int **matriz, int n){
  int i=0;
  for(i=0; i<n; i++){
    matriz[i]=malloc(n*sizeof(int*));
  }
}
void monta_matriz(int **matriz,int n){
  int i=0 , j=0;
  for (i=0 ; i<n ; i++){
    for (j=0; j<n; j++){
      matriz[i][j] = 0;
    }
  }
  //GLIDER
  int lin = 1, col = 1;
  matriz[lin  ][col+1] = 1;
  matriz[lin+1][col+2] = 1;
  matriz[lin+2][col  ] = 1;
  matriz[lin+2][col+1] = 1;
  matriz[lin+2][col+2] = 1;
  //R-pentomino
  lin =10; col = 30;
  matriz[lin  ][col+1] = 1;
  matriz[lin  ][col+2] = 1;
  matriz[lin+1][col  ] = 1;
  matriz[lin+1][col+1] = 1;
  matriz[lin+2][col+1] = 1;
  /*matriz[0][1] = 1;
  matriz[0][2] = 1;
  matriz[0][3] = 1;
  matriz[1][4] = 1;
  matriz[1][4] = 1;*/
}
void printa_matriz(int **matriz, int n){
  int i=0, j=0;
  for (i=0 ; i<n ; i++){
    for (j=0; j<n; j++){
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}
int encontra_num_vizinhos(int **matriz, int i, int j, int n, int p){
  int k = 0, l = 0, vizinhos = 0;
  // QUINAS ---
  if (i == 0 && j == 0){ // quina sup esquerda
    if (matriz[n-1][n-1] == 1) vizinhos += 1; // início dos vizinhos opostos
    if (matriz[n-1][0] == 1) vizinhos += 1;
    if (matriz[n-1][1] == 1) vizinhos += 1;
    if (matriz[0][n-1] == 1) vizinhos += 1;
    if (matriz[1][n-1] == 1) vizinhos += 1; // fim vizinhos opostos
    // vizinhos com fronteiras
    if (matriz[0][1] == 1) vizinhos += 1;
    if (matriz[1][1] == 1) vizinhos += 1;
    if (matriz[1][0] == 1) vizinhos += 1;
  }
  else if (i == 0 && j == (n-1)){ // quina sup direita 
    if (matriz[n-1][0] == 1) vizinhos += 1; // início dos vizinhos opostos
    if (matriz[n-1][n-1] == 1) vizinhos += 1;
    if (matriz[n-1][n-2] == 1) vizinhos += 1;
    if (matriz[0][0] == 1) vizinhos += 1;
    if (matriz[1][0] == 1) vizinhos += 1; // fim vizinhos opostos
    // vizinhos com fronteiras
    if (matriz[0][n-2] == 1) vizinhos += 1;
    if (matriz[1][n-2] == 1) vizinhos += 1;
    if (matriz[1][n-1] == 1) vizinhos += 1;
  }
  else if (i == (n-1) && j == 0){ // quina inf esquerda
    if (matriz[0][n-1] == 1) vizinhos += 1; // início dos vizinhos opostos
    if (matriz[n-1][n-1] == 1) vizinhos += 1;
    if (matriz[n-2][n-1] == 1) vizinhos += 1;
    if (matriz[0][0] == 1) vizinhos += 1;
    if (matriz[0][1] == 1) vizinhos += 1; // fim vizinhos opostos
    // vizinhos com fronteiras
    if (matriz[n-2][0] == 1) vizinhos += 1;
    if (matriz[n-2][1] == 1) vizinhos += 1;
    if (matriz[n-1][1] == 1) vizinhos += 1;
  }
  else if (i == (n-1) && j == (n-1)){ // quina inf direita
    if (matriz[0][0] == 1) vizinhos += 1; // início dos vizinhos opostos
    if (matriz[n-1][0] == 1) vizinhos += 1;
    if (matriz[n-2][0] == 1) vizinhos += 1;
    if (matriz[0][n-1] == 1) vizinhos += 1;
    if (matriz[0][n-2] == 1) vizinhos += 1; // fim vizinhos opostos
    // vizinhos com fronteiras
    if (matriz[n-1][n-2] == 1) vizinhos += 1;
    if (matriz[n-2][n-2] == 1) vizinhos += 1;
    if (matriz[n-2][n-1] == 1) vizinhos += 1;
  }
  // BORDAS --- 
  else if ( i == 0 && (j > 0 && j < (n-1))){   // borda superior
    
    if (matriz[n-1][j-1] == 1) vizinhos += 1; // início dos vizinhos opostos
    if (matriz[n-1][j] == 1) vizinhos += 1;
    if (matriz[n-1][j+1] == 1) vizinhos += 1; // fim vizinhos opostos
    // vizinhos com fronteiras
    if (matriz[i][j-1] == 1) vizinhos += 1;
    if (matriz[i][j+1] == 1) vizinhos += 1;
    if (matriz[i+1][j-1] == 1) vizinhos += 1;
    if (matriz[i+1][j] == 1) vizinhos += 1;
    if (matriz[i+1][j+1] == 1) vizinhos += 1;
    if (vizinhos != 0){
     // printf(" \n borda sup %d,geração é %d posição %d,%d \n", vizinhos, p, i,j);
    }
    
  }
  else if ( i == (n-1) && (j > 0 && j < (n-1))){ // borda inferior
    if (matriz[0][j-1] == 1) vizinhos += 1; // início dos vizinhos opostos
    if (matriz[0][j] == 1) vizinhos += 1;
    if (matriz[0][j+1] == 1) vizinhos += 1; // fim vizinhos opostos
    // vizinhos com fronteiras
    if (matriz[n-1][j-1] == 1) vizinhos += 1;
    if (matriz[n-1][j+1] == 1) vizinhos += 1;
    if (matriz[n-2][j] == 1) vizinhos += 1;
    if (matriz[n-2][j-1] == 1) vizinhos += 1;
    if (matriz[n-2][j+1] == 1) vizinhos += 1;
  }
  else if (( i > 0 && i < (n-1)) && j == 0){ // borda esquerda
    if (matriz[i-1][n-1] == 1) vizinhos += 1; // início dos vizinhos opostos
    if (matriz[i][n-1] == 1) vizinhos += 1;
    if (matriz[i+1][n-1] == 1) vizinhos += 1; // fim vizinhos opostos
    // vizinhos com fronteiras
    if (matriz[i-1][j] == 1) vizinhos += 1;
    if (matriz[i+1][j] == 1) vizinhos += 1;
    if (matriz[i-1][j+1] == 1) vizinhos += 1;
    if (matriz[i][j+1] == 1) vizinhos += 1;
    if (matriz[i+1][j+1] == 1) vizinhos += 1;
  } 
  else if (( i > 0 && i < (n-1)) && j == (n-1)){ // borda direita
    if (matriz[i-1][n-1] == 1) vizinhos += 1; // início dos vizinhos opostos
    if (matriz[i][n-1] == 1) vizinhos += 1;
    if (matriz[i+1][n-1] == 1) vizinhos += 1; // fim vizinhos opostos
    // vizinhos com fronteiras
    if (matriz[i-1][n-1] == 1) vizinhos += 1;
    if (matriz[i+1][n-1] == 1) vizinhos += 1;
    if (matriz[i-1][n-2] == 1) vizinhos += 1;
    if (matriz[i][n-2] == 1) vizinhos += 1;
    if (matriz[i+1][n-2] == 1) vizinhos += 1;
  }  
  else{ // célula fora das bordas da matriz
    for (k = 0; k < 3; k++){
      for (l = 0; l < 3; l++){
        if (matriz[i-k+1][j-l+1] == 1) vizinhos += 1;
      }   
    }
  } 
  return vizinhos;
}
int aplica_condicoes(int **matriz, int i, int j, int n, int p){
  int vizinhos = 0;
  int prox_estado_celula = matriz[i][j]; 
  if (matriz[i][j] == 1){ // célula viva
    vizinhos = encontra_num_vizinhos(matriz,i,j,n,p); 
    
    if ( i == 0 || j == 0 || i == (n-1) || j == (n-1)){
      vizinhos = vizinhos + 1;
    }
    vizinhos = vizinhos - 1;
    
    //printf(" \n Viva com %d vizinhos", vizinhos);
    if ( vizinhos == 2 || vizinhos == 3 ){   // fica viva
      prox_estado_celula = 1;
    }
    else{  // deve morrer
      prox_estado_celula = 0;
    }
    
  }
  else if (matriz[i][j] == 0){ // célula morta
    vizinhos = encontra_num_vizinhos(matriz,i,j,n,p);
    if (vizinhos == 3){  // três vizinhos deve ficar viva
      prox_estado_celula = 1;
    }
  }
  return prox_estado_celula;
}
void varredura_matriz(int **grid, int **new_grid, int n, int p){
  int i=0, j=0;
  for (i=0 ; i<n ; i++){
    for (j=0; j<n; j++){
      new_grid[i][j] = aplica_condicoes(grid, i, j,n,p);
    }
  }
}
void evolui_grid(int **grid, int **new_grid, int n){
  int i,j;
  for (i =0; i<n; i++){
    for (j=0; j<n ; j++){
      grid[i][j] = new_grid[i][j];
    }
  }
}
void loop_geracoes(int **grid, int **new_grid, int n, int geracoes, int p, int qthreads){
  int i;
  #pragma omp parallel
  {
   #pragma omp for
   for (i=0; i < geracoes ; i++){
     varredura_matriz(grid, new_grid, n, p); // new_grid evolui
     evolui_grid(grid, new_grid,n); // grid = new_grid
     //qthreads = omp_get_num_threads();
    
   }
   qthreads = omp_get_num_threads();
   printf(" %d ", qthreads);
  }
}
int contador_celulas_vivas(int **new_grid, int geracoes, int n){
  int i,j,cont = 0;
  
  for (i=0; i<n; i++){
    for (j=0; j<n; j++){
      if (new_grid[i][j] == 1){
        cont = cont + 1 ;
      }
    }
  }
  return cont;
}
int main(void) {

  long int t,y;
  double a[m], b[m];
  double start, end, run;

  for (t=0; t<m; t++) a[t] = (double)(t*2)/(t+6);

  start = omp_get_wtime();

  int qthreads = 0;
  int geracoes = 2000; // quantidade de geracoes
  int n = 2048;     //dimensão da matriz (n x n) 2048
  int **grid, **new_grid;
  grid = malloc(n*sizeof(int*));
  new_grid = malloc(n*sizeof(int*));
  aloca_matriz(grid,n);
  monta_matriz(grid,n);
  aloca_matriz(new_grid,n);
  monta_matriz(new_grid,n);
 // printa_matriz(grid,n);
  printf("\n");
  int i,p,j,cont=0;
  loop_geracoes(grid,new_grid,n,geracoes,p,qthreads);
  cont = contador_celulas_vivas(new_grid,geracoes,n);
  
  //qthreads=omp_get_num_threads();
  
  end = omp_get_wtime();
    printf(" took %f seconds.\n", end-start);
  printf("\n");
  return 0;
 
}

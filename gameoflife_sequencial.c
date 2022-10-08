#include <stdio.h>
  #include <stdlib.h>
  #include <pthread.h>
  #include <unistd.h>
  #include <time.h>
  #include <sys/time.h>
  #include <omp.h>
  
  int getNeighbors(int** grid, int i, int j); //Retorna os vizinhos de cada célula
  int **grid;
  int **newGrid; 
  int **aux;
  
  int TAMANHO_TOTAL = 2048;
  int GERACAO_TOTAL = 2000;
  
  int getNeighbors(int **grid, int i, int j){
      int totalNeighbors = 0;
      int linhaMin, colunaMin, linhaMax, colunaMax;
  
      if(i-1 < 0){
          linhaMin = TAMANHO_TOTAL - 1;
      }
      else{
          linhaMin = i-1;
      }
      if(i+1 == TAMANHO_TOTAL){
          linhaMax = 0;
      }
      else{
          linhaMax = i+1;
      }
      if(j-1 < 0){
          colunaMin = TAMANHO_TOTAL - 1;
      }
      else{
          colunaMin = j-1;
      }
      if(j+1 == TAMANHO_TOTAL){
          colunaMax = 0;
      }
      else{
          colunaMax = j+1;
      }
  
      totalNeighbors += grid[linhaMin][j];
      totalNeighbors += grid[linhaMin][colunaMin];
      totalNeighbors += grid[linhaMin][colunaMax];
      totalNeighbors += grid[i][colunaMin];
      totalNeighbors += grid[i][colunaMax];
      totalNeighbors += grid[linhaMax][j];
      totalNeighbors += grid[linhaMax][colunaMin];
      totalNeighbors += grid[linhaMax][colunaMax];
      return totalNeighbors;
  }
  
  int inicializarCelula(int** grid){
      int lin, col;
      //GLIDER
      lin = 1;
      col = 1;
      grid[lin  ][col+1] = 1;
      grid[lin+1][col+2] = 1;
      grid[lin+2][col  ] = 1;
      grid[lin+2][col+1] = 1;
      grid[lin+2][col+2] = 1;
  
      //R-pentomino
      lin =10; col = 30;
      grid[lin  ][col+1] = 1;
      grid[lin  ][col+2] = 1;
      grid[lin+1][col  ] = 1;
      grid[lin+1][col+1] = 1;
      grid[lin+2][col+1] = 1;
      return 10;
  
  }
  
  void atualizaGrid(){
    int companheiro;
  
      for(int i = 0; i < TAMANHO_TOTAL; i++){
        for(int j=0; j < TAMANHO_TOTAL; j++){
          companheiro = getNeighbors(grid, i, j);
          if(companheiro == 2 && grid[i][j] == 1){
            newGrid[i][j] = 1;
          }
          else{
            if(companheiro == 3){
              newGrid[i][j] = 1;
            }
            else{
              newGrid[i][j] = 0;
            }
          }
        }
      }
    
    
    
  }
  
  int contarTotal(){
    int totalCelulas = 0;
    for(int i =0; i < TAMANHO_TOTAL; i++){
      for(int j=0; j < TAMANHO_TOTAL; j++){
        if(grid[i][j] == 1){
          totalCelulas++;
        }
     }
    }  
    return totalCelulas;
  }
  
  void passarGeracao(){
    int totalCelulas;
    
    for(int cont = 0; cont < 2000; cont++){
      atualizaGrid();
      
      aux = grid;
      grid = newGrid;
      newGrid = aux;
  
      
      
    }
    totalCelulas = contarTotal();
    printf("\n Geracao Final: %d\n", totalCelulas);
    //return NULL;
  }
  
  int main()
  {
      struct timeval inicio,final;
      long long tmili;
    
      gettimeofday(&inicio,NULL);
    
      grid = (int**)calloc(TAMANHO_TOTAL,(sizeof(int*)));
      newGrid = (int**)calloc(TAMANHO_TOTAL,(sizeof(int*)));
      aux = (int**)calloc(TAMANHO_TOTAL,(sizeof(int*)));
      int *celula;
      
    int companheiro = 0;
    int totalCelulas = 0;
    int create;
  
      for(int cont = 0; cont < TAMANHO_TOTAL; cont++)    {
          grid[cont] = (int*)calloc(TAMANHO_TOTAL,sizeof(int));
          newGrid[cont] = (int*)calloc(TAMANHO_TOTAL,sizeof(int));
      }
  
      totalCelulas = inicializarCelula(grid);
    passarGeracao();
  
      printf("\n Geracao 0: %d\n", totalCelulas);
      gettimeofday(&final,NULL);
      tmili = (int) (1000*(final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
      printf(" Sequencial tempo: %lld ms\n", tmili);
    
      return 0;
  }

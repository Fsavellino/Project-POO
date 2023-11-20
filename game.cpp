// Implementação do funcionamento do jogo

#include "game.h"

const QSize Game::resolution = QSize(380,380);

//Construtor
Game::Game()
    //Caminho para os arquivos de imagem do jogo, e a variavel ITERATION_VALUE que define a taxa de atualização
    : w(32), PATH_TO_TILES(":/images/tiles.png"), PATH_TO_FACE(":/images/face.png"), ITERATION_VALUE(1000.0f/60.0f)
{
    init();
}

//Função responsável por iniciar o jogo
void Game::init()
{
    //Inicializa a semente da função rand()
    srand(time_t(0));
    //Cria a grade 10x10 e preenche com 10 minas aleatoriamente
    //Probabilidade de colocar a mina é de 1 em 5
    for (int i=1;i<=10;i++)
    {
        for (int j=1;j<=10;j++)
         {
           sgrid[i][j]=10;
           if (rand()%5==0)  grid[i][j]=9;
           else grid[i][j]=0;
         }
    }

    //Itera todos os quadrados para contar a quantidade de minas ao redor de cada quadrado
    //Verificando os quadrados vizinhos
    for (int i=1 ; i<=10 ; i++)
    {
        for (int j=1; j<=10; j++)
         {
           int n=0;
           if (grid[i][j] == 9)
           {
               continue;
           }
           if (grid[i+1][j] == 9)
           {
               n++;
           }
           if (grid[i][j+1] == 9)
           {
               n++;
           }
           if (grid[i-1][j] == 9)
           {
               n++;
           }
           if (grid[i][j-1] == 9)
           {
               n++;
           }
           if (grid[i+1][j+1] == 9)
           {
               n++;
           }
           if (grid[i-1][j-1] == 9)
           {
               n++;
           }
           if (grid[i-1][j+1] == 9)
           {
               n++;
           }
           if (grid[i+1][j-1] == 9)
           {
               n++;
           }
           grid[i][j]=n;
         }
    }
}

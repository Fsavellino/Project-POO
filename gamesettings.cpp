#include "gamesettings.h"
#include "GameOverDialog.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <queue>

//Construtor
GameSettings::GameSettings(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_timer(new QTimer(this)), m_x(0), m_y(0), m_resetVal(false)
{
    loadPixmap();
    setSceneRect(0,0, m_game.resolution.width(), m_game.resolution.height());
    connect(m_timer, &QTimer::timeout, this, &GameSettings::update);
    //Temporizador para a função
    m_timer->start(m_game.ITERATION_VALUE);
}

//Função update
void GameSettings::update()
{
    clear();
    QGraphicsPixmapItem *faceItem = new QGraphicsPixmapItem(m_facePixmap.copy(int(m_resetVal)*m_facePixmap.width()/2, 0, m_facePixmap.width()/2, m_facePixmap.height()));
    addItem(faceItem);
    faceItem->setPos(1 * m_game.w,0);

    for (int i = 1;i <= 10; i++)
    {
        for (int j = 1;j <= 10; j++)
        {
            if ( m_game.sgrid[m_x][m_y] == 9)
            {
                m_game.sgrid[i][j] = m_game.grid[i][j];
            }
            QGraphicsPixmapItem *gridItem =
                    new QGraphicsPixmapItem(m_tilesPixmap.copy( m_game.sgrid[i][j]*m_game.w, 0, m_game.w, m_game.w) );
            gridItem->setPos(i*m_game.w, j*m_game.w);
            addItem(gridItem);
        }
    }
}

//Função para manipular os eventos de clique do mouse
void GameSettings::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Qt::MouseButton button = event->button();

    QPointF clickedPos =  event->scenePos();
    m_x = static_cast<int>(clickedPos.x()) / m_game.w;
    m_y = static_cast<int>(clickedPos.y()) / m_game.w;

    if (m_game.grid[m_x][m_y] == 9) {
            GameOverDialog gameOverDialog;
            gameOverDialog.exec();
        }

    /*//Determina a função para cada tipo de clique (Esquerdo/Direito)
    if(button == Qt::LeftButton)
    {
        m_game.sgrid[m_x][m_y] = m_game.grid[m_x][m_y];
        checkResetClick(m_x, m_y);
    }*/
    if(button == Qt::LeftButton) {
        // Se a célula clicada for vazia, revele as células vazias adjacentes
        if (m_game.grid[m_x][m_y] == 0) {
            revealEmptyCells(m_x, m_y);
        } else {
            // Se a célula não for vazia, apenas revele essa célula
            m_game.sgrid[m_x][m_y] = m_game.grid[m_x][m_y];
            checkResetClick(m_x, m_y);
        }
    }
    else if(button == Qt::RightButton)
    {
        m_game.sgrid[m_x][m_y] = 11;
    }
    QGraphicsScene::mousePressEvent(event);
}

//Função para manipular os eventos de liberação do clique do mouse
void GameSettings::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_resetVal)
    {
        m_resetVal = false;
        m_game.init();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

//Função para carregar o pixmaps atraves dos arquivos de imagem
void GameSettings::loadPixmap()
{
    if(m_tilesPixmap.load(m_game.PATH_TO_TILES))
    {
        qDebug() << "TilesPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "TilesPixmap is not loaded successfully";
    }

    if(m_facePixmap.load(m_game.PATH_TO_FACE))
    {
        qDebug() << "FacePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "FacePixmap is not loaded successfully";
    }
}

//Função para verificar se o botão de reset
void GameSettings::checkResetClick(int x, int y)
{
    if( y == 0 && (x == 1 || x == 2))
    {
        m_resetVal = true;
    }
}

void GameSettings::revealEmptyCells(int x, int y) {
    // Verificar limites da matriz
    if (x < 0 || y < 0 || x >= m_game.resolution.width() || y >= m_game.resolution.height()) {
        return;
    }

    // Se a célula já foi revelada ou não é vazia, não faça nada
    if (m_game.sgrid[x][y] != -1 || m_game.grid[x][y] != 0) {
        return;
    }

    // Criar uma fila para realizar a busca em largura
    std::queue<std::pair<int, int>> cellsQueue;
    cellsQueue.push({x, y});

    while (!cellsQueue.empty()) {
        std::pair<int, int> cell = cellsQueue.front();
        cellsQueue.pop();

        int currentX = cell.first;
        int currentY = cell.second;

        // Revela a célula atual
        m_game.sgrid[currentX][currentY] = m_game.grid[currentX][currentY];

        // Verifica células vizinhas
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newX = currentX + i;
                int newY = currentY + j;

                // Verifica limites da matriz e se a célula já foi revelada
                if (newX >= 0 && newY >= 0 && newX < m_game.resolution.width() && newY < m_game.resolution.height() &&
                m_game.sgrid[newX][newY] == -1 && m_game.grid[newX][newY] == 0) {
                cellsQueue.push({newX, newY});
                }
            }
       }
   }
}

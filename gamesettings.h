#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <QGraphicsScene>
#include "game.h"
#include "cell.h"

class QTimer;
class GameSettings : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameSettings(QObject *parent = nullptr);

private slots:
    void update();
private:
    void loadPixmap();
    void checkResetClick(int x, int y);
    void revealEmptyCells(int x, int y);
    Game m_game;
    QPixmap m_tilesPixmap;
    QPixmap m_facePixmap;
    QTimer *m_timer;
    int m_elapsedTime; // Tempo decorrido em segundos
    int m_x, m_y;
    bool m_resetVal;
    // Matriz de células para representar o campo do jogo
    Cell* m_cells[11][11]; // Ajuste o tamanho conforme necessário

    // QGraphicsScene interface
   protected:
       virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
       virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

   };

   #endif // GAMESETTINGS_H



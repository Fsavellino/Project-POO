#ifndef GAME_H
#define GAME_H
#include <QSize>
#include <QString>


class Game
{
public:
    Game();
    static const QSize resolution;
    const int w;
    const QString PATH_TO_TILES;
    const QString PATH_TO_FACE;
    int grid[11][11];
    int sgrid[11][11];
    const float ITERATION_VALUE;


    void init();
};

#endif // GAME_H

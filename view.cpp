#include "view.h"
#include "game.h"
#include "cell.h"
#include "gamesettings.h"

//Construtor
View::View()
    : QGraphicsView(), m_gameSettings(new GameSettings(this))
{
    setWindowTitle("Campo Minado");
    //Desabilitar as barras de rolagem verticais e horizontais
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(m_gameSettings);
}


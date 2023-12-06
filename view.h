#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QLabel>

class GameSettings;

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View();

signals:
private:
    GameSettings *m_gameSettings;
};

#endif // VIEW_H

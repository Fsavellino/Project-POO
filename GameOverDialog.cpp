#include "GameOverDialog.h"

GameOverDialog::GameOverDialog(QWidget *parent) : QDialog(parent) {
    QLabel *gameOverLabel = new QLabel("Game Over!!!  =(", this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    gameOverLabel->setFont(font);
    // Definindo o tamanho fixo da janela do Game Over
    setFixedSize(200, 60);
    // Definindo a janela como não redimensionável
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

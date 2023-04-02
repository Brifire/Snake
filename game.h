#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QTimer>
#include <QKeyEvent>
#include <QString>
#include <QRandomGenerator>
class SnakeItem;
class Snake;
class GameField;





class GameField: public QWidget
{
    Q_OBJECT
 public:
    GameField();
protected:
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void setGameStatus();
    void startNewGame();
    void gameOver();
    void createFood();
private:
    Snake *m_snake;
    int m_snakeItemSize;
    QTimer *m_moveSnakeTimer;
    int m_fieldSize;
    bool m_isGamePaused;
    int m_score;
    bool m_isMoveBlocked;
    bool m_isGameOver;
    SnakeItem *m_food;
private slots:
    void MoveSnakeSlot();
 signals:
    void changeTextSignal(QString text);
};





class SnakeItem
{
    friend Snake;
    friend GameField;
 public:
    SnakeItem(int x,int y);
private:
    int m_x;
    int m_y;
};




class Snake
{


public:
    friend GameField;
    Snake();
private:
    QList<SnakeItem*> m_snakebody;
    int m_snakeBeginSize;
    enum SnakeDirection
    {
        up,
        left,
        down,
        right
    };
    SnakeDirection m_snakeDirection;
signals:

};

#endif // GAME_H

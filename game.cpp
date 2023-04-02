#include "game.h"
#include <QPainter>



GameField::GameField()
{
 setFixedSize(300,300);
 setFocusPolicy(Qt::StrongFocus);
 m_snakeItemSize=10;
 m_fieldSize=width()/m_snakeItemSize;
 startNewGame();

}

void GameField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QBrush gameFieldBrush(QColor(140, 126, 122),Qt::SolidPattern);
    QBrush snakeBrush(QColor(10, 127, 65),Qt::SolidPattern);
    QPainter painter;
    painter.begin(this);
    if(m_isGameOver)
    {
        painter.setFont(QFont("Arial",20,700));
        painter.drawText(QRect(0,0,width(),height()),Qt::AlignCenter,"Game is over \n Score : " + QString::number(m_score));
        return;
    }
    painter.setBrush(gameFieldBrush);
    painter.setPen(QColor(50,50,50));
    painter.drawRect(0,0,width()-1,height()-1);
    painter.setBrush(snakeBrush);
    painter.setPen(QColor(0,0,0));

    for(int i=0;i<m_snake->m_snakebody.size();++i)
    {
        painter.drawEllipse(m_snake->m_snakebody[i]->m_x*m_snakeItemSize,m_snake->m_snakebody[i]->m_y*m_snakeItemSize,m_snakeItemSize,m_snakeItemSize);
    }
    painter.drawEllipse(m_food->m_x*m_snakeItemSize,m_food->m_y*m_snakeItemSize,m_snakeItemSize,m_snakeItemSize);
    painter.end();
    m_isMoveBlocked=false;



}

void GameField::keyPressEvent(QKeyEvent *e)
{

 if(e->key()==Qt::Key_Space)
 {
     if(m_isGameOver)
     {
         startNewGame();
         return;
     }
     m_isGamePaused=!m_isGamePaused;
     setGameStatus();
 }
 if(m_isMoveBlocked)
 {
     return;
 }
 if(e->key()==Qt::Key_Left&&m_snake->m_snakeDirection!=Snake::SnakeDirection::right)
 {
     m_snake->m_snakeDirection=Snake::SnakeDirection::left;
 }
 if(e->key()==Qt::Key_Right&&m_snake->m_snakeDirection!=Snake::SnakeDirection::left)
 {
     m_snake->m_snakeDirection=Snake::SnakeDirection::right;
 }
 if(e->key()==Qt::Key_Down&&m_snake->m_snakeDirection!=Snake::SnakeDirection::up)
 {
     m_snake->m_snakeDirection=Snake::SnakeDirection::down;
 }
 if(e->key()==Qt::Key_Up&&m_snake->m_snakeDirection!=Snake::SnakeDirection::down)
 {
     m_snake->m_snakeDirection=Snake::SnakeDirection::up;
 }
 m_isMoveBlocked=true;

}



void GameField::gameOver()
{
m_isGameOver=true;
QString text="Start new game - SPACE";
emit changeTextSignal(text);
m_moveSnakeTimer->stop();
delete m_snake;
delete m_moveSnakeTimer;
delete m_food;

}

void GameField::createFood()
{
m_food->m_x=QRandomGenerator::global()->bounded(0,m_fieldSize-1);
m_food->m_y=QRandomGenerator::global()->bounded(0,m_fieldSize-1);
for(int i=0;i<m_snake->m_snakebody.size();++i)
{
    if(m_food->m_x==m_snake->m_snakebody[i]->m_x&&m_food->m_y==m_snake->m_snakebody[i]->m_y)
    {

        return createFood();


    }
}

}

void GameField::setGameStatus()
{
    QString text;
    if(m_isGamePaused==true)
    {
     m_moveSnakeTimer->stop();
     text="Score: "+ QString::number(m_score)+ "\nContinue - SPACE";
    }
    else
    {
        m_moveSnakeTimer->start(100);
        text="Score: "+ QString::number(m_score)+ "\nPause - SPACE";
    }
    emit changeTextSignal(text);
}

void GameField::startNewGame()
{
    m_snake=new Snake();
    m_isGamePaused=false;
    m_isMoveBlocked=false;
    m_isGameOver=false;
    m_moveSnakeTimer= new QTimer();
    m_food=new SnakeItem(m_fieldSize/2,m_fieldSize/2);
    connect(m_moveSnakeTimer,&QTimer::timeout,this,&GameField::MoveSnakeSlot);
    m_moveSnakeTimer->start(100);
    m_score=0;
    QString text="Score: "+ QString::number(m_score)+ "\nPause - SPACE";
    emit changeTextSignal(text);
}

void GameField::MoveSnakeSlot()
{
    SnakeItem *newSnakeItem;
    if(m_snake->m_snakeDirection==Snake::SnakeDirection::right)
    {
        newSnakeItem=new SnakeItem(m_snake->m_snakebody[0]->m_x +1,m_snake->m_snakebody[0]->m_y);
    }
    else if(m_snake->m_snakeDirection==Snake::SnakeDirection::left)
    {
        newSnakeItem= new SnakeItem(m_snake->m_snakebody[0]->m_x - 1,m_snake->m_snakebody[0]->m_y);
    }
    else if(m_snake->m_snakeDirection==Snake::SnakeDirection::up)
    {
         newSnakeItem= new SnakeItem(m_snake->m_snakebody[0]->m_x ,m_snake->m_snakebody[0]->m_y -1);
    }
    else
    {
        newSnakeItem= new SnakeItem(m_snake->m_snakebody[0]->m_x ,m_snake->m_snakebody[0]->m_y +1);
    }
    // field
    if(newSnakeItem->m_x>=m_fieldSize)
    {
        newSnakeItem->m_x=0;
    }
    else if(newSnakeItem->m_x<0)
    {
        newSnakeItem->m_x=m_fieldSize-1;
    }
    else if(newSnakeItem->m_y<0)
    {
        newSnakeItem->m_y=m_fieldSize-1;
    }
    else if(newSnakeItem->m_y>=m_fieldSize)
    {
        newSnakeItem->m_y=0;
    }
    //GameOver
    for(int i=0;i<m_snake->m_snakebody.size();++i)
    {
        if(newSnakeItem->m_x==m_snake->m_snakebody[i]->m_x && newSnakeItem->m_y==m_snake->m_snakebody[i]->m_y)
        {
            gameOver();
            repaint();
            delete newSnakeItem;
            return;
        }
    }
    if(newSnakeItem->m_x==m_food->m_x&&newSnakeItem->m_y==m_food->m_y)
    {
        m_score++;
        createFood();
        QString text="Score: "+ QString::number(m_score)+ "\nPause - SPACE";;
        emit changeTextSignal(text);
    }
    else
    {
        m_snake->m_snakebody.removeLast();
    }

    m_snake->m_snakebody.insert(0,newSnakeItem);

    repaint();
}

SnakeItem::SnakeItem(int x, int y)
{
m_x=x;
m_y=y;
}

Snake::Snake()
{
    m_snakeBeginSize=4;
    for(int i=0;i<m_snakeBeginSize;++i)
    {
        m_snakebody.insert(0,new SnakeItem(i,0));
    }
    m_snakeDirection=SnakeDirection::right;
}

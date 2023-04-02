#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    setFixedSize(320,360);
    m_gameField=new GameField();
    m_helpField=new HelpField();
    m_gridLayout= new QGridLayout();
    m_centralWidget=new QWidget();
    connect(m_gameField,&GameField::changeTextSignal,m_helpField,&HelpField::changeTextSlot);
    m_gridLayout->addWidget(m_gameField,0,0);
    m_gridLayout->addWidget(m_helpField,1,0);
    m_centralWidget->setLayout(m_gridLayout);
    setCentralWidget(m_centralWidget);
    setStyleSheet("background: rgb(153, 144, 141)");

}

MainWindow::~MainWindow()
{
    delete ui;
}


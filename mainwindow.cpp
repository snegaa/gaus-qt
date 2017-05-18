#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crossitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(QRectF(0,0,800,600))        // уст коорд сцены
  ,item(new CrossItem())
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&scene);
    scene.addItem(item);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    item->modern();
    ui->graphicsView->scene()->update(ui->graphicsView->scene()->sceneRect());
}

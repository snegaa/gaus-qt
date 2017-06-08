#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crossitem.h"
#include <QFileDialog>
#include "filters/gausfilter.h"
#include "filters/konturfilter.h"
#include "filters/medianfilter.h"
#include "filters/rezkfilter.h"
#include "filters/relfilter.h"
#include "filters/yarkfilter.h"
#include "QtConcurrent/QtConcurrent"
#include "unistd.h"

FilterOption::FilterOption(QString aKey, QString aDescription)
{
    mKey = aKey;
    mDescription = aDescription;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(QRectF(0,0,800,600))        // уст коорд сцены
  ,item(0)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&scene);
    //scene.addItem(item);


    mFilters[GausFilter::key()] = new GausFilter();
    mFilters[KonturFilter::key()] = new KonturFilter();
    mFilters[MedianFilter::key()] = new MedianFilter();
    mFilters[RezkFilter::key()] = new RezkFilter();
    mFilters[RelFilter::key()] = new RelFilter();
    mFilters[YarkFilter::key()] = new YarkFilter();

}

MainWindow::~MainWindow()
{
    delete ui;
    for (int i =0; i < mFilters.count(); ++i)
        delete mFilters[mFilters.keys().at(i)];
}


void MainWindow::on_open_file_triggered()
{
    QString vFileName = QFileDialog::getOpenFileName(this, "message", QString(), QString("Images (*.bmp *.png)"));
    if (!vFileName.isEmpty())
    {
        if (item)
        {
            scene.removeItem(item);
            delete item;
        }
        mHistory.clear();
        item = new CrossItem(vFileName);
        scene.addItem(item);
        /*QRectF vRectScene = ui->graphicsView->scene()->sceneRect();
        QRectF vRectItem = item->boundingRect();
        QRectF vUpdateRect( 0, 0, 0, 0);
        qreal vWidthView = ui->graphicsView->width();
        qreal vHeightView = ui->graphicsView->height();
        vUpdateRect.setWidth(qMax(qMax(vRectScene.width(), vRectItem.width()), vWidthView));
        vUpdateRect.setHeight(qMax(qMax(vRectScene.height(), vRectItem.height()), vHeightView));
        ui->graphicsView->scene()->setSceneRect(vUpdateRect);*/
    }
}

void MainWindow::on_save_file_triggered()
{
    if (item)
    {
        QString vFileName = QFileDialog::getSaveFileName(this, "message", QString(), QString("Images (*.bmp *.png)"));
        if (!vFileName.isEmpty())
        {
                item->getImage().save(vFileName);
        }
    }
}

void MainWindow::on_exit_triggered()
{
    close();
}

void MainWindow::setFilter(QString aFilterKey)
{
    BaseFilter* vpFilter = mFilters[aFilterKey];
    if (item)
    {
        QtConcurrent::run(item, CrossItem::modern, vpFilter);
        ui->progressBar->setValue(0);
        while (item->getState() < 100)
        {
            ui->progressBar->setValue(item->getState());
            usleep(100);
        }
        ui->progressBar->setValue(100);

        ui->graphicsView->scene()->update();
        ui->graphicsView->updateSceneRect(ui->graphicsView->scene()->sceneRect());

    }
}

void MainWindow::gausFilter()
{
    setFilter(GausFilter::key());
    mHistory.append(FilterOption(GausFilter::key(), GausFilter::description()));
}

void MainWindow::konturFilter()
{
    setFilter(KonturFilter::key());
    mHistory.append(FilterOption(KonturFilter::key(), KonturFilter::description()));
}
void MainWindow::medianFilter()
{
    setFilter(MedianFilter::key());
    mHistory.append(FilterOption(MedianFilter::key(), MedianFilter::description()));
}
void MainWindow::rezkFilter()
{
    setFilter(RezkFilter::key());
    mHistory.append(FilterOption(RezkFilter::key(), RezkFilter::description()));
}

void MainWindow::relFilter()
{
    setFilter(RelFilter::key());
    mHistory.append(FilterOption(RelFilter::key(), RelFilter::description()));
}

void MainWindow::yarkFilter()
{
    setFilter(YarkFilter::key());
    mHistory.append(FilterOption(YarkFilter::key(), YarkFilter::description()));
}
void MainWindow::on_gaus_filter_triggered()
{
    gausFilter();
}

void MainWindow::on_kontur_filter_triggered()
{
    konturFilter();
}

void MainWindow::on_median_filter_triggered()
{
    medianFilter();
}

void MainWindow::on_rel_filter_triggered()
{
    relFilter();
}

void MainWindow::on_history_save_triggered()
{
    QString vFileName = QFileDialog::getSaveFileName(this, "message", QString(), QString("*.hst"));
    if (!vFileName.isEmpty())
    {
        QJsonDocument doc;
        QJsonArray vArray;
        for (int i = 0; i < mHistory.count(); ++i)
        {
            FilterOption options = mHistory.at(i);
            QJsonObject json_option;
            json_option["key"] = options.mKey;
            json_option["description"] = options.mDescription;
            vArray.append(json_option);
            doc.setArray(vArray);
            QFile vFile(vFileName);
            if (vFile.open(QIODevice::WriteOnly))
            {
                vFile.write(doc.toJson());
            }
            vFile.close();
        }
    }
}

void MainWindow::on_history_load_triggered()
{
    QString vFileName = QFileDialog::getOpenFileName(this, "message", QString(), QString("*.hst"));
    if (!vFileName.isEmpty())
    {

        QFile vFile(vFileName);
        QString json_text;
        if (vFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            json_text = vFile.readAll();
            vFile.close();
        }

        QJsonDocument doc = QJsonDocument::fromJson(json_text.toUtf8());
        QJsonArray vArray = doc.array();
        for (int i = 0; i < vArray.count(); ++i)
        {
            QJsonObject json_option = vArray.at(i).toObject();
            FilterOption option(json_option["key"].toString(), json_option["description"].toString());
            mHistory.append(option);
            setFilter(option.mKey);
        }
    }
}

void MainWindow::on_reload_file_triggered()
{
    if (item)
    {
        item->reload();
        ui->graphicsView->scene()->update(ui->graphicsView->scene()->sceneRect());
    }
}

void MainWindow::on_rezk_filter_triggered()
{
    rezkFilter();
}

void MainWindow::on_yark_filter_triggered()
{
    yarkFilter();
}

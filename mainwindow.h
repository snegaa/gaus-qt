#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMap>

class BaseFilter;

namespace Ui {
class MainWindow;
}

class FilterOption
{
public:
    QString mKey;
    QString mDescription;

    FilterOption(QString aKey, QString aDescription);
};

class CrossItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_open_file_triggered();

    void on_save_file_triggered();

    void on_exit_triggered();

    void on_gaus_filter_triggered();

    void on_kontur_filter_triggered();
    //
    void on_median_filter_triggered();

    void gausFilter();
    void konturFilter();
    void medianFilter();
    void rezkFilter();
    void relFilter();
    void yarkFilter();

    void setFilter(QString aFilterKey);

    void on_history_save_triggered();

    void on_history_load_triggered();

    void on_reload_file_triggered();

    void on_rezk_filter_triggered();
    void on_rel_filter_triggered();
    void on_yark_filter_triggered();

    void on_yrak_filter_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    CrossItem* item;

    QList<FilterOption> mHistory;
    QMap<QString, BaseFilter*> mFilters;
};

#endif // MAINWINDOW_H

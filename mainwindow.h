#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void mouseClickEvent();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
	void on_button_new_clicked();
	void on_button_clear_item_clicked();
	void addDotItem();
	void onPlotClicked();



	private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

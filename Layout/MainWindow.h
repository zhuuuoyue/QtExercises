#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Transfer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOkClicked(bool checked = false);
private:
    Ui::MainWindow *ui;
    Transfer* m_transfer;
};

#endif // MAINWINDOW_H

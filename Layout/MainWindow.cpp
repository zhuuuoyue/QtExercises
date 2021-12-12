#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_transfer = ui->transfer;
    QStringList candidates = {"湖北省", "湖南省", "河北省", "河南省", "山东省", "山西省", "广东省", "广西壮族自治区"};
    QStringList selected = {"北京市", "天津市", "上海市", "重庆市"};
    m_transfer->loadData(candidates, selected);
    connect(ui->ok, &QPushButton::clicked, this, &MainWindow::onOkClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOkClicked(bool checked)
{
    QList<QString> result = m_transfer->getSelected();
    QStringList temp;
    for (const QString& item : result)
    {
        temp.push_back(item);
    }
    ui->result->setText(temp.join("\n"));
}

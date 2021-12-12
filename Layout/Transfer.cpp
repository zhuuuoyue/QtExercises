#include "Transfer.h"

#include <QStringList>
#include <QList>
#include <algorithm>
#include <vector>

Transfer::Transfer(QWidget *parent) : QWidget(parent)
{
    initializeTransfer();
    initializeEvents();
}

void Transfer::loadData(const QList<QString> &candidates, const QList<QString> &selected)
{
    QList<QString> tempSelected;
    for (const QString& item : selected)
    {
        if (!tempSelected.contains(item))
        {
            tempSelected.append(item);
        }
    }
    loadListItems(m_pRightList, tempSelected);
    updateRightCount();

    QList<QString> tempCandidates;
    for (const QString& item : candidates)
    {
        if (!tempSelected.contains(item) && !tempCandidates.contains(item))
        {
            tempCandidates.append(item);
        }
    }
    loadListItems(m_pLeftList, tempCandidates);
    updateLeftCount();
}

void Transfer::setTitle(const QString &title)
{
    m_pTitle->setText(title);
}

void Transfer::setLeftTitle(const QString &title)
{
    m_pLeftTitle->setText(title);
}

void Transfer::setRightTitle(const QString &title)
{
    m_pRightTitle->setText(title);
}

QList<QString> Transfer::getCandidates() const
{
    return getListItems(m_pLeftList);
}

QList<QString> Transfer::getSelected() const
{
    return getListItems(m_pRightList);
}

void Transfer::initializeTransfer()
{
    this->resize(320, 240);

    // title
    m_pTitle = new QLabel(this);
    m_pTitle->setText("<h1>Transfer</h1>");

    // left title
    m_pLeftTitle = createColumnTitle("<h3>Candidates</h3>");
    QSpacerItem* item_1 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout* layout_1 = new QHBoxLayout();
    layout_1->addWidget(m_pLeftTitle);
    layout_1->addSpacerItem(item_1);

    // left list
    m_pLeftList = createList();

    // left count
    m_pLeftCount = new QLabel(this);
    m_pLeftCount->setText("");
    QSpacerItem* item_2 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout* layout_2 = new QHBoxLayout();
    layout_2->addSpacerItem(item_2);
    layout_2->addWidget(m_pLeftCount);

    // left layout
    QVBoxLayout* layout_3 = new QVBoxLayout();
    layout_3->addLayout(layout_1);
    layout_3->addWidget(m_pLeftList);
    layout_3->addLayout(layout_2);

    // center
    QSpacerItem* item_3 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_pMoveAllRight = createButton(">>");
    m_pMoveRight = createButton(">");
    m_pMoveLeft = createButton("<");
    m_pMoveAllLeft = createButton("<<");
    QSpacerItem* item_4 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QVBoxLayout* layout_4 = new QVBoxLayout();
    layout_4->addSpacerItem(item_3);
    layout_4->addWidget(m_pMoveAllRight);
    layout_4->addWidget(m_pMoveRight);
    layout_4->addWidget(m_pMoveLeft);
    layout_4->addWidget(m_pMoveAllLeft);
    layout_4->addSpacerItem(item_4);

    // right title
    m_pRightTitle = createColumnTitle("<h3>Selected</h3>");
    QSpacerItem* item_5 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_pMoveUp = createButton("^");
    m_pMoveDown = createButton("v");
    QHBoxLayout* layout_5 = new QHBoxLayout();
    layout_5->addWidget(m_pRightTitle);
    layout_5->addSpacerItem(item_5);
    layout_5->addWidget(m_pMoveUp);
    layout_5->addWidget(m_pMoveDown);

    // right list
    m_pRightList = createList();

    // right count
    m_pRightCount = new QLabel(this);
    m_pRightCount->setText("");
    QSpacerItem* item_6 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QHBoxLayout* layout_6 = new QHBoxLayout();
    layout_6->addSpacerItem(item_6);
    layout_6->addWidget(m_pRightCount);

    // right layout
    QVBoxLayout* layout_7 = new QVBoxLayout();
    layout_7->addLayout(layout_5);
    layout_7->addWidget(m_pRightList);
    layout_7->addLayout(layout_6);

    QHBoxLayout* layout_8 = new QHBoxLayout();
    layout_8->addLayout(layout_3);
    layout_8->addLayout(layout_4);
    layout_8->addLayout(layout_7);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(8);
    layout->addWidget(m_pTitle);
    layout->addLayout(layout_8);
    this->setLayout(layout);

    enableMoveLeft(false);
    enableMoveRight(false);
    enableMoveUp(false);
    enableMoveDown(false);
}

void Transfer::initializeEvents()
{
    connect(m_pLeftList, &QListWidget::itemSelectionChanged, this, &Transfer::onLeftListItemSelectionChanged);
    connect(m_pRightList, &QListWidget::itemSelectionChanged, this, &Transfer::onRightListItemSelectionChanged);
    connect(m_pLeftList, &QListWidget::itemDoubleClicked, this, &Transfer::onLeftListItemDoubleClicked);
    connect(m_pRightList, &QListWidget::itemDoubleClicked, this, &Transfer::onRightListItemDoubleClicked);
    connect(m_pMoveRight, &QPushButton::clicked, this, &Transfer::onMoveRightClicked);
    connect(m_pMoveLeft, &QPushButton::clicked, this, &Transfer::onMoveLeftClicked);
    connect(m_pMoveAllRight, &QPushButton::clicked, this, &Transfer::onMoveAllRightClicked);
    connect(m_pMoveAllLeft, &QPushButton::clicked, this, &Transfer::onMoveAllLeftClicked);
    connect(m_pMoveUp, &QPushButton::clicked, this, &Transfer::onMoveUpClicked);
    connect(m_pMoveDown, &QPushButton::clicked, this, &Transfer::onMoveDownClicked);
}

void Transfer::loadListItems(QListWidget *pList, const QList<QString> &items)
{
    if (nullptr == pList)
        return;
    for (const QString& item : items)
    {
        QListWidgetItem* pItem = new QListWidgetItem(pList);
        pItem->setText(item);
        pList->addItem(pItem);
    }
}

void Transfer::onMoveRightClicked(bool checked)
{
    moveRight();
}

void Transfer::onMoveLeftClicked(bool checked)
{
    moveLeft();
}

void Transfer::onMoveAllRightClicked(bool checked)
{
    m_pLeftList->selectAll();
    moveRight();
}

void Transfer::onMoveAllLeftClicked(bool checked)
{
    m_pRightList->selectAll();
    moveLeft();
}

void Transfer::onMoveUpClicked(bool checked)
{
    QList<QListWidgetItem*> selected = m_pRightList->selectedItems();
    for (QListWidgetItem* pItem : selected)
    {
        int i = m_pRightList->row(pItem);
        swapListItems(m_pRightList, i, i - 1);
    }
}

void Transfer::onMoveDownClicked(bool checked)
{
    QList<QListWidgetItem*> selected = m_pRightList->selectedItems();
    for (int index = selected.size() - 1; index >= 0; --index)
    {
        int i = m_pRightList->row(selected[index]);
        swapListItems(m_pRightList, i, i + 1);
    }
}

void Transfer::onLeftListItemSelectionChanged()
{
    QList<QListWidgetItem*> selected = m_pLeftList->selectedItems();
    enableMoveRight(selected.size());
    updateLeftCount();
}

void Transfer::onRightListItemSelectionChanged()
{
    QList<QListWidgetItem*> selected = m_pRightList->selectedItems();
    int selectedCount = selected.size();
    enableMoveLeft(selectedCount);

    if (0 == selectedCount)
    {
        enableMoveUp(false);
        enableMoveDown(false);
    }
    else
    {
        std::vector<int> rows;
        for (int i = 0; i < selected.size(); ++i)
        {
            QListWidgetItem* pItem = selected[i];
            int rowIndex = m_pRightList->row(pItem);
            rows.push_back(rowIndex);
        }
        std::sort(rows.begin(), rows.end());
        enableMoveUp(0 != rows[0]);
        enableMoveDown(rows[rows.size() - 1] != m_pRightList->count() - 1);
    }

    updateRightCount();
}

void Transfer::onLeftListItemDoubleClicked(QListWidgetItem *pItem)
{
    moveRight();
}

void Transfer::onRightListItemDoubleClicked(QListWidgetItem *pItem)
{
    moveLeft();
}

void Transfer::moveRight()
{
    moveSelected(m_pLeftList, m_pRightList);
}

void Transfer::moveLeft()
{
    moveSelected(m_pRightList, m_pLeftList);
}

void Transfer::moveSelected(QListWidget *pFrom, QListWidget *pTo)
{
    QStringList selectedItems;
    QList<QListWidgetItem*> selected = pFrom->selectedItems();
    for (int i = 0; i < selected.size(); ++i)
    {
        selectedItems.push_back(selected[i]->text());
    }
    for (int i = selected.size() - 1; i >= 0; --i)
    {
        QListWidgetItem* pCurrent = selected[i];
        pFrom->removeItemWidget(pCurrent);
        delete pCurrent;
    }
    for (int i = 0; i < selectedItems.size(); ++i)
    {
        pTo->addItem(selectedItems[i]);
    }
    enableMoveAllRight(m_pLeftList->count());
    enableMoveAllLeft(m_pRightList->count());
    updateLeftCount();
    updateRightCount();
}

void Transfer::updateLeftCount()
{
    int leftTotal = m_pLeftList->count();
    QList<QListWidgetItem*> leftSelected = m_pLeftList->selectedItems();
    updateCount(m_pLeftCount, leftSelected.size(), leftTotal);
}

void Transfer::updateRightCount()
{
    int rightTotal = m_pRightList->count();
    QList<QListWidgetItem*> rightSelected = m_pRightList->selectedItems();
    updateCount(m_pRightCount, rightSelected.size(), rightTotal);
}

void Transfer::updateCount(QLabel *pLabel, int selected, int total)
{
    QStringList sl;
    sl.push_back(QString::number(selected));
    sl.push_back(QString::number(total));
    QString content = sl.join("/");
    pLabel->setText(content);
}

void Transfer::enableMoveRight(bool enabled)
{
    QList<QWidget*> widgets = {m_pMoveRight};
    enableWidgets(widgets, enabled);
}

void Transfer::enableMoveLeft(bool enabled)
{
    QList<QWidget*> widgets = {m_pMoveLeft};
    enableWidgets(widgets, enabled);
}

void Transfer::enableMoveAllRight(bool enabled)
{
    QList<QWidget*> widgets = {m_pMoveAllRight};
    enableWidgets(widgets, enabled);
}

void Transfer::enableMoveAllLeft(bool enabled)
{
    QList<QWidget*> widgets = {m_pMoveAllLeft};
    enableWidgets(widgets, enabled);
}

void Transfer::enableMoveUp(bool enabled)
{
    QList<QWidget*> widgets = {m_pMoveUp};
    enableWidgets(widgets, enabled);
}

void Transfer::enableMoveDown(bool enabled)
{
    QList<QWidget*> widgets = {m_pMoveDown};
    enableWidgets(widgets, enabled);
}

void Transfer::enableWidgets(QList<QWidget *> &widgets, bool enabled)
{
    for (QWidget* pWidget : widgets)
    {
        if (pWidget)
        {
            pWidget->setDisabled(!enabled);
        }
    }
}

QPushButton *Transfer::createButton(const QString &text)
{
    QPushButton* pButton = new QPushButton(this);
    pButton->setText(text);
    QSize btnSize(20, 20);
    pButton->resize(btnSize);
    pButton->setMinimumSize(btnSize);
    pButton->setMaximumSize(btnSize);
    return pButton;
}

QListWidget *Transfer::createList()
{
    QListWidget* pList = new QListWidget(this);
    pList->setMinimumSize(QSize(120, 240));
    pList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    return pList;
}

QLabel *Transfer::createColumnTitle(const QString &title)
{
    QLabel* pTitle = new QLabel(this);
    pTitle->setText(title);
    pTitle->setMinimumHeight(24);
    return pTitle;
}

QList<QString> Transfer::getListItems(QListWidget *pList) const
{
    QList<QString> items;
    int count = pList->count();
    for (int i = 0; i < count; ++i)
    {
        QListWidgetItem* pItem = pList->item(i);
        items.push_back(pItem->text());
    }
    return items;
}

void Transfer::swapListItems(QListWidget *pList, int i, int j)
{
    QListWidgetItem* pFirst = pList->item(i);
    QListWidgetItem* pSecond = pList->item(j);

    QString tempText = pFirst->text();
    pFirst->setText(pSecond->text());
    pSecond->setText(tempText);

    bool selection = pFirst->isSelected();
    pFirst->setSelected(pSecond->isSelected());
    pSecond->setSelected(selection);
}

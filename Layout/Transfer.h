#ifndef TRANSFER_H
#define TRANSFER_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QList>
#include <QString>
#include <QList>

class Transfer : public QWidget
{
    Q_OBJECT
public:
    explicit Transfer(QWidget *parent = nullptr);
    void loadData(const QList<QString>& candidates, const QList<QString>& selected);
    void setTitle(const QString& title);
    void setLeftTitle(const QString& title);
    void setRightTitle(const QString& title);

    QList<QString> getCandidates() const;
    QList<QString> getSelected() const;

signals:

private:

    void initializeTransfer();
    void initializeEvents();
    void loadListItems(QListWidget* pList, const QList<QString>& items);

private slots:

    void onMoveRightClicked(bool checked = false);
    void onMoveLeftClicked(bool checked = false);
    void onMoveAllRightClicked(bool checked = false);
    void onMoveAllLeftClicked(bool checked = false);
    void onMoveUpClicked(bool checked = false);
    void onMoveDownClicked(bool checked = false);
    void onLeftListItemSelectionChanged();
    void onRightListItemSelectionChanged();
    void onLeftListItemDoubleClicked(QListWidgetItem* pItem);
    void onRightListItemDoubleClicked(QListWidgetItem* pItem);

private:

    void moveRight();
    void moveLeft();
    void moveSelected(QListWidget* pFrom, QListWidget* pTo);
    void updateLeftCount();
    void updateRightCount();
    void updateCount(QLabel* pLabel, int selected, int total);

private:

    void enableMoveRight(bool enabled);
    void enableMoveLeft(bool enabled);
    void enableMoveAllRight(bool enabled);
    void enableMoveAllLeft(bool enabled);
    void enableMoveUp(bool enabled);
    void enableMoveDown(bool enabled);
    void enableWidgets(QList<QWidget*>& widgets, bool enabled);

private:

    QPushButton* createButton(const QString& text);
    QListWidget *createList();
    QLabel* createColumnTitle(const QString& title);
    QList<QString> getListItems(QListWidget* pList) const;
    void swapListItems(QListWidget* pList, int i, int j);

private:
    QLabel*         m_pTitle;
    QLabel*         m_pLeftTitle;
    QLabel*         m_pRightTitle;
    QListWidget*    m_pLeftList;
    QListWidget*    m_pRightList;
    QPushButton*    m_pMoveRight;
    QPushButton*    m_pMoveLeft;
    QPushButton*    m_pMoveAllRight;
    QPushButton*    m_pMoveAllLeft;
    QPushButton*    m_pMoveUp;
    QPushButton*    m_pMoveDown;
    QLabel*         m_pLeftCount;
    QLabel*         m_pRightCount;
};

#endif // TRANSFER_H

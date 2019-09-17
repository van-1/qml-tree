#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>

class TreeModelItem: public QObject
{
  Q_OBJECT
  public:
    explicit TreeModelItem(const QString& content, QObject* parent = nullptr);
    ~TreeModelItem() = default;

    Q_PROPERTY(QString content READ content NOTIFY contentChanged)
    Q_PROPERTY(bool hasChild READ hasChild NOTIFY hasChildChanged)
    Q_PROPERTY(QList<QObject*> childItems READ childItems NOTIFY childItemsChanged)
    Q_PROPERTY(bool open READ open WRITE setOpen NOTIFY openChanged)

    bool hasChild() const;
    bool open() const;
    const QList<QObject*> childItems() const;
    QString content() const;

    void setContent(const QString& content);
    void addChildItem(TreeModelItem* childItem);
    void setOpen(bool open);

  signals:
    void contentChanged();
    void childItemsChanged();
    void openChanged();
    void hasChildChanged();

  private:
    QString m_content;
    bool m_isOpen;
};

class TreeModel : public QObject
{
  Q_OBJECT
  public:

    Q_PROPERTY(QList<QObject*> tree READ tree NOTIFY treeChanged)

    explicit TreeModel(QObject* parent = nullptr);
    ~TreeModel() = default;
    void addItem(TreeModelItem* item);

  private:
    const QList<QObject*> tree() const;

  signals:
    void treeChanged();
};

#endif // TREEMODEL_H

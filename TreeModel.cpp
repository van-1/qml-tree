#include "TreeModel.h"

TreeModel::TreeModel(QObject* parent)
  : QObject(parent)
{}


void TreeModel::addItem(TreeModelItem* item)
{
  item->setParent(this);
}


const QList<QObject*> TreeModel::tree() const
{
  return children();
}


QString TreeModelItem::content() const
{
  return m_content;
}


void TreeModelItem::setContent(const QString& content)
{
  if (content != m_content)
  {
    m_content = content;
    emit contentChanged();
  }
}


void TreeModelItem::addChildItem(TreeModelItem* childItem)
{
  childItem->setParent(this);
  emit childItemsChanged();
  if (children().size() == 1)
    emit hasChildChanged();
}


void TreeModelItem::setOpen(bool open)
{
  if (open != m_isOpen)
  {
    m_isOpen = open;
    emit openChanged();
  }
}


TreeModelItem::TreeModelItem(const QString& content, QObject* parent)
  : QObject(parent)
  , m_content(content)
  , m_isOpen(false)
{}


bool TreeModelItem::hasChild() const
{
  return !children().isEmpty();
}


bool TreeModelItem::open() const
{
  return m_isOpen;
}


const QList<QObject*> TreeModelItem::childItems() const
{
  return children();
}

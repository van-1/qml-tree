// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVariant>

// Local
#include "TreeModel.h"


int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  TreeModel* model = new TreeModel();

  for (auto i = 0; i < 10; ++i)
  {
    if (i % 2 == 0)
    {
      TreeModelItem* parent = new TreeModelItem("parent_" + QString::number(i));
      TreeModelItem* child = new TreeModelItem("child_" + QString::number(i));
      TreeModelItem* subChild = new TreeModelItem("subChild_" + QString::number(i));
      child->addChildItem(subChild);
      parent->addChildItem(child);
      model->addItem(parent);
    }
  }

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("treeModel", model);
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}

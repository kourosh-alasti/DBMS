#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTextEdit>

#include "db/db.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QMainWindow window;
  QWidget *centralWidget = new QWidget;
  QVBoxLayout *layout = new QVBoxLayout; 

  QLineEdit *queryInput = new QLineEdit;
  queryInput->setPlaceholderText("Enter SQL Query...");

  QPushButton *executeButton = new QPushButton("Execute Query");
  QTextEdit *output = new QTextEdit;

  layout->addWidget(queryInput);
  layout->addWidget(executeButton);
  layout->addWidget(output);

  centralWidget->setLayout(layout);
  window.setCentralWidget(centralWidget);
  window.resize(600, 400);
  window.show();

  QObject::connect(executeButton, &QPushButton::clicked, [&]() {
      executeQuery(output, queryInput->text());
  });

  return app.exec();
}

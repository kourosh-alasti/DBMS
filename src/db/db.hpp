#include <libpq-fe.h>
#include <QTextEdit>
#include <QString>

// void checkConnStatus(PGConn *conn);
void executeQuery(QTextEdit *output, const QString &query);
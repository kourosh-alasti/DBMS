#include <iostream>

#include "db.hpp"

// void check_conn_status(PGConn *conn) {
//   if(PQStatus(conn) != CONNECTION_OK) {
//     std::cerr << "Connection to Database failed: " << PQerrorMessage(conn) << std:: endl;
//     PQfinish(conn);
//     exit(1);
//   }
// }

void executeQuery(QTextEdit *output, const QString &query) {
  // Read connection info from environment variables
  const char* dbname = std::getenv("DB_NAME");
  const char* user = std::getenv("DB_USER");
  const char* password = std::getenv("DB_PASSWORD");
  const char* hostaddr = std::getenv("DB_HOST");
  const char* port = std::getenv("DB_PORT");

  // Construct connection string
  std::string conninfo = "dbname=" + std::string(dbname ? dbname : "") +
                         " user=" + std::string(user ? user : "") +
                         " password=" + std::string(password ? password : "") +
                         " hostaddr=" + std::string(hostaddr ? hostaddr : "") +
                         " port=" + std::string(port ? port : "");

  PGconn *conn = PQconnectdb(conninfo.c_str());

  if(PQstatus(conn) != CONNECTION_OK) {
    output->append("Connection Failed: " + QString(PQerrorMessage(conn)));
    PQfinish(conn);
    return;
  }

  PGresult *res = PQexec(conn, query.toStdString().c_str());
  if(PQresultStatus(res) != PGRES_TUPLES_OK) {
    output->append("Query Failed: " + QString(PQerrorMessage(conn)));
    PQclear(res);
    PQfinish(conn);
    return;
  }
  
  int nFields = PQnfields(res);
  std::cout << nFields << std::endl;
  for(int i = 0; i < PQntuples(res); i++ ) {
    QString row;
    for(int j = 0; j < nFields; j++) {
      row += PQgetvalue(res, i, j);
      row += " ";
    }
    output->append(row);
  }

  PQclear(res);
  PQfinish(conn);
}
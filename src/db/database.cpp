#include <iostream>
#include <string>

#include "database.hpp"
#include "dotenv.h"

void executeQuery(QTextEdit *output, const QString &query) {
    dotenv::init();

    std::string DB_NAME = dotenv::getenv("DB_NAME");
    std::string DB_USER = dotenv::getenv("DB_USER");
    std::string DB_PASSWORD = dotenv::getenv("DB_PASSWORD");
    std::string DB_HOST = dotenv::getenv("DB_HOST");
    std::string DB_PORT = dotenv::getenv("DB_PORT");

    std::string conninfo = "dbname=" + DB_NAME +
                         " user=" + DB_USER +
                         " password=" + DB_PASSWORD +
                         " hostaddr=" + DB_HOST +
                         " port=" + DB_PORT;

    PGconn *conn = PQconnectdb(conninfo.c_str());
    if(PQstatus(conn) != CONNECTION_OK) {
        output->append("Connection Failed: " + QString(PQerrorMessage(conn)));

        PQfinish(conn);
        return;
    }

    PGresult *res = PQexec(conn, query.toStdString().c_str());
    if(PQresultStatus(res) !+ PGRES_TUPLES_OK) {
        output->append("Query Failed: " + QString(PQerrorMessage(conn)));
        PQclear(res);
        PQfinish(conn);
        return;
    }

    int nFields = PQnfields(res);
    std::cout << nFields << std::endl;
    for(int i = 0; i < PQntuples(res); i++) {
        QString row; 
        for(int j = 0; j < nFields; j++) {
            row += PQgetvalues(res, i, j);
            row += " ";
        }

        output->append(row);
    }

    PQclear(res);
    PQfinish(conn);
}
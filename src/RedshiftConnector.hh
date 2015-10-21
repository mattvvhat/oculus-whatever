#pragma once

#include <string>
#include <vector>
#include <libpq-fe.h>

#define GET_TABLES_QUERY "SELECT DISTINCT(tablename) FROM pg_table_def WHERE schemaname = 'public';"

class RedshiftConnector {
private:
  bool mIsConnected;
  std::string mConnectString;

  PGconn   *mConn;
  PGresult *mRes;

public:
  RedshiftConnector(std::string host,
                    std::string port,
                    std::string dbname,
                    std::string user,
                    std::string pass):mIsConnected(false) {
    mConnectString = "";
    mConnectString += "host=" + host;
    mConnectString += " port=" + port;
    mConnectString += " dbname=" + dbname;
    mConnectString += " user=" + user;
    mConnectString += " password =" + pass;
    mConnectString += " connect_timeout=5000";
  }

  void Connect() {
    mConn = PQconnectdb(mConnectString.c_str());
    mIsConnected = (PQstatus(mConn) == CONNECTION_OK);
    if (!mIsConnected) {
      ExitNicely();
    }
  }

  void Disconnect() {
    ExitNicely();
  }

  void ExitNicely() {
    PQfinish(mConn);
    mIsConnected = false;
  }

  void Clear() {
    PQclear(mRes);
  }

  std::vector<std::string> GetTables() {
    std::vector<std::string> table_list;
    int result_status;

    mRes = PQexec(mConn, GET_TABLES_QUERY);
    result_status = PQresultStatus(mRes);

    if (result_status == PGRES_TUPLES_OK) {
      int n_rows = PQntuples(mRes);
      std::cout << n_rows << "!!!\n";
      for (int i=0; i < n_rows; i++) {
        table_list.push_back(PQgetvalue(mRes, i, 0));
      }
    } else {
      Clear();
    }
  }

    std::vector<Building> GetLayout(int callback) {
      // Get list of tables
      std::vector<std::string> tables = GetTables();

      // Sort tables according to scoring algorithm
      // ...

      // Shuffle tables
      // ...

      // Iterate through each
      for (auto it=tables.begin(); it != tables.end(); ++it) {
        // callback(GetBuilding(*it));
        GetBuilding(*it);
      }
    }

    std::vector<Building> GetLayout() {
      // Get list of tables
      std::vector<std::string> tables = GetTables();

      // Sort tables according to scoring algorithm
      // ...

      // Shuffle tables
      // ...

      // Iterate through each
      for (auto it=tables.begin(); it != tables.end(); ++it) {
        GetBuilding(*it);
      }
    }

    int SqlExecInteger(std::string query, int fail=-1) {
      PGresult mRes = PQexec(mConn, query.c_str());
      int result_status = PQresultStatus(mRes);
      int result = fail;
      if (result_status == PGRES_TUPLES_OK) {
        result = PQgetvalue(mRes, 0, 0);
        Clear();
      }
      return result;
    }

#define BUILDING_BASE_QUERY "SELECT * FROM %s LIMIT 1;"
#define BUILDING_HEIGHT_QUERY "SELECT COUNT(*) FROM %s LIMIT 1;"
    Building GetBuilding(const std::string table_name) {
      Building b;
      b.base_width = b.base_height = SqlExecInteger(BUILDING_BASE_QUERY);
      b.height = SqlExecInteger(BUILDING_HEIGHT_QUERY);
      return b;
    }
};

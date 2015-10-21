#pragma once

#include <string>
#include <iterator>

#include "Building.hh"
#include "RedshiftConnector.hh"

#include <string>

class RedshiftCityLayoutBuilder {
protected:
  std::string mHost;
  std::string mPort;
  std::string mDbName;
  std::string mUser;
  std::string mPassword;

  RedshiftConnector *mConnector;

public:

  // Constructor
  RedshiftCityLayoutBuilder():mHost(""),
                              mPort(""),
                              mDbName(""),
                              mUser(""),
                              mPassword("") {
  }

  // Destructor
  ~RedshiftCityLayoutBuilder() {
    if (mConnector) {
      mConnector->Disconnect();
      delete mConnector;
    }
  }

  // Configure
  void Configure(const std::string key, const std::string val) {
      if (key == "host") {
          mHost = val;
      } else if (key == "port") {
          mPort = val;
      } else if (key == "dbname") {
          mDbName = val;
      } else if (key == "user") {
          mUser = val;
      } else if (key == "pass") {
          mPassword = val;
      }
  }

  void BuildCity() {
//    mConnector = new RedshiftConnector(
//        std::string host,
//        std::string port,
//        std::string dbname,
//        std::string user,
//        std::string pass);
//
//    mConnector->GetTables();
  }
};

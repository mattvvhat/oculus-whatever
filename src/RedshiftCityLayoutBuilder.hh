#pragma once

#include <string>
#include <iterator>

#include "Building.hh"

class RedshiftCityLayoutBuilder:public CityLayoutBuilder  {
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
    switch(key) {
      case "host":
        mHost = val;
        break;
      case "port":
        mPort = val;
        break;
      case "dbname":
        mDbName = val;
        break;
      case "user":
        mUser = val;
        break;
      case "pass":
        mPassword = val;
        break;
      default:
        // Do nothing
    }
  }

  void BuildCity() {
    mConnector = new RedshiftConnector(
        std::string host,
        std::string port,
        std::string dbname,
        std::string user,
        std::string pass);

    mConnector->GetTables();
  }

  virtual void ClearCity() = 0;
  virtual BuildingIterator GetBuildings() = 0;
};

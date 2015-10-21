/**
 * :D
 */

#include <stdlib.h>
#include <iostream>
#include <libpq-fe.h>
#include <string>
#include <vector>

#include "RedshiftCityLayoutBuilder.hh"

/**
 * Main
 */
int main(int argc, char **argv) {
  std::vector<std::string> table_list;
  RedshiftConnector connector(
    );

  RedshiftCityLayoutBuilder city_builder;

  city_builder.Configure("host", "host");
  city_builder.Configure("port", "port");
  city_builder.Configure("dname", "dbname");
  city_builder.Configure("user", "user")
  city_builder.Configure("pass", "pass");

  connector.Connect();

  table_list = connector.GetTables();

  for (auto it=table_list.begin(); it != table_list.end(); ++it) {
    std::cout << *it << "\n";
  }


//std::cout << "Fin.";

  return 0;
}

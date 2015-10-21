#pragma once

#include <string>
#include <iterator>

#include "Building.hh"

class CityBuilderInterface {
public:
  virtual void Configure(const std::string key, const std::string val) = 0;
  virtual void BuildCity() = 0;
  virtual void ClearCity() = 0;
  virtual BuildingIterator GetBuildings() = 0;
};

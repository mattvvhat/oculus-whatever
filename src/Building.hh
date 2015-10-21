#pragma once

#include <iterator>

struct Building {
  int base_width;
  int base_height;
  int height;
};

class BuildingIterator : public std::iterator<std::input_iterator_tag, Building> {
private:
  Building* p;

public:
  BuildingIterator(Building* x) : p(x) {
  }

  BuildingIterator(const BuildingIterator& mit) : p(mit.p) {
  }

  BuildingIterator& operator++() {
    ++p;
    return *this;
  }

  BuildingIterator operator++(int) {
    BuildingIterator tmp(*this);
    operator++();
    return tmp;
  }

  bool operator==(const BuildingIterator& rhs) {
    return p==rhs.p;
  }

  bool operator!=(const BuildingIterator& rhs) {
    return p!=rhs.p;
  }

  Building& operator*() {
    return *p;
  }
};

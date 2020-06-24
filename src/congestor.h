#ifndef CONGESTOR_H
#define CONGESTOR_H

#include <stdint.h>
#include <iostream>

class congestor {
  private:
    uint64_t counter;
    uint64_t random_number;
    uint64_t rand_max;
    bool congest;

  public:
    congestor();
    congestor(uint64_t rand_max);
    ~congestor();
    bool get_and_update();
    void set(uint64_t rand_max);
};
#endif

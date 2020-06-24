#ifndef FUZZER_H
#define FUZZER_H

#include <vector>
#include <cstdlib>
#include "congestor.h"
#include <iostream>
#include <cassert>

class fuzzer {
  private:
    std::vector<congestor*> congestors;
    uint64_t num_congestors;
    uint64_t num_table_mutators;
    uint64_t rand_max_range;

  public:
    fuzzer();
    ~fuzzer();
    void init_fuzzers(uint64_t seed, uint64_t num_congestors, uint64_t rand_max_range);
    void set_seed(uint64_t seed);
    congestor* get_congestor(uint64_t congestor_id);
};
#endif

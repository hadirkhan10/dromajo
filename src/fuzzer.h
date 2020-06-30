#ifndef FUZZER_H
#define FUZZER_H

#include <vector>
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <cassert>
#include "congestor.h"
#include "table_mutator.h"

class fuzzer {
  private:
    std::vector<congestor*> congestors;
    std::vector<table_mutator*> table_mutators;
    uint64_t num_congestors;
    uint64_t num_table_mutators;
    uint64_t rand_max_range;

  public:
    fuzzer();
    ~fuzzer();
    void init_fuzzers(uint64_t seed, uint64_t num_congestors,
                      uint64_t num_table_mutators,
                      uint64_t rand_max_range);
    void set_seed(uint64_t seed);
    congestor* get_congestor(uint64_t congestor_id);
    table_mutator* get_table_mutator(uint64_t table_mutator_id);
    void mutate_tables();
    void update_table_triggers();
    void dump_table_utilizations();
};
#endif

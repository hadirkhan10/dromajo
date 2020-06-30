#ifndef TABLE_MUTATOR_H
#define TABLE_MUTATOR_H

#include <vector>
#include <cassert>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>

class table_mutator {
  private:
    uint64_t table_mutator_id;
    uint64_t width;
    uint64_t depth;
    uint64_t init_value;
    uint64_t last_read;
    uint64_t counter;
    uint64_t rand_max;
    std::vector<uint64_t> table;
    std::vector<uint64_t> utilization_table;
    
  public:
    table_mutator();
    table_mutator(uint64_t table_mutator_id, uint64_t rand_max);
    ~table_mutator();
    uint64_t emu_ariane_mem_acc(uint64_t addr_di, uint64_t ben_si, 
                                uint64_t wrdata_di, bool wren_si,
                                bool reset_n, bool csel_si);
    void init_table(uint64_t depth, uint64_t init_value);
    void mutate_table();
    void update_trigger();
    void dump_utilization();
};

#endif

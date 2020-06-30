#include "table_mutator.h"

table_mutator::table_mutator() {
  this->table_mutator_id = 0;
  this->width = 0;
  this->depth = 0;
  this->init_value = 0;
  this->last_read = 0;
  this->rand_max = 0;
}

table_mutator::table_mutator(uint64_t table_mutator_id, uint64_t rand_max) {
  this->table_mutator_id = table_mutator_id;
  this->width = 0;
  this->depth = 0;
  this->init_value = 0;
  this->last_read = 0;
  this->rand_max = rand_max+7;
}

table_mutator::~table_mutator() {
}

void table_mutator::init_table(uint64_t depth, uint64_t init_value) {
  this->depth = depth;
  this->init_value = init_value;
  for (uint32_t i=0; i<depth; i++) {
    this->table.push_back(init_value);
    this->utilization_table.push_back(0);
  }
}

uint64_t table_mutator::emu_ariane_mem_acc(uint64_t addr_di, uint64_t ben_si, 
                                           uint64_t wrdata_di, bool wren_si,
                                           bool reset_n, bool csel_si) {
  assert(addr_di < this->depth);

  if (!reset_n) {
    for (uint32_t i=0; i<this->depth; i++) {
      table[i] = this->init_value;
    }
  }

  uint64_t data_to_write = 0;
  if (csel_si) {
    if (wren_si) {
      for (uint32_t i=0; i<8; i++) {
        if ((ben_si >> i) & 1) {
          data_to_write |= wrdata_di & (0xff << (i*8));
        }
      }

      //std::cout << "In table mutator, writing " << data_to_write << std::endl;
      this->table[addr_di] = data_to_write;
      this->utilization_table[addr_di]++;
      this->last_read = 0;
    } else {
      this->last_read = this->table[addr_di];
    }
  }

  //std::cout << "Emu mem access(" << this->table_mutator_id << "). Addr = " << std::hex << addr_di << "; read value = " << this->last_read;
  //std::cout << "; we = " << wren_si << "; write value = " << data_to_write << std::endl;
  //std::cout << "In table mutator, reading: " << this->last_read << std::endl;
  return this->last_read;
}

void table_mutator::mutate_table() {
  //std::cout << "Mutating table " << this->table_mutator_id << std::endl;
  for (uint32_t i=0; i<this->depth; i++) {
    this->table[i] = (uint64_t)std::rand();

    // invalidation mechanisms
    if (this->table_mutator_id < 4) {
      this->table[i] = this->table[i]&(~((uint64_t)1<<44));
    } else {
      this->table[i] = this->table[i]|((uint64_t)1<<44);
    }
  }
}

void table_mutator::update_trigger() {
  if (this->counter <= 0) {
    this->mutate_table();
    this->counter = (std::rand()%this->rand_max)*444;
  } else {
    this->counter--;
  }
}

void table_mutator::dump_utilization() {
  std::cout << "Table " << this->table_mutator_id << " ";
  for (uint32_t i=0; i<this->depth; i++) {
    std::cout << this->utilization_table[i] << " ";
  }
  std::cout << ";" << std::endl;
}

#include "fuzzer.h"

fuzzer::fuzzer() {
  std::srand(1);
  this->num_congestors = 0;
  this->num_table_mutators = 0;
  this->rand_max_range = 0;
}

fuzzer::~fuzzer() {
  for (uint32_t i=0; i<num_congestors; i++) {
    delete this->congestors.back();
    this->congestors.pop_back();
  }

  for (uint32_t i=0; i<num_table_mutators; i++) {
    delete this->table_mutators.back();
    this->table_mutators.pop_back();
  }
}

void fuzzer::init_fuzzers(uint64_t seed, uint64_t num_congestors,
                          uint64_t num_table_mutators,
                          uint64_t rand_max_range) {
  std::srand(seed);
  this->num_congestors = num_congestors;
  this->num_table_mutators = num_table_mutators;
  this->rand_max_range = rand_max_range;

  for (uint32_t i=0; i<num_congestors; i++) {
    congestor* new_congestor;
    new_congestor = new congestor((std::rand()%rand_max_range) + 1);
    this->congestors.push_back(new_congestor);
  }

  for (uint32_t i=0; i<num_table_mutators; i++) {
    table_mutator* new_table_mutator;
    new_table_mutator = new table_mutator(i, (std::rand()%rand_max_range) + 1);
    this->table_mutators.push_back(new_table_mutator);
  }
}

void fuzzer::set_seed(uint64_t seed) {
  std::srand(seed);
}

congestor* fuzzer::get_congestor(uint64_t congestor_id) {
  assert(congestor_id < this->num_congestors);
  return this->congestors[congestor_id];
}

table_mutator* fuzzer::get_table_mutator(uint64_t table_mutator_id) {
  assert(table_mutator_id < this->num_table_mutators);
  return this->table_mutators[table_mutator_id];
}

void fuzzer::mutate_tables() {
  for (uint32_t i=0; i<num_table_mutators; i++) {
    this->table_mutators[i]->mutate_table();
  }
}

void fuzzer::update_table_triggers() {
  for (uint32_t i=0; i<num_table_mutators; i++) {
    this->table_mutators[i]->update_trigger();
  }
}

void fuzzer::dump_table_utilizations() {
  for (uint32_t i=0; i<num_table_mutators; i++) {
    this->table_mutators[i]->dump_utilization();
  }
}

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
}

void fuzzer::init_fuzzers(uint64_t seed, uint64_t num_congestors,
                          uint64_t rand_max_range) {
  std::srand(seed);
  this->num_congestors = num_congestors;
  this->rand_max_range = rand_max_range;
  for (uint32_t i=0; i<num_congestors; i++) {
    congestor* new_congestor;
    new_congestor = new congestor((std::rand()%rand_max_range) + 1);
    congestors.push_back(new_congestor);
  }
  #ifdef DEBUG
  std::cout << "seed: " << seed << std::endl;
  std::cout << "num cong: " << num_congestors << std::endl;
  std::cout << "range: " << rand_max_range << std::endl;
  #endif
}

void fuzzer::set_seed(uint64_t seed) {
  std::srand(seed);
}

congestor* fuzzer::get_congestor(uint64_t congestor_id) {
  assert(congestor_id < this->num_congestors);
  return this->congestors[congestor_id];
}

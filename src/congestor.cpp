#include "congestor.h" 

congestor::congestor() {
  this->counter       = 0;
  this->congest       = false;
}

congestor::congestor(uint64_t rand_max) {
  this->counter       = 0;
  this->congest       = false;
  this->rand_max      = rand_max + 7;
}

congestor::~congestor() {

}

void congestor::set(uint64_t rand_max) {
  this->rand_max = rand_max;
}

bool congestor::get_and_update() {
  if (this->counter <= 0) {
    this->congest = !(this->congest);
    this->counter = (std::rand()%this->rand_max);
    if (!this->congest) {
      this->counter = this->counter * 11;
    }
  } else {
    this->counter--;
  }
  
  return congest;
}

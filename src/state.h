#ifndef __STATE_H__
#define __STATE_H__

#include <Arduino.h>

class StableState {
 public:
  StableState() : entries{-1, -1, -1}, current{-1} {}

  bool add(int entry) {
    memmove(this->entries, this->entries + 1, sizeof(this->entries));
    this->entries[2] = entry;

    if (this->entries[0] == this->entries[1] &&
        this->entries[1] == this->entries[2] &&
        this->current != this->entries[2]) {
      this->current = this->entries[2];
      return true;
    }
    return false;
  }

  int get() { return this->current; }

 private:
  int entries[3];
  int current;
};

#endif /* __STATE_H__ */

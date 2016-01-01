#include "utils.h"
#include <iostream>

Kmer::Kmer (string label, int occurrence) {
    this->occurrence = occurrence;
    this->label = label;
}


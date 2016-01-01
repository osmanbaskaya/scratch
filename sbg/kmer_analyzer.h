#ifndef __KMER_ANALYZER_H_INCLUDED__
#define __KMER_ANALYZER_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>
#include "utils.h"

class Compare
{
    public:
        bool operator() (Kmer left, Kmer right)
        {
            return left.occurrence > right.occurrence;
        }
};


class KmerAnalyzer {
    public:
        // methods
        KmerAnalyzer(const char*, const int);
        priority_queue<Kmer, std::vector<Kmer>, Compare> find_top_kmers(int);
        void print_top_kmers(int);
    private:
        // attributes
        const int kmer_size;
        const char * filename;
        unordered_map<string, int> occurrence_map;
        bool is_loaded;
        // methods
        void load_kmers();
        void extract_kmers_and_add(const string &);
};


#endif // __KMER_ANALYZER_H_INCLUDED__

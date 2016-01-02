#ifndef __KMER_ANALYZER_H__
#define __KMER_ANALYZER_H__

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
        void load_kmers();
        int get_unique_kmer_size();
        int get_total_kmer_size();
    private:
        // attributes
        const int kmer_size;
        const char * filename;
        int sequence_size;
        unordered_map<string, int> occurrence_map;
        bool is_loaded;
        // methods
        void extract_kmers_and_add(const string &, const string &);
        void clean_infrequent_kmers(int);
};


#endif // __KMER_ANALYZER_H__

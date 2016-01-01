#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;

class Kmer
{
    public:
        int occurrence;
        string label;
        Kmer (string, int);
};

Kmer::Kmer (string label, int occurrence) {
    this->occurrence = occurrence;
    this->label = label;
}

class Compare
{
    public:
        bool operator() (Kmer left, Kmer right)
        {
            return left.occurrence > right.occurrence;
        }
};


priority_queue<Kmer, std::vector<Kmer>, Compare> find_top_kmers(const unordered_map<string, int> & occurrence_map, const int num_top_kmers) {
    priority_queue<Kmer, std::vector<Kmer>, Compare> min_heap;
    for (const auto & element: occurrence_map) {
        if (min_heap.size() < num_top_kmers) {
            min_heap.push(Kmer(element.first, element.second));
        }
        else {
            if (min_heap.top().occurrence < element.second) {
                min_heap.pop();  // remove the minimum
                min_heap.push(Kmer(element.first, element.second));
            }
        }
    }

    return min_heap;

}

void print_top_kmers(priority_queue<Kmer, std::vector<Kmer>, Compare> min_heap) {
    // Assumption: min_heap will be relatively small. No problem to copy it.
    // We do not want to lose min_heap.
    while (!min_heap.empty()) {
        Kmer first = min_heap.top();
        cout << first.occurrence << "\t" << first.label << "\n";
        min_heap.pop();
    }
}

void extract_kmers_and_add(unordered_map<string, int> & occurrence_map, const string & sequence, const int kmer_size) {
    string kmer;
    int end = sequence.size() - kmer_size;
    for (int i=0; i < end; i++){
        kmer = sequence.substr(i, kmer_size);
        ++occurrence_map[kmer];
    }
}


void print_map(const unordered_map<string, int> & my_map) {
    for (const auto & element: my_map) {
        cout << element.first << "\t" << element.second << "\n";
    }
}

unordered_map<string, int> load_kmers(const char* filename, const int kmer_size) {
    unordered_map<string, int> occurrence_map;
    string line;
    ifstream myfile (filename);
    int line_number = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            line_number++;
            // read only the sequence rows.
            if (line_number % 4 == 2) {
                extract_kmers_and_add(occurrence_map, line, kmer_size);
            }
        }
        // print_map(occurrence_map);
        myfile.close();
    }
    else cerr << "Unable to open file"; 
    return occurrence_map;
}

void run(const char * filename, const int kmer_size, const int num_top_kmers) {
    const unordered_map<string, int> occurrence_map = load_kmers(filename, kmer_size);
    const priority_queue<Kmer, std::vector<Kmer>, Compare> min_heap = find_top_kmers(occurrence_map, num_top_kmers);
    print_top_kmers(min_heap);
}

int main ( int argc, char *argv[] ) {
    if (argc != 4) {
        cerr << "Usage:\nkmers.out FILENAME KMER_SIZE NUM_TOP_KMERS\n";
    }
    const char * filename = argv[1];
    const int kmer_size = atoi(argv[2]);
    const int num_top_kmers = atoi(argv[3]);

    run(filename, kmer_size, num_top_kmers);
    return 0;
}


// http://askubuntu.com/questions/61408/what-is-a-command-to-compile-and-run-c-programs
// https://codeconnect.wordpress.com/2013/09/0/max-min-heap-using-c-stl/
// http://stackoverflow.com/questions/1842941/translating-python-dictionary-to-c
// http://www.cprogramming.com/tutorial/lesson14.html

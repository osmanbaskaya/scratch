#include "kmer_analyzer.h"
#include <fstream>
#include <gtest/gtest.h>

using namespace std;

class KmerAnalyzerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
      ofstream myfile;
      myfile.open("test.txt");
      string seq = 
          "line1\n"
          "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATTTTTTTTTTTTTTTTTTTTTTTTTTTTTTGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n"
          "line3\n"
          "line4\n"
          "line5\n"
          "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATTTTTTTTTTTTTTTTTTTTTTTTTTTTTTGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG\n"
          "line7\n"
          "line8\n";
      myfile << seq;

  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
  }
};

TEST_F(KmerAnalyzerTest, load_test_file){
    KmerAnalyzer analyzer("test.txt", 90);
    analyzer.load_kmers();
    EXPECT_EQ(90, analyzer.get_unique_kmer_size());
    EXPECT_EQ(91, analyzer.get_total_kmer_size());
}

TEST_F(KmerAnalyzerTest, load_smallest_fastq){
    KmerAnalyzer analyzer("smallest.fastq", 4);
    analyzer.load_kmers();
    EXPECT_EQ(57, analyzer.get_unique_kmer_size());
    EXPECT_EQ(87, analyzer.get_total_kmer_size());
}

TEST_F(KmerAnalyzerTest, find_top_kmers_test){
    KmerAnalyzer analyzer("test.txt", 90);
    analyzer.load_kmers();
    Kmer top = analyzer.find_top_kmers(1).top();
    string correct_label = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATTTTTTTTTTTTTTTTTTTTTTTTTTTTTTGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG";
    EXPECT_EQ(correct_label, top.label);
}


TEST_F(KmerAnalyzerTest, find_top_kmers_smallest_fastq){
    KmerAnalyzer analyzer("smallest.fastq", 4);
    analyzer.load_kmers();
    priority_queue<Kmer, std::vector<Kmer>, Compare> min_heap = analyzer.find_top_kmers(2);

    Kmer kmer = min_heap.top(); // second biggest.
    EXPECT_EQ("ATTA", kmer.label);
    EXPECT_EQ(4, kmer.occurrence);

    min_heap.pop(); // remove second biggest.
    kmer = min_heap.top(); // biggest.
    EXPECT_EQ("AAAA", kmer.label);
    EXPECT_EQ(7, kmer.occurrence);
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

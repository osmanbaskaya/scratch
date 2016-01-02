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

TEST_F(KmerAnalyzerTest, load_kmers){
    KmerAnalyzer analyzer("test.txt", 90);
    analyzer.load_kmers();
    EXPECT_EQ(90, analyzer.get_unique_kmer_size());
    EXPECT_EQ(91, analyzer.get_total_kmer_size());
}

TEST_F(KmerAnalyzerTest, find_top_kmers){
    KmerAnalyzer analyzer("test.txt", 90);
    analyzer.load_kmers();
    Kmer top = analyzer.find_top_kmers(1).top();
    string correct_label = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAATTTTTTTTTTTTTTTTTTTTTTTTTTTTTTGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG";
    EXPECT_EQ(correct_label, top.label);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

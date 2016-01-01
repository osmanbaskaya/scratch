KMER_SIZE = 30
NUM_TOP_KMERS = 25

### WITHOUT CLASS STRUCTURE ###
kmers.out: kmers.cpp
	g++ $^ -std=c++11 -o $@

top-kmers-%.txt: kmers.out %.fastq.gz
	./$< <(zcat $*.fastq.gz) ${KMER_SIZE} ${NUM_TOP_KMERS} | sort -nr > $@ # better not the open unzip compressed files (49 GB)
	cat $@


### WITH CLASS STRUCTURE ###
class-kmers.out: kmer_analyzer.cpp utils.cpp
	g++ $^ -std=c++11 -o $@

class-top-kmers-%.txt: class-kmers.out %.fastq.gz
	./$< <(zcat $*.fastq.gz) ${KMER_SIZE} ${NUM_TOP_KMERS} | sort -nr > $@  # better not the open unzip compressed files (49 GB)
	cat $@

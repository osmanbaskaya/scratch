SHELL := /bin/bash

KMER_SIZE = 30
NUM_TOP_KMERS = 25

### WITH CLASS STRUCTURE ###

# Speed: 142.4 secs / 1M sequence lines. Memory: ~3GB memory.
top-kmers-%.txt: kmers.out %.fastq.gz
	./$< <(zcat $*.fastq.gz) ${KMER_SIZE} ${NUM_TOP_KMERS} | sort -nr > $@  # better not the open unzip compressed files
	cat $@

kmers.out: runner.cpp kmer_analyzer.cpp utils.cpp
	g++ $^ -std=c++11 -o $@

clean:
	-rm -r *.out

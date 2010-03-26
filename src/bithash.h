#ifndef BITHASH_H
#define BITHASH_H

#include <string>
#include <vector>
#include <cmath>
#include <bitset>
using namespace::std;

const int k = 19;
const unsigned long bitssize = 274877906944; // i.e. 4^19
//const unsigned long bitssize = 17179869184; // i.e. 4^17
//const unsigned long bitssize = 1073741824;  // i.e. 4^15

class bithash {
 public:
  bithash();
  ~bithash();
  void add(long long unsigned kmer);
  bool check(unsigned kmer[k]);
  bool check(unsigned kmer[k], long long unsigned & kmermap);
  bool check(long long unsigned & kmermap, unsigned last, unsigned next);
  void meryl_file_load(const char* merf, const double boundary);
  void tab_file_load(istream & mer_in, const double boundary);
  void tab_file_load(istream & mer_in, const vector<double> boundary);
  long long unsigned binary_kmer(const string &s);
  long long unsigned binary_rckmer(const string &s);
  void binary_file_output(char* outf);

  void binary_file_input(char* inf);
  void binary_file_input_lowmem(char* inf);
  unsigned int num_kmers();

 private:
  unsigned binary_nt(char ch);
  int count_at(string seq);

  bitset<bitssize> bits;
  unsigned long long mask;
};

#endif

#include "prefix_tree.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace::std;

int main() {
  const char* merf = "../results/12-2/HPKX_1039_AG0C1.1.cts";
  const int boundary = 8;
  const char* nts = "ACGT";

  prefix_tree mytree;

  ifstream mer_in(merf);
  string line;
  int count;
  int seq[k];
  bool add_kmer = false;

  while(getline(mer_in, line)) {
    if(line[0] == '>') {
      // get count
      count = atoi(line.substr(1).c_str());
      //cout << count << endl;
      
      // compare to boundary
      if(count >= boundary) {
	add_kmer = true;
      } else {
	add_kmer = false;
      }

    } else if(add_kmer) {
      // convert sequence
      for(int i = 0; i < k; i++) {
	seq[i] = strchr(nts, line[i]) - nts;
	//cout << seq[i] << " ";
      }
      //cout << endl;

      // add to tree
      mytree.add(seq);
    }
  }

  int node_count = mytree.count_nodes();
  cout << node_count << " nodes in prefix tree" << endl;

  return 0;
}


#include <vector>
using namespace std;

vector<int> repeteix_vector(const vector<int>& v, int llarg) {
   vector<int> res;
   for (int i = 0; i < llarg; i++) {
      res.push_back(v[i % v.size()]);
   }
   return res;
}

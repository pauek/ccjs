

bool cerca(int n, const vector<int>& v) {
   for (int i = 0; i < v.size(); i++) {
      if (v[i] == n) return true;
   }
   return false;
}

vector<int> interseccio(const vector<int>& v1, const vector<int>& v2) {
   vector<int> res;
   for (int i = 0; i < v1.size(); i++) {
      if (cerca(v1[i], v2)) {
         res.push_back(v1[i]);
      }
   }
   return res;
}

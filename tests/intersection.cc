
vector<double> interseccio(const vector<double>& v1, 
			   const vector<double>& v2) {
  vector<double> result;
  vector<double>::const_iterator i = v1.begin(), j = v2.begin();
  while (i != v1.end() && j != v2.end()) {
    if (*i == *j) {
      result.push_back(*i);
      i++, j++;
    } else if (*i > *j) {
      j++;
    } else {
      i++;
    }
  }
  return result;
}

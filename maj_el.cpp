#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

long get_majority_element(vector<long> &a, int left, int right) {
 if (left == right) {return a[left];}
  if (left + 1 == right) {
	if (a[left]!=a[right]) return -1;
	else return a[left];}
/*
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
*/
  
  int mid =left + (right-left)/2;
  int count_l=0, count_r=0;
  
  long x_l=get_majority_element(a,left,mid);
  long x_r=get_majority_element(a,mid +1, right);
  
  for(int i =left; i<=right; ++i){
  	if(x_l==a[i]) {count_l++;}
  	else if(x_r==a[i]){count_r++;}
	}
  int n= right -left +1;

  if(count_l>count_r && count_l>(n/2)) return x_l;
  if(count_l<count_r && count_r>(n/2)) return x_r;

  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<long> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}


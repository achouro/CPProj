#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<int> partition3(vector<int> &a, int l, int r) {
  int i = l;
  vector<int> pos(2); //position of the repeating pivot
  while(i<=r) 
    {
    if (a[i] < a[l])    { swap(a[i], a[l]);  ++l;  ++i;}
    else if(a[i]==a[l])  { ++i;}
    else/*(a[i]>a[l])*/ { swap(a[r],a[i]);  --r;}
    }
    
 
  pos[0]=l;
  pos[1]=i;

  return pos;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  vector<int> m(2);
  m = partition3(a, l, r);
  
  randomized_quick_sort(a,l, m[0]);
  randomized_quick_sort(a, m[1], r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}



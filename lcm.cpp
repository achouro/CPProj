#include <iostream>

/*long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}
*/
int gcd(int a, int b)
{ 
if(b==0){return a;}

int c=a%b; 

return gcd(b,c);
}
long long lcm(int a, int b)
{
long long x=gcd(a,b);
long long temp= a/x;
return b*temp;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}

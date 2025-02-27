#include <iostream>

int main() {
  int a, b;
  std::cin >> a >> b;
  int a4 = 0, b2 = 0;
  for (int ac = 0; ac < a; ++ac)
    for (int ac2 = 0; ac2 < a; ++ac2)
      for (int ac3 = 0; ac3 < a; ++ac3)
        a4 += a;
  for (int bc = 0; bc < b; ++bc)
    b2 += b;
  std::cout << a4 + b2 - 1 << std::endl;
  return 0;
}

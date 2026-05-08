#include <cmath>

constexpr int RX = 0, RY = 1, RT = 2;
inline int LX(int i) { return 3 + 2 * i; }
inline int LY(int i) { return 3 + 2 * i + 1; }

inline double wrap(double a) {
  a = std::fmod(a + M_PI, 2 * M_PI);
  if (a < 0)
    a += 2 * M_PI;
  return a - M_PI;
}

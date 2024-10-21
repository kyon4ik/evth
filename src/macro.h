#pragma once

#define Max(a, b) (a) > (b) ? (a) : (b)
#define Min(a, b) (a) < (b) ? (a) : (b)
#define Swap(x, y, T) do { T tmp = *x; *x = *y; *y = tmp; } while (0)

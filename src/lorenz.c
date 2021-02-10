#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double **malloc_array_2d(unsigned int x, unsigned int y)
{
  double **arr = (double **)malloc(sizeof(double *) * x);
  for (unsigned int i = 0; i < x; i++)
  {
    arr[i] = (double *)malloc(sizeof(double) * y);
  }
  return arr;
}

double **lorenz_attractor(unsigned int count, unsigned long long n, float step, double *init)
{
  unsigned char m = 3;
  double **result = malloc_array_2d(n, m);
  for (unsigned char i = 0; i < m; i++)
  {
    result[0][i] = init[i];
  }
  float a = 10, b = 8 / 3, c = 28;
  while (count > 0)
  {
    unsigned long long i = 1;
    while (i < n)
    {
      double *p0 = result[i - 1];
      double x = p0[0];
      double y = p0[1];
      double z = p0[2];
      result[i][0] = x + step * a * (y - x);
      result[i][1] = y + step * (x * (c - z) - y);
      result[i][2] = z + step * (x * y - b * z);
      i++;
    }
    for (unsigned char i = 0; i < m; i++)
    {
      result[0][i] = result[n - 1][i];
    }
    count--;
  }
  printf("total %llu\n", n);
  return result;
}

void free_array_2d(double **arr, unsigned int x, unsigned int y)
{
  for (unsigned int i = 0; i < x; i++)
  {
    free(arr[i]);
  }
  free(arr);
}

void test(void)
{
  double init[3] = {0.1, 0, 0};
  // this will take 2^22*3*8 = 100,663,296 bytes
  long long n = pow(2, 24);
  double **arr = lorenz_attractor(1000, n, 0.1, init);
  free_array_2d(arr, n, 3);
}

int main(void)
{
  // test();
}

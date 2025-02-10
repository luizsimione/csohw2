#include <stdio.h>

#include "sum_squares.h"

void print_32_bits(void *p) {
  unsigned int x = *((unsigned int *) p);
  unsigned int mask = 1 << 31;
  for(int i = 0; i < 32; i++) {
    if (x & mask)
      printf("1");
    else
      printf("0");
    mask >>= 1;
  }
}

unsigned int reverse_bits(unsigned int x) {
    unsigned int reversed = 0;
    
    for (int i = 0; i < 32; i++) {
        reversed <<= 1;
        reversed |= (x & 1);
        x >>= 1;
    }
    
    return reversed;
}

long int multiply(int x, int y) {
    unsigned long int mask = 1;
    unsigned long int prod = 0;
    
    long int lx = (long int)x;
    long int ly = (long int)y;

    for (int i = 0; i < 64; i++) {
        if (ly & mask)
            prod += lx;
        
        lx <<= 1;
        mask <<= 1;
    }

    return (long int)prod;
}

#define SIGN(x) ((x >> 31) & 1)
#define EXP(x) ((x >>23) & 0xFF)
#define FRAC(x) (x & 0x7FFFFF)

float float_add(float f, float g) {
    
  unsigned int sign_f = SIGN(*(unsigned int *) &f);
  unsigned int sign_g = SIGN(*(unsigned int *) &g);
  
  unsigned int exp_f =  EXP(*(unsigned int *) &f);
  unsigned int exp_g =  EXP(*(unsigned int *) &g);

  unsigned int frac_f = FRAC(*(unsigned int *) &f);
  unsigned int frac_g =  FRAC(*(unsigned int *) &g);

  if (exp_f == 0 && frac_f == 0)
      return g;
  if (exp_g == 0 && frac_g == 0)
      return f;

  unsigned int mantissa_f = (1 << 23) | frac_f;
  unsigned int mantissa_g = (1 << 23) | frac_g;
    
    if (exp_f < exp_g) {
        mantissa_f >>= (exp_g - exp_f);
        exp_f = exp_g;
    } else {
        mantissa_g >>= (exp_f - exp_g);
        exp_g = exp_f;
    }

  unsigned int sign_res;
  unsigned int mantissa_res;
  unsigned int exp_res = exp_f;

  if (sign_f == sign_g) {
      sign_res = sign_f;
      mantissa_res = mantissa_f + mantissa_g;
      if (mantissa_res & (1 << 24)) {
          mantissa_res >>= 1;
          exp_res++;
      }
  } else {
      
      if (mantissa_f > mantissa_g) {
          sign_res = sign_f;
          mantissa_res = mantissa_f - mantissa_g;
      } else if (mantissa_g > mantissa_f) {
          sign_res = sign_g;
          mantissa_res = mantissa_g - mantissa_f;
      } else
          return 0.0;
      
      while ((mantissa_res & (1 << 23)) == 0) {
          mantissa_res <<= 1;
          exp_res--;
      }
  }
  
  unsigned int result  = (sign_res << 31) | (exp_res << 23) | (mantissa_res & 0x7FFFFF);

  return *(float *) &result;
}

int main() {

  int x;
  int y;

  printf("Enter a number (to reverse) > ");
  scanf("%d", &x);

  printf("%d = ", x);
  print_32_bits(&x);
  printf("\n");

  int r = reverse_bits((unsigned int) x);
  printf("Reversed, the number is %d = ", r);
  print_32_bits(&r);
  printf("\n");

  printf("Enter two integers (to multiply) > ");
  scanf("%d %d", &x, &y);

  printf("%d * %d = %ld\n", x, y, multiply(x,y));
  printf("Result should be %ld\n", (long) x * (long) y);

  float f, g;

  printf("Enter two floating point numbers (to add) > ");
  scanf("%f", &f);
  scanf("%f", &g);

  printf("Computed %f + %f = %f\n", f, g, float_add(f,g));
  printf("Result should be close to %f\n", f + g);

  long n;
  printf("Enter n for sum_squares > ");
  scanf("%ld", &n);
  printf("sum_squares(%ld) = %ld\n", n, sum_squares(n));
  long res = 0;
  for (long i = 1; i <= n; i++) res += i*i;
  printf("Result should be %ld\n", res);
}

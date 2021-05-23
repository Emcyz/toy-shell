# toy-shell
## OS Environment
- Ubuntu 18.04

# Euclidean algorithm(유클리드 호제법)
- algorithm to solve greatest common divisor(GCD)
- 최대공약수를 구하는 알고리즘
``` c
int gcd(int a, int b)
{
  return b ? gcd(b, a % b) : a;
}
```

- run
``` shell
$ ./prog
num1  num2
```

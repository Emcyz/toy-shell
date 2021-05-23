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
```
$ ./prog
MyShell $ {int} {int}
```
- example
```
$ ./prog
MyShell $ 456 68
child : 68 48
parent : 48 20
child : 20 8
parent : 8 4
child solved GCD : 4
MyShell $
```

# Universal-Convertor

_the following is a technical task for this practical work_
  
Convert nums from one number system to another (from $p$ to $q$)  
The interface should be **well designed**.

## Additionally-mandatory part
Class _big integer_ for numbers.  
We need overload some operators for this class.
## The problem is in the backend
1) there are no limits for a numbers size
2) we must work with float and periodic fractions
3) digits
	+ angel $p, q \leq 36$ 
	+ devil $p, q - int$ (actually $p, q \leq 255$). When letters run out we will use number in square brackets.


## Foolprof
Actually it's not a problem.  
We protect from letters only p and q.  
For numbers we will check for the validity of the digets for our number system.  

## Basics of arbitrary-precision arithmetic
Every byte is a digit.  
string or vector of unsigned char.  
Digits will be stored in order from least to most significant.  
The fractional part is stored separately, the period and the pre-period too.  
  
For fraction we can use class _fraction_.  
#### How to use +
a + b - long addition.
carry - to transfer to the next digit.

```cpp
carry = 0
s_i = (a_i + b_i + carry) % p
carry = (a_i + b_i + carry) % p
```
  
It can be in cycle. After that:

```cpp
if (carry > 0) {
  s.push_back(что-то);
}
```

#### Multiplication algorithms
+ Supernative (addition)
+ Native - in a column $O(n^2)$
+ \*optional: Karatsuba algorithm

#### Division
Binary search on answer

## Deadline
Main deadline on 07.12.23

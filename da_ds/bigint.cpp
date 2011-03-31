#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string convert_base(string n, int from_b, int to_b) {
}

class BigInt {
public:
  BigInt():_data(string("0")) {}
  BigInt(const BigInt &n):_data(n._data) {}
  BigInt(string str_n, int base = 10);
  
  BigInt& operator+=(const BigInt &n);
  const BigInt operator+(const BigInt &n) const { return BigInt(*this)+=n; }
  
  BigInt& operator*=(const BigInt &n);
  const BigInt operator*(const BigInt &n) const { return BigInt(*this)*=n; }
private:
  string _data;
};

BigInt::BigInt(string str_n, int base = 10) {
  
}

BigInt& operator+=(const BigInt &n) {
  
  return *this;
}

int main(int argc, char **argv) {
}


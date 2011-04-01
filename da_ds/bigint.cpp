// For now only addition and multiplication

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned char byte;

string to_string(int num) {
  string res;
  while(num > 0) {
    res = res + (char)(num%10) + '0';
    num /= 10;
  }
  reverse(res.begin(), res.end());
  return res;
}

class BigInt {
public:
  BigInt(const BigInt &n):_data(n._data.begin(), n._data.end()) {}
  BigInt(string str_n, int base = 10);
  BigInt(int n = 0);
  
  BigInt& operator+=(const BigInt &n);
  const BigInt operator+(const BigInt &n) const { return BigInt(*this)+=n; }
  
  BigInt& operator*=(const BigInt &n);
  const BigInt operator*(const BigInt &n) const { return BigInt(*this)*=n; }
  BigInt& operator*=(const int &n);
  const BigInt operator*(const int &n) const { return BigInt(*this)*=n; }

  string to_string() const;
private:
  vector<byte> _data;
};

ostream& operator<<(ostream &out, const BigInt &n);

BigInt::BigInt(string str_n, int base) {
  BigInt m = BigInt(1);
  BigInt res = BigInt();

  string::reverse_iterator it = str_n.rbegin();

  while(it < str_n.rend()) {
    int n;
    if(isdigit(*it))
      n = *it - '0';
    else if(isalpha(*it))
      n = toupper(*it)-'A'+11;
    else throw string("Error: unsupported number - ")+str_n;
    //cout << "in str_n constructor " <<  n << endl;
    res = res + m * n;
    m *= base;

    it++;
  }
  cout << res._data.size() << endl;
  _data.clear();
  _data = vector<byte>(res._data);
}

BigInt::BigInt(int n) {
  _data.clear();
  while(n > 0) {
    byte c = (byte)n & 0xFF;
    //cout << "in while " <<  n << " " <<  (int)c << endl;
    _data.push_back(c);
    n >>= 8;
  }
}

BigInt& BigInt::operator+=(const BigInt &n) {
  vector<byte> num1 = this->_data;
  vector<byte> num2 = n._data;
  vector<byte> res;
  
  if(_data.size() < n._data.size()) {
    num1 = n._data;
    num2 = _data;
  }

  int carry = 0;
 
  vector<byte>::const_iterator it_n1 = num1.begin();
  vector<byte>::const_iterator it_n2 = num2.begin();
  while(it_n1 != num1.end()) {
    int sum = *it_n1;
    if(it_n2 != num2.end()) {
      sum += *it_n2;
      it_n2++;
    }
    sum += carry;
    res.push_back(sum & 0xFF);
    carry = sum >> 8;

    it_n1++;
  }

  while(carry > 0) {
    res.push_back((byte)carry & 0xFF);
    carry >>= 8;
  }
  _data.clear();
  _data = vector<byte>(res);
  return *this;
}

BigInt& BigInt::operator*=(const BigInt &n) {
  vector<byte> res;
  int i = 0;
  cout << "Multiplying " << *this << " " << n << endl;
  for(vector<byte>::const_iterator it_1 = _data.begin(); it_1 != _data.end(); it_1++, i++) {
    int carry = 0;
    int k = i;
    int j = 0;
    for(vector<byte>::const_iterator it_2 = n._data.begin(); it_2 != n._data.end(); it_2++, j++, k++) {
      int prod = *it_1 * (*it_2) + carry;
      if(k >= res.size()) {
	res.push_back((byte)prod & 0xFF);
      }
      else {
	prod += res[k];
	res[k] = ((byte)prod & 0xFF);
      }

      carry = prod >> 8;
    }

    while(carry > 0) {
      if(k >= res.size())
	res.push_back((byte)carry & 0xFF);
      else {
	carry += res[k];
	res[k] = ((byte)carry & 0xFF);
      }
      carry = carry >> 8;
    }
  }
  _data.clear();
  _data = vector<byte>(res);

  cout << "prod " << *this << endl;

  return *this;
}

BigInt& BigInt::operator*=(const int &n) {
  BigInt b_n(n);
  *this *= b_n;
  return *this;
}

string BigInt::to_string() const{
  if(_data.size() == 0)
    return string("0");

  string res;
  vector<byte>::const_iterator it = _data.begin();
  int carry = 0;
  while(it != _data.end()) {
    int sum = *it + carry;
    res += ((char)(sum%10) + '0');
    carry = sum/10;
    it++;
  }
  while(carry > 0) {
    res += ((char)(carry%10) + '0');
    carry = carry/10;
  }
  reverse(res.begin(), res.end());
  return res;
}

ostream& operator<<(ostream &out, const BigInt &n) {
  out << n.to_string();
  return out;
}

int main(int argc, char **argv) {
  cout << BigInt("256")
       << endl;

  return 0;
}


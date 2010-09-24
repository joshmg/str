// File: str.cpp
// Written by Joshua Green

#include "str.h"
#include <string>
#include <cctype>
#include <cstdio>
using namespace std;

//        numeric                capital                 lowercase
// (_a > 47 && _a < 58)    (_a > 64 && _a < 91)    (_a > 96 && _a < 123)

string itos(long int number) {
  if (number == 0) return "0";
  string reversed, temp;

  if (number < 0) {
    temp = "-";
    number *= -1;
  }

  while (number > 0) {
    reversed += number%10+48;
    number/=10;
  }
  int length = reversed.length();
  for (int i=0;i<length;i++) temp += reversed[length-i-1];
  return temp;
}

string ftos(float number) {
  char temp[30];
  temp[29] = 0;
  sprintf(temp, "%f", number);
  return string(temp);
}

string strtolower(const string &str) {
  int length = str.length();
  string data;
  for (int i=0;i<length;i++) {
    if ((int)str[i] > 64 && (int)str[i] < 91) data.append(1, (char)((int)str[i]+32));
    else data.append(1, str[i]);
  }
  return data;
}

bool is_numeric(const string &str) {
  int length = str.length();
  for (int i=0;i<length;i++) {
    if ((int)str[i] < 48 || (int)str[i] > 57) return false;
  }
  return true;
}

// case insensitive lessthan
bool strlessthan(const string &a, const string &b) {
  int a_length = a.length();
  bool equal = true;
  for (int i=0;i<a_length;i++) {
    
    // convert to lowercase; if not alpha-numeric set char to 0
    char _a = tolower(a[i]), _b = tolower(b[i]);
    if (!( (_a > 47 && _a < 58) || (_a > 96 && _a < 123) )) _a = (char)0;
    if (!( (_b > 47 && _b < 58) || (_b > 96 && _b < 123) )) _b = (char)0;
    
    if ((int)_a > (int)_b) return false;
    if (_a != _b) equal = false;
  }
  if (!equal) return true;
  else return false;
}

vector<string> explode(const string& unparsed, const string& delim, int limit) {
  vector<string> exploded;

  if (unparsed.length() == 0 || delim.length() == 0) {
    exploded.push_back(unparsed);
    return exploded;
  }

  string temp;
  for (int i=0;i<unparsed.length();i++) {
    string compare;
    for (int c=0;c<delim.length() && limit != 0;c++) compare += unparsed[i+c];
    if (compare == delim && (i > 0 && unparsed[(i-1)] != '\\')) {
      if (temp.length() > 0) exploded.push_back(temp);
      temp = "";
      i += (delim.length()-1);
      limit--;
    }
    else temp += unparsed[i];
  }
  if (temp.length() > 0) exploded.push_back(temp);
  return exploded;
}

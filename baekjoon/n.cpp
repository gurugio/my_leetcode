#include <iostream>

using namespace std;

void find(string &letters, int k, string &temp, int index, string &last) {
  cout << "letters:" << letters << "temp:" << temp << endl;
  if (index >= letters.length())
    return;
  if (temp.length() == k) {
    if (temp > last)
      last = temp;
    return;
  }
  temp.push_back(letters[index]);
  find(letters, k, temp, index + 1, last);
  temp.pop_back();
  find(letters, k, temp, index + 1, last);
}

int main(void) {
  int k = 3;
  string letters = "zbgaj";
  string last;
  string temp;
  find(letters, k, temp, 0, last);
  cout << last << endl;
}
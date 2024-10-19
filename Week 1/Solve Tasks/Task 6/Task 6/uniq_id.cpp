#include <string>
#include <vector>
using namespace std;

#define LINE(a) a
#define TOKEN(a) var##a
#define VAR(a)  TOKEN(a)
#define UNIQ_ID  VAR(LINE(__LINE__))

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}

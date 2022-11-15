#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
using namespace std;
ifstream in("test\\testcase.txt");
ofstream out("test\\testcaseIeteration.txt");
ofstream outans("test\\testcaseAns.txt");
int target[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0},
};
struct node {
  int state[4][4];
  int depth;
  int value;
  node *parent;
  bool operator<(const node a) const { return this->value > a.value; }
};
int evaluate(node a) {
  int cnt = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cnt += a.state[i][j] != target[i][j];
    }
  }
  return cnt;
}
string toString(node a) {
  string str;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      str += a.state[i][j] + '0';
    }
  }
  return str;
}
node *AstarSearch(node *start) {
  cout << "Astar Algorithm start" << endl;
  cout << "Print Iterations to testcaseIteration.txt files." << endl;

  priority_queue<node> nodes;
  nodes.push(*start);
  set<string> maps;
  maps.insert(toString(*start));

  node *curnode;
  node *nextnode;

  string str;
  int vary;
  bool flag = false;
  int cnt = 0;

  if (evaluate(*start) != 0) {
    while (!nodes.empty()) {
      curnode = new node;
      *curnode = nodes.top();
      nodes.pop();

      out << "Iteration #" << ++cnt << ":" << endl;
      out << "Search Depth #" << curnode->depth << endl;
      out << "Evaluation Value :" << curnode->value << endl;
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          out << curnode->state[i][j] << ' ';
        }
        out << endl;
      }
      out << endl;

      if (cnt % 100000 == 0) {
        cout << "Calculating Iteration " << cnt << " times...." << endl;
      }

      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (curnode->state[i][j] == 0) {
            if (j > 0) {
              nextnode = new node;
              *nextnode = *curnode;
              nextnode->depth++;
              nextnode->parent = curnode;
              nextnode->state[i][j] ^= nextnode->state[i][j - 1];
              nextnode->state[i][j - 1] ^= nextnode->state[i][j];
              nextnode->state[i][j] ^= nextnode->state[i][j - 1];
              str = toString(*nextnode);
              if (maps.find(str) == maps.end()) {
                maps.insert(str);
                vary = evaluate(*nextnode);
                if (vary == 0) {
                  flag = true;
                  break;
                } else {
                  nextnode->value = nextnode->depth + vary;
                  nodes.push(*nextnode);
                }
              }
            }

            if (i > 0) {
              nextnode = new node;
              *nextnode = *curnode;
              nextnode->depth++;
              nextnode->parent = curnode;
              nextnode->state[i][j] ^= nextnode->state[i - 1][j];
              nextnode->state[i - 1][j] ^= nextnode->state[i][j];
              nextnode->state[i][j] ^= nextnode->state[i - 1][j];
              str = toString(*nextnode);
              if (maps.find(str) == maps.end()) {
                maps.insert(str);
                vary = evaluate(*nextnode);
                if (vary == 0) {
                  flag = true;
                  break;
                } else {
                  nextnode->value = nextnode->depth + vary;
                  nodes.push(*nextnode);
                }
              }
            }

            if (i < 3) {
              nextnode = new node;
              *nextnode = *curnode;
              nextnode->depth++;
              nextnode->parent = curnode;
              nextnode->state[i][j] ^= nextnode->state[i + 1][j];
              nextnode->state[i + 1][j] ^= nextnode->state[i][j];
              nextnode->state[i][j] ^= nextnode->state[i + 1][j];
              str = toString(*nextnode);
              if (maps.find(str) == maps.end()) {
                maps.insert(str);
                vary = evaluate(*nextnode);
                if (vary == 0) {
                  flag = true;
                  break;
                } else {
                  nextnode->value = nextnode->depth + vary;
                  nodes.push(*nextnode);
                }
              }
            }

            if (j < 3) {
              nextnode = new node;
              *nextnode = *curnode;
              nextnode->depth++;
              nextnode->parent = curnode;
              nextnode->state[i][j] ^= nextnode->state[i][j + 1];
              nextnode->state[i][j + 1] ^= nextnode->state[i][j];
              nextnode->state[i][j] ^= nextnode->state[i][j + 1];
              str = toString(*nextnode);
              if (maps.find(str) == maps.end()) {
                maps.insert(str);
                vary = evaluate(*nextnode);
                if (vary == 0) {
                  flag = true;
                  break;
                } else {
                  nextnode->value = nextnode->depth + vary;
                  nodes.push(*nextnode);
                }
              }
            }
          }
        }
      }

      if (flag) {
        break;
      }
    }
  } else {
    nextnode = curnode;
  }
  out << "Iteration #" << ++cnt << ":" << endl;
  out << "Search Depth #" << nextnode->depth << endl;
  out << "Evaluation Value :" << nextnode->value << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out << nextnode->state[i][j] << ' ';
    }
    out << endl;
  }
  out << endl;

  std::cout << "Astar Algorithm is done!" << endl;
  std::cout << "Total iteration done " << cnt << " times" << endl;
  std::cout << "Steps is in testcaseAns.txt files" << endl;

  return nextnode;
}
void printans(node *s) {
  if (s == NULL) {
    return;
  }
  printans(s->parent);

  outans << "Step #" << s->depth << ":" << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      outans << s->state[i][j] << '\t';
    }
    outans << endl;
  }
  outans << endl;

  return;
}
int main() {
  std::cout << "Calculating 15shuma question\n";
  std::cout << "Reading input from file testcase.txt..." << endl;
  node *start = new node;
  node *ans;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      in >> start->state[i][j];
    }
  }
  start->depth = 0;
  start->value = evaluate(*start) + start->depth;
  start->parent = NULL;
  ans = AstarSearch(start);

  cout << "Print ans to file testcaseAns.txt" << endl;
  printans(ans);

  std::cout << "Best steps is " << ans->depth << " steps" << endl;

  return 0;
}
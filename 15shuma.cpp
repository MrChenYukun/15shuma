#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
using namespace std;
ifstream in("testcase1.txt");
ofstream out("testcaseAns1.txt");
int target[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0},
};
//目标状态
struct node {
  int state[4][4];  //记录当前状态
  int depth;        //记录搜索深度
  int value;        //记录估价函数的值
  bool operator<(const node a) const { return this->value > a.value; }
};

//通过和目标矩阵对比不一样的数量，计算估价函数
int evaluate(node a) {
  int cnt = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cnt += a.state[i][j] != target[i][j];
    }
  }
  return cnt;
}
//转换成字符串，方便当前状态是否有重复出现
string toString(node a) {
  string str;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      str += a.state[i][j] + '0';
    }
  }
  return str;
}
//A星算法本体
node AstarSearch(node start) {
  cout << "Astar Algorithm start" << endl;

  priority_queue<node> nodes;
  nodes.push(start);
  set<string> maps;
  maps.insert(toString(start));

  node curnode, nextnode;
  string str;
  int vary;
  bool flag = false;
  int cnt = 0;

  if (evaluate(curnode) != 0) {
    while (!nodes.empty()) {
      curnode = nodes.top();
      nodes.pop();

      out << "Iteration #" << ++cnt << ":" << endl;
      out << "Search Depth #" << curnode.depth << endl;
      out << "Evaluation Value :" << curnode.value << endl;
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          out << curnode.state[i][j] << ' ';
        }
        out << endl;
      }
      out << endl;

      if (cnt % 10000 == 0) {
        cout << "Calculating Iteration " << cnt << "times...." << endl;
      }

      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (curnode.state[i][j] == 0) {
            //左右交换
            if (j > 0) {
              nextnode = curnode;
              nextnode.depth++;
              nextnode.state[i][j] ^= nextnode.state[i][j - 1];
              nextnode.state[i][j - 1] ^= nextnode.state[i][j];
              nextnode.state[i][j] ^= nextnode.state[i][j - 1];
              str = toString(nextnode);
              if (maps.find(str) == maps.end()) {
                maps.insert(str);
                vary = evaluate(nextnode);
                if (vary == 0) {//记录是否找到答案
                  flag = true;
                  break;
                } else {
                  nextnode.value = nextnode.depth + vary;
                  nodes.push(nextnode);
                }
              }
            }
            //上下交换
            if (i > 0) {
              nextnode = curnode;
              nextnode.depth++;
              nextnode.state[i][j] ^= nextnode.state[i - 1][j];
              nextnode.state[i - 1][j] ^= nextnode.state[i][j];
              nextnode.state[i][j] ^= nextnode.state[i - 1][j];
              str = toString(nextnode);
              if (maps.find(str) == maps.end()) {
                maps.insert(str);
                vary = evaluate(nextnode);
                if (vary == 0) {
                  flag = true;
                  break;
                } else {
                  nextnode.value = nextnode.depth + vary;
                  nodes.push(nextnode);
                }
              }
            }
            //上下交换
            if (i < 3) {
              nextnode = curnode;
              nextnode.depth++;
              nextnode.state[i + 1][j] ^= nextnode.state[i][j];
              nextnode.state[i][j] ^= nextnode.state[i + 1][j];
              nextnode.state[i + 1][j] ^= nextnode.state[i][j];
              str = toString(nextnode);
              if (maps.find(str) == maps.end()) {
                maps.insert(str);
                vary = evaluate(nextnode);
                if (vary == 0) {
                  flag = true;
                  break;
                } else {
                  nextnode.value = nextnode.depth + vary;
                  nodes.push(nextnode);
                }
              }
            }
            //左右交换
            if (j < 3) {
              nextnode = curnode;
              nextnode.depth++;
              nextnode.state[i][j + 1] ^= nextnode.state[i][j];
              nextnode.state[i][j] ^= nextnode.state[i][j + 1];
              nextnode.state[i][j + 1] ^= nextnode.state[i][j];
              str = toString(nextnode);
              if (maps.find(str) == maps.end()) {
                maps.insert(str);
                vary = evaluate(nextnode);
                if (vary == 0) {
                  flag = true;
                  break;
                } else {
                  nextnode.value = nextnode.depth + vary;
                  nodes.push(nextnode);
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
  out << "Search Depth #" << nextnode.depth << endl;
  out << "Evaluation Value :" << nextnode.value << endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out << nextnode.state[i][j] << ' ';
    }
    out << endl;
  }
  out << endl;

  std::cout << "Astar Algorithm is done!" << endl;
  std::cout << "Total iteration done " << cnt << " times" << endl;
  std::cout << "Steps is in testcaseAns.txt files" << endl;

  return nextnode;
}
int main() {
  std::cout << "Calculating 15shuma question\n";
  std::cout << "Reading input from file testcase.txt..." << endl;
  node start;

  node ans;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      in >> start.state[i][j];
    }
  }
  start.depth = 0;
  start.value = evaluate(start) + start.depth;
  ans = AstarSearch(start);

  std::cout << "Best steps is " << ans.depth << " steps" << endl;

  return 0;
}
#include "avlbst.h"
#include "print_bst.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

struct Rectangle {
  int ID;
  int length;
  int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's

typedef AVLTree<int, Rectangle> InputMapType;
typedef AVLTree<int, std::pair<int, int>> OutputMapType;

// Allowed global variables: the dimensions of the grid
int n; // X-dim size
int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream &operator<<(std::ostream &os, const Rectangle &r) {
  os << r.ID;
  return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
  os << p.first << "," << p.second;
  return os;
}

void printSolution(std::ostream &os, InputMapType &input,
                   OutputMapType &output) {
  for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it) {
    InputMapType::iterator rbit = input.find(it->first);
    os << it->first << " ";
    os << it->second.first << " ";
    os << it->second.second << " ";
    os << rbit->second.length << " ";
    os << rbit->second.height << endl;
  }
}

// Changes the grid entries to their opposite values for the
// rectangle r starting at x1,y1
void flip(int x1, int y1, const Rectangle &r, vector<vector<bool>> &grid) {
  for (int x = x1; x < x1 + r.length; x++) {
    for (int y = y1; y < y1 + r.height; y++)
      grid[x][y] = !grid[x][y];
  }
}

/*filp function for rotated block*/
void rot_filp(int x1, int y1, int height, int length,
              vector<vector<bool>> &grid) {
  for (int x = x1; x < x1 + length; x++) {
    for (int y = y1; y < y1 + height; y++)
      grid[x][y] = !grid[x][y];
  }
}

bool check_fit(int curr_x, int curr_y, int curr_h, int curr_l,
               vector<vector<bool>> &grid) {
  if (((n - curr_x) >= curr_l) && ((m - curr_y) >= curr_h)) {
    /*block is within boundary from the location put down*/
    for (int x = curr_x; x < curr_x + curr_l; x++) {
      for (int y = curr_y; y < curr_y + curr_h; y++) {
        if (grid[x][y]) {
          /*occupied!*/
          return false;
        }
      }
    }
    /*all space neede can be allocated to this block*/
    return true;
  } else {
    return false;
  }
}

// TODO: Write your backtracking search function here

bool check_next(InputMapType::iterator it, InputMapType &input,
                OutputMapType &output, vector<vector<bool>> &grid) {

  if (it == input.end()) {
    /*the last block is placed at valid location*/
    return true;
  }

  InputMapType::iterator curr = it;
  bool valid = false;
  int curr_height = it->second.height;
  int curr_length = it->second.length;
  int rot_height = curr_length;
  int rot_length = curr_height;

  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {

      /*if the position not occupied*/
      if (!grid[x][y]) {

        if (check_fit(x, y, curr_height, curr_length, grid)) {
          /*there is enough space, occupy this space*/
          flip(x, y, it->second, grid);

          /*check for next block*/
          ++it;
          valid = check_next(it, input, output, grid);

          if (valid) {
            /*all blocks left can fit, solution found*/
            /*cuurent position is valid*/
            output.insert(std::make_pair(curr->first, std::make_pair(x, y)));
            /*original orientation valid*/
            return true;
          } else if (!valid) { /*consecutive block can not be placed*/
            /*restore grid, move on to check roatated orientation*/
            flip(x, y, curr->second, grid);
          }
          it = curr;
          /*original orientation failed to fit; rotate*/
        }

        if (check_fit(x, y, rot_height, rot_length, grid)) {

          /*fit after rotation; occupy this space*/
          rot_filp(x, y, rot_height, rot_length, grid);

          /*check for next block*/
          ++it;
          valid = check_next(it, input, output, grid);
          if (valid) {
            /*all blocks left can fit, solution found*/
            /*current position is valid, update output*/
            output.insert(std::make_pair(curr->first, std::make_pair(x, y)));
            /*rotated orientation valid, update input*/
            Rectangle rot_r;
            rot_r.ID = curr->first;
            rot_r.length = rot_length;
            rot_r.height = rot_height;
            input.insert(std::make_pair(rot_r.ID, rot_r));
            return true;
          } else if (!valid) { /*consecutive block can not be placed*/
            /*restore grid*/
            rot_filp(x, y, rot_height, rot_length, grid);
          }
          it = curr;
          /*current position not valid, move on to next position*/
        }
      }
    }
  }
  /*no position is valid*/
  return false;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "please specify an input and output file";
    return 0;
  }
  ifstream ifile(argv[1]);
  stringstream ss;
  string line;
  ofstream ofile(argv[2]);
  int x;
  getline(ifile, line);
  ss << line;
  ss >> n;
  ss >> m;
  ss >> x;

  InputMapType input;
  OutputMapType output;
  for (int i = 0; i < x; i++) {
    getline(ifile, line);
    stringstream ss2(line);
    Rectangle r;
    ss2 >> r.ID;
    ss2 >> r.length;
    ss2 >> r.height;
    input.insert(
        std::make_pair(r.ID, r)); /*the map: key = id, value = rectangle*/
  }
  ifile.close();
  vector<vector<bool>> grid;

  for (int i = 0; i < n; i++) {
    grid.push_back(vector<bool>(m, false));
  }
  InputMapType::iterator it = input.begin();

  bool solution_exists = false;

  // TODO:  Call your backtracking search function here

  solution_exists = check_next(it, input, output, grid);

  if (!solution_exists) {
    ofile << "No solution found.";
  } else {
    printSolution(ofile, input, output);
  }
  ofile.close();

  return 0;
}
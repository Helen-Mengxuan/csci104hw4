#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include "avlbst.h"
#include <map>

using namespace std;

struct Rectangle
{
    int ID;
    int length;
    int height;
};

// Typedefs for you input and output map. Start with
// std::map but once the backtracking search algorithm is working
// try to use your AVL-tree map implementation by changing these
// typedef's

typedef std::map<int, Rectangle> InputMapType;
typedef std::map<int, std::pair<int, int> > OutputMapType;

// Allowed global variables: the dimensions of the grid
int n; // X-dim size

int m; // Y-dim size

// No other global variables are allowed

// A dummy operator << for Rectangles so the BST and AVL BST will
// compile with their printRoot() implementations
std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << r.ID;
    return os;
}

// A dummy operator << for pairs so the BST and AVL BST will
// compile with their printRoot() implementations
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
{
    os << p.first << "," << p.second;
    return os;
}



void printSolution(std::ostream& os, InputMapType& input, OutputMapType& output)
{
    for (OutputMapType::iterator it = output.begin(); it != output.end(); ++it)
    {
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
void flip(int x1, int y1, const Rectangle& r, vector<vector<bool> >& grid)
{
    cerr << "filp: length: " << r.length << "  height: " << r.height << endl;

    for (int x = x1; x < x1+r.length; x++)
    {
        for (int y = y1; y < y1+r.height; y++) grid[x][y] = !grid[x][y];
    }
}

/*filp function for rotated block*/
void rot_filp(int x1, int y1, int height, int length, vector<vector<bool> >& grid)
{

    cerr << "rot_filp: length: " << length << "  height: " << height << endl;

    for (int x = x1; x < x1+length; x++)
    {
        for (int y = y1; y < y1+height; y++) grid[x][y] = !grid[x][y];
    }
}

bool check_fit(int curr_x, int curr_y, int curr_h, int curr_l){

    cerr << "check fit: curr_x " << curr_x << "  curr_y: " << curr_y << endl;
    cerr << "check fit: length: " << curr_l << "  height: " << curr_h << endl;

    if( ((n - curr_x) >= curr_l) && ( (m - curr_y) >= curr_h) ){
            return true;
    }
    else{
            return false;
    }
}

// TODO: Write your backtracking search function here

// pass in: it, input, output, grid
// "it" points to the rectangle object in each call

bool check_next(InputMapType::iterator it, InputMapType& input, OutputMapType& output, vector<vector<bool> >& grid)
{
    InputMapType::iterator curr = it;
    bool valid = false;
    int curr_height = it->second.height;
    int curr_length = it->second.length;
    int rot_height = curr_length;
    int rot_length = curr_height;

    cerr << "current block " << curr->first << endl;

    for(int x = 0; x < n; x++){
        for(int y = 0; y < m; y++){
            
            /*if the position not occupied*/
            if( !grid[x][y] ){

                if( check_fit(x, y, curr_height, curr_length) ){
                    /*there is enough space, occupy this space*/
                    flip(x, y, it->second, grid);
                    /*check for next block*/ 
                    ++it;
                    if( it == input.end() ){
                        /*this is the last block, and valid*/
                        output.insert( std::make_pair(curr->first, std::make_pair(x, y)));
                        /*original orientation valid*/
                        cerr << "ori-orien LAST block no need to update input" << endl;
                        return true;
                    }
                    else{ /*it != end, still blocks left*/
                        valid = check_next(it, input, output, grid);
                        if( valid ){
                            /*all blocks left can fit, solution found*/         
                            /*cuurent position is valid*/
                            output.insert( std::make_pair(curr->first, std::make_pair(x, y)) );
                            cerr << "block insert to output: " << curr->first << endl;
                            /*original orientation valid*/
                            return true;
                        }
                        else if( !valid ){ /*consecutive block can not be placed*/
                            /*restore grid, move on to check roatated orientation*/
                            flip(x, y, curr->second, grid);
                        }
                    }
                }
                it = curr;
                /*original orientation failed to fit; rotate*/
                cerr << "rotate block: " << it->first << endl;

                if( check_fit(x, y, rot_height, rot_length) ){

                    /*fit after rotation; occupy this space*/
                    cout << "------ rot_length: " << rot_length << " rot_height: " << rot_height << endl;
                    rot_filp(x, y, rot_height, rot_length, grid);

                    /*check for next block*/
                    ++it;
                    if( it == input.end() ){
                        /*this is the last block, and valid*/
                        output.insert( std::make_pair(curr->first, std::make_pair(x, y)));
                        /*rotated orientation valid, update input*/
                        Rectangle rot_r;
                        rot_r.ID = curr->first;
                        rot_r.height = rot_height;
                        rot_r.length = rot_length;
                        input.insert(std::make_pair(rot_r.ID, rot_r));
                        cerr << "rotated LAST block update to input: " << curr->first << endl; 
                        return true;
                    }
                    else{ /*it != end, still blocks left*/
                        valid = check_next(it, input, output, grid);
                        if( valid ){
                            /*all blocks left can fit, solution found*/         
                            /*current position is valid, update output*/
                            output.insert( std::make_pair(curr->first, std::make_pair(x, y)));
                            cerr << "block insert to output: " << curr->first << endl;
                            /*rotated orientation valid, update input*/
                            Rectangle rot_r;
                            rot_r.ID = curr->first;
                            rot_r.height = rot_height;
                            rot_r.length = rot_length;
                            input.insert(std::make_pair(rot_r.ID, rot_r));
                            cerr << "rotated block update to input: " << curr->first << endl;                            
                            return true;
                        }
                        else if( !valid ){ /*consecutive block can not be placed*/
                            /*restore grid*/
                            rot_filp(x, y, rot_height, rot_length, grid);
                        }
                    }
                }
                /*current position not valid, move on to next position*/
            }
        }
    }
    /*no position is valid*/
    return false;
}

int main(int argc, char *argv[])
{
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
        input.insert(std::make_pair(r.ID, r)); /*the map: key = id, value = rectangle*/
    }
    ifile.close();
    vector<vector<bool> > grid;

    for (int i = 0; i < n; i++)
    {
        grid.push_back(vector<bool>(m, false));
    }
    InputMapType::iterator it = input.begin();
    bool solution_exists = false;

    // TODO:  Call your backtracking search function here

    solution_exists = check_next(it, input, output, grid);

    if (!solution_exists) {
        ofile << "No solution found.";
    }
    else {
        printSolution(ofile, input, output);
    }
    ofile.close();
    return 0;
}
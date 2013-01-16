/*
*        file: calc_edit_distance.cpp 
*      author: Bryan B. Cabalo
* last 4 cwid: 5529
*       class: Bioinformatics
*
*       input: string m, string n
*      output: edit matrix, edit distance, alignment pair 
* description: Calculates the edit distance between two words and output both 
*              the matrix, the distance and an alignment that demonstrates the 
*              result
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using std::vector;
using namespace std;

void getUserInput(string &m, string &n) {
  cout << "Please input the two words:" << endl;
  cout << "First Word: ";
  getline(cin, m);
  cout << "Second Word: ";
  getline(cin, n);
}

void intializeEditMatrix(int width, int height, vector<vector<int> > &matrix) {
  matrix.resize(height);
  int i;
  int j;
  for (i=0; i < height; i++) {
    matrix[i].resize(width);
  }

  // Initialize all squares to 0
  for (i=0; i < height; i++) {
    for (j=0; j < width; j++) {
      matrix[i][j] = 0;
    }
  }

  // Initialize rows
  for (i=0; i < height; i++) {
    matrix[i][0] = i;
  }
  // Initialize columns
  for (j=0; j < width; j++) {
    matrix[0][j] = j;
  }
}

void showEditMatrix(vector<vector<int> > matrix) {
  int height = matrix.size();
  int width = matrix[0].size();

  cout << "\nThe matrix: " << endl;

  // Show matrix
  for (int i=0; i < height; i++) {
    cout << setw(3) << i << ": ";

    for (int j=0; j < width; j++) {
      cout << setw(4) << matrix[i][j] << " ";
    }

    cout << "\n";
  }

  cout << "\n";

  //Print edit distance
  cout << "The edit distance is: " << matrix[height-1][width-1] << "\n\n";
}

void calculateEditMatrix( string m, string n, vector<vector<int> > &matrix ) {
  int i; // Matrix row index
  int j; // Matrix column index

  int height = matrix.size();
  int width = matrix[0].size();

  // Calculate edit matrix
  for( i=1; i < height; i++ ) {
    for ( j=1; j < width; j++ ) {
      // Match!
      if ( m[j-1] == n[i-1] ) {
        matrix[i][j] = matrix[i-1][j-1];
      }
      // No match
      else {
        matrix[i][j] = min( (matrix[i-1][j] + 1), (matrix[i][j-1] + 1) );
        matrix[i][j] = min( matrix[i][j], (matrix[i-1][j-1] + 1) );
      }
    }
  }
}

void findAlignment(string m, string n, vector<vector<int> > &matrix) {
  int i = matrix.size() - 1; // Index matrix columns
  int j = matrix[0].size() - 1; // Index matrix rows
  int k = i; // Index string n
  int h = j; // Index string k
  string charm; // Placehold char* in string m
  string charn; // Placehold char* in string n
  string newm; // New string m alignment result
  string newn; // New string n alignment result
  m.insert(0,"_"); // Initialize string m
  n.insert(0,"_"); // Initialize string n

  // Find alignment
  while (i > -1 && j > -1) {
    charm = m[h];
    charn = n[k];

    // Characters match case
    if(m[h] == n[k]) {
      // Do not insert appended "_" on index terminate case
      // i=0, j=0
      if (i != 0 && j !=0) {
        newm.insert(0, charm);
        newn.insert(0, charn);
      }

      h--; // Move m and n indicies to next letter
      k--;
      j--; // Move matrix indicies to new position
      i--;
    }
    // Characters not match
    else {
      // Check all 3 squares for min
      // Check Mi-1 Nj
      if ( (i > 0) && matrix[i-1][j] < matrix[i][j]) {
        newm.insert(0, "_");
        newn.insert(0, charn);
        k--; // Move n index to next letter
        i--; // Move matrix index to new position
      }
      // Check Mi Nj-1
      else if ( ( j > 0 ) && (matrix[i][j-1] < matrix[i][j]) ) {
        newm.insert(0, charm);
        newn.insert(0, "_");
        j--; // Move m index to next letter
        h--; // Move matrix index to new position
      }
      // Align both characters
      else {
        newm.insert(0, charm);
        newn.insert(0, charn);
        h--; // Move m and n indicies to next letter
        k--;
        j--; // Move matrix indicies to new position
        i--;
      }
    }
  }

  // Show aligment
  cout << "The alignment: " << endl;
  cout << newm << endl;
  cout << newn << endl;
}

int main() {
  string m; // First word
  string n; // Second word
  vector<vector<int> > matrix; // Edit matrix

  getUserInput(m, n);
	
  int mlen = m.length();
  int nlen = n.length();
  int width = mlen + 1;
  int height = nlen + 1;

  intializeEditMatrix(width, height, matrix);

  calculateEditMatrix(m, n, matrix);

  showEditMatrix(matrix);

  findAlignment(m, n, matrix);

  return 0;
}
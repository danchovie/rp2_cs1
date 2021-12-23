#include <stdio.h>
//the maximum size for either the rows or columns is 100
#define SIZE 100
//the maximum number of cases to test is 50
#define CASES 50
//the replacement character is 'S', to be filled into previous star spots
#define REPLACEMENT 'S'
//the floodFill can travel in 4 different directions
//note: because we only want adjacent chars, we do not need to worry about diagonals; thus, there should never be a point where we move in both an x and y direction
#define DIRECTIONS 4
//positive x and negative x
const int DX[] = {-1,0,0,1};
//positive y and negative y
const int DY[] = {0,-1,1,0};
//floodFill function, which takes the grid (with room for the end char \0), the x and y coords, and the number of rows and columns
void fillStar(char grid[][SIZE+1], int x, int y, int max_x, int max_y);
//function to check if the given coords are in-bounds, given the coords and the number of rows and columns
int checkBounds(int x, int y, int max_x, int max_y);

int main(void) {
  //iterator for the number of test cases, starting at 1
  int g = 1;
  //we can continue until g reaches the max number of allowed cases, which is defined as 50
  //note: because of how Kattis takes input, there is no variable given for an exact number of test cases. it seems the code just has to continue working for as long as Kattis wants it to, without inputting a "Number of Loops" variable. thus, the while loop may not technically end when the input ends. i guess to break from the loop, you'd just have to enter a garbage variable for rows, cols, or grid, since that would violate their if clauses and return 0. i blame kattis, i think it's a bad idea not to give a specific number of test cases. oh well, i guess. don't blame me.
  while(g<=CASES){
    //variables for rows, columns, and the eventual number of whole stars counted
    int rows, cols, stars=0;
    //current "placeholder" for our grid of the sky, with maximum row x column size of SIZE x SIZE+1 (for end of line char)
    char grid[SIZE][SIZE+1];
    //as long as the ints entered for rows and cols are actually ints, as in not garbage values, the code will continue. what this statement says in specific is that if they ARE garbage, end the code. admittedly i never use anything like this since it's designed for a user who will only enter logical values, but Kattis wanted it. it works, i guess.
    if(scanf("%d", &rows)!=1||scanf("%d", &cols)!=1){
      return 0;;
    }
    //for the given number of rows, the user will enter in the sky LINE BY LINE rather than char by char. the user enters the row as a string, and as long as it isn't a garbage value, it will carry on. if it IS garbage, the code ends.
    for(int i = 0; i < rows; i++){
        if(scanf("%s", grid[i])!=1){
          return 0;
        }
    }
    //for the entire grid of chars (not of strings), we're gonna check for the value of a star. in this case, it's '-'. if we find it, we're gonna call the fillStar function to that coordinate of the array and have it and its adjacent star spots filled. then, we'll add 1 to the total number of whole stars.
    for(int x = 0; x < rows; x++){
      for(int y = 0; y < cols; y++){
        if(grid[x][y]=='-'){
          fillStar(grid, x, y, rows, cols);
          stars++;
        }
      }
    }
    //give the number of total stars for the test loop, then increase the while loop iterator by one to make sure it's still within the bounds of the loop and to increase it for the next Case print statement.
    printf("Case %d: %d\n", g, stars);
    g++;
  }
  //main ends
  return 0;
}
//our floodfill array, as desribed in the function header
void fillStar(char grid[][SIZE+1], int x, int y, int max_x, int max_y){
  //first, we fill in the given coordinate, which we know is a star spot given the if statement in the main, with the given replacement char, as known by the defined variable.
  grid[x][y] = REPLACEMENT;
  //for the total number of possible directions the coordinate can move in (adjacent spots, so only 4), we wanna check each possible direction for star spots. so we'll check (x-1,y),(x,y-1),(x,y+1),and (x+1,y). if at any of these points we find a star spot, we'll recursively call fillStar with that new coord and repeat the process.
  for(int i = 0; i < DIRECTIONS; i++){
    int row = x + DX[i];
    int col = y + DY[i];
    //the if statement makes sure that the new coordinates, modified by our DX and DY values, are still within the bounds of the overall grid. if they aren't, we obviously can't use the value, so the if will break and that iteration of the fillStar call will return.
    if(checkBounds(row, col, max_x, max_y)&&grid[row][col]=='-'){
      fillStar(grid, row, col, max_x, max_y);
    }
  }
}
//function to check if coords are in bounds, as described in the function header
int checkBounds(int x, int y, int max_x, int max_y){
  //if the x or y coords are either less that 0 or greater than the given number of rows or columns (respectively), we wanna return a false value, which in int terms is 0. otherwise, we're in bounds, so we return a true value, which in int terms is 1.
  if(x<0||x>=max_x||y<0||y>=max_y){
    return 0;
  }
  else{
    return 1;
  }
}
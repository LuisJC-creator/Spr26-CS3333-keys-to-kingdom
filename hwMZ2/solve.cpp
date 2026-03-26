#include "solve.h"
#include "vertex.h"

string solve(string maze){
        // stuff we need.
    int row = 1;
    int col = 1;
    int width = maze.find('\n'); // using this to make unique keys for the map.
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; // our "north, south, west, east" I just don't want to manually write these each time. maybe it's dumb to create a var for this but oh well. (edited with the loop in mind)
    unordered_map<int, Vertex*> VertexMap;
    Vertex* entryVert;
    Vertex* exitVert;
    int blankCount = 0;
    int lastRow = 0;

    // quick loop to find howm any rows so the loop below works properly
    for(int i = 0; i < maze.size(); i++){
        if (maze[i] == '\n')
            lastRow++;
    }


    for(int i = 0; i < maze.size(); i++){
        if(maze[i] == '\n'){
            col = 1;
            row++;
        }
        else if(row == 1 || row == lastRow || col == 1 || col == width){ // lol, this checks if we are at a boundary to find entry and exist correctly
            if(blankCount == 0 && maze[i] == ' '){
                entryVert = new Vertex(row, col);
                VertexMap[row * width + col] = entryVert;
                blankCount++;
                col++;
            }
            else if(blankCount == 1 && maze[i] == ' '){
                exitVert = new Vertex(row, col);
                VertexMap[row * width + col] = exitVert;
                col++;
            }
            else{
                col++;
            }
        }
        else if(isDigit(maze[i])){
            // do things, now you're thinking with portals.
            // if we encounter an number, we need to create a weighted edge between the two.
            // think of problem framing. we maybe need to go back and assign each of the edges from before a default weight
        }
        else if (maze[i] != '#'){
            Vertex* temp = new Vertex(row, col);
            VertexMap[row * width + col] = temp;
            col++;
        }
        else {
            // we hit a wall.
            col++;
        }
    }
}

bool isDigit(char c){
    char digitList[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for(int i = 0; i < 10; i++){
        if(c == digitList[i]){
            return true;
        }
    }
    return false;
}
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
        
        else if (maze[i] != '#'){
            if (row == 1 || row == lastRow || col == 1 || col == width) { // it is on the boundary (it can only be a digit or blank space.)
                // make entrance or exit
                if(blankCount == 0){
                    entryVert = new Vertex(row, col);
                    VertexMap[row * width + col] = entryVert;
                    blankCount++;
                    col++;
                }

                else if(blankCount == 1){
                    exitVert = new Vertex(row, col);
                    VertexMap[row * width + col] = exitVert;
                    col++;
                }
            }
        }

        else {
            // we hit a wall.
            col++;
        }
    }

     // when the above is done, we have a map filled with vertexes.

    // now we just loop through the map, find the valid neighbors in the 4 directions. (n, s, w, e)
    for(auto& [key, vertex] : VertexMap){
        for(int i = 0; i < 4; i++){
            // need this to find the key.
            int neighborRow = vertex->row + dirs[i][0];
            int neighborCol = vertex->col + dirs[i][1];

            int neighborKey = neighborRow * width + neighborCol;
            if(VertexMap.find(neighborKey) != VertexMap.end()){
                // add it to the neighbor list if it is in the map
                vertex->neighs.push_back(VertexMap[neighborKey]);
            }
        }
    }
}
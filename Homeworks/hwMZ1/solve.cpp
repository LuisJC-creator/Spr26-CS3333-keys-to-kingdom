#include "solve.h"
#include "vertex.h"

using namespace std;

void breadFirstSearch(Vertex* s, unordered_map<Vertex*, Vertex*>& bc){
    queue<Vertex*> Q;
    unordered_set<Vertex*> marked;

    marked.insert(s);
    Q.push(s);

    while (!Q.empty()){
        Vertex* x = Q.front();
        Q.pop();

        // visit all the unmarked neighbors.
        for (auto y : x->neighs){
            if (marked.find(y) == marked.end()){
                marked.insert(y);
                Q.push(y);

                // breadcrumb setting
                bc[y] = x;
            }
        }
    }
}

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

    // shortest path stuff
    unordered_map<Vertex*, Vertex*> breadCrumbs;
    breadFirstSearch(entryVert, breadCrumbs);

    // we need to trace the path from exit to entry, editing the map string at each location.
    Vertex* cur = exitVert;
    while (cur != entryVert){
        int temp_index = (cur->row - 1) * (width + 1) + (cur->col - 1); // this is the string index (i think it was off by 1 from the start oh well)
        // actually change the map here
        maze[temp_index] = 'o';
        cur = breadCrumbs.at(cur);
    }
    // mark the entrance too.
    int entry_index = (entryVert->row - 1) * (width + 1) + (entryVert->col - 1);
    maze[entry_index] = 'o';

    return maze;
}




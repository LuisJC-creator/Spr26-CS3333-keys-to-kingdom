#include "solve.h"
#include "vertex.h"
#include "minpriorityqueue.h"

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
    Vertex* portalList[10] = {nullptr}; // logic: if portalList[digit-1] == nullptr, add the vertex* to the list. else: we know it's the second time we encountered the digit, we can make the weighted edge here based on the digit.

    // quick loop to find how many rows so the loop below works properly
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
            Vertex* temp = new Vertex(row, col);
            VertexMap[row*width+col] = temp;

            if (isDigit(maze[i])){
                    // add it to the portalList
                    if (portalList[maze[i] - '0'] == nullptr){
                        portalList[maze[i] - '0'] = temp; // some ASCII value arithmetic for you.
                    }
                    else {
                        // create the weighted edge.
                        int index = maze[i] - '0';
                        portalList[index]->neighs.push_back(make_pair(temp, index)); // create edge from A -> B
                        temp->neighs.push_back(make_pair(portalList[index], index));
                    }
                }
            
            if (row == 1 || row == lastRow || col == 1 || col == width) { // it is on the boundary (it can only be a digit or blank space).

                if(blankCount == 0){
                    entryVert = temp;
                    blankCount++;
                }

                else if(blankCount == 1){
                    exitVert = temp;
                }
            }
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
                vertex->neighs.push_back(make_pair(VertexMap[neighborKey], 1));
            }
        }
    }

    // Now that we have the graph, we do Djikstra's stuff

}

bool isDigit(char c){
    char digitList[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for(int i = 0; i < 10; i++){
        if(c == digitList[i]){ return true;}
        else {return false;}
    }
}
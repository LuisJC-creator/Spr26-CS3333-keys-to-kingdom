#include "solve.h"
#include "vertex.h"
#include "minpriorityqueue.h"

bool isDigit(char c){
    char digitList[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for(int i = 0; i < 10; i++){
        if(c == digitList[i]){ return true;}
    }
    return false;
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
    MinPriorityQueue<Vertex*> pq;
    unordered_map<Vertex*, Vertex*> breadCrumbs;
    unordered_map<Vertex*, int> costTable;

    for( auto& [key, vertex] : VertexMap){
        pq.push(vertex, 10000); // put their priority, or cost as something large, trying to mock infinity (can't be larger than 9 in the maze anyways lol)
        costTable[vertex] = 10000;
    }
    costTable[entryVert] = 0; // fix this after
    pq.decrease_key(entryVert, 0);

    while(pq.size() != 0) { // while not empty.
        // get the min
        Vertex* x = pq.front();
        pq.pop();

        // relax all neighbors
        for(auto y : x->neighs){
            if ((costTable[x] + y.second) < costTable[y.first]){
                costTable[y.first] = costTable[x] + y.second;
                pq.decrease_key(y.first, costTable[y.first]);
                breadCrumbs[y.first] = x;
            }
        }
    }

    // once the above loop is done, we should have the correct breadCrumbs. (SAME CODE FROM MZ1)
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


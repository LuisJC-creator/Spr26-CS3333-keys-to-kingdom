#include "tiling.h"
#include "vertex.h"

using namespace std;


// Finds a (shortest according to edge length) augmenting path
// from s to t in a graph with vertex set V.
// Returns whether there is an augmenting path.
bool augmenting_path(Vertex* s, Vertex* t, 
        unordered_set<Vertex*> V, vector<Vertex*> &P)
{
        // Check that s and t aren't nullptr
        if (s == nullptr || t == nullptr)
	{
		cerr << "augmenting_path() was passed nullptr s or t." << endl;
		abort();
	}

        // Check that s and t are in the graph
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "augmenting_path() was passed s or t not in V." << endl;
		abort();
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "augmenting_path() was passed invalid vertex." << endl;
				abort();
			}

        // Since augmenting paths should have the fewest edges,
	// not the minimum weight, run BFS.
	queue<Vertex*> Q;
	Q.push(s);

	unordered_set<Vertex*> R;
	R.clear(); 
	R.insert(s);

	unordered_map<Vertex*, Vertex*> prev;

	while (!Q.empty())
	{
		Vertex* cur = Q.front();
		Q.pop();

		for (Vertex* nei : cur->neighs)
		{
			// Must have positive edge weight
			if (cur->weights[nei] == 0)
				continue;

			if (R.find(nei) == R.end())
			{
				Q.push(nei);
				R.insert(nei);
				prev[nei] = cur; 
			}
		}
	}      

        // If BFS never reached t
        if (R.find(t) == R.end())
                return false;

        // Reconstruct shortest path backwards
        P.clear();
        P.push_back(t);
        while (P[P.size()-1] != s)
                P.push_back(prev[P[P.size()-1]]);

        // Reverse shortest path
        for (int i = 0; i < P.size()/2; ++i)
		swap(P[i], P[P.size()-1-i]);

        return true;
}

// Returns the maximum flow from s to t in a weighted graph with vertex set V.
// Assumes all edge weights are non-negative.
int max_flow(Vertex* s, Vertex* t, unordered_set<Vertex*> V)
{
	// If s or t is invalid.
        if (s == nullptr || t == nullptr)
	{
		cerr << "max_flow() was passed nullptr s or t." << endl;
		abort(); 
	}

	// If s or t is not in the vertex set.
        if (V.find(s) == V.end() || V.find(t) == V.end())
	{
		cerr << "max_flow() was passed s or t not in V." << endl;
		abort(); 
	}

	// Check that every vertex has valid neighs/weights.
	for (Vertex* v : V)
		for (Vertex* vn : v->neighs)
			if (v->weights.find(vn) == v->weights.end())
			{
				cerr << "max_flow() was passed invalid vertex." << endl;
				abort();
			}

        // Create a deep copy of V to use as the residual graph
        unordered_set<Vertex*> resV;
        unordered_map<Vertex*, Vertex*> C; // Maps vertices in V to copies in resV
        for (Vertex* vp : V)
        {
                Vertex* rp = new Vertex;
                resV.insert(rp);
                C[vp] = rp;
        }
        for (Vertex* vp : V)
                for (Vertex* np : vp->neighs)
                {
                        C[vp]->neighs.insert(C[np]);
                        C[vp]->weights[C[np]] = vp->weights[np];
                }
	// Add any missing necessary "back" edges. 
        for (Vertex* vp : V)
                for (Vertex* np : vp->neighs)
		{
			if (C[np]->neighs.find(C[vp]) == C[np]->neighs.end())
			{
				C[np]->neighs.insert(C[vp]);
				C[np]->weights[C[vp]] = 0;
			}
		}

        // Run Edmonds-Karp
        while (true)
        {
                // Find an augmenting path
                vector<Vertex*> P;
                if (!augmenting_path(C[s], C[t], resV, P))
                        break;  
                // Update residual graph
                for (int i = 0; i < P.size()-1; ++i)
                {
                        --((*(resV.find(P[i])))->weights[P[i+1]]);
                        ++((*(resV.find(P[i+1])))->weights[P[i]]);
                }
        }

        // Compute actual flow amount
        int flow = 0;
        for (Vertex* snp : C[s]->neighs)
                flow += 1 - C[s]->weights[snp];

        // Delete residual graph
        for (Vertex* vp : resV)
                delete vp;

        return flow;
}


bool has_tiling(string floor)
{
        // TODO
        // I'm reusing code from maze.
		int row = 1;
		int col = 1;
        int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; 
		int width = floor.find('\n');
        unordered_map<int, Vertex*> VertexMap;
		unordered_set<Vertex*> White;
		unordered_set<Vertex*> Black;
		Vertex* s = new Vertex();
		Vertex* t = new Vertex();

		// make the string workable information.
		for(int i = 0; i < floor.size(); i++){
			// we find a newline character. 
			if(floor[i] == '\n'){
				row++;
				col=1;
			}
			else if (floor[i] == '#') {
				// do nothing, make blank the else case.
				col++;
			}
			else {
				// make vertex. I'm using a chessboard color scheme to determine color.
				// rule: if the sum of the coordinates is even, they are White if it is odd, they are Black.
				bool cSumEven = (row+col) % 2 == 0;
				Vertex* temp = new Vertex();
				VertexMap[row*width+col] = temp;
				if(cSumEven) {
					White.insert(temp);
				}
				else {
					Black.insert(temp);
				}
				col++;

			}
		}

		// easy
		if(White.size() != Black.size()){
			return false;
		}

		// less easy
		for (auto& [key, vertex] : VertexMap){
			for(int i = 0; i < 4; i++){
				int row = key / width;
				int col = key % width;

				int neighborRow = row + dirs[i][0];
				int neighborCol = col+ dirs[i][1];

				int neighborKey = neighborRow * width + neighborCol;
				if((VertexMap.find(neighborKey) != VertexMap.end()) && (White.find(vertex) != White.end())){
					// add it to the neighbor list if it is in the map
					vertex->neighs.insert(VertexMap[neighborKey]);
					vertex->weights[VertexMap[neighborKey]] = 1;
				}
			}
		}

		for(auto& x : White){
 		   s->neighs.insert(x);
    		s->weights[x] = 1;
		}

		for(auto& x : Black){
			x->neighs.insert(t);
			x->weights[t] = 1;
		}

		unordered_set<Vertex*> sol;
		sol.insert(s);
		sol.insert(t);
		for(auto& [key, vertex] : VertexMap){
			sol.insert(vertex);
		}
		
		return max_flow(s, t, sol) == White.size();
        
        
}





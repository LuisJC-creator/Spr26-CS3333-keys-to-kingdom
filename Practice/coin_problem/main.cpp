#include <vector>
#include <queue>
#include <iostream>

// coin problem from class, an implentation for my solution.
class Vertex {
public:
    int total;
    Vertex* parent;
    std::vector<Vertex*> neighs;

    Vertex(int x, Vertex* p){
        total = x;
        parent = p;
    }
    
};

int CoinProblem(int n, std::vector<int> coins){
    // initial confusion: I thought we needed to build a graph, but we can just think of the graph as implicit.
    // n is our goal, each Vertex encodes our total. The possible paths or neighbors are the set k.
    int steps = 0;
    std::vector<bool> tracker(n+1, false); // this only exists as a "marked" type structure for bfs // changed to bool array *credit Xavier
    std::queue<Vertex*> Q;
    Vertex* s = new Vertex(0, nullptr); // start somewhere
    Q.push(s);
    while(!Q.empty()){ // BFS style.
        Vertex* x = Q.front();
        Q.pop();
        
        // is the coin type valid?
        for(int i = 0; i < coins.size(); i++){
            int new_sum = x->total + coins[i];
            if((new_sum <= n) && tracker[new_sum] == false) { // have we seen it already? don't revisit, helps the runtime
                // make neighbors
                x->neighs.push_back(new Vertex((new_sum), x));
                tracker[new_sum] = true;
            }
        }

        if (x->total == n){
            // if we arrived at n, we have the shortest path.
            Vertex* curr = x;
            while(curr){
                curr = curr->parent;
                steps++;
            }
            return steps-1;
        }
        
        if(x->total > n) {
            return -1;
        }

        for (auto y : x->neighs){
            Q.push(y);
        }
    

    }

}

int main(){
    // idea: graph is implicit, you can do a BFS style approach.
    int n = 5; // what we want to make change for
    std::vector<int> k = {1, 1, 1, 11, 1, 4}; // set of coins.
    std::cout << "Number of coins needed: " << CoinProblem(n, k) << std::endl;

    return 0;
}
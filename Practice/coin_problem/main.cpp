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
    std::vector<int> tracker(n+1, 0);
    std::queue<Vertex*> Q;
    Vertex* s = new Vertex(0, nullptr); // start somewhere
    Q.push(s);
    while(!Q.empty()){
        Vertex* x = Q.front();
        Q.pop();
        
        // is the coin type valid?
        for(int i = 0; i < coins.size(); i++){
            int new_sum = x->total + coins[i];
            if((new_sum <= n) && tracker[new_sum] == 0) {
                // make neighbors
                x->neighs.push_back(new Vertex((new_sum), x));
                tracker[new_sum]++;
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
    int n = 34; // what we want to make change for
    std::vector<int> k = {1, 7, 10}; // set of coins.
    std::cout << "Number of coins needed: " << CoinProblem(n, k) << std::endl;

    return 0;
}
#include <iostream>
#include <fstream>

#include <string>
#include <unordered_map>

#include <queue>

class Node {
public:
    std::string name;
    int skepticism;
    std::vector<Node*> connections;
    bool heardRumor;
    int daySpread; // I DONT THINK I NEED IDK WHY I WROTRE THIS
    bool visited;
};

// =============================================================================================================================
// INPUT
// =============================================================================================================================
void addToAdj(Node* adding, std::unordered_map<std::string, Node> &adjList){
    adjList[adding->name] = *adding;
}

void addConnection(std::string &name1, std::string &name2, std::unordered_map<std::string, Node> &adjList){
    adjList[name1].connections.push_back(&adjList[name2]);
    adjList[name2].connections.push_back(&adjList[name1]);

}

void getInput(int &n, int &m, int &d, std::unordered_map<std::string, Node> &adjList){
    int e;
    std::string g;
    std::cin >> n >> m >> d;
    
    for(int i = 0; i < n; i++ ){
        std::string name;
        int skepticism;
        std::cin >> name >> skepticism;

        Node* newNode = new Node;
        newNode->name = name;
        newNode->skepticism = skepticism;
        newNode->heardRumor = false;
        newNode->daySpread = -1;
        newNode->visited = false;

        addToAdj(newNode, adjList);
    }

    for(int j = 0; j < m; j++){
        std::string name1;
        std::string name2;

        std::cin >> name1 >> name2;

        addConnection(name1, name2, adjList);
    }

}

// =============================================================================================================================
// BFS MODIFIED
// =============================================================================================================================

struct CompareNode {
    bool operator()(const Node* a, const Node* b){
        return a->skepticism > b->skepticism;
    }
};

void runRumor( std::unordered_map<std::string, Node> &adjList, int &d){
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq;
    std::string r;
    std::cin >> r;
    pq.push(&adjList[r]);

    int days = 0;
    
    while((!pq.empty()) && (days < d)){
        Node* u = pq.top();
        pq.pop();
        u->daySpread = days;
        u->visited = true;
        days++;

        //std::cout << "u: " << u->name << "\n     visiting: ";

        for(int i = 0; i < u->connections.size(); i++){
            Node* v = u->connections[i];

            //std::cout << v->name << ", ";

            if(v->skepticism == 1 && v->visited == false){

                v->daySpread = days;
                pq.push(v);
                v->heardRumor = true;
                v->visited= true;
                //std::cout<<v->heardRumor;

            } else if (v->visited == false) {
                v->skepticism--;
                v->heardRumor = true;
            }
        }

        //std::cout << "\n";
    }
    

}

int howManyHeard(std::unordered_map<std::string, Node> &adjList){
    int count = 0;
    for(const auto& pair : adjList){
        if(pair.second.heardRumor == true){
            count++;
        }
    }
    return count;
}

int main() {
    
    int n, m, d;
    std::unordered_map<std::string, Node> adjList;

    getInput(n, m, d, adjList);

    runRumor(adjList, d);
    
    std::cout << howManyHeard(adjList);


    // Test printing
    /*std::ofstream outFile("output.txt");

    outFile << "first line inputs: "<< n << " " << m << " " << d << "\n \n";

    outFile << "getting the people and there connections: \n";
    for(const auto& pair : adjList){
        outFile << "     name: " << pair.second.name << " skepticism: " << pair.second.skepticism << "\n";
        outFile << "          connections: ";
        for(const auto& connection : pair.second.connections){
            outFile << connection->name << ", ";
        }
        outFile << "\n \n";
    }
    outFile << "\n";
    

    outFile << "spread of the rumor: \n";
    for(const auto& pair : adjList){
        outFile << "name: " << pair.second.name << " skepticism: " << pair.second.skepticism << " heard rumor: " <<  pair.second.heardRumor << "\n";
    }
*/
    return 0;
}
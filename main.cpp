#include <tuple>
#include <map>
#include <set>
#include <optional>
#include <iostream>




/*LSM-Like Implementation of multicopy template*/
enum OptionTS {
    someTS,
    noneTS
};

enum OptionNode {
    someNode,
    noneNode
};

/*Definition of a Node*/

//Type of Node
enum NodeType {
    memtableNode,
    sstableNode
};

// TODO
// ghost var indices: Map<K, Int>;  // inverse of tableK for sstableNodes
class Node {
public:
    NodeType nodeType;
    int *tableK;
    int *tableT;
    int tableLen;
    Node *next;
};

//TODO
//const int B
const int B = 10;

std::tuple<Node*, std::map<Node*,std::set<int>>, std::map<int,int>> init(){
    Node* r = new Node();
    r->tableK = new int[2*B];
    r->tableT = new int[2*B];
    r->tableLen = 0;
    r->next = nullptr;
    r->nodeType = memtableNode;

    std::map<Node*,std::set<int>> esr;
    std::map<int,int> Cr ;

    return std::make_tuple(r,esr,Cr);

}

std::optional<int> inContents(Node* n, int k){
    if (n->nodeType == memtableNode){
        int i = n->tableLen - 1;
        bool flag = false;

        while(i>=0 && !flag) {
            if (n->tableK[i] == k) {
                flag = true;
            } else {
                i -= 1;
            }
        }

        if(flag){
            return n->tableT[i];
        }else{
            return {};
        }
    }else{

    }
}

int main() {
    Node *node;
    std::map<Node*,std::set<int>> esr;
    std::map<int,int> Cr ;

    std::tie(node,esr,Cr) = init();

}

/* ------------------- Abstract Tree Height ------------------ */
/* input format example
/* 5 (Node 0~4)
/* Parent 4 -1 4 1 1  // -1:root node, 4:children of node 4
/* Node   0  1 2 3 4  // Node number
/* ------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class TreeHeight{
    int n;
    vector<int> parent;
    vector<int> depth;
public:
    void read(){
        cin >> n;
        parent.resize(n);
        depth.resize(n);
        for (int i = 0; i < n; i++){
            cin >> parent[i];
        }
    }
    int compute_height(){
        int maxHeight = 0;
        // empty tree
        if(n == 0)
            return n;
        // fill depth of all nodes
        for(int i = 0; i < n; i++){
            fillDepth(i);
        }
        for(int i = 0; i < n; i++){
            int height = depth[i];
            maxHeight = max(maxHeight, height);
        }
        return maxHeight;
    }
    // �ھڦ��D�������c, ��±qparent�Proot���, �p�Gparent�٨S����X�`�׫h��parent node��J���j
    // �]��root�@�w�s�b, �ҥH�|�����root(first parent)
    void fillDepth(int nodeNumber){
        // root node, depth = 1
        if(parent[nodeNumber] == -1){
            depth[nodeNumber] = 1;
            return;
        }
        // the depth of this node has been calculated
        if(depth[nodeNumber])
            return;
        // if depth of parent is not calculated, put the parent node to recursive to get the depth
        if(!depth[parent[nodeNumber]])
            fillDepth(parent[nodeNumber]);  // ���Jrecursive ���̫���parent depth, �|����U������

        // depth of this node = depth of parent plus 1
        depth[nodeNumber] = depth[parent[nodeNumber]] + 1;
    }
};
int main(){
    ios_base::sync_with_stdio(0);
    TreeHeight tree;
    tree.read();
    cout << tree.compute_height() << endl;
}

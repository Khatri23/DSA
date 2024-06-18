#include<iostream>
#include<vector>
#include<queue>
#include<stack>
//Tree structure.
class TreeNode{
public:
    int data;
    TreeNode*left;
    TreeNode*right;
    TreeNode(){}
    TreeNode(int data){
        this->data=data;
        left=right=NULL;
    }
};
//printing in standard form of the array.
void BFS_Print(TreeNode*root){//O(N)
    std::queue<TreeNode*>BFS;
    BFS.push(root);
    while(!BFS.empty()){
        TreeNode*top=BFS.front();
        BFS.pop();
        if(top->left!=NULL) BFS.push(top->left);
        if(top->right!=NULL) BFS.push(top->right);
        std::cout<<top->data<<" ";
    }
}
//preserving the indexing value of vector using BFS to build my tree. or it can be formed as you want ie..
//building the tree from DFS is also a choice.
TreeNode* buildTree(std::vector<int>&values,TreeNode*root,int &index){//O(N)
    std::queue<TreeNode*>BFS;
    BFS.push(root);
    int parent=0;
    
    while(!BFS.empty()){
        TreeNode * Top=BFS.front();
        BFS.pop();
        int left=2*parent+1;
        int right=2*parent+2;
        if(left < values.size()){
            Top->left=new TreeNode(values[left]);
        }
        if(right < values.size()){
            Top->right=new TreeNode(values[right]);
        }
        if(Top->left!=NULL) BFS.push(Top->left);
        if(Top->right!=NULL) BFS.push(Top->right);
        parent++;
       
    }
    return root;
}
//standard logic for the heapify.
void Min_Heap(TreeNode* root,int parent){//O(log(Node))
    TreeNode* next=root;
    if(root->left!=NULL && root->left->data < next->data){
        next=root->left;
    }
    if(root->right!=NULL && root->right->data < next->data){
        next=root->right;
    }
    if(root!=next){
        root->data=next->data;
        next->data=parent;
        Min_Heap(next,next->data);
    }
}
void BuildMin_Heap(TreeNode*root,std::stack<TreeNode*>&Parent){ //O(N)
    if(root==NULL) return;
    //stack is preferred since it is LIFO and the objective is to find the ending parent node.
    //which it behaves as size/2-1 in building heap from the array.
  std::queue<TreeNode*>BFS;
  BFS.push(root);
  while(!BFS.empty()){
    TreeNode* top=BFS.front();
    BFS.pop();
    if(top->left!=NULL || top->right!=NULL)
    Parent.push(top);

    if(top->left!=NULL) BFS.push(top->left);
    if(top->right!=NULL) BFS.push(top->right);
  }

}
int main()
{   
    std::vector<int>Test={85, 20, 17, 46, 4, 10, 33, 87, 57, 28};
    TreeNode *root=new TreeNode(Test[0]);
    int index=1;
    root=buildTree(Test,root,index);
    std::stack<TreeNode*>Parent;
    BuildMin_Heap(root,Parent);
    while(!Parent.empty()){//O(Nlog(Nodes)) ~~ O(N).
        Min_Heap(Parent.top(),Parent.top()->data);
        Parent.pop();
    }
    BFS_Print(root);
    //General case is O(N).
    return 0;
}
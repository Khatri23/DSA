#include<iostream>
#include<vector>
//structure of the tree.
class TreeNode{
public:
    int data;
    int Lrange,Rrange;
    TreeNode*left;
    TreeNode* right;
    TreeNode(){}
    TreeNode(int data){
        this->data=data;
        left=right=nullptr;
    }
};

class Segmentation_tree{
private:
    int Dsize; //Dynamic size tracking the next index in dynamic growth.
    TreeNode*root;
    std::vector<int>Buffer;//container for incoming datas    
public:
    bool flag; //indication of is tree build?
    Segmentation_tree(std::vector<int>&data):Dsize(0){
        root=Build_tree(data,0,data.size()-1);
        flag=true;
        Dsize=data.size();
    }
    ~Segmentation_tree(){
        clear(root);
    }
    void Display(){
        preorder(root);
    }
    void Update(int data,int index){
        root=Update(root,data,index);
    }
    void Query(int left,int right){
        std::cout<<"Value- "<<Query(root,left,right);
    }
    void Add_Element(int data)
    {
        Buffer.push_back(data);
        //if it contain empty i have to reinitialize all 
        if(Dsize==0){
            root=Build_tree(Buffer,0,Buffer.size()-1);
            Dsize=Buffer.size();
            Buffer.resize(0);
            flag=true;
            return;
        }
         if(Dsize==Buffer.size()){
            //build the tree for the buffer and release the memory.
            TreeNode* current=Build_tree(Buffer,0,Buffer.size()-1);
            
            //merge the previous and current data.
            TreeNode* temp=new TreeNode(root->data+current->data);
            temp->left=root;temp->right=current;
            temp->Lrange=root->Lrange;temp->Rrange=current->Rrange;
            root=temp;
            Buffer.resize(0);
            Dsize*=2;
            flag=true;//usecase to indicate whether the tree is build from the incoming data stream.
        }
        else flag=false; 
    }
private:
    TreeNode* Build_tree(const std::vector<int>&data,int start,int end) //based on divide and conquare algorithm.
    {
        if(start > end){
            return NULL;
        }
        int mid=(start+end)/2;
        if(start == end){
            //represent the leaf node with the element .
            TreeNode* curr=new TreeNode(data[mid]);
            curr->Rrange=curr->Lrange=start+Dsize;
            return curr;
        }
        TreeNode* root=new TreeNode();
        root->left=Build_tree(data,start,mid);
        root->right=Build_tree(data,mid+1,end);
        //bubble up for summing the range sum from the child.
        //tree start filling in bottom up manner.
        root->data=root->left->data+root->right->data;
        root->Lrange=root->left->Lrange;
        root->Rrange=root->right->Rrange;
        return root;
    }
    void preorder(TreeNode*root){
        if(root==NULL) return;
        std::cout<<root->data<<" L-"<<root->Lrange<<" R-"<<root->Rrange<<std::endl;
        preorder(root->left);
        preorder(root->right);
    }
    TreeNode* Update(TreeNode* root,int data,int index){
        //if it is a leaf.
        if(root->left==NULL && root->right==NULL){
            root->data=data;
            return root;
        }
        int mid=(root->Lrange+root->Rrange)/2;
        if(index <=mid){//go in left subtree
            root->left=Update(root->left,data,index);
        }
        else
            root->right=Update(root->right,data,index);
        root->data=root->left->data+root->right->data;
        return root;
    }
    int Query(TreeNode* root,int& left,int& right){
        if(left > root->Rrange || right < root->Lrange) return 0; //if the recursion exceed any of the two it yeild 0
        if(left <=root->Lrange && right >=root->Rrange) return root->data;

        return Query(root->left,left,right)+Query(root->right,left,right);
    }
    //releasing the memory
    void clear(TreeNode* root) {
    if (root == nullptr) return;
    
    // Recursively delete left and right subtrees
    clear(root->left);
    clear(root->right);
    
    // Delete the current node
    delete root;
}
};

int main()
{
    // std::vector<int> initial; // empty input size
    // Segmentation_tree obj(initial);
    // obj.Add_Element(1);
    // obj.Add_Element(2);
    // obj.Add_Element(3);
    // obj.Add_Element(4);
    // obj.Display(); 

   
    //first pass.
    std::vector<int>initial={1,2};
    Segmentation_tree obj(initial);
    //second pass
    obj.Add_Element(3);
    obj.Add_Element(4);
    obj.Display();
    //new data exactly the size of the previous data.
    for(int i=5;i<=8;i++){
        obj.Add_Element(i);
    }
    std::cout<<"\n Second pass\n";
    obj.Display();

    std::cout<<std::endl;
    obj.Query(3,6);
    return 0;
}
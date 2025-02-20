/*
Instruction on building the binary search tree!
(iterative method)
Property: 
    if x is a node then its left subtree is smaller than x.key and its right subtree is bigger than x.key
    this property is applied to all of the node except for the leaves node.
Inserting a node in a BST is just placing that value in NULL position note cannot insert in between nodes .
Successor defination is the node which is smallar than the node but bigger to that node.(located in right subpart left traversal) if right
subtree is absent then just go for the parents which is bigger than node but smaller than other.
*/
#include<iostream>
class TreeNode{
public:
    int data;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
public:
    TreeNode(int data){ //for leaves
        this->data=data;
        left=right=parent=NULL;
    }
    TreeNode(int data, TreeNode * p){
        this->data=data;
        parent=p;
        left=right=NULL;
    }
};
void inorder(TreeNode* root)
{
    //this the validation of the BST as inorder traversal always yeild the ascending order
    if(root!=NULL){
        inorder(root->left);
        std::cout<<root->data<<" ";
        inorder(root->right);
    }
}

TreeNode * Search(int val,TreeNode * root) //return NULL if no key is in BST else return  that node
{
    TreeNode * x=root;
    while(x !=NULL && x->data != val){
        if(x->data > val) x=x->left;
        else x=x->right;
    }   
    return x;
}
TreeNode * Insert(int val,TreeNode* root)
{
    TreeNode * y=NULL;
    TreeNode * x=root;
    while(x != NULL)
    {
        y=x; //track of the parent.
        if(x->data > val) x=x->left;
        else x=x->right;
    }

    if(y==NULL) return new TreeNode(val); //this case is for root==NULL no data in the tree.
    else if( y->data > val) y->left= new TreeNode(val,y);
    else y->right=new TreeNode(val,y);
    return root;
}

TreeNode * DELETE(int val,TreeNode * root)
{
    TreeNode * x=Search(val,root);
    if(x==NULL) return root; // no valid node 
    TreeNode * p=x->parent;
    //check if left is null.or leaf node
    if(x->left==NULL){
        if(p->data <= val)p->right=x->right;   //definitely right
        else p->left=x->right;
        if(x->right) x->right->parent=p;
        x->right=x->parent=NULL;
        delete x;
    }
    else if(x->right==NULL)
    {
        if(p->data <= val)p->right=x->left;   //definitely right
        else p->left=x->left;
        x->left->parent=p;
        x->left=x->parent=NULL;
        delete x;
    }
    else{ //case for both child then find the successor of the x node
        TreeNode * y=x->right;
        while(y->left != NULL){
            y=y->left;
        }
        x->data=y->data;
        DELETE(y->data,y);
    }
    return root;
}

int main()
{
    int arr[]={15,8,3,2,4,7,6,13,9,18,17,20}; //random inputs
    int size=sizeof(arr)/sizeof(int);
    TreeNode * root=NULL;
    for(int i=0;i<size;i++)
    {
        root=Insert(arr[i],root);
    }
    root=DELETE(15,root);
    inorder(root);

    return 0;
}
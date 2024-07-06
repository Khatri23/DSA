#include<iostream>
//AVL a self balancing tree implementation.
//Tree structure.
class TreeNode
{
public:
    int data;
    TreeNode*left;
    TreeNode*right;
    int height;
    TreeNode(){}
    TreeNode(int data):height(0){
        this->data=data;
        left=right=NULL;
    }
};
int Height(TreeNode*);
int BalanceFactor(TreeNode*);
TreeNode*rotateLeft(TreeNode*);
TreeNode*rotateRight(TreeNode*);
TreeNode*LL(TreeNode*);
TreeNode*LR(TreeNode*);
TreeNode*RR(TreeNode*);
TreeNode*RL(TreeNode*);
TreeNode*Insert(TreeNode*,int);
TreeNode* DELETE(TreeNode*,int);
bool Search(TreeNode *,int);

void preOrder(TreeNode*root)
{
    if(root==NULL) return;
    std::cout<<root->data<<" ";
    preOrder(root->left);
    preOrder(root->right);
}

int main()
{
    TreeNode* root=new TreeNode;
    root=NULL;
    int input[]={3,5,11,8,4,1,12,7,2,6,10};
    int size=sizeof(input)/sizeof(int);
    for(int i=0;i<size;i++)
    {
        root=Insert(root,input[i]);
    }
    root=DELETE(root,4);
    preOrder(root);
    std::cout<<std::endl;
    
    return 0;
}
TreeNode*Insert(TreeNode*root,int data)
{
    if(root==NULL){
        return new TreeNode(data);
    }
    if(data < root->data)
    {
        root->left=Insert(root->left,data);
        if(BalanceFactor(root) > 1){ //BF lies in -1,0,1.if it exceed by 1 then the left sub tree in unbalanced.
            if(root->left->data > data){//LL case. rotate right
                    root=LL(root);
            } 
            else{
                root=LR(root);
            }
        }
    }
    else if(data > root->data)
    {
        root->right=Insert(root->right,data);
        if(BalanceFactor(root) < -1){//BF lies in -1,0,1.if it less than -1 then the right sub tree in unbalanced.
            if(root->right->data < data)//RR case so rotate left.
                root=RR(root);
            else
                root=RL(root);
        }
    }
    root->height=Height(root);
    return root;
}

int Height(TreeNode* root)
{
    if(root==NULL) return 0;
    int lh=(root->left==NULL)?0:1+root->left->height;
    int rh=(root->right==NULL)?0:1+root->right->height;

    return std::max(lh,rh);
}
int BalanceFactor(TreeNode*root)
{
    if(root==NULL) return 0;
    int lh=(root->left==NULL)?0:1+root->left->height;
    int rh=(root->right==NULL)?0:1+root->right->height;
    return (lh-rh);
}
TreeNode* rotateLeft(TreeNode*root){
    TreeNode*temp=root->right;
    root->right=temp->left;
    temp->left=root;
    temp->height=Height(temp);
    root->height=Height(root);
    return temp;
}
TreeNode* rotateRight(TreeNode*root){
    TreeNode* temp=root->left;
    root->left=temp->right;
    temp->right=root;
    temp->height=Height(temp);
    root->height=Height(root);
    return temp;
}
TreeNode*LL(TreeNode* root){
    return rotateRight(root);
}
TreeNode*LR(TreeNode* root){
    root->left=rotateLeft(root->left);
    root=rotateRight(root);
    return root;
}
TreeNode*RR(TreeNode* root){
    return rotateLeft(root);
}
TreeNode*RL(TreeNode* root){
    root->right=rotateRight(root->right);
    root=rotateLeft(root);
    return root;
}

TreeNode* DELETE(TreeNode*root,int data)
{
    if(root==NULL) return NULL;
    if(data < root->data){
        root->left=DELETE(root->left,data);
        if(BalanceFactor(root) < -1){ //esure that it is balance.
            if(BalanceFactor(root->right) <= 0) //when deleting left child the balance should be performed in right since the hight of the parent is effected.
                root=RR(root);
            else
                root=RL(root);
        }
    }
    else if(data > root->data){
        root->right=DELETE(root->right,data);
        if(BalanceFactor(root) > 1){
            if(BalanceFactor(root->left) >= 0)//balance is in left since the height of parent is effect and case unbalance in left.
                root=LL(root);
            else   
                root=LR(root);
        }
    }
    else{//data is found .
        if(root->right!=NULL){
            //adjust parent as max value of left sub tree or min value of right sub tree.
            TreeNode* temp=root->right;
            while(temp->left!=NULL)
                temp=temp->left;
            root->data=temp->data;
            root->right=DELETE(root->right,temp->data);
            if(BalanceFactor(root) > 1){
                if(BalanceFactor(root->left) >= 0)//balance is in left since the height of parent is effect and case unbalance in left.
                    root=LL(root);
                else   
                    root=LR(root);
            }
        }
        else{
            TreeNode* temp=root->left;
            delete root;
            return temp;
        }
    }
    root->height=Height(root);
    return root;
}

bool Search(TreeNode* root,int data)
{
    if(root==NULL) return false;

    if(root->data==data)
        return true;
    if(data < root->data){
        return Search(root->left,data);
    }
    else if(data > root->data){
        return Search(root->right,data);
    }
    return false;
}
#include <iostream>

using namespace std;



struct tree
{
    int data;
    tree *left;
    tree *right;
};

 tree *new_n(int x)
{
    tree *tmp= new tree();
    tmp->data=x;
    tmp->left=tmp->right=NULL;
    return tmp;
}

 tree* inserty(int x,  tree* root)
{
    if(root==NULL)
    {
        return new_n(x);
    }

    if (x<root->data)
        root->left=inserty(x,root->left);
    else
        if(x>root->data)
        root->right=inserty(x,root->right);
    return root;
}

tree* searchy(int x, tree* root)
{
    if(root==NULL||root->data==x)
        return root;
    if(root->data<x)
        return searchy(x, root->right);
    return searchy(x, root->left);
}

void RSD(tree *root)
{
    if(root!=NULL)
    {
        RSD(root->left);

        cout<<root->data<<" ";

        RSD(root->right);
    }
}

void RDS(tree *root)
{
    if(root!=NULL)
    {
        RSD(root->right);

        cout<<root->data<<" ";

        RSD(root->left);
    }
}

void SDR(tree *root)
{
    if(root!=NULL)
    {
        RSD(root->left);

        RSD(root->right);

        cout<<root->data<<" ";
    }
}

int main()
{
     tree *r=new tree();
    r=NULL;
    r=inserty(44,r);
    inserty(77,r);
    inserty(88,r);
    inserty(22,r);
    inserty(11,r);
    inserty(33,r);
    inserty(99,r);

    SDR(r);

    return 0;
}

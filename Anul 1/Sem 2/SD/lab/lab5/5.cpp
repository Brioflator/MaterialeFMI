#include <bits/stdc++.h>

using namespace std;

int k1,k2;

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

void RSD(tree *root)
{
    if(root!=NULL)
    {
        RSD(root->left);

        cout<<root->data<<" ";

        RSD(root->right);
    }
}

void RSD_interval(tree *root)
{
    if(root!=NULL)
    {
        RSD_interval(root->left);
        if(root->data>=k1 && root->data<=k2)
            cout<<root->data<<" ";

        RSD_interval(root->right);
    }
}


//caut primul nod al carui valoare e intre cele 2 valori date: k1<x<k2
tree* LCA(tree* root)
{
    //exit case
    if(root==NULL) return NULL;

    //ambele valori sunt mai mici decat nodul curent, deci trebuie sa merg la stanga
    if(root->data>k1 && root->data>k2) return LCA(root->left);
    //ambele valori sunt mai mari decat nodul curent, deci trebuie sa merg la dreapta
    if(root->data<k1 && root->data<k2) return LCA(root->right);

    return root;
}

int main()
{
    k1=11;
    k2=99;
    if(k1>k2) swap(k1,k2);
     tree *r=new tree();
    r=NULL;
    r=inserty(44,r);
    inserty(66,r);
    inserty(88,r);
    inserty(22,r);
    inserty(11,r);
    inserty(99,r);

    cout<<LCA(r)->data;


    return 0;
}


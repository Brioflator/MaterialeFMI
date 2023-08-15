#include <bits/stdc++.h>

using namespace std;

int n;
vector <string > v;

struct tree
{
    string data;
    tree *left;
    tree *right;
};

 tree *new_n(string x)
{
    tree *tmp= new tree();
    tmp->data=x;
    tmp->left=tmp->right=NULL;
    n++;
    return tmp;
}

 tree* inserty(string x,  tree* root)
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

tree* searchy(string x, tree* root)
{
    if(root==NULL||root->data==x)
        return root;
    if(root->data<x)
        return searchy(x, root->right);
    return searchy(x, root->left);
}


void RSD_desc(tree *root)
{
    if(root!=NULL)
    {
        RSD_desc(root->left);

        n--;
        v[n]=root->data;

        RSD_desc(root->right);
    }
}



int main()
{
    int m;

     tree *r=new tree();
    r=NULL;
    string a;
    cin>>a;
    v.push_back(a);
    r=inserty(a,r);
    while(cin>>a)
    {
        if(a=="stop") break;
        inserty(a,r);
        v.push_back(a);
    }

    m=n;
    RSD_desc(r);
    for(int i=0;i<m;i++)
        cout<<v[i]<<endl;

    return 0;
}

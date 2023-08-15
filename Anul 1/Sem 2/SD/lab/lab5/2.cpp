
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

//ia cel mai din stanga element, cel mai mic din tot arborele
tree* min_val(tree* root)
{
    tree* crnt=root;
    while(crnt && crnt->left!=NULL)
        crnt=crnt->left;
    return crnt;
}

tree* del(tree* root, int x)
{
   if(root==NULL)
        return root;

    //
    if(x<root->data) root->left=del(root->left, x);
    else if(x>root->data) root->right=del(root->right, x);
    else
    {
        //e frunza
        if(root->left==NULL && root->right==NULL)
            return NULL;
        // are un fiu drept
        else if (root->left==NULL)
        {
            tree* tmp=root->right;
            free(root);
            return tmp;
        }
        // are un fiu stang
        else if (root->right==NULL)
        {
            tree* tmp=root->left;
            free(root);
            return tmp;
        }
        // are 2 fii
        // il iau pe cel mai mic din partea dreapta
        //  2
        // / \
        //1   4
        //   /
        //  3
        tree* aux= min_val(root->right);

        root->data=aux->data;

        root->right=del(root->right, aux->data);
    }
    return root;
}



int main()
{
     tree *r=new tree();
    r=NULL;
    r=inserty(44,r);
    inserty(66,r);
    inserty(88,r);
    inserty(22,r);
    inserty(11,r);
    inserty(33,r);
    inserty(99,r);

    RSD(r);
    del(r,33);
    cout<<endl;
    RSD(r);

    return 0;
}

#include<bits/stdc++.h>
#define N 4
//11 12 9 4 5 6 7 2 10 3 1 8
using namespace std;

int mid_point;



void split_point()
{
    if(N%2)
        mid_point = N/2+1;
    else
        mid_point = N/2;
}



struct treeNode
{
    int val[N];
    treeNode **child;
    bool leaf;
    int vals;
    treeNode *next;
    treeNode *prev;
    treeNode *parent;
}*root = NULL, *temp = NULL, *new_node = NULL, *dup = NULL, *tmp = NULL, *tmp2 = NULL;



treeNode* init()
{
    new_node = new treeNode;
    new_node->child = new treeNode *[N];
    new_node->leaf = true;
    new_node->vals = 0;
    new_node->next = NULL;
    new_node->prev = NULL;
    new_node->parent = NULL;

    for(int i = 0; i<N-1; i++)
        new_node->child[i] = NULL;

    new_node->child[N-1] = NULL;
    return new_node;
}



treeNode* find_node(int val)
{
    int f;
    temp = root;

    while(!temp->leaf)
    {
        f = 0;
        for(int i=0; i<temp->vals; i++)
        {
            if(temp->val[i]>val)
            {
                cout << "find = " << temp->val[i]<< endl;
                temp = temp->child[i];
                f = 1;
                break;
            }
        }
        if(f==0)
            temp = temp->child[temp->vals];
    }
    return temp;
}



void split_parent(treeNode* par, treeNode *child1, treeNode* child2, int val)
{
    int i, mid, j, flag = 0;
    treeNode *n1 = NULL, *n2 = NULL, *n3 = NULL;
    n1 = init();
    n2 = init();
    n1->leaf = n2->leaf = false;
    dup = par;
    dup->val[dup->vals] = val;
    sort(dup->val, dup->val+dup->vals+1);
    mid = dup->val[mid_point];

    if(val==mid)
    {
        for(i = 0; i < mid_point; i ++)
        {
            n1->val[n1->vals++] = par->val[i];
            n1->child[i] = par->child[i];
            par->child[i]->parent = n1;
        }

        n1->child[i++] = child1;
        child1->parent = n1;
        child2->parent = n2;
        n2->child[0] = child2;
        for(j = 0; i < N; i ++, j ++)
        {
            n2->val[n2->vals++] = par->val[i];
            n2->child[j+1] = par->child[i];
            par->child[i]->parent = n2;
        }
    }
    else
    {
        for(i = 0; i < mid_point; i ++)
        {
            n1->val[n1->vals++] = dup->val[i];
            if(dup->val[i]==val)
            {
                n1->child[i] = child1;
                dup->child[i+1] = child2;
                child1->parent = n1;
                child2->parent = n1;
            }
            else
            {
                n1->child[i] = dup->child[i];
                dup->child[i]->parent = n1;
            }
        }

        n1->child[i] = dup->child[i++];
        dup->child[i-1]->parent = n1;
        n2->child[0] = dup->child[i];
        dup->child[i]->parent = n2;

        for(j = 0; i < N; i ++, j ++)
        {
            n2->val[n2->vals++] = dup->val[i];

            if(dup->val[i]==val)
            {
                n2->child[j] = child1;
                n2->child[j+1] = child2;
                child1->parent = n2;
                child2->parent = n2;
            }
            else
            {
                n2->child[j+1] = dup->child[i];
                dup->child[i]->parent = n2;
            }
        }
    }

    if(par->prev!=NULL)
        par->prev->next = n1;

    if(par->next!=NULL)
        par->next->prev = n2;

    n1->next = n2;
    n1->prev = par->prev;
    n2->prev = n1;
    n2->next = par->next;

    if(par->parent == NULL)
    {
        n3 = init();
        n3->leaf = false;
        n3->val[n3->vals++] = mid;
        n1->parent = n2->parent = n3;
        n3->child[0] = n1;
        n3->child[1] = n2;
        root = n3;
    }
    else if(par->parent->vals < N-1)
    {
        n1->parent = n2->parent = par->parent;

        for(i = 0; i < N-1; i++)
        {
            if(i==par->parent->vals)
            {
                par->parent->child[i] = n1;
                par->parent->child[i+1] = n2;
                par->parent->val[i] = mid;
                par->parent->vals++;
                break;
            }
            if(par->parent->val[i] > mid)
            {
                for(j=N-2; j>=i; j--)
                {
                    par->parent->val[j] = par->parent->val[j-1];
                    par->parent->child[j+1] = par->parent->child[j];
                }
                par->parent->child[i] = n1;
                par->parent->child[i+1] = n2;
                par->parent->val[i] = mid;
                par->parent->vals++;
                break;
            }
        }
    }
    else
        split_parent(par->parent, n1, n2, mid);

    return;
}



void split_leaf(treeNode* n, int val)
{
    int i, mid, j;
    treeNode *n1 = NULL, *n2 = NULL, *n3 = NULL;
    n1 = init();
    n2 = init();
    n->val[n->vals] = val;
    sort(n->val, n->val+n->vals+1);
    mid = n->val[mid_point];

    for(i = 0; i < mid_point; i ++)
        n1->val[n1->vals++] = n->val[i];

    for(; i < N; i ++)
        n2->val[n2->vals++] = n->val[i];

    if(n->prev!=NULL)
        n->prev->next = n1;

    if(n->next!=NULL)
        n->next->prev = n2;

    n1->next = n2;
    n1->prev = n->prev;
    n2->prev = n1;
    n2->next = n->next;
    //if(n->parent != NULL)cout<<n->parent->val[0];
    if(n->parent == NULL)
    {
        n3 = init();
        n3->leaf = false;
        n3->val[n3->vals++] = mid;
        n1->parent = n2->parent = n3;
        n3->child[0] = n1;
        n3->child[1] = n2;
        root = n3;
        return;
    }
    else if(n->parent->vals < N-1)
    {

        n1->parent = n2->parent = n->parent;
        for(i = 0; i < N-1; i++)
        {
            if(i==n->parent->vals)
            {
                n->parent->child[i] = n1;
                n->parent->child[i+1] = n2;
                n->parent->val[i] = mid;
                n->parent->vals++;
                break;
            }
            if(n->parent->val[i] > mid)
            {
                for(j=N-2; j>=i; j--)
                {
                    n->parent->val[j] = n->parent->val[j-1];
                    n->parent->child[j+1] = n->parent->child[j];
                }
                n->parent->child[i] = n1;
                n->parent->child[i+1] = n2;
                n->parent->val[i] = mid;
                n->parent->vals++;
                break;
            }
        }
    }
    else
        split_parent(n->parent, n1, n2, mid);
    return;
}



void insertion(int val)
{
    if(root == NULL)
    {
        root = init();
        root->val[root->vals++] = val;
        return;
    }
    else
    {
        temp = find_node(val);

        if(temp->vals < N-1)
        {
            temp->val[temp->vals++] = val;
            sort(temp->val, temp->val+temp->vals);
        }
        else
            split_leaf(temp, val);

    }
}



void print()
{
    treeNode* print, *out;

    if(root==NULL)
    {
        cout<<"nothing to print"<<endl;
        return;
    }
    print = root;
    out = root;

    do{
        for(int i = 0; i< out->vals; i++)
            cout<<out->val[i]<<"|| ";

        cout<<'\b'<<'\b'<<"    ";
        out = out->next;
    }while(out!=NULL);
    cout<<endl;

    while(!print->leaf)
    {
        print = print->child[0];
        out = print;

        do{
            for(int i = 0; i< out->vals; i++)
                cout<<out->val[i]<<"| ";

            cout<<'\b'<<'\b'<<"    ";
            out = out->next;
        }while(out!=NULL);
        cout<<endl;
    }
}






int main()
{
    split_point();

    printf("1. insert\n");
    printf("2. print\n");
    printf("3. exit\n\n");

    int flag, value;

    while (scanf("%d", &flag) != EOF)
    {
        switch (flag)
        {
            case 1:
                cout<<"Enter Data for insertion: ";
                scanf("%d", &value);
                insertion(value);
                break;

            case 2:
                print();
                break;

            case 3:
                return 0;
                break;

            default:
                printf("Please enter correct one...\n");
        }

       printf("\n1. insert\n");
       printf("2. print\n");
       printf("3. exit\n\n");
    }

   return 0;
}

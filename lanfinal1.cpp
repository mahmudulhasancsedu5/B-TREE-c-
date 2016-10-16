#include<stdio.h>
#include<iostream>
#include <bits/stdc++.h>
using namespace std;
class Node
{   public:
    int num;
    int level;
    Node *parent;
    Node *ptr[4];
    string str[3];
    bool leaf;

};
Node *root=NULL;
queue <Node *> q;
void non_leaf_split(Node *p,string s);
Node *find(string s);
int level=1;
int found_position(Node *p,string s)
{   int i;
    if(s.compare(p->str[0])<0) return 0;
    for(i=0;i<p->num-1;i++)
    {
        if(s.compare(p->str[i])>0 && s.compare(p->str[i+1])<0) return i+1;
    }
    if(s.compare(p->str[i])>0) return i+1;

}
void leaf_split(Node *p,string s)
{
    Node *n=new Node();
    int i=found_position(p,s);
    string st[4];
    int j;
    for(j=0;j<3;j++)
    {
        st[j]=p->str[j];
        p->str[j]="";
    }
    for(j=3;j>i;j--)
    {
        st[j]=st[j-1];
    }
    st[j]=s;

    for(j=0;j<2;j++)
    {
        p->str[j]=st[j];
        n->str[j]=st[j+2];
    }
    p->num=n->num=2;
    n->leaf=true;
    n->ptr[3]=p->ptr[3];
    p->ptr[3]=n;
    n->parent=p->parent;
    if(p==root)
    {
        Node *n1=new Node();
        n1->leaf=false;
        p->leaf=true;
        n1->num=1;
        n1->str[0]=st[2];
        n1->ptr[0]=p;
        n1->ptr[1]=n;
        root=n1;
        n->parent=p->parent=root;
    }
    else
    {
        if(p->parent->num<3)
        {
            i=found_position(p->parent,st[2]);
            for(j=3;j>i+1;j--) {p->parent->ptr[j]=p->parent->ptr[j-1]; p->parent->str[j-1]=p->parent->str[j-2];}
            p->parent->num+=1;
            p->parent->ptr[i+1]=n;
            p->parent->str[i]=st[2];
        }
        else
        {
            non_leaf_split(n,st[2]);
        }
    }
}
void non_leaf_split(Node *p,string s)
{
    Node *n=new Node();
    Node *n1=new Node();
    int i=found_position(p->parent,s);
    string st[4];
    Node *pt[5];
    int j;
    for(j=0;j<3;j++)
    {
        st[j]=p->parent->str[j];
        p->parent->str[j]="";
        pt[j]=p->parent->ptr[j];
        p->parent->ptr[j]=NULL;
    }
    pt[j]=p->parent->ptr[j];
    p->parent->ptr[j]=NULL;
    for(j=3;j>i;j--)
    {
        st[j]=st[j-1];
        pt[j+1]=pt[j];
    }
    pt[j+1]=p;
    st[j]=s;

    if(p->parent!=root)
    {
        for(j=0;j<2;j++)
        {
            p->parent->str[j]=st[j];
            p->parent->ptr[j]=pt[j];
            n->ptr[j]=pt[j+3];
        }
        p->parent->ptr[j]=pt[j];
        n->str[0]=st[3];
        p->parent->num=2;
        n->num=1;
        n->leaf=false;
        n->parent=p->parent->parent;
        for(int i=0;i<n->num+1;i++)
        {
            n->ptr[i]->parent=n;
        }
        if(p->parent->parent->num<3)
        {
            i=found_position(p->parent->parent,st[2]);
            for(j=3;j>i+1;j--)
            {
                p->parent->parent->ptr[j]=p->parent->parent->ptr[j-1];
                p->parent->parent->str[j-1]=p->parent->parent->str[j-2];
            }
            p->parent->parent->num+=1;
            p->parent->parent->ptr[i+1]=n;
            p->parent->parent->str[i]=st[2];
        }
        else
        {
            non_leaf_split(n,st[2]);
        }
    }
    else
    {
        for(j=0;j<2;j++)
        {
            n->str[j]=st[j];
            n->ptr[j]=pt[j];
            n1->ptr[j]=pt[j+3];
        }
        n1->str[0]=st[3];
        n->ptr[2]=pt[2];
        n1->num=1;
        n->num=2;
        n1->leaf=n->leaf=false;
        n1->parent=n->parent=p->parent;
        p->parent->str[0]=st[2];
        p->parent->ptr[0]=n;
        p->parent->ptr[1]=n1;
        p->parent->num=1;
        for(int i=0;i<n->num+1;i++)
        {
            n->ptr[i]->parent=n;
        }
        for(int i=0;i<n1->num+1;i++)
        {
            n1->ptr[i]->parent=n1;
        }
    }
}
void pri()
{
    q.push(root);
    root->level=1;
    Node *n;
    cout<<"       ";
    while(!q.empty())
    {
        n=q.front();
        q.pop();
        int i;
        if(level!=n->level) {cout<<endl<<endl<<endl;level=n->level;}
        else if(n->leaf && n!=root) cout<<"||";
        else if(n!=root) cout<<" || ";
        //cout<<n->num;
        for(i=0;i<n->num+1;i++)
        {
            if(i<n->num) cout<<n->str[i]<<"   ";
            //if(n->ptr[i]==NULL) cout<<"yes"<<endl;
            if(n->leaf==false)
            {
                n->ptr[i]->level=n->level+1;
                q.push(n->ptr[i]);
            }
        }
    }
}
void insert(string s)
{   if(root && find(s))
    {
        Node *n=find(s);
        int i;
        Node *p=new Node();
        for(i=0;i<n->num;i++)
        {
            if(s==n->str[i]) break;
        }

    }
    if(!root)
    {
        root=new Node();
        root->leaf=true;
        root->num=1;
        root->parent=NULL;
        root->str[0]=s;
    }
    else
    {
        if(root->ptr[0]==NULL)
        {
            if(root->num<3)
            {   int i=found_position(root,s);
                for(int j=root->num;j>i;j--)
                {
                    root->str[j]=root->str[j-1];
                }
                root->str[i]=s;
                root->num+=1;
            }
            else
            {
                leaf_split(root,s);
            }
        }
        else
        {
            Node *n;
            int i=found_position(root,s);
            n=root->ptr[i];
            for(;n->leaf!=true;)
            {
                n=n->ptr[found_position(n,s)];
            }
            i=found_position(n,s);
            if(n->num<3)
            {
                for(int j=n->num;j>i;j--)
                {
                    n->str[j]=n->str[j-1];
                }
                n->str[i]=s;
                n->num+=1;
            }
            else
            {
                leaf_split(n,s);
            }
        }
    }
}
Node *find(string s)
{
    Node *n=root;
    for(int i=0;i<level-1;i++) n=n->ptr[0];
    int flag=0;
    for(;;n=n->ptr[3])
    {
        for(int i=0;i<n->num;i++)
        {
            if(n->str[i]==s) flag=1;
        }
        if(flag) break;
        else if(n->ptr[3]==NULL) break;
    }
    if(flag==0) n=NULL;
    return n;
}
void merge_redes(Node *n)
{  Node *p=n->parent;
    cout<<"call\n";
   if(n->leaf)
   {    int i,j,k;
        //found position in parent ptr
        //cout<<"saeed\n";

        for(i=0;i<p->num+1;i++) if(p->ptr[i]==n) break;
        if(i==0) k=1;
        else k=0;
        if(p==root && p->num==1 && p->ptr[k]->num<3)
        {   cout<<"yes";
            if(i==0)
            {
                p->ptr[0]->str[1]=p->ptr[1]->str[0];
                p->ptr[0]->str[2]=p->ptr[1]->str[1];
                p->ptr[0]->num+=2;
                root=p->ptr[0];
            }
            else
            {
                p->ptr[0]->str[2]=p->ptr[1]->str[0];
                p->ptr[0]->num+=1;
                root=p->ptr[0];
            }
        }
        else if(i==0)
        {
            if(p->ptr[i+1]->num<3)
            {   //correct
                p->ptr[i]->str[1]=p->ptr[i+1]->str[0];
                p->ptr[i]->str[2]=p->ptr[i+1]->str[1];
                p->ptr[i]->num+=2;
                p->ptr[i]->ptr[3]=p->ptr[i+1]->ptr[3];

                int j;
                for(j=0;j<p->num-1;j++)
                {
                    p->str[j]=p->str[j+1];
                    p->ptr[j+1]=p->ptr[j+2];
                }
                p->ptr[j+1]=NULL;
                p->str[j]="";
                p->num-=1;

                if(p->num==0) merge_redes(p);
            }
            else
            {
                p->ptr[i]->str[1]=p->ptr[i+1]->str[0];
                p->ptr[i]->num+=1;
                p->ptr[i+1]->str[0]=p->ptr[i+1]->str[1];
                p->ptr[i+1]->str[1]=p->ptr[i+1]->str[2];
                p->ptr[i+1]->num-=1;
                p->str[i]=p->ptr[i+1]->str[0];
            }
        }
        else if(i==p->num)
        {
            if(p->ptr[i-1]->num<3)
            {
                p->ptr[i-1]->str[2]=p->ptr[i]->str[0];
                p->ptr[i-1]->num+=1;
                p->ptr[i-1]->ptr[3]=p->ptr[i]->ptr[3];
                p->ptr[i]=NULL;
                p->str[i-1]="";
                p->num-=1;
                //may be rec call

                if(p->num==0) merge_redes(p);
            }
            else
            {
                p->ptr[i]->str[1]=p->ptr[i]->str[0];
                p->ptr[i]->str[0]=p->ptr[i-1]->str[2];
                p->ptr[i-1]->str[2]="";
                p->ptr[i]->num+=1;
                p->ptr[i-1]->num-=1;
                p->str[i-1]=p->ptr[i]->str[0];
            }
        }
        else
        {   //cout<<"\n"<<i<<p->num;
            if(p->ptr[i-1]->num<3)
            {
                p->ptr[i-1]->str[2]=p->ptr[i]->str[0];
                p->ptr[i-1]->num+=1;
                p->ptr[i-1]->ptr[3]=p->ptr[i]->ptr[3];
                //p->ptr[i]=NULL;
                int j;
                for(j=i;j<p->num;j++)
                {
                    p->str[j-1]=p->str[j];
                    p->ptr[j]=p->ptr[j+1];
                }
                p->ptr[j]=NULL;
                p->str[j-1]="";
                p->num-=1;

                if(p->num==0) merge_redes(p);

            }
            else if(p->ptr[i+1]->num<3)
            {
                p->ptr[i]->str[1]=p->ptr[i+1]->str[0];
                p->ptr[i]->str[2]=p->ptr[i+1]->str[1];
                p->ptr[i]->num+=2;
                p->ptr[i]->ptr[3]=p->ptr[i+1]->ptr[3];
                int j;
                for(j=i;j<p->num-1;j++)
                {
                    p->str[j]=p->str[j+1];
                    p->ptr[j+1]=p->ptr[j+2];
                }
                p->ptr[j+1]=NULL;
                p->str[j]="";
                p->num-=1;
                if(p->num==0) merge_redes(p);
            }
            else
            {
                p->ptr[i]->str[1]=p->ptr[i]->str[0];
                p->ptr[i]->str[0]=p->ptr[i-1]->str[2];
                p->ptr[i-1]->str[2]="";
                p->ptr[i]->num+=1;
                p->ptr[i-1]->num-=1;
                p->str[i-1]=p->ptr[i]->str[0];
            }
        }
   }
   else
   {
       Node *p=n->parent;
        int i,j,k;
        for(i=0;i<p->num+1;i++) if(p->ptr[i]==n) {break;}

        if(p==root && p->num==1)
        {
            if(i==1) j=0;
            else j=1;

            if(p->ptr[j]->num<3)
            {   if(j==0)
                {
                    p->ptr[j]->str[p->ptr[j]->num]=p->str[0];
                    p->ptr[j]->ptr[p->ptr[j]->num+1]=p->ptr[i]->ptr[0];
                    p->ptr[i]->ptr[0]->parent= p->ptr[j];
                    p->ptr[j]->num+=1;
                    p->ptr[j]->parent=NULL;
                    root=p->ptr[j];
                }
                else
                {
                    p->ptr[i]->str[0]=p->str[0];
                    p->ptr[i]->num+=1;

                    for(k=1;k<p->ptr[j]->num+1;k++)
                    {
                        p->ptr[i]->str[k]=p->ptr[j]->str[k-1];
                        p->ptr[i]->ptr[k]=p->ptr[j]->ptr[k-1];
                        p->ptr[i]->ptr[k]->parent=p->ptr[i];
                        p->ptr[i]->num+=1;
                    }
                    p->ptr[i]->ptr[k]=p->ptr[j]->ptr[k-1];
                    p->ptr[i]->ptr[k]->parent=p->ptr[i];
                    p->ptr[i]->parent=NULL;
                    root=p->ptr[i];
                }
            }
            else
            {
                p->ptr[i]->ptr[1]=p->ptr[i]->ptr[0];
                p->ptr[i]->ptr[0]=p->ptr[j]->ptr[3];
                p->ptr[j]->ptr[3]->parent=p->ptr[i];
                p->ptr[i]->str[0]=p->str[0];
                p->str[0]=p->ptr[j]->str[2];
                p->ptr[j]->ptr[3]=NULL;
                p->ptr[j]->str[2]="";
                p->ptr[i]->num+=1;
                p->ptr[j]->num-=1;

            }
        }
        else
        {
            if(i==0)
            {
                if(p->ptr[i+1]->num<3)
                {
                    for(j=0,k=1;j<p->ptr[i+1]->num;j++,k++)
                    {
                        p->ptr[i]->str[k]=p->ptr[i+1]->str[j];
                        p->ptr[i]->ptr[k]=p->ptr[i+1]->ptr[j];
                        p->ptr[i+1]->ptr[j]->parent=n;
                        p->ptr[i]->num+=1;
                    }

                    p->ptr[i]->ptr[k]=p->ptr[i+1]->ptr[j];
                    p->ptr[i+1]->ptr[j]->parent=n;
                    p->ptr[i]->num+=1;
                    p->ptr[i]->str[0]=p->str[0];

                    for(j=0;j<p->num-1;j++)
                    {
                        p->str[j]=p->str[j+1];
                        p->ptr[j+1]=p->ptr[j+2];
                    }
                    //cout<<j;
                    p->ptr[j+1]=NULL;

                    p->str[j]="";

                    p->num-=1;
                    if(p->num==0) merge_redes(p);
                }
                else
                {
                    p->ptr[i]->str[0]=p->ptr[i+1]->str[0];
                    p->ptr[i]->num+=1;
                    p->ptr[i]->ptr[1]=p->ptr[i+1]->ptr[1];
                    p->ptr[i+1]->ptr[1]->parent=n;
                    for(j=0;j<p->ptr[i+1]->num-1;j++)
                    {
                        p->ptr[i+1]->str[j]=p->ptr[i+1]->str[j+1];
                        p->ptr[i+1]->ptr[j]=p->ptr[i+1]->ptr[j+1];
                    }
                    p->ptr[i+1]->str[j+1]="";
                    p->ptr[i+1]->ptr[j+1]=p->ptr[i+1]->ptr[j+2];
                    p->ptr[i+1]->ptr[j+2]=NULL;
                    p->ptr[i+1]->num-=1;
                    p->str[i]=p->ptr[i+1]->str[0];
                }
            }
            else if(i==p->num)
            {
                if(p->ptr[i-1]->num<3)
                {   //correct
                    p->ptr[i-1]->str[p->ptr[i-1]->num]=p->str[i-1];
                    p->ptr[i-1]->ptr[p->ptr[i-1]->num+1]=p->ptr[i]->ptr[0];
                    p->ptr[i]->ptr[0]->parent=p->ptr[i-1];
                    p->ptr[i-1]->num+=1;

                    p->num-=1;
                    p->ptr[i]=NULL;
                    p->str[i-1]="";

                    if(p->num==0) merge_redes(p);
                }
                else
                {
                    p->ptr[i]->str[0]=p->ptr[i-1]->str[2];
                    p->ptr[i-1]->str[2]="";
                    p->ptr[i]->ptr[1]=p->ptr[i-1]->ptr[3];
                    p->ptr[i-1]->ptr[3]->parent=n;
                    p->ptr[i-1]->ptr[3]=NULL;
                    p->ptr[i]->num+=1;
                    p->ptr[i-1]->num-=1;
                    p->str[i-1]=p->ptr[i]->str[0];
                }
            }
            else
            {
                if(p->ptr[i-1]->num<3)
                {   //correct
                    //cout<<"sayed\n";
                    p->ptr[i-1]->str[p->ptr[i-1]->num]=p->str[i-1];

                    //cout<<p->ptr[i]->ptr[0]->num;
                    //cout<<p->ptr[i-1]->num;
                    p->ptr[i-1]->ptr[p->ptr[i-1]->num+1]=p->ptr[i]->ptr[0];
                    p->ptr[i]->ptr[0]->parent=p->ptr[i-1];
                    p->ptr[i]->ptr[0]=NULL;
                    //cout<<p->ptr[i-1]->ptr[2]->num;
                    p->ptr[i-1]->num+=1;
                    for(j=i;j<p->num;j++)
                    {
                        p->str[j-1]=p->str[j];
                        p->ptr[j]=p->ptr[j+1];
                    }
                    p->ptr[j]=NULL;
                    p->str[j-1]="";
                    p->num-=1;
                    //cout<<p->ptr[i-1]->num;
                    //cout<<endl;
                    //for(int l=0;l<p->ptr[i-1]->num+1;l++) cout<<p->ptr[i-1]->ptr[l]->str[0]<<endl;
                    if(p->num==0) merge_redes(p);

                }
                else if(p->ptr[i+1]->num<3)
                {   //corr
                    for(j=0,k=1;j<p->ptr[i+1]->num;j++,k++)
                    {
                        p->ptr[i]->str[k]=p->ptr[i+1]->str[j];
                        p->ptr[i]->ptr[k]=p->ptr[i+1]->ptr[j];
                        p->ptr[i+1]->ptr[j]->parent=n;
                        p->ptr[i]->num+=1;
                    }

                    p->ptr[i]->ptr[k]=p->ptr[i+1]->ptr[j];
                    p->ptr[i+1]->ptr[j]->parent=n;
                    p->ptr[i]->num+=1;
                    p->ptr[i]->str[0]=p->str[i];

                    for(j=i;j<p->num-1;j++)
                    {
                        p->str[j]=p->str[j+1];
                        p->ptr[j+1]=p->ptr[j+2];
                    }

                    p->ptr[j+1]=NULL;
                    //cout<<"sayed\n";
                    p->str[j]="";
                    //cout<<"sayed\n";
                    p->num-=1;

                    if(p->num==0) merge_redes(p);
                }
                else
                {
                    p->ptr[i]->str[0]=p->ptr[i-1]->str[2];
                    p->ptr[i-1]->str[2]="";
                    p->ptr[i]->ptr[1]=p->ptr[i-1]->ptr[3];
                    p->ptr[i-1]->ptr[3]->parent=n;
                    p->ptr[i-1]->ptr[3]=NULL;
                    p->ptr[i]->num+=1;
                    p->ptr[i-1]->num-=1;
                    p->str[i-1]=p->ptr[i]->str[0];
                }
            }
        }
    }
}
void deletes(string s)
{
    Node *n=find(s);
    if(n==NULL)
    {
        cout<<"No Such key ..Try Again.."<<endl;
    }
    else
    {
        for(int i=0;i<n->num;i++)
        {
            if(n->str[i]==s)
            {   n->str[i]="";
                n->num=n->num-1;
                for(int j=i;j<n->num;j++)
                {
                    n->str[j]=n->str[j+1];
                }
                break;
            }
        }
        if(n->num==1 && n!=root) merge_redes(n);
    }
}
int main()
{   int i;
    string s;
    while(true)
    {
        cout<<"Press 1 for insert"<<endl;
        cout<<"Press 2 for delete"<<endl;
        cin>>i;
        cin>>s;
        if(i==1) insert(s);
        else if(i==2) deletes(s);
        cout<<"B+ TREE  : "<<endl<<endl;
        pri();
        cout<<endl<<endl<<endl;
    }
    return 0;
}

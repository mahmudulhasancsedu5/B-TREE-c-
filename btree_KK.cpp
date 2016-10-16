#include<stdio.h>



#include<iostream>
#define MAX 4

using namespace std;

struct B_TreeNode

{

    int *data;

    B_TreeNode **child_ptr;

    bool leaf;

    int n;

}*root = NULL, *np = NULL, *x = NULL;

B_TreeNode * init()

{

    int i;

    np = new B_TreeNode;

    np->data = new int[MAX];

    np->child_ptr = new B_TreeNode *[6];

    np->leaf = true;

    np->n = 0;

    for (i = 0; i <= MAX; i++)

    {

        np->child_ptr[i] = NULL;

    }

    return np;

}

void traverse(B_TreeNode *p)

{

    cout<<endl;


    for (int i = 0; i < p->n; i++)

    {
        cout << " " << p->data[i];
    }
    for (int i = 0; i <= p->n; i++)

    {

        if (p->leaf == false)

        {

            traverse(p->child_ptr[i]);

        }
    }



    cout<<endl;

}

void sort(int *p, int n)

{

    int i, j, temp;

    for (i = 0; i < n; i++)

    {

        for (j = i; j <= n; j++)

        {

            if (p[i] > p[j])

            {

                temp = p[i];

                p[i] = p[j];

                p[j] = temp;

            }

        }

    }

}

int split_child(B_TreeNode *x, int i)

{

    int j, mid;

    B_TreeNode *np1, *np3, *y;

    np3 = init();

    np3->leaf = true;

    if (i == -1)

    {

        mid = x->data[MAX/2];

        //x->data[MAX/2] = 0;

        //x->n--;

        np1 = init();

        np1->leaf = false;

        x->leaf = true;

        for (j = MAX/2; j < MAX; j++)

        {

            np3->data[j - MAX/2] = x->data[j];

            np3->child_ptr[j - MAX/2] = x->child_ptr[j];

            np3->n++;

            x->data[j] = 0;

            x->n--;

        }


        for(j = 0; j < 6; j++)

        {

            x->child_ptr[j] = NULL;

        }

        np1->data[0] = mid;

        np1->child_ptr[np1->n] = x;

        np1->child_ptr[np1->n + 1] = np3;

        np1->n++;

        root = np1;

    }

    else

    {

        y = x->child_ptr[i];

        mid = y->data[MAX/2];

//        y->data[MAX/2] = 0;
//
//        y->n--;

        for (j = MAX/2; j < MAX; j++)

        {

            np3->data[j - MAX/2] = y->data[j];

            np3->n++;

            y->data[j] = 0;

            y->n--;

        }

        x->child_ptr[i] = y;

        x->child_ptr[i + 1] = np3;
        //printf("non leaf\n");

    }

    return mid;

}

void insert(int a)

{

    int i, temp;

    x = root;

    if (x == NULL)

    {

        root = init();

        x = root;

    }

    else

    {

        if (x->leaf == true && x->n == MAX)

        {

            temp = split_child(x, -1);

            x = root;

            for (i = 0; i < (x->n); i++)

            {

                if ((a > x->data[i]) && (a < x->data[i + 1]))

                {

                    i++;

                    break;

                }

                else if (a < x->data[0]) break;
            }

            x = x->child_ptr[i];

        }

        else

        {

            while (x->leaf == false)

            {

            for (i = 0; i < (x->n); i++)

            {

                if ((a > x->data[i]) && (a < x->data[i + 1]))

                {

                    i++;

                    break;

                }

                else if (a < x->data[0])

                {

                    break;

                }


            }

                if ((x->child_ptr[i])->n == MAX)

                {

                    temp = split_child(x, i);

                    x->data[x->n] = temp;

                    x->n++;

                    continue;

                }

                else

                {

                    x = x->child_ptr[i];

                }

            }

        }

    }

    x->data[x->n] = a;

    sort(x->data, x->n);

    x->n++;

}

int main()

{

    int i, n, t;

    cout<<"enter the no of elements to be inserted\n";

    cin>>n;

    for(i = 0; i < n; i++)

    {

        cout<<"enter the element\n";

        cin>>t;

        insert(t);

    }

    cout<<"traversal of constructed tree\n";

    traverse(root);


}

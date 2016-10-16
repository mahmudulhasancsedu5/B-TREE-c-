#include<bits/stdc++.h>

using namespace std;

int main(){

    char* str[4];
    char strt[100]="mama";
    str[0]="mama";
    str[1]="kaka";
    str[2]="nana";
    str[3]="dada";
    list<string>li;
    for(int i=0;i<4;i++){

        li.push_back(str[i]);
    }
    li.sort();

    for(int i=0;i<4;i++){

            string strs=li.front();
            str[i]=(char*)strs.c_str();
        cout << str[i] << endl;
        li.pop_front();

    }

    return 0;
}

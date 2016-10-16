#include<bits/stdc++.h>
using namespace std;

#define MAX 50
int numberOfPointers;

struct Block{
    int tNodes;
    Block *parentBlock;
    int value[MAX];
    Block *childBlock[MAX];
    Block(){
        tNodes = 0;
        parentBlock = NULL;
        for(int i=0; i<MAX; i++){
            value[i] = INT_MAX;
            childBlock[i] = NULL;
        }
    }
};
Block *rootBlock = new Block();

void splitLeaf(Block *curBlock){
    int x, i, j;
    if(numberOfPointers%2)
        x = (numberOfPointers+1)/2;
    else x = numberOfPointers/2;
    Block *rightBlock = new Block();
    curBlock->tNodes = x;
    rightBlock->tNodes = numberOfPointers-x;
    rightBlock->parentBlock = curBlock->parentBlock;

    for(i=x, j=0; i<numberOfPointers; i++, j++){
        rightBlock->value[j] = curBlock->value[i];
        curBlock->value[i] = INT_MAX;
    }
    int val = rightBlock->value[0];
    if(curBlock->parentBlock==NULL){
        Block *parentBlock = new Block();
        parentBlock->parentBlock = NULL;
        parentBlock->tNodes=1;
        parentBlock->value[0] = val;
        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;
        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;
        rootBlock = parentBlock;
        return;
    }
    else
    {
        curBlock = curBlock->parentBlock;

        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;

        for(i=0; i<=curBlock->tNodes; i++){
            if(val < curBlock->value[i]){
                swap(curBlock->value[i], val);
            }
        }
        curBlock->tNodes++;

        for(i=0; i<curBlock->tNodes; i++){
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0]){
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;

        for(i=0;curBlock->childBlock[i]!=NULL;i++){
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }

}

void splitNonLeaf(Block *curBlock){
    int x, i, j;


    x = numberOfPointers/2;
    Block *rightBlock = new Block();

    curBlock->tNodes = x;
    rightBlock->tNodes = numberOfPointers-x-1;
    rightBlock->parentBlock = curBlock->parentBlock;


    for(i=x, j=0; i<=numberOfPointers; i++, j++){
        rightBlock->value[j] = curBlock->value[i];
        rightBlock->childBlock[j] = curBlock->childBlock[i];
        curBlock->value[i] = INT_MAX;
        if(i!=x)curBlock->childBlock[i] = NULL;
    }


    int val = rightBlock->value[0];
    memcpy(&rightBlock->value, &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
    memcpy(&rightBlock->childBlock, &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));

    for(i=0;curBlock->childBlock[i]!=NULL;i++){
        curBlock->childBlock[i]->parentBlock = curBlock;
    }
    for(i=0;rightBlock->childBlock[i]!=NULL;i++){
        rightBlock->childBlock[i]->parentBlock = rightBlock;
    }

    if(curBlock->parentBlock==NULL){
        Block *parentBlock = new Block();
        parentBlock->parentBlock = NULL;
        parentBlock->tNodes=1;
        parentBlock->value[0] = val;
        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;
        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;
        rootBlock = parentBlock;
        return;
    }
    else{

        curBlock = curBlock->parentBlock;


        Block *newChildBlock = new Block();
        newChildBlock = rightBlock;



        for(i=0; i<=curBlock->tNodes; i++){
            if(val < curBlock->value[i]){
                swap(curBlock->value[i], val);
            }
        }

        curBlock->tNodes++;

        for(i=0; i<curBlock->tNodes; i++){
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0]){
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;

         for(i=0;curBlock->childBlock[i]!=NULL;i++){
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }

}

void insertNode(Block *curBlock, int val){

    for(int i=0; i<=curBlock->tNodes; i++){
        if(val < curBlock->value[i] && curBlock->childBlock[i]!=NULL){
            insertNode(curBlock->childBlock[i], val);
            if(curBlock->tNodes==numberOfPointers)
                splitNonLeaf(curBlock);
            return;
        }
        else if(val < curBlock->value[i] && curBlock->childBlock[i]==NULL){
            swap(curBlock->value[i], val);
            if(i==curBlock->tNodes){
                    curBlock->tNodes++;
                    break;
            }
        }
    }

    if(curBlock->tNodes==numberOfPointers){

            splitLeaf(curBlock);
    }
}


void redistributeBlock(Block *leftBlock, Block *rightBlock, bool isLeaf, int posOfLeftBlock, int whichOneisCurBlock){


    int PrevRightFirstVal = rightBlock->value[0];


    if(whichOneisCurBlock==0){

        if(!isLeaf){
            leftBlock->value[leftBlock->tNodes] = leftBlock->parentBlock->value[posOfLeftBlock];
            leftBlock->childBlock[leftBlock->tNodes+1] = rightBlock->childBlock[0];
            leftBlock->tNodes++;
            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
            memcpy(&rightBlock->value[0], &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->childBlock[0], &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));
            rightBlock->tNodes--;

        }else
        {
            leftBlock->value[leftBlock->tNodes] = rightBlock->value[0];
            leftBlock->tNodes++;
            memcpy(&rightBlock->value[0], &rightBlock->value[1], sizeof(int)*(rightBlock->tNodes+1));
            rightBlock->tNodes--;

            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
        }



    }
    else
    {

        if(!isLeaf){

            memcpy(&rightBlock->value[1], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
            memcpy(&rightBlock->childBlock[1], &rightBlock->childBlock[0], sizeof(rootBlock)*(rightBlock->tNodes+1));
            rightBlock->value[0] = leftBlock->parentBlock->value[posOfLeftBlock];
            rightBlock->childBlock[0] = leftBlock->childBlock[leftBlock->tNodes];

            rightBlock->tNodes++;

            leftBlock->parentBlock->value[posOfLeftBlock] = leftBlock->value[leftBlock->tNodes-1];
            leftBlock->value[leftBlock->tNodes-1] = INT_MAX;
            leftBlock->childBlock[leftBlock->tNodes] = NULL;
            leftBlock->tNodes--;

        }else{

            memcpy(&rightBlock->value[1], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
            rightBlock->value[0] = leftBlock->value[leftBlock->tNodes-1];
            rightBlock->tNodes++;

            leftBlock->value[leftBlock->tNodes-1] = INT_MAX;
            leftBlock->tNodes--;

            leftBlock->parentBlock->value[posOfLeftBlock] = rightBlock->value[0];
        }
    }
}

void mergeBlock(Block *leftBlock, Block *rightBlock, bool isLeaf, int posOfRightBlock){

    if(!isLeaf){

        leftBlock->value[leftBlock->tNodes] = leftBlock->parentBlock->value[posOfRightBlock-1];
        leftBlock->tNodes++;
    }

    memcpy(&leftBlock->value[leftBlock->tNodes], &rightBlock->value[0], sizeof(int)*(rightBlock->tNodes+1));
    memcpy(&leftBlock->childBlock[leftBlock->tNodes], &rightBlock->childBlock[0], sizeof(rootBlock)*(rightBlock->tNodes+1));


    leftBlock->tNodes += rightBlock->tNodes;


    memcpy(&leftBlock->parentBlock->value[posOfRightBlock-1], &leftBlock->parentBlock->value[posOfRightBlock], sizeof(int)*(leftBlock->parentBlock->tNodes+1));
    memcpy(&leftBlock->parentBlock->childBlock[posOfRightBlock], &leftBlock->parentBlock->childBlock[posOfRightBlock+1], sizeof(rootBlock)*(leftBlock->parentBlock->tNodes+1));
    leftBlock->parentBlock->tNodes--;

    for(int i=0;leftBlock->childBlock[i]!=NULL;i++){
        leftBlock->childBlock[i]->parentBlock = leftBlock;
    }



}
bool dataFound;
void deleteNode(Block *curBlock, int val, int curBlockPosition){

     bool isLeaf;
     if(curBlock->childBlock[0]==NULL)
        isLeaf = true;
     else isLeaf = false;

    int prevLeftMostVal = curBlock->value[0];



     for(int i=0;dataFound==false &&  i<=curBlock->tNodes; i++){
        if(val < curBlock->value[i] && curBlock->childBlock[i] != NULL){
            deleteNode(curBlock->childBlock[i], val, i);

        }
        else if(val == curBlock->value[i] && curBlock->childBlock[i] == NULL){

            memcpy(&curBlock->value[i], &curBlock->value[i+1], sizeof(int)*(curBlock->tNodes+1));
            curBlock->tNodes--;
            dataFound = true;
            break;
        }
     }

     if(curBlock->parentBlock == NULL && curBlock->childBlock[0] == NULL){
        return;
     }


    if(curBlock->parentBlock==NULL && curBlock->childBlock[0] != NULL && curBlock->tNodes == 0){
        rootBlock = curBlock->childBlock[0];
        rootBlock->parentBlock = NULL;
        return;
    }


    if(isLeaf && curBlock->parentBlock!=NULL){

        if(curBlockPosition==0){
            Block *rightBlock = new Block();
            rightBlock = curBlock->parentBlock->childBlock[1];

            if(rightBlock!=NULL && rightBlock->tNodes > (numberOfPointers+1)/2){

                    redistributeBlock(curBlock, rightBlock, isLeaf, 0, 0);
            }
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers){

                    mergeBlock(curBlock, rightBlock, isLeaf, 1);
            }
        }

        else{


            Block *leftBlock = new Block();
            Block *rightBlock = new Block();


            leftBlock = curBlock->parentBlock->childBlock[curBlockPosition-1];

            rightBlock = curBlock->parentBlock->childBlock[curBlockPosition+1];


            if(leftBlock!=NULL && leftBlock->tNodes > (numberOfPointers+1)/2){
                 redistributeBlock(leftBlock, curBlock, isLeaf, curBlockPosition-1, 1);
            }
            else if(rightBlock!=NULL && rightBlock->tNodes > (numberOfPointers+1)/2){
                redistributeBlock(curBlock, rightBlock, isLeaf, curBlockPosition, 0);
            }
            else if (leftBlock!=NULL && curBlock->tNodes+leftBlock->tNodes < numberOfPointers){
                mergeBlock(leftBlock, curBlock, isLeaf, curBlockPosition);
            }
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers){
               mergeBlock(curBlock, rightBlock, isLeaf, curBlockPosition+1);
            }
        }
    }
    else if(!isLeaf && curBlock->parentBlock!=NULL){

        if(curBlockPosition==0){
            Block *rightBlock = new Block();
            rightBlock = curBlock->parentBlock->childBlock[1];

            if( rightBlock!=NULL && rightBlock->tNodes-1 >= ceil((numberOfPointers-1)/2) ){
                redistributeBlock(curBlock, rightBlock, isLeaf, 0, 0);
            }
            else if (rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers - 1){
                mergeBlock(curBlock, rightBlock, isLeaf, 1);
            }
        }
        else{


            Block *leftBlock = new Block();
            Block *rightBlock = new Block();


            leftBlock = curBlock->parentBlock->childBlock[curBlockPosition-1];

            rightBlock = curBlock->parentBlock->childBlock[curBlockPosition+1];


            if( leftBlock!=NULL && leftBlock->tNodes-1 >= ceil((numberOfPointers-1)/2)){
                 redistributeBlock(leftBlock, curBlock, isLeaf, curBlockPosition-1, 1);
            }
            else if(rightBlock!=NULL && rightBlock->tNodes-1 >=  ceil((numberOfPointers-1)/2)){
                redistributeBlock(curBlock, rightBlock, isLeaf, curBlockPosition, 0);
            }

            else if ( leftBlock!=NULL && curBlock->tNodes+leftBlock->tNodes < numberOfPointers-1) {
                mergeBlock(leftBlock, curBlock, isLeaf, curBlockPosition);
            }
            else if ( rightBlock!=NULL && curBlock->tNodes+rightBlock->tNodes < numberOfPointers-1){
               mergeBlock(curBlock, rightBlock, isLeaf, curBlockPosition+1);
            }
        }

    }



    Block *tempBlock = new Block();
    tempBlock = curBlock->parentBlock;
    while(tempBlock!=NULL){
            for(int i=0; i<tempBlock->tNodes;i++){
                if(tempBlock->value[i]==prevLeftMostVal){
                    tempBlock->value[i] = curBlock->value[0];
                    break;
                }
        }
        tempBlock = tempBlock->parentBlock;
    }

}

void print(vector < Block* > Blocks){
    vector < Block* > newBlocks;
    for(int i=0; i<Blocks.size(); i++){
        Block *curBlock = Blocks[i];

        cout <<"[|";
        int j;
        for(j=0; j<curBlock->tNodes; j++)
        {
            cout << curBlock->value[j] << "|";
            if(curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);
        }
        if(curBlock->value[j]==INT_MAX && curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);

        cout << "]  ";
    }

    if(newBlocks.size()==0)
    {
        puts("");
        puts("");
        Blocks.clear();
    }
    else {
        puts("");
        puts("");
        Blocks.clear();
        print(newBlocks);
    }
}

int main(){
    int num;


    printf("Pointers: ");
    scanf("%d", &numberOfPointers);




    vector < Block* > Blocks;


    int ch;
    int i = 0;
    int totalValues = 0;
//    printf("1.Insert a value\n2.Print the tree\n3.Delete a value\n");
//    while(scanf("%d", &ch)!=EOF){
//
//        if(ch==1){
//            printf("**** Insert : ****\n\n", num);
//            scanf("%d", &num);
//
//            insertNode(rootBlock, num);
//            i++;
//            totalValues++;
//
//        }else if(ch==2){
//            Blocks.clear();
//            Blocks.push_back(rootBlock);
//            print(Blocks);
//            puts("");
//
//        }else if(ch==3) {
//            int val;
//            fscanf(p, "%d", &val);
//            if(totalValues==0) {
//                printf("Sorry! There is no more data to be deleted!!");
//                continue;
//
//            }
//            printf("---- Delete %d ----\n\n", val);
//            dataFound = false;
//            deleteNode(rootBlock, val, 0);
//            totalValues--;
//        }
//    }
    //input manually
    while(scanf("%d", &ch)!=EOF){


        if(ch==1){
            scanf("%d", &num);
            printf("**** Insert %d ****\n\n", num);
            insertNode(rootBlock, num);
            //i++;
            totalValues++;

        }else if(ch==2){
            Blocks.clear();
            Blocks.push_back(rootBlock);
            print(Blocks);
            puts("");

        }else if(ch==3) {
            int val;
            scanf("%d", &val);
            if(totalValues==0) {
                printf("Sorry! There is no more data to be deleted!!");
                continue;

            }
            printf("---- Delete %d ----\n\n", val);
            dataFound = false;
            deleteNode(rootBlock, val, 0);
            totalValues--;
        }
    }


    return 0;
}

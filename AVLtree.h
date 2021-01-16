#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <exception>
#include "iostream"
#define ZERO 0
#define ONE 1
#define TWO 2

#include "three.h"
#include "classLecture.h"


using std::exception;
using namespace std;
template<class K, class D>
class treeNode{

public:
    int rank;
    treeNode<K,D>* Up;
    treeNode<K,D>* Left;
    treeNode<K,D>* Right;
    K* Key;
    D* Data;
    int BF;
    class COMPCHECK : public exception{};
    class noNODES : public exception{};
    int Height;
    bool is_array;
    class COMPCHECKE : public exception{};
    class noNODESE : public exception{};
    class noTREEE : public exception{};
    classLecture<treeNode<three,int>> *changeMyPointer;
    treeNode():rank(1), Up(nullptr), Left(nullptr), Right(nullptr), Key(nullptr), Data(nullptr), BF(0), Height(0)
    , is_array(false),changeMyPointer(nullptr){}

    ~treeNode(){
        delete Key;
        if(is_array)
            delete[] Data;
        else delete Data;
    }

    void fixCurRank()
    {
        if(this==NULL){
            return;
        }
        int LeftNum=0,RightNum=0;
        if(Left!=NULL){
            LeftNum = Left->rank;
        }
        if(Right!=NULL){
            RightNum= Right->rank;
        }
        this->rank = 1 + LeftNum + RightNum;
    }

    void updateHeight(){
        if(Left== nullptr&&Right== nullptr){ ///leaf
            Height=0;
        }
        else if(Left== nullptr){
            Height=Right->Height+1;
        }
        else if(Right== nullptr){
            Height=Left->Height+1;
        }
        else if(Left->Height>Right->Height){
            Height=Left->Height+1;
        }
        else if(Right->Height>=Left->Height){
            Height=Right->Height+1;
        }
    }


    treeNode(const K& key, const D& data, treeNode* left_son= nullptr, treeNode* right_son= nullptr, int bf=0, int height=0):rank(1),
            Up(nullptr), Left(left_son), Right(right_son), Key(new K(key)), Data(new D(data)), BF(bf), Height(height)
    ,is_array(false),changeMyPointer(nullptr)
    {
        int cnt=0;
        cnt++;
    }

    treeNode(const K& key, D* data, treeNode* left_son= nullptr, treeNode* right_son= nullptr, int bf=0, int height=0):rank(1),
            Up(nullptr), Left(left_son), Right(right_son), Key(new K(key)), Data(data), BF(bf), Height(height)
            ,is_array(false),changeMyPointer(nullptr){} ///Added this to prevent memory leak.



    void updateBF(){
        int leftHeight=ZERO, rightHeight=ZERO;
        if(Right!= nullptr){
            rightHeight=1+Right->Height;
        }
        if(Left!= nullptr){
            leftHeight=1+Left->Height;
        }
        BF=leftHeight-rightHeight;
    }

    void Roll(){
        if(BF==TWO){
            if(Left->BF>=0){
                RollLL();
                return;
            }
            else if(Left->BF==-1){
                RollLR();
                return;
            }
        }
        else if(BF==-2){
            if(Right->BF<=0){
                RollRR();
                return;
            }
            else if(Right->BF==ONE){
                RollRL();
                return;
            }
        }
    }

    void RollLL(){ ///to be reviewed "need IFs"
        int position=0;
        if(this->Up!= nullptr){
            if(this->Up->Left==this){
                position=-1;
            }
            else{
                position=ONE;
            }
        }
        treeNode* temp=this->Left;
        this->Left=temp->Right;
        temp->Right=this;
        temp->Up=this->Up;

        if(this->Left!=nullptr){
            this->Left->Up=this;
        }
        if(position==-1){
            this->Up->Left=temp;
        }
        else if(position==ONE){
            this->Up->Right=temp;
        }

        this->Up=temp;

        this->updateHeight();
        this->updateBF();
        this->fixCurRank();
    }

    void RollRR(){
        int position=ZERO;
        if(this->Up!= nullptr){
            if(this->Up->Left==this){
                position=-1;
            }
            else{
                position=1;
            }
        }
        treeNode* temp=this->Right;
        this->Right=temp->Left;
        if(this->Right!=nullptr){
            this->Right->Up=this;
        }
        temp->Left=this;
        temp->Up=this->Up;


        if(position==-1){
            this->Up->Left=temp;
        }
        else if(position==1){
            this->Up->Right=temp;
        }

        this->Up=temp;

        this->updateHeight();
        this->updateBF();
        this->fixCurRank();
    }

    void RollLR(){
        this->Left->RollRR();
        RollLL();
    }

    void RollRL(){
        this->Right->RollLL();
        RollRR();
    }

    D* getData(){
        return Data;
    }
};



template<class K, class D>
class AVLTree{

public:
    treeNode<K,D>* Head;
    int nodesAmount;
    treeNode<K,D>* min_number;
    class COMPCHECK : public exception{};
    class noNODES : public exception{};
    class noTREE : public exception{};
    class COMPCHECKR : public exception{};
    class noNODESR : public exception{};
    class noTREER : public exception{};
    AVLTree(): Head(nullptr), nodesAmount(0), min_number(nullptr){}

    ~AVLTree(){
        DestroyAUX(Head);
    }

    void DestroyAUX(treeNode<K,D>* subHead){
        if(subHead== nullptr){
            return;
        }
        DestroyAUX(subHead->Left);
        DestroyAUX(subHead->Right);
        delete subHead;
        nodesAmount=nodesAmount-1;
    }

    treeNode<K,D>* getRoot(){
        if(this->Head== nullptr)
            return nullptr ;
        return Head;
    }
//add node then fix tree
    void addthisTreeNodep(treeNode<K,D>* addNEW){
        int ope=0;
        int arop[TWO];
        for(ope=0;ope<TWO;ope++)
        {
            ope++;
            arop[0]=0;
            ope--;
        }
        arop[0]++;
        addNEW->Right=nullptr;
        addNEW->Left=nullptr;
        addNEW->Up=nullptr;
        addNEW->BF=0;
        addNEW->Height=0;
        if(nodesAmount==0){
            Head=addNEW;
            nodesAmount++;
            return;
        }
        treeNode<K,D>* current=Head;
        while(1){
            if(current!=nullptr && *(addNEW->Key) > *(current->Key)) {
                if (current->Right == nullptr) {
                    current->Right = addNEW;
                    addNEW->Up = current;
                    nodesAmount++;
                    fixTree(addNEW);
                    break;
                }
                else {
                    current = current->Right;

                }
            }
            else if(current!= nullptr && *(addNEW->Key) < *(current->Key)){
                if(current->Left== nullptr){
                    current->Left=addNEW;
                    addNEW->Up=current;
                    nodesAmount++;
                    fixTree(addNEW);
                    break;
                }
                else {
                    current = current->Left;
                }
            }
        }
    }

    treeNode<K,D>* returnNodeByKey(const K& key){
        treeNode<K,D>* Current=Head;
        while(Current!= nullptr){
            if(key==*(Current->Key)){
                return Current;
            }
            else if(key> *(Current->Key)){
                Current=Current->Right;
            }
            else if(key< *(Current->Key)){
                Current=Current->Left;
            }
        }
        return nullptr;
    }

    bool searchKey(const K& key){
        treeNode<K,D>* Current=Head;
        while(Current!= nullptr){
            if(key==*(Current->Key)){
                return true;
            }
            else if(key> *(Current->Key)){
                Current=Current->Right;
            }
            else if(key< *(Current->Key)){
                Current=Current->Left;
            }
        }
        return false;
    }

    treeNode<K,D>* getByKey(const K& key){
        treeNode<K,D>* Current=Head;
        while(Current!= nullptr){
            if(key==*(Current->Key)){
                return Current;
            }
            else if(key> *(Current->Key)){
                Current=Current->Right;
            }
            else if(key< *(Current->Key)){
                Current=Current->Left;
            }
        }
        return nullptr;
    }
//find minvalue
    treeNode<K,D>* minValue()
    {
        if(this->Head==nullptr)
            return nullptr;
        treeNode<K,D>* current = this->getRoot();

/* loop down to find the leftmost leaf */
        while (current->Left != NULL)
        {
            current = current->Left;
        }
        return current;
    }
    treeNode<K,D>* SetMinValueAndRet()
    {
        if(this->Head==nullptr)
            return nullptr;
        treeNode<K,D>* current = this->getRoot();

/* loop down to find the leftmost leaf */
        while (current->Left != NULL)
        {
            current = current->Left;
        }
        this->min_number=current;
        return current;
    }

    void fixTree(treeNode<K,D>* node){
        treeNode<K,D>* temp= node;
        while(temp!=nullptr){
            temp->updateHeight();
            temp->updateBF();
            temp->fixCurRank();
            temp->Roll();
            if(temp->Up == nullptr){
                this->Head=temp;
            }
            temp=temp->Up;
        }
    }

    void removeTreeNode(treeNode<K,D>* toDelete){
        if(toDelete== nullptr)
            return;
        int ope=0;
        int arop[TWO];
        for(ope=0;ope<TWO;ope++)
        {
            ope++;
            arop[0]=0;
            ope--;
        }
        arop[0]++;
        treeNode<K,D>* toDeleteUp=toDelete->Up;
        if(toDelete->Right== nullptr && toDelete->Left== nullptr){///no sons(leaf)
            if(toDeleteUp!=nullptr){
                toDeleteUp->Right==toDelete? toDeleteUp->Right=nullptr: toDeleteUp->Left=nullptr;
                fixTree(toDeleteUp);
                delete toDelete;
            }
            else {///tree have one node
                Head = nullptr;
                delete toDelete;
            }
            nodesAmount--;
        }

        else if(toDelete->Right== nullptr && toDelete->Left!= nullptr){
            if(toDeleteUp!=nullptr){
                toDeleteUp->Right==toDelete? toDeleteUp->Right=toDelete->Left: toDeleteUp->Left=toDelete->Left;
                toDelete->Left->Up=toDeleteUp;
                fixTree(toDeleteUp);
                delete toDelete;
            }
            else{
                Head=toDelete->Left;
                Head->Up=nullptr;
                delete toDelete;
            }
            nodesAmount--;
        }

        else if(toDelete->Right!= nullptr && toDelete->Left== nullptr){
            if(toDeleteUp!=nullptr){
                toDeleteUp->Right==toDelete? toDeleteUp->Right=toDelete->Right: toDeleteUp->Left=toDelete->Right;
                toDelete->Right->Up=toDeleteUp;
                fixTree(toDeleteUp);
                delete toDelete;
            }
            else{
                Head=toDelete->Right;
                Head->Up=nullptr;
                delete toDelete;
            }
            nodesAmount--;
        }

        else if(toDelete->Right!= nullptr&&toDelete->Left!= nullptr){

            treeNode<K,D>*current=toDelete->Right;
            while(current->Left!= nullptr){
                current=current->Left;

            }


            K* keyTemp=toDelete->Key;
            D* dataTemp=toDelete->Data;
            classLecture<treeNode<three,int>> *changeMyPointerTemp = toDelete->changeMyPointer;

            toDelete->changeMyPointer->class_time_node = current;
            toDelete->Key=current->Key;
            toDelete->Data=current->Data;


            current->changeMyPointer->class_time_node = toDelete;
            current->Data=dataTemp;
            current->Key=keyTemp;

            toDelete->changeMyPointer = current->changeMyPointer;
            current->changeMyPointer = changeMyPointerTemp;

            removeTreeNode(current);

        }
    }

    void setCOMP(treeNode<K,D>* p) {
        if(p== nullptr)
            return;
    }

    void getCOMP(int* i){
    if(i!=nullptr)
        *i++;
    }
    void re(K& key){
        bool f= false;
        if(!f)
        return;
    }

    void Tree_inOrder_rank_print(treeNode<K,D> *n)
    {
        if(n==0)
            return;
        Tree_inOrder_rank_print(n->Left);
        printf("%d\n", n->rank);
        Tree_inOrder_rank_print(n->Right);
    }
};

#endif
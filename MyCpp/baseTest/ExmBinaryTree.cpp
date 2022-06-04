#include <iostream>
using namespace std;
#define ElementType char

struct BinNode {
    ElementType Data;
    struct BinNode *Left = NULL;
    struct BinNode *Right = NULL;
};

BinNode *creatBinNode(ElementType item);//创建结点
BinNode *creatBinTree(void);//创建二叉树
void PrintBinTree(void);//打印二叉树
bool isEmpty(BinNode *BT);//判断BT是否为空
void PreOrderTravelsal(BinNode *BT);//先序遍历,根，左子树，右子树
void InOrderTravelsal(BinNode *BT);//中序遍历,左子树，根，右子树
void PostOrderTravelsal(BinNode *BT);//后序遍历,左子树，右子树，根
//void LevelOrderTravelsal(BinNode *BT);//层次遍历,从上到下，从左到右

int main (void) {
    struct BinNode *BinTree;//定义根节点指针
    BinTree = creatBinTree();
    PrintBinTree();

    cout << endl << "先序遍历: ";
    PreOrderTravelsal(BinTree);

    cout << endl << "中序遍历: ";
    InOrderTravelsal(BinTree);

    cout << endl << "后序遍历: ";
    PostOrderTravelsal(BinTree);



    return 0;
}
//创建结点
BinNode *creatBinNode(ElementType item) {
    struct BinNode *tempnode;
    tempnode = new BinNode;
    tempnode->Data = item;
    return tempnode;
}
/*创建二叉树
     A
    / \
   B   C
  /\   /\
 D  F G  I
   /   \
  E     H

 */
BinNode *creatBinTree(void) {
    struct BinNode *BinTree, *temp;
    BinTree = creatBinNode('A');
    BinTree->Left = creatBinNode('B');
    BinTree->Right = creatBinNode('C');
    temp = BinTree->Left;
    temp->Left = creatBinNode('D');
    temp->Right = creatBinNode('F');
    temp = temp->Right;
    temp->Left = creatBinNode('E');
    temp = BinTree->Right;
    temp->Left = creatBinNode('G');
    temp->Right = creatBinNode('I');
    temp = temp->Left;
    temp->Right = creatBinNode('H');
    return BinTree;
}
void PrintBinTree(void) {
    cout << "打印二叉树" << endl;
    cout << "     A" << endl;
    cout << "    / \\ " << endl;
    cout << "   B   C" << endl;
    cout << "  /\\   /\\ " << endl;
    cout << " D  F G  I" << endl;
    cout << "   /   \\ " << endl;
    cout << "  E     H" << endl;
}
//先序遍历,根，左子树，右子树
void PreOrderTravelsal(BinNode *BT) {
    if (BT) {
        cout << BT->Data << " ";
        PreOrderTravelsal( BT->Left );
        PreOrderTravelsal( BT->Right );
    }
}
//中序遍历,左子树，根，右子树
void InOrderTravelsal(BinNode *BT) {
    if (BT) {
        InOrderTravelsal( BT->Left );
        cout << BT->Data << " ";
        InOrderTravelsal( BT->Right );
    }
}
//后序遍历,左子树，右子树，根
void PostOrderTravelsal(BinNode *BT) {
    if (BT) {
        PostOrderTravelsal( BT->Left );
        PostOrderTravelsal( BT->Right );
        cout << BT->Data << " ";
    }
}
//判断BT是否为空
bool isEmpty(BinNode *BT) {
    if( (BT->Left == NULL) && (BT->Right == NULL) ) {
        return true;
    }
    return false;
}


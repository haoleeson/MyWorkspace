#include <iostream>
using namespace std;

//定义链表的节点 结构体
struct node {//链表的节点
    int listNum;//节点编号
    int data;//节点数据
    struct node *next;//指向下一个节点
};

bool ifContinueInput(struct node *nowPoint);//输入当前节点数据区数字，并判断是否继续
struct node* createLinkedList(void);//创建链表
void OutputLinkedList(struct node *head);//输出链表数据
void deleteTheLinkedList(struct node *head);//释放链表内存

int main(void) {
    struct node *head/*头节点*/;
    head = createLinkedList();//创建链表
    OutputLinkedList(head);//输出链表数据
    deleteTheLinkedList(head);//释放链表内存
    delete []head;//释放头节点内存
    return 0;
}

//输入当前节点数据区数字，并判断是否继续
bool ifContinueInput(struct node *nowPoint) {
    int tempNum = -1;/*输入数字缓存*/
    cout << "请输入第" << nowPoint->listNum << "节点数据区的数字（输入0结束）:";
    cin >> tempNum;
    if (tempNum == 0) {
        return false;//退出连续输入
    }
    nowPoint->data = tempNum;
    return true;
}
//创建链表
struct node* createLinkedList(void) {
    struct node *head/*头节点*/, *lastPoint/*前节点*/, *nowPoint/*当下节点*/;
    head = NULL;
    lastPoint = NULL;
    //分配内存（并配置）头节点
    nowPoint = new node;
    head = nowPoint;//记录头节点地址到head
    nowPoint->listNum = 1;
    nowPoint->next = NULL;
    while ( ifContinueInput(nowPoint) ) {//输入当前节点数据区数字，并判断是否继续
        lastPoint = nowPoint;//将当下节点地址，缓存到前节点
        nowPoint = new node;//分配新节点内存
        nowPoint->next = NULL;
        lastPoint->next = nowPoint;//将前节点(next)链接到当下节点
        nowPoint->listNum = lastPoint->listNum + 1;//当下节点标号
    }
    return head;
}
//输出链表数据
void OutputLinkedList(struct node *head) {
    struct node *nowPoint;
    nowPoint = head;//取头节点地址
    cout << endl << "输出链表数据：" << endl;
    while (nowPoint->next != NULL) {
        cout << "No." << nowPoint->listNum << " " << nowPoint->data << endl;
        nowPoint = nowPoint->next;//当下节点向下一节点移动
    }
}
//释放链表内存
void deleteTheLinkedList(struct node *head) {
    struct node *nowPoint,*nextPoint;
    nowPoint = head;//取头节点地址
    cout << endl << "释放链表内存：" << endl;
    while (nowPoint->next != NULL) {
        nextPoint = nowPoint->next;//将链表下一个节点地址缓存到nextPoint
        cout << "释放No." << nowPoint->listNum << "节点内存"<< endl;
        delete []nowPoint;//释放当下节点内存
        nowPoint = nextPoint;//光标移动到下一个节点
    }
}

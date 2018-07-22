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
/******** Plus  **********/
void addOneNodeInTheEnd(struct node *head, int Data);//在链表尾部增加一个节点，并为其数据区赋值
void deleteOneNodeInTheEnd(struct node *head);//在链表尾部删除一个节点

int main(void) {
    struct node *head/*头节点*/;
    head = createLinkedList();//创建链表
    OutputLinkedList(head);//输出链表数据
    //addOneNodeInTheEnd(head);
    //OutputLinkedList(head);//输出链表数据
    deleteOneNodeInTheEnd(head);//在链表尾部删除一个节点
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
    getchar();
    if (tempNum == 0) {
        nowPoint->next = NULL;
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
    while ( ifContinueInput(nowPoint) ) {//输入当前节点数据区数字，并判断是否继续（只要第一节点数据不为0，默认创建下一节点）
        lastPoint = nowPoint;//将当下节点地址，缓存到前节点
        nowPoint = new node;//分配新节点内存
        nowPoint->next = NULL;
        lastPoint->next = nowPoint;//将前节点(next)链接到当下节点
        nowPoint->listNum = lastPoint->listNum + 1;//当下节点标号
    }
    delete []nowPoint;//释放多生成的节点内存
    lastPoint->next = NULL;//因为当前多生成的节点内存已被释放
    return head;
}
//在链表尾部增加一个节点，并为其数据区赋值
void addOneNodeInTheEnd(struct node *head, int Data) {
    struct node *nowPoint, *lastPoint;
    nowPoint = head;//取头节点地址
    while (nowPoint->next != NULL) { //光标移动到链表尾部
        nowPoint = nowPoint->next;
    }
    lastPoint = nowPoint;//将当下节点地址，缓存到前节点
    nowPoint = new node;//分配新节点内存
    nowPoint->next = NULL;
    lastPoint->next = nowPoint;//将前节点(next)链接到当下节点
    nowPoint->listNum = lastPoint->listNum + 1;//当下节点标号
    nowPoint->data = Data;
}
//在链表尾部删除一个节点
void deleteOneNodeInTheEnd(struct node *head){
    struct node *nowPoint, *lastPoint;
    nowPoint = head;//取头节点地址
    //如果链表只有一个节点
    if(nowPoint->next == NULL) {
        delete []nowPoint;//释放当前节点内存：
        head = NULL;
    }
    while (1) { //光标移动到链表尾部
        nowPoint = nowPoint->next;//光标下移
        if (nowPoint->next == NULL) {
            break;
        }
        lastPoint = nowPoint;
    }
    lastPoint->next = NULL;
    delete []nowPoint;//释放链表最末节点内存
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
    cout << "No." << nowPoint->listNum << " " << nowPoint->data << endl;//输出链表最末节点数据
}
//释放链表内存
void deleteTheLinkedList(struct node *head) {
    struct node *nowPoint, *nextPoint;
    nowPoint = head;//取头节点地址
    cout << endl << "释放链表内存：" << endl;
    while (nowPoint->next != NULL) {
        nextPoint = nowPoint->next;//将链表下一个节点地址缓存到nextPoint
        cout << "释放No." << nowPoint->listNum << "节点内存"<< endl;
        delete []nowPoint;//释放当下节点内存
        nowPoint = nextPoint;//光标移动到下一个节点
    }
    cout << "释放No." << nowPoint->listNum << "节点内存"<< endl;
    delete []nowPoint;//释放链表最末节点内存
}

#include <iostream>
using namespace std;

//定义链表的节点 结构体
struct node {//链表的节点
    int listNum;//节点编号
    int data;//节点数据
    struct node *next;//指向下一个节点
};

int inputNum(void);//输入数字
struct node* createLinkedList(void);//创建链表
void OutputLinkedList(struct node *head);//输出链表数据
void deleteTheLinkedList(struct node *head);//释放链表内存
/******** Plus  **********/
void addOneNodeInTheEnd(struct node *head, int Data);//在链表尾部增加一个节点，并为其数据区赋值
void insertBehindK(struct node *head, int K, int Data);//在链表第K个节点后插入一个节点
void deleteOneNodeInTheEnd(struct node *head);//在链表尾部删除一个节点
struct node *findKth(struct node *head, int K);//查找链表中第Ｋ个节点
struct node *findData(struct node *head, int Data);//查找链表中数据为:data的所有节点，并构成链表，返回链表指针

int main(void) {
    struct node *head/*头节点*/;
    head = createLinkedList();//创建链表
    OutputLinkedList(head);//输出链表数据

    cout << endl << "在链表尾部插入一个节点 54 " << endl;
    addOneNodeInTheEnd(head, 54);
    OutputLinkedList(head);//输出链表数据

    cout << endl << "在链表第3个节点后插入一个节点 123 " << endl;
    insertBehindK(head, 3, 123);//在链表第K个节点后插入一个节点
    OutputLinkedList(head);//输出链表数据

    cout << endl << "删除链表尾部一个节点" << endl;
    deleteOneNodeInTheEnd(head);//在链表尾部删除一个节点
    OutputLinkedList(head);//输出链表数据

    cout << endl << "查找链表的第3个节点" << endl;
    struct node *find1;
    find1 = findKth(head, 3);

    cout << endl << "查找链表中数据为:1 的所有节点，并构成链表，返回链表指针" <<endl;
    struct node *find2;
    find2 = findData(head, 1);

    cout << endl << "释放链表内存" << endl;
    deleteTheLinkedList(head);//释放链表内存
    delete []head;//释放头节点内存
    return 0;
}

//输入数字
int inputNum(void) {
    int numTemp = -1;/*输入数字缓存*/
    cin >> numTemp;
    getchar();
    return numTemp;
}
//创建链表
struct node* createLinkedList(void) {
    int nodeCount=0, numTemp;
    struct node *head/*头节点*/, *temp;
    cout << "请输入No.1 节点数据区的数字（输入0结束）:";
    numTemp = inputNum();
    while (numTemp) {
        if (nodeCount == 0) {
            head = new node;//分配头节点内存
            head->listNum = ++nodeCount;
            head->data = numTemp;
            head->next = NULL;
            temp = head;//取头节点地址
        } else {
            temp->next = new node;//分配新节点内存
            temp = temp->next;//链表节点下移
            temp->listNum = ++nodeCount;
            temp->data = numTemp;
            temp->next = NULL;
        }
        cout << "请输入No." << nodeCount+1 << " 节点数据区的数字（输入0结束）:";
        numTemp = inputNum();
    }
    if (nodeCount > 0) {
        cout << endl << "Success: 创建链表成功" <<endl;
        return head;
    }
    cout << endl << "Error: 创建链表失败" <<endl;
    return NULL;
}
//在链表尾部增加一个节点，并为其数据区赋值
void addOneNodeInTheEnd(struct node *head, int Data) {
    struct node *nowPoint;
    nowPoint = head;//取头节点地址
    while (nowPoint->next != NULL) { //光标移动到链表尾部
        nowPoint = nowPoint->next; //节点下移
    }
    nowPoint->next = new node; //分配新节点内存
    (nowPoint->next)->listNum = nowPoint->listNum + 1;//新增节点编号
    nowPoint = nowPoint->next; //节点下移
    nowPoint->data = Data;
    nowPoint->next = NULL;
}
//在链表尾部删除一个节点
void deleteOneNodeInTheEnd(struct node *head) {
    struct node *nowPoint, *lastPoint;
    //如果链表只有一个节点
    if(head->next == NULL) {
        delete []head;//释放当前节点内存：
        head = NULL;
        return;
    }
    nowPoint = head;//取头节点地址
    while (1) {
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
    while (nowPoint) { //nowPoint 为NULL时跳出
        cout << "No." << nowPoint->listNum << " " << nowPoint->data << endl;
        nowPoint = nowPoint->next;//当下节点向下一节点移动
    }
}
//释放链表内存
void deleteTheLinkedList(struct node *head) {
    struct node *nowPoint, *nextPoint;
    nowPoint = head;//取头节点地址
    cout << endl << "释放链表内存：" << endl;
    while (nowPoint) {
        nextPoint = nowPoint->next;//将链表下一个节点地址缓存到nextPoint
        cout << "释放No." << nowPoint->listNum << "节点内存"<< endl;
        delete []nowPoint;//释放当下节点内存
        nowPoint = nextPoint;//光标移动到下一个节点
    }
}
//查找链表中第Ｋ个节点
struct node *findKth(struct node *head, int K) {
    struct node *nowPoint;
    int i=1;
    nowPoint = head;//取头节点地址
    while( (nowPoint != NULL )&&(i<K) ) {
        nowPoint = nowPoint->next;
        i++;
    }
    if (i==K) {
        cout << "Success: 查找到链表中第" << K << "个元素为:　" << endl << "No." << nowPoint->listNum << " " << nowPoint->data << endl;
        return nowPoint;
    }
    cout << "Error: 查找第K个元素超出链表总数" << endl;
    return NULL;
}
//查找链表中数据为:data的所有节点，并构成链表，返回链表指针
struct node *findData(struct node *head, int Data) {
    int findCount = 0;
    struct node *nowPoint, *reDataListedHead, *temp;
    nowPoint = head;//取头节点地址
    while (nowPoint) {
        if (nowPoint->data == Data) {
            if (findCount == 0) { //首次找到节点
                reDataListedHead = new node;//分配新节点内存
                reDataListedHead->listNum = nowPoint->listNum;
                reDataListedHead->data = nowPoint->data;
                reDataListedHead->next = NULL;
                temp = reDataListedHead;
                findCount++;
            } else {
                temp->next = new node;//分配新节点内存
                temp = temp->next;//返回链表的光标下移
                temp->listNum = nowPoint->listNum;
                temp->data = nowPoint->data;
                temp->next = NULL;
                findCount++;
            }
        }
        nowPoint = nowPoint->next;
    }
    if (findCount != 0) {
        cout << "Success: 已找到节点" << endl;
        OutputLinkedList(reDataListedHead);//打印出找到的节点(s)
        return reDataListedHead;
    }
    cout << "Error: 未找到节点" << endl;
    return NULL;
}
//在链表第K个节点后插入一个节点
void insertBehindK(struct node *head, int K, int Data) {
    struct node *nowPoint, *temp;
    int nodeCount = 1;
    nowPoint = head;//取头节点地址
    while( (nowPoint != NULL) && (nodeCount < K) ) {
        nowPoint = nowPoint->next;
        nodeCount++;
    }
    if (nodeCount == K) {
        temp = new node;//分配新节点内存
        temp->next = nowPoint->next;
        nowPoint->next = temp;
        temp->data = Data;
        //后续节点编号+1
        while(temp) {
            temp->listNum = ++nodeCount;
            temp = temp->next;
        }
        cout << "Success: 成功添加节点" << endl;
        return;
    }
    cout << "Error: 要第K个元素超出链表总数" << endl;
    return;
}

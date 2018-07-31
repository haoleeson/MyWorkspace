#include <iostream>
using namespace std;
#define MAX(a, b) ( (a)>(b) ? (a) : (b) )
#define MIN(a, b) ( (a)<(b) ? (a) : (b) )
//定义链表的节点 结构体
struct node {//链表的节点
    int listNum;//节点编号
    int data;//节点数据
    struct node *next;//指向下一个节点
};

int inputNum(void);//输入数字
void swapNodeData(struct node *node1, struct node *node2);//交换两个节点数据
struct node* createLinkedList(void);//创建链表
void OutputLinkedList(struct node *head);//输出链表数据
void deleteTheLinkedList(struct node *head);//释放链表内存
/******** Plus  **********/
void addOneNodeInTheEnd(struct node *head, int Data);//在链表尾部增加一个节点，并为其数据区赋值
void deleteOneNodeInTheEnd(struct node *head);//在链表尾部删除一个节点
struct node *findKth(struct node *head, int K);//查找链表中第Ｋ个节点
struct node *findData(struct node *head, int Data);//查找链表中数据为:data的所有节点，并构成链表，返回链表指针
struct node *insertBehindK(struct node *head, int K, int Data);//在链表第K个节点后插入一个节点
struct node *insertFrontK(struct node *head, int K, int Data);//在链表第K个节点前插入一个节点
struct node *swapTwoNode(struct node *head, int num1, int num2);//交换链表中的两个节点
struct node *deleteKthNode(struct node *head, int K);//删除链表第K个节点

int main(void) {
    struct node *head/*头节点*/, *p;
    head = createLinkedList();//创建链表
    OutputLinkedList(head);//输出链表数据

    cout << endl << "在链表尾部插入一个节点 54 " << endl;
    addOneNodeInTheEnd(head, 54);
    OutputLinkedList(head);//输出链表数据

    cout << endl << "在链表第3个节点后插入一个节点 123 " << endl;
    p = insertBehindK(head, 3, 123);//在链表第K个节点后插入一个节点
    OutputLinkedList(head);//输出链表数据

    cout << endl << "在链表第2个节点前插入一个节点 222 " << endl;
    p = insertFrontK(head, 2, 222);//在链表第K个节点前插入一个节点
    OutputLinkedList(head);//输出链表数据

    cout << endl << "交换链表中的两个节点　No.1 No.4" << endl;
    head = swapTwoNode(head, 1, 4);//交换链表中的两个节点　No.1 No.4
    OutputLinkedList(head);//输出链表数据

    cout << endl << "删除链表第4个节点" << endl;
    deleteKthNode(head,4);//删除链表第4个节点
    OutputLinkedList(head);//输出链表数据

    cout << endl << "删除链表尾部一个节点" << endl;
    deleteOneNodeInTheEnd(head);//在链表尾部删除一个节点
    OutputLinkedList(head);//输出链表数据

    cout << endl << "查找链表的第3个节点" << endl;
    p = findKth(head, 3);

    cout << endl << "查找链表中数据为:1 的所有节点，并构成链表，返回链表指针" <<endl;
    p = findData(head, 1);

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
//交换两个节点数据
void swapNodeData(struct node *node1, struct node *node2) {
    struct node *temp;
    temp->listNum = node1->listNum;
    temp->data = node1->data;
    temp->next = node1->next;

    node1->listNum = node2->listNum;
    node1->data = node2->data;
    node1->next = node2->next;

    node2->listNum = temp->listNum;
    node2->data = temp->data;
    node2->next = temp->next;
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
//查找链表中第K个节点
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
struct node *insertBehindK(struct node *head, int K, int Data) {
    struct node *nowPoint, *temp;
    int nodeCount = 1;
    if ( K < 1) {
        cout << "Error: 插入第K个元素，位置不合法" << endl;
        return NULL;
    } else {
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
            return head;
        }
    }
    cout << "Error: 要第K个元素超出链表总数" << endl;
    return NULL;
}
//在链表第K个节点前插入一个节点
struct node *insertFrontK(struct node *head, int K, int Data) {
    struct node *nowPoint, *temp;
    int nodeCount = 1;
    if ( K < 1) {
        cout << "Error: 插入第K个元素，位置不合法" << endl;
        return NULL;
    } else if (K==1) {
        temp = new node;//分配新节点内存
        temp->listNum = nodeCount;
        temp->data = Data;
        temp->next = head;
        head = temp;//新的头节点地址更新
        //后续节点编号+1
        temp = temp->next;
        while(temp) {
            temp->listNum = ++nodeCount;
            temp = temp->next;
        }
        cout << "Success: 成功添加节点" << endl;
        return head;
    } else {
        nowPoint = head;//取头节点地址
        while( (nowPoint->next != NULL) && (nodeCount < (K-1) ) ) {
            nowPoint = nowPoint->next;
            nodeCount++;
        }
        if (nodeCount == (K-1)) {
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
            return head;
        }
    }
    cout << "Error: 要第K个元素超出链表总数" << endl;
    return NULL;
}
//交换链表中的两个节点
struct node *swapTwoNode(struct node *head, int num1, int num2) {
    int bigNum, smallNum, nodeCount = 1;
    struct node *bignodeBef, *smallnodeBef, *temp, *bignode;
    bigNum = MAX(num1, num2);
    smallNum = MIN(num1, num2);
    if (smallNum < 1) {
        cout << "Error: 要换的第" << smallNum << "个元素不在链表内" << endl;
        return NULL;
    }
    if (smallNum == bigNum) {
        cout << "Error: 要交换的两个节点序号不能相同" << endl;
        return NULL;
    }
    //两序号不等，继续
    bignodeBef = head;//取头节点地址
    while( (bignodeBef != NULL) && (nodeCount < (bigNum-1) ) ) {
        if ( nodeCount == (smallNum-1) ) {
            smallnodeBef = bignodeBef;//缓存较小序号节点的前一节点指针
        }
        bignodeBef = bignodeBef->next;
        nodeCount++;
    }
    if ( nodeCount == (bigNum-1) ) {
    //能找到较大序号前一节点,开始交换
        if ( (bigNum-smallNum) == 1 ) {
        //两序号相邻，交换两个节点在链表中指针
            if ( smallNum == 1 ) {
                //最小节点序号为1，最大节点序号为2，需更新head
                bignode = bignodeBef->next;
                head->next = bignode->next;//头->next = 大->next
                bignode->next = head;//大->next = 头
                head = bignode;//更新头节点地址
                cout << "Success: 成功交换节点" << endl;
                return head;
            }
            bignode = bignodeBef->next;
            (smallnodeBef->next)->next = bignode->next;//小->next = 大->next
            bignode->next = (smallnodeBef->next);//大->next = 小
            smallnodeBef->next = bignode;//小前->next = 大
        } else {
        //两序号相差大于１个节点，交换两个节点在链表中指针
            if ( smallNum == 1 ) {
                //最小节点序号为1，需更新head
                bignode = bignodeBef->next;
                temp = bignode->next;//缓存大->next 到 temp
                bignode->next = head->next;//大->next = 头->next
                bignodeBef->next = head;//大前->next = 头
                head->next = temp;//头->next = temp
                head = bignode;//更新头节点地址
                cout << "Success: 成功交换节点" << endl;
                return head;
            }
            bignode = bignodeBef->next;
            temp = bignode->next;//缓存大->next 到 temp
            bignode->next = (smallnodeBef->next)->next;//大->next = 小->next
            (smallnodeBef->next)->next = temp;//小->next = temp
            temp = bignode;//缓存大 到 temp
            bignodeBef->next = smallnodeBef->next;//大前->next = 小前->next
            smallnodeBef->next = temp;//小前->next = temp
        }
        cout << "Success: 成功交换节点" << endl;
        return head;
    }
    cout << "Error: 要换的第" << bigNum << "个元素超出链表总数" << endl;
    return NULL;
}
//删除链表第K个节点
struct node *deleteKthNode(struct node *head, int K) {
    struct node *nowPoint, *temp;
    int i=1;
    if (K < 1) {
        cout << "Error: 要删除的第" << K << "个元素不在链表内" << endl;
        return NULL;
    }
    if (K == 1) {
        nowPoint = head->next;//节点下移
        cout << "Success: 删除链表中第" << K << "个节点　" << endl << "No." << head->listNum << " " << head->data << endl;
        delete []head;//释放当下节点内存
        return nowPoint;
    }
    nowPoint = head;//取头节点地址
    while( (nowPoint != NULL )&&(i<(K-1)) ) {
        nowPoint = nowPoint->next;
        i++;
    }
    if (i==(K-1)) {
        temp = nowPoint->next;//要删除的节点
        nowPoint->next = temp->next;
        cout << "Success: 删除链表中第" << K << "个节点　" << endl << "No." << temp->listNum << " " << temp->data << endl;
        delete []temp;//删除第K个节点
        return head;
    }
    cout << "Error: 待删除的第K个元素超出链表总数" << endl;
    return NULL;
}

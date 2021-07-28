//OOT第2次作业-EisenHao
#ifndef MYQUEUEBYLINKEDCLASS_H_
#define MYQUEUEBYLINKEDCLASS_H_
//链接队列优势，除可用内存限制外，不用额外考虑队列满的问题


//Class1: 定义队列的节点类（简化节点类）
//完全隐藏节点类，只能被友元类sQueue访问
template <class snodeType>
class sNode
{
    template <class myQueueType> friend class MyQueue; //MyQueue类的所有实例化, 都为sNode的友元, 注意模板参数(myQueueType)不能相同
    snodeType snodeData; //存节点数据
    sNode<snodeType>* next; //next指针：存下一个节点地址
    //构造函数私有，仅能被 MyQueue 类调用
    sNode<snodeType>(const snodeType& nodeData)
    {
        snodeData = nodeData; //拷贝数据
        next = 0; //指向链表下一节点地址，为0
    }
};

//Class2:定义获得出队信息类, 全公开
template <class receiveDataType>
class receiveData
{
public:
    bool isSuccessReceived;//是否正常返回，用来记录空队列时执行pop(), top()是否正常返回数据
    receiveDataType snodeData; //存节点数据
    //构造函数0：
    receiveData()
    {
        isSuccessReceived = false;//返回错误码, 默认为false
    }
    //构造函数1： 发生错误时，只初始化错误码
    receiveData(bool Flag)
    {
        isSuccessReceived = Flag;//返回错误码
    }
    //构造函数2： 无错误时，返回数据部分
    receiveData(const receiveDataType& nodeData)
    {
        isSuccessReceived = true;//ErrorNum为true表示正常返回数据
        snodeData = nodeData; //拷贝数据
    }
};

//Class3: 定义队列类
template <class myQueueType>
class MyQueue
{
private:
    sNode<myQueueType>* front;//保存 队列--头节点 地址
    sNode<myQueueType>* rear;//保存 队列--尾节点 地址
public:
    MyQueue();//构造函数：初始化队列对象
    ~MyQueue();//析构函数：释放内部主动申请的资源
    void push(const myQueueType& e);//入队函数：将元素 e 加入队尾
    receiveData<myQueueType> pop();//出队函数，移除队首元素(若队列不为空的话)
    receiveData<myQueueType> top();//返回队首元素, 但它不出队(若队列不为空的话)
    unsigned int count(); //返回队列中的元素个数
};
//构造函数：初始化队列对象
//假定构造后队列无元素，队列首尾节点指针为空
template <class myQueueType>
MyQueue<myQueueType>::MyQueue()
{
    front = 0;//保存队列头节点地址
    rear = 0;//保存队列尾节点地址
}
//析构函数：释放内部主动申请的资源
template <class myQueueType>
MyQueue<myQueueType>::~MyQueue()
{
    if(front != 0) //若调用过push函数 --> 删除申请空间
    {
        delete []front;//删除push函数申请的sNode空间
        front = 0;//指针赋NULL
    }
}
//入队函数：将元素 e 加入队尾
template <class myQueueType>
void MyQueue<myQueueType>::push(const myQueueType& e)
{
    //若队列为空，添加第一个节点
    if (this->count() == 0)
    {
        rear = new sNode<myQueueType>(e); //1.新建一个节点，并把地址返回给队列--尾节点rear
        front = rear;//2.队列--首尾指针 都指向这唯一的一个节点
    }
        //若队列不为空，链接“新的尾节点”到“旧的尾节点->next”，然后更新队列尾部指针到新节点
    else
    {
        rear->next = new sNode<myQueueType>(e); //1. 链接“新的尾节点”到“旧的尾节点->next”
        rear = rear->next; //2. 队列--尾节点rear 后移
    }
}
//出队函数，移除队首元素(若队列不为空的话)
template <class myQueueType>
receiveData<myQueueType> MyQueue<myQueueType>::pop()
{
    //利用receiveData类构造函数的过载多态性质，分别返回: 错误码 or 数据
    //若队列为空的，返回错误码
    if (this->count() == 0)
    {
        return receiveData<myQueueType>(false);//返回包含错误标识的 类
    }
        //若队列不为空的， 返回数据
    else
    {
        receiveData<myQueueType> tempData(front->snodeData); //1.拷贝队首节点的数据到temp, 构造时实现拷贝
        //2. 分情况删除队首节点
        //2a. 若队列只剩一个节点
        if (this->count()==1)
        {
            delete front; //释放front指向的 sNode内存
            front = 0;//指针赋NULL
            rear = 0;//指针赋NULL
        }
            //2b. 若队列有多个节点
        else
        {
            sNode<myQueueType>* temp = front;//暂存队首地址
            front = front->next;//队列首地址下移
            delete temp; //释放队列首的sNode内存
        }
        //3. 返回数据
        return tempData;
    }
}
//返回队首元素, 但它不出队(若队列不为空的话)
template <class myQueueType>
receiveData<myQueueType> MyQueue<myQueueType>::top()
{
    //利用receiveData类构造函数的过载多态性质，分别返回: 错误码 or 数据
    //若队列为空的，返回错误码
    if (this->count() == 0)
    {
        return receiveData<myQueueType>(false);//只返回错误码
    }
        //若队列不为空的， 返回队列首节点数据
    else
    {
        receiveData<myQueueType> tempData(front->snodeData); //1.拷贝队首节点的数据到temp, 构造时实现拷贝
        return tempData; //2. 返回数据
    }
}
//返回队列中的元素个数
template <class myQueueType>
unsigned int MyQueue<myQueueType>::count()
{
    unsigned int counter;
    //队列为空
    if (front == 0)
    {
        counter = 0;
    }
        //队列只有一个节点
    else if (front == rear)
    {
        counter = 1;
    }
        //队列有多个节点
    else
    {
        sNode<myQueueType>* Ptr = front;
        counter = 0;
        while (Ptr != 0)
        {
            Ptr = Ptr->next;
            counter++;
        }
    }
    return counter;
}

#endif

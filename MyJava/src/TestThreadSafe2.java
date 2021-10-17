/**
 * 测试线程安全-2
 * -- 多个线程同时读写单一对象数据时(加同步锁)，避免引发安全问题
 * eg. 对于多线程买票问题，考虑线程同步机制（安全）
 * */
public class TestThreadSafe2 implements Runnable{
    int leftNum = 5;//设置剩余票数
    int purchaseTime = 0;//统计买票次数

    //synchronized关键字修饰的"买一张票"方法
    synchronized boolean purchaseAticket(){
        int readValue;//定义读取值
        if((readValue = leftNum) > 0){
            try {
                Thread.sleep(100);//线程休眠0.1秒, 模仿买票操作用时
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("ReadLeftNum = " + readValue + ", After Purchase leftNum = " + --leftNum);//购票，将剩余票数减一
            purchaseTime++;//统计已购买票次数变量 +1
            return true;//成功买票，返回true
        }
        return false;//买票失败，返回false
    }

    @Override
    public void run() {
        while(purchaseAticket());
    }

    public static void main(String[] args) {
        TestThreadSafe2 testThreadSafe = new TestThreadSafe2();//实例化类对象
        //以下实例化四个子线程
        Thread threadA = new Thread(testThreadSafe);
        Thread threadB = new Thread(testThreadSafe);
        Thread threadC = new Thread(testThreadSafe);
        Thread threadD = new Thread(testThreadSafe);
        System.out.println("安全的有线程同步机制的多线程演示：\n总票数：" + testThreadSafe.leftNum);
        //启动四个子线程
        threadA.start();
        threadB.start();
        threadC.start();
        threadD.start();
        //主线程休眠
        try {
            Thread.sleep(3000);//主线程休眠3秒(足够这四个子线程买票)
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("总共买票次数：" + testThreadSafe.purchaseTime);
    }
}
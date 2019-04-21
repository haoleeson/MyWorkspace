/**
 * 测试线程安全
 * -- 多个线程同时读写单一对象数据时，可能引发的安全问题
 * eg. 未考虑线程安全的对线程买票（不安全）
 * */
public class TestThreadUnsafe implements Runnable {
    int leftNum = 5;//设置剩余票数
    int purchaseTime = 0;//统计买票次数

    @Override
    public void run(){
        int readValue;//定义读取值
        while(true){
            if ((readValue = leftNum) > 0) {
                try {
                    Thread.sleep(100);//线程休眠0.1秒, 模仿买票操作用时
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("ReadLeftNum = " + readValue + ", After Purchase leftNum = " + --leftNum);//购票，将剩余票数减一
                purchaseTime++;//统计已购买票次数变量 +1
            } else {
                break;
            }
        }
    }

    public static void main(String[] args) {
        TestThreadUnsafe testThreadUnsafe = new TestThreadUnsafe();//实例化类对象
        //以下实例化四个子线程
        Thread threadA = new Thread(testThreadUnsafe);
        Thread threadB = new Thread(testThreadUnsafe);
        Thread threadC = new Thread(testThreadUnsafe);
        Thread threadD = new Thread(testThreadUnsafe);
        System.out.println("不安全的多线程演示：\n总票数：" + testThreadUnsafe.leftNum);
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
        System.out.println("总共买票次数：" + testThreadUnsafe.purchaseTime);
    }
}
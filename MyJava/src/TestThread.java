import java.lang.Thread;

/**
 * 多线程，继承Thread类
 * */


public class TestThread extends Thread {
    public TestThread(String name) {
        super(name);//调用父类Thread构造函数，给线程命名
    }
    //重写run()方法实现线程执行的操作
    public void run() {
        int i = 0;
        while (++i < 5) {
            System.out.println(i + ":" + this.getName());
            //延时方式1：
//            for (long k=0; k<100000000; k++);//阻塞式延时，不推荐（占CPU）
            //延时方式2：
            try {
                Thread.sleep(1000);//推荐（让出CPU）
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public static void main(String[] args) {
        int i = 0;
        Thread test1 = new TestThread("A");//定义线程"A"
        Thread test2 = new TestThread("BBB");//定义线程"BBB"
        test1.start();//启动线程"A"
        test2.start();//启动线程"BBB"
        while (true) {//主线程在while死循环内
            System.out.println((i++) + ":Main");//Main主线程执行
            try {
                Thread.sleep(600);//主线程延时
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if (i > 100) break;
        }
    }
}
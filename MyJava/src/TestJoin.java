import java.lang.Runnable;
import java.lang.Thread;

/**
 * 线程等待join测试
 * */

public class TestJoin {
    Thread threadA;//声明线程A
    Thread threadB;//声明线程B

    //构造函数
    public TestJoin(){
        super();
        //使用匿名内部类型形式初始化Thread实例
        threadA = new Thread(new Runnable() {
            int countA = 0;
            @Override
            public void run() {
                while (true){
                    System.out.println("A: " + countA);
                    try {
                        Thread.sleep(100);   // 线程A休眠0.1秒
                        threadB.join();             // 线程B调用join()方法
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    if (++countA > 5) break;
                }
            }
        });
        threadA.start();                            // 启动线程A

        threadB = new Thread(new Runnable() {
            int countB = 0;
            @Override
            public void run() {
                while (true) {
                    System.out.println("B: " + countB);
                    try {
                        Thread.sleep(100); //线程B休眠0.1秒
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    if (++countB > 5) break;
                }
            }
        });
        threadB.start();                            // 启动线程B
    }
    public static void main(String[] args) {
        TestJoin t = new TestJoin();
    }
}


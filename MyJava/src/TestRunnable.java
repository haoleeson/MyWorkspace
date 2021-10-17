import java.lang.Runnable;
import java.lang.Thread;

/**
 * 多线程，继承Runnable接口
 * */

public class TestRunnable {
/**
 * 实现Runnable接口类
 */
    public static class Dosomething implements Runnable {
        private String name;
        public Dosomething(String name) {
            this.name = name;
        }
        //重写run()方法实现线程执行的操作
        public void run() {
            int i = 0;
            while (++i < 5){
                System.out.println(i+ ":" + this.name);
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    
/**
 * 主程序：测试Runnable多线程
 */
    public static void main(String[] args) {
        Dosomething t1 = new Dosomething("A");
        Dosomething t2 = new Dosomething("BBB");
        Thread test1 = new Thread(t1);//创建Thread对象，并与继承了Runnable接口的对象关联
        Thread test2 = new Thread(t2);
        test1.start();
        test2.start();
    }
}


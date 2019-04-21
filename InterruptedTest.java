import static java.lang.Thread.sleep;

/**
 * 线程中断（用一个布尔变量控制）
 * */


public class InterruptedTest implements Runnable {
    private boolean isStop = false;//设置一个标记变量（默认值为false）
    private int count = 0;
    @Override
    public void run() {
        while (true) {
            if (isStop) break;//当isStop为true时，停止线程
            /** Do something **/
            System.out.println((++count) + ". Hello...");
            try {
                sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    //定义设置停止线程标志位的方法
    public void setStop() {
        isStop = true;//设置isStop为true
    }

    public static void main(String[] args) {
        InterruptedTest interruptedTest = new InterruptedTest();
        Thread t = new Thread(interruptedTest);
        t.start();//启动线程t
        try {
            sleep(1500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        interruptedTest.setStop();//设置停止线程的标志位（停止线程t）
    }
}


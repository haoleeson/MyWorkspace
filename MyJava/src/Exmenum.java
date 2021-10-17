public class Exmenum {
    static class FreshJuice {
        enum FreshJuiceSize{ SMALL, MEDIUM , LARGE }
        FreshJuiceSize size;
    }
    public static void main(String []args){
        int i = 1;
        double j = 3.14;
        FreshJuice juice = new FreshJuice();
        juice.size = FreshJuice.FreshJuiceSize.MEDIUM;
        System.out.print("用print输出<<i:"+ i);
        System.out.println("用println输出<<i:"+ i);//输出后换行
        System.out.printf("用printf输出<<i的值为%d,j的值为%f", i, j);
        System.out.println("juice.size= "+ juice.size);
    }
}

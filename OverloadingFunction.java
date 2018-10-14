public class OverloadingFunction {
    public static int multipluy ( int a, int b ) {
        return a*b;
    }
    public static double multipluy ( double a, double b ) {
        return a*b;
    }
    public static int multipluy ( int a, int b, int c ) {
        return (a*b*c);
    }
    public static double multipluy ( double a, double b, double c ) {
        return (a*b*c);
    }

    public static void main ( String[] args ) {
        System.out.println( multipluy(3.2, 4.8, 5.1) );
    }
}

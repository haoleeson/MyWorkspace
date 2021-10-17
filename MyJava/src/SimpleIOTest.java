import java.io.*;

public class SimpleIOTest {
    public static void main ( String[] args ) {
        int ch;
        try {
            System.out.println("请输入一个字符:");
            ch = (char)System.in.read();//从键盘输入一个字符
            if ( ch >= '0' && ch <= '9' ) {
                System.out.println("你输入了一个数字字符:'" + (char)ch + "'" );
            } else {
                System.out.println("你输入了一个非数字字符:'" + (char)ch + "'" );
            }
        } catch ( IOException e ) { }
    }
}

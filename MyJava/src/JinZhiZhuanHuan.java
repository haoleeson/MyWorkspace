/*十进制与其他进制转换，这里的转换是显示出来，实际在计算机中是以2进制存储的*/

public class JinZhiZhuanHuan {
    public static void main ( String[] args ) {
        D_to_Hex(26);//十进制转换为十六进制
        D_to_Octal(26);//十进制转换为八进制
        D_to_Binary(26);//十进制转换为二进制
    }

    //进制转换基础函数
    public static void trans ( int num, int base, int offset ) {
        if ( num == 0 ) {
            System.out.println("0");
            return ;
        }
        //定义一个对应关系表
        char[] chs = {'0','1','2','3','4','5','6','7','8','9',
        'A','B','C','D','E','F'};
        char[] arr = new char [32];
        int pos = arr.length;
        while ( num != 0 ) {
            int Temp = num & base;
            arr[--pos] = chs[Temp];
            num = num >>> offset;//表示num除以2的offset次方
        }
        for ( int i=pos; i<arr.length; i++ ) {
            System.out.print(arr[i]);
        }
        System.out.println();
    }

    //十进制转换为十六进制
    public static void D_to_Hex ( int num ) {
        System.out.print("十进制数（"+num+"）转换为 十六进制:\t");
        trans(num,15,4);//2的4次方= 16
    }
    //十进制转换为八进制
    public static void D_to_Octal ( int num ) {
        System.out.print("十进制数（"+num+"）转换为   八进制:\t");
        trans(num,7,3); //2的3次方 = 8
    }
    //十进制转换为二进制
    public static void D_to_Binary ( int num ) {
        System.out.print("十进制数（"+num+"）转换为   二进制:\t");
        trans(num,1,1); //2的1次方 = 2//移位运算的移位个数
    }
}

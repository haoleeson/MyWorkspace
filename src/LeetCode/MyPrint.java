package LeetCode;

/**
 * 打印类
 * */
public class MyPrint {
    /**
     * 打印一纬数组 int
     * */
    public static void printArray(int[] Input) {
        System.out.print("[");
        for (int i = 0; i < Input.length-1; i++) {
            System.out.print(Input[i] + ", ");
        }
        System.out.println(Input[Input.length-1] + "]");
    }

    /**
     * 打印二纬数组 int
     * */
    public static void printMatrix(int matrix[][]) {
        for (int i = 0; i < matrix.length; i++) {
            System.out.print("[");
            for (int j = 0; j < matrix[0].length-1; j++) {
                System.out.print("" + matrix[i][j] + ", ");
            }
            System.out.println("" + matrix[i][matrix[0].length-1] + "]");
        }
    }
}

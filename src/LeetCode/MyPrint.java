package LeetCode;

import java.util.List;

/**
 * 打印类
 * */
public class MyPrint {
    /**
     * 打印一纬数组 int
     * */
    public static void printArray(String name, int[] nums) {
        System.out.print(name + ": [");
        for (int i = 0; i < nums.length-1; i++) {
            System.out.print(nums[i] + ", ");
        }
        System.out.println(nums[nums.length-1] + "]");
    }

    /**
     * 打印二纬数组 int
     * */
    public static void printMatrix(String name, int matrix[][]) {
        for (int i = 0; i < matrix.length; i++) {
            System.out.print("[");
            for (int j = 0; j < matrix[0].length-1; j++) {
                System.out.print("" + matrix[i][j] + ", ");
            }
            System.out.println("" + matrix[i][matrix[0].length-1] + "]");
        }
    }

    /**
     * 打印一纬数组 List<String>
     * */
    public static void printArray(String name, List<String> strList) {
        System.out.println("[");
        for (int i = 0; i < strList.size()-1; i++) {
            System.out.println("\"" + strList.get(i) + "\", ");
        }
        System.out.println("\"" + strList.get(strList.size()-1) + "\"\n]");
    }
}

import java.util.*;//使用Arrays.sort(arr);Arrays.countTheBiggerNums(arr,number);必须调用该库
public class ArrayDemo {

    public static void main ( String[] args ) {

        int[] array1 = new int []{3,5,1,7};
        int[] array2 = new int[4];
        int[] array3 = {1,2,3,4};

        int[][] array4 = { {3,1,7}, {5,8,2,9}, {4,1} };
        int[][][] array5 = new int[3][2][4];

        int[] arr = {89,34,270,98,17,67,123,890};//乱序
        //int[] arr = {13,15,19,28,33,45,78,106,197}; //专用于二分法查找（升序） Half_Search
        System.out.println("arr's length="+arr.length+"\n修改之前数组arr");
        Printf_arr(arr);//打印修改之前数组arr

        //Traversal_arr(arr);//遍历数组
        //Paixu_Diaoyongneibu_hanshu(arr);//调用Java内部排序函数
        Bubble_Sort(arr);//冒泡排序法
        //Select_Sort(arr);//选择排序法 0.7s
        //Select_Sort2(arr);//选择排序法优化版 0.7s
        //System.out.println( GetArrMaxNumber(arr) );//求数组的最大值
        //System.out.println( Search_number_NeiBuDiaoYong(arr,98) );//内部调用函数，搜索数组中的某值,当一个数组内出现两个相同的数字时返回值有错
        //内部调用函数，搜索数组中的某值
        //System.out.println( Search_number(             arr,67) );//搜索数组中是否含有该值(仅返回第一个值得下标)
        //System.out.println( Search_number_Plus(arr,17) );//搜索数组中是否含有该值_plus(返回有无布尔型变量，显示所有相同值下标)
        //System.out.println( Half_Search(arr,33) );//二分法查找该数组
        //System.out.println( Half_Search_2(arr,33) );//二分法查找该数组
        //reverseArray(arr);//置换数组,将数组的首位交换

        System.out.println("修改之后数组arr");
        Printf_arr(arr);//打印修改之后数组arr
    }

    //打印数组
    public static void Printf_arr ( int[] arr ) {
        System.out.print("[");
        for( int i = 0; i<arr.length; i++ ) {
            System.out.print(" "+arr[i]);
        }
        System.out.println(" ]");
    }

    //交换数组arr中a,b下标的值
    public static void Exchange_Arr_a_b( int[] arr, int a, int b ) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    //遍历数组
    public static void Traversal_arr( int[] arr ) {
        System.out.println("遍历数组arr");
        for ( int i=0; i<arr.length; i++) {
            System.out.print(arr[i]+" ");
        }
        System.out.println();
    }

    //调用Java内部排序函数
    public static void Paixu_Diaoyongneibu_hanshu ( int[] arr ) {
        Arrays.sort(arr);
    }

    //冒泡排序法，从小到大排序
    public static void Bubble_Sort(int[] arr) {
        System.out.print("冒泡排序法：");
        for ( int i=0; i<arr.length-1; i++ ) {
            for ( int j=0; j<arr.length - i -1; j++ ) {
                if ( arr[j] > arr[j+1] ) {
                    Exchange_Arr_a_b(arr,j,j+1);
                }
            }
        }
    }

    //选择排序法，从小到大排序
    public static void Select_Sort ( int[] arr ) {
        System.out.print("选择排序法：");
        for ( int x=0; x<arr.length - 1; x++ ) {
            for ( int y=x+1; y<arr.length; y++ ) {
                if( arr[x] > arr[y] ) {
                    Exchange_Arr_a_b(arr,x,y);
                }
            }
        }
    }

    //选择排序法优化版，从小到大排序
    public static void Select_Sort2 ( int[] arr ) {
        //外循环每循环一次只进行一次交换
        System.out.print("选择排序法优化版：");
        for ( int i=0; i<arr.length - 1; i++ ) {
            int Min_FLAG = i;
            for ( int j=i+1; j<arr.length; j++ ) {
                if ( arr[Min_FLAG] > arr[j] ) {
                    Min_FLAG=j;
                }
            }
            //若最小值下标不是第一个则交换
            if ( Min_FLAG != i ) {
                Exchange_Arr_a_b(arr,i,Min_FLAG);
            }
        }
    }

    //求数组的最大值
    public static int GetArrMaxNumber ( int[] arr ) {
        System.out.println("求数组的最大值：");
        int MaxNumber=arr[0],  index=0;
        for ( int i=1; i<arr.length; i++ ) {
            if ( MaxNumber < arr[i] ) {
                MaxNumber = arr[i];
                index = i;//记录下标
            }
        }
        System.out.println("the biggest number is : arr["+index+"] = "+MaxNumber);
        return MaxNumber;
    }

    //调用Java内部搜索函数,当一个数组内出现两个相同的数字时返回值有错
    public static int Search_number_NeiBuDiaoYong ( int[] arr, int number ) {
        // System.out.println("内部调用函数，搜索数组中的某值：");
        return ( Arrays.binarySearch(arr,number) );//如果存在返回的具体的角标位置，不存在返回的是  -插入点-1
    }

    //搜索数组中是否含有该值
    public static int Search_number ( int[] arr, int number ) {
        System.out.println("搜索数组中是否含有该值:");
        int index = -1;
        for ( int i=0; i<arr.length; i++ ) {
            if ( arr[i] == number ) {
                System.out.println("数组中含有该值:arr["+i+"] ="+arr[i]);
                index=i;
                return index;
            }
        }
        if( index == -1 ) {
            System.out.println("数组中不含有该值");
        }
        return index;
    }

    //搜索数组中是否含有该值，若无返回值0 ;若有返回值为1，并打印下标
    public static boolean Search_number_Plus ( int[] arr, int number ) {
        System.out.println("搜索数组中是否含有该值:");
        boolean flag = false;//是否含有要查找的数字-标识符
        for ( int i=0; i<arr.length; i++ ) {
            if ( arr[i] == number ) {
                if ( !flag ) {
                    flag = true;
                    System.out.println("数组中含有该值"+number+": ");
                }
                System.out.print(" arr["+i+"] ");
            }
        }
        if ( !flag ) {
            System.out.println("数组中不含有该值");
        }
        return flag;
    }

    //二分法查找该数组（至少两个元素）中是否含有该值:数组为从小到大排列
    public static int Half_Search ( int[] arr, int number ) {
        System.out.println("二分法查找该数组中是否含有该值:");
        boolean SortWay_Flag = true;//排序方式标志，默认从小到大（升序）
        if ( arr[0] > arr[1] ) SortWay_Flag=false;//排序方式为降序
        int Right_Border = arr.length -1, Left_Border = 0, Mid_Border = (Right_Border+Left_Border)/2;
        while ( arr[Mid_Border] != number ) {
            if ( SortWay_Flag ) {//若数组排列方式为从小到大（升序）
                if ( arr[Mid_Border] > number ) {//数字可能在中左侧
                    Right_Border = Mid_Border - 1;//将右边界移至中左移一格
                } else if ( arr[Mid_Border] < number ) {//数字可能在中右侧
                    Left_Border = Mid_Border + 1;//将左边界移至中右移一格
                }
            } else {//若数组排列方式为从大到小（降序）
                if ( arr[Mid_Border] > number ) {//数字可能在中右侧
                    Left_Border = Mid_Border + 1;//将左边界移至中右移一格
                } else if ( arr[Mid_Border] < number ) {//数字可能在中左侧
                    Right_Border = Mid_Border - 1;//将右边界移至中左移一格
                }
            }
            if ( Right_Border < Left_Border ) return -1;//特殊标识，未搜索到目的数字
                Mid_Border =(Right_Border+Left_Border)/2;
        }
        return Mid_Border;//在有效二分范围时arr[Mid_Border] == number即找到，返回该值
    }

    //二分法查找该数组【方式二】（至少两个元素）中是否含有该值:数组为从小到大排列
    public static int Half_Search_2 ( int[] arr, int number ) {
        System.out.println("二分法查找该数组中是否含有该值("+number+"):");
        boolean SortWay_Flag = true;//排序方式标志，默认从小到大（升序）
        if ( arr[0] > arr[1] ) SortWay_Flag = false;//排序方式为降序
        int Right_Border = arr.length -1, Left_Border = 0, Mid_Border = (Right_Border+Left_Border)/2;

        while ( Left_Border <= Right_Border ) {
            Mid_Border =(Right_Border+Left_Border)/2;
            if ( SortWay_Flag ) {//若数组排列方式为从小到大（升序）
                if ( arr[Mid_Border] > number ) {//数字可能在中左侧
                    Right_Border = Mid_Border - 1;//将右边界移至中左移一格
                } else if ( arr[Mid_Border] < number ) {//数字可能在中右侧
                    Left_Border = Mid_Border + 1;//将左边界移至中右移一格
                } else {
                    return Mid_Border;
                }
            } else {//若数组排列方式为从大到小（降序）
                if(arr[Mid_Border] > number ){//数字可能在中右侧
                    Left_Border = Mid_Border + 1;//将左边界移至中右移一格
                } else if ( arr[Mid_Border] < number ) {//数字可能在中左侧
                    Right_Border = Mid_Border - 1;//将右边界移至中左移一格
                } else {
                    return Mid_Border;
                }
            }
        }
        return -Mid_Border - 1;//在有效二分范围时arr[Mid_Border] == number即找到，返回该值
    }

    public static void reverseArray ( int[] arr ) {//置换数组,将数组的首位交换
        System.out.println("置换数组,将数组的首位交换:");
        for ( int i=0; i<(arr.length)/2; i++ ) {
            Exchange_Arr_a_b(arr,i,(arr.length)-i-1);//交换关于中心对称的下标的值
        }
    }

}

layout: post
title: Java学习笔记
date: 2019/04/05 15:10:30
updated: 2019/04/21 19:12:45
comments: true
tags:
- Java
categories:
- 技术

---
<img src="../../../../uploads/JavaStudyNote.png" class="full-image" />

# 1. Java基础知识

## 1.1. 引用 & 对象
- **对象**：类的实例化，实质为运行时堆内为类内各属性值顺序分配的一组内存空间。<br>类变量(static)只在堆内分配一次，类内方法只在代码段内存一次。
<!-- more -->
- **引用**：传递消息的入口（通过引用访问与之关联的对象的各属性值或调用对象的方法，类似方法调用），引用可不指向对象单独存在（但仅声明无意义）

备注：Java中除基本类型外，其他类型都是类**class**，都能实例化为对象，eg. String

### 1.1.1. Java引用与C/C++指针的区别

- 相同点：
Java中的引用和C/C++中的指针本质上都是通过一个别名，找到要操作的目标（变量对象等），方便在程序里操作

- 不同点：
  - 指针可以改变所指向的对象；引用一旦绑定某个对象后总是指向该对象不可改变。原因：在编译时，
    - 指针变量在符号表上对应的地址值为指针变量的地址值，而引用在符号表上对应的地址值为引用对象的地址值。
    - 符号表生成后就不会再改，因此指针可以改变指向的对象（指针变量中的地址值可以改），而引用对象不能改。
  - 指针在32位系统中占4字节（64位系统中占8字节）；引用为被Java封装后的所指向对象的实际地址
  - 指针声明时不会占内存，用到时才会分配内存；引用（编译时被确定为对象的实际地址）没有实体不占空间
  - 指针可能产生越界访问；引用通过'.'访问所属类的属性值，有边界控制，不会出现越界

### 1.1.2. equals()的引用和对象区别（忽视将会造成重大问题）
- equals()默认行为是比较引用（而非对象的内容），如自定义类调用
- 大多数Java类库实现了equals()可比较对象的内容
```java
Test t1 = new Test(10);
Test t2 = new Test(10);
System.out.println(t1.equals(t2));//输出false，equals()默认行为是比较引用

String s1 = new String("Hello");
String s2 = new String("Hello");
System.out.println(s1.equals(s2));//输出true，Java的String类库实现了equals()比较对象的内容
```

## 1.2. String 用法小记

### 1.2.1. String 当作对象处理需要new
Java将String视为一个对象，而非C/C++中的数据类型
```java
String str1 = new String();
String str2;//只是声明引用，但未与对象关联
```

### 1.2.2. 初始化字符串的其他方法
```java
String str = "Hello World";//静态初始化
String str = new String("Hello World");//创建对象初始化
String str = new String(char Array[]);//将字符数组转化为字符串
String str = new String(str1 + str2);
String str = str1;//实测也是可以的，是根据str1重新分配内存并复制值，并非引用str1
```

### 1.2.3. 访问字符串指定下标的字符
```java
str.charAt(1);//访问索引为1的字符（返回"Hello"中的'e'）
```

### 1.2.4. 判断两个字符串是否相等
```java
str1.equals(str2);//严格区分大小写
str1.equalsIgnoreCase(str2);//不区分大小写
```

### 1.2.5. 比较两个字符串
```java
str1.compareTo(str2);//只有当str1与str2完全相等时才返回0, 否则返回按次序比较第一个不同字符的计算差值 eg:  "aB".compareTo("aC");//会返回'B'-'C'的值-1
```

### 1.2.6. 分割字符串
```java
String str = "Hello world xiao ming";
String[] strArray = str.split(" ");//用空格字符串将上述字符串分割
for (int i = 0; i < strArray.length; i++) {
    System.out.println(strArray[i]);
}
/* 运行结果：
Hello
world
xiao
ming
*/
String str = "Hello world xiao ming";
String[] strArray = str.split(" ", 3);//用空格字符串将上述字符串分割, 最多分3个子串（按空格正常分前两个，最后一个为剩余字符子串）
for (int i = 0; i < strArray.length; i++) {
    System.out.println(strArray[i]);
}
/* 运行结果：
Hello
world
xiao ming
*/
```

### 1.2.7. 查找子串
```java
str.indexOf(String s);//返回子串s第一次出现的下标
str.lastIndexOf(String s);//返回子串s最后出现的下标
```

### 1.2.8. 返回字符串去除前后空格的子串的副本
```java
str = str.trim();//忽略字符串前后空格字符
```

### 1.2.9. 替换子串
将字符串内的部分子串替换为另外子串
```java
String newStr = str.replace("ABC", "abc");//将字符串str内所有“ABC”子串全部替换为“abc”
```

### 1.2.10. 判断字符串是否以目标子串开始或结束
```java
boolean a = str.startsWith("He");//字符串是否以子串“He”开头，返回true
boolean b = str.endsWith("llo");//字符串是否以子串“llo”结尾，返回true
```

### 1.2.11. 转换大小写字符
```java
str = str.toLowerCase();//将字符串内所有大写字符全转换为对应小写字符
str = str.toUpperCase();//将字符串内所有小写字符全转换为对应大写字符
```

## 1.3. 数组用法小记

### 1.3.1. 声明初始化二维数组
```java
int array1[][] = {{0}, {1,2,3}, {4,5,6,7}};
int array2[3][];
array2[0] = new int[1];
array2[1] = new int[3];
array2[2] = new int [4];
```

### 1.3.2. 填充数组
```java
Arrays.fill(array, 8);//将array1数组的所有元素值更改为8
```

### 1.3.3. 排序数组
```java
Arrays.sort(array);//用Java自带的(快排算法)对array1进行排序，默认从小到大
```

### 1.3.4. 复制数组

#### 1.3.4.1. copyOf(int a[], int length);
- 若length小于a.length，创建length大小的数组，然后复制a的前length长度的元素
- 若length大于a.length，创建length大小的数组，复制整个数组a，其后部分默认值0填充
```java
int newArray[] = Arrays.copyOf(array, 5);//复制array前5个元素组成一个新数组
```

#### 1.3.4.2. copyOfRange(int a[], int fromIndex, int toIndex);
创建toIndex-fromIndex大小的数组（可大于原始数组，其后用0填充），复制数组a从下标fromIndex到下标toIndex-1的元素
**备注**：
- 若toIndex-1 > a.length-1，只复制到a[a.length-1]且其后填0
- fromIndex 必须在取值范围[0, a.length-1]内，否则报错

#### 1.3.4.3. 特殊用法，给已固定数组扩容
```java
array = Arrays.copyOf(array, array.length*2);//扩容array一倍，其后扩容的元素默认值为0
```

## 1.4. 产生随机数小记
Java产生随机数的方式有两种：调用Math类的random()方法、调用Random类

### 1.4.1. 调用Math类的random()方法
```java
double num = Math.random();//产生 [0, 1.0) 之间的随机数
double num2 = a + Math.random() * (b - a);//产生 [a, b) 之间的随机数
```

### 1.4.2. 调用Random类
```java
Random r = new Random();//Java运行时JVM以当前系统时间为随机数生成器的种子
Random r2 = new Random(SeedValue);//手动设置种子数值
Random r = new Random();//Java运行时JVM以当前系统时间为随机数生成器的种子
int b = r.nextInt(100);//产生一个在 [0, 100)范围内的整数
boolean c = r.nextBoolean();//产生一个随机布尔值
float d = r.nextFloat();//产生一个随机单精度浮点数
double e = r.nextDouble();//产生一个随机双精度浮点数
double f = r.nextGaussian();//产生一个概率密度为高斯分布的随机双精度浮点数（连续调用一组）
```
**注意**：两次函数调用的时间间隔过小，可能返回相同的随机数。


# 2. Java核心技术

## 2.1. Java类的继承小记
用代码更亲切地展示继承相关细节
```java
//爷爷类
class GrandParents {
    GrandParents(){
        System.out.println("调用爷爷类的构造函数");
    }
    @Override
    protected void finalize() throws Throwable {//无特殊要求非必须，Java垃圾回收机制会自动回收
        System.out.println("销毁爷爷类实例");
        super.finalize();//爷爷类的父类是Object类，Java每个类都直接或间接继承于java.lang.Object类，爷爷类定义等价于class GrandParents extends Object {...}
    }
}
//父类（继承于爷爷类）
class Parents extends GrandParents {
    Parents(String name){
        System.out.println("调用父类:"+name+"的构造函数");
    }
    protected void doSomething(){}
    @Override
    protected void finalize() throws Throwable {//无特殊要求非必须，Java垃圾回收机制会自动回收
        System.out.println("销毁父类实例");
        super.finalize();
    }
}
//子类（继承于父类）
class Childron extends Parents {
    Childron(){
        super("Parents");//父类构造函数有参数时，不能自动调用，只能通过super显示调用父类构造函数
        System.out.println("调用子类的构造函数");
    }
    public void doSomething(){}//重写父类doSomething函数，但修改权限只能不变或放大，不能缩小（若改为private会报错）
    public void doSomething(int a){}//【方法的重载】参数类型不同、参数个数不同、参数顺序不同均可构成重载(仅返回值不同不能构成重载)
    public int doSomething(int... a) {//定义不定长方法
        int sum=0;
        for (int i = 0; i < a.length; i++) {
            sum += a[i];//当作数组来操作参数
        }
        return sum;
    }
    @Override
    protected void finalize() throws Throwable {//无特殊要求非必须，Java垃圾回收机制会自动回收
        System.out.println("销毁子类实例");
        super.finalize();
    }
}

public class Main {
    public static void main(String[] args) {
        Childron c = new Childron();
        System.out.println(c.doSomething(1,2,3,4,5));
        try {
            c.finalize();//手动调用finalize销毁子类实例
        } catch (Throwable throwable) {
            throwable.printStackTrace();
        }
    }
}
//首先实例化父类对象，再实例化子类对象；销毁时先销毁子类再逐级销毁父类实例
/* 运行结果：
调用爷爷类的构造函数
调用父类:Parents的构造函数
调用子类的构造函数
15
销毁子类实例
销毁父类实例
销毁爷爷类实例
*/
```

## 2.2. Object类
Java每个类都直接或间接继承于java.lang.Object类。在Object类中主要包括: clone(), finalize(), equals(), toString()等可重写的方法，及getClass(), notify(), notifyAll(), wait()等不可重写方法（Object中被定义为final类型）

### 2.2.1. getClass()方法
返回对象执行时的Class实例，一般于获取类的名称getName()方法连用
```java
String name = c.getClass().getName();//将返回实例c的类名“Childron”
```

## 2.3. Java 接口小记
接口是抽象类的延伸，可以将它看作是纯粹的抽象类，接口中的所有方法都没有方法体。接口的可以在子类中更灵活地选择方法功能，一个子类可以选择多个接口，然后每个接口类的方法都在该子类中有具体实现，不需要的方法直接不用接口就行，相比于在父类定义虚函数造成代码冗余和不能多继承，接口的出现更方便在子类中按需添加自定义方法。

### 2.3.1. 对比接口与抽象父类 

#### 2.3.1.1. 1.先定义抽象父类实现子类不同方法的需求
```java
//定义抽象四边形类
abstract class Quadrangle {
    abstract void draw();//声明抽象draw方法
    abstract void ba();//声明抽象ba方法
}

//定义一个平行四边形类（假设需要draw方法）
class Rhomboid extends Quadrangle{
    public void draw(){}//重写draw方法以满足要求
    public void ba(){}//虽然不需要ba方法，但却不得不重写ba，否则报错，造成极大代码冗余
}

//定义一个正方形类（假设需要draw方法和ba方法）
class Square extends Quadrangle{
    public void draw(){}//重写draw方法以满足要求
    public void ba(){}//重写ba方法以满足要求
}

//定义一个长方形类（不需要其他方法）
class Rectangle extends Quadrangle {
    void draw(){}//虽然不需要draw方法，但却不得不重写draw，否则报错，造成极大代码冗余
    void ba() {}//虽然不需要ba方法，但却不得不重写ba，否则报错，造成极大代码冗余
}
```

#### 2.3.1.2. 抽象父类缺点：
- 造成极大代码冗余
- 引发逻辑问题，不需要某些方法的子类必须重写抽象父类的所有虚函数，与逻辑不符

#### 2.3.1.3. 2.定义接口，子类灵活选择接口即可
```java
//定义接口 1
interface drwaTest {
    public void draw();//接口内的方法（类型只能是public或abstract）
}
//定义接口 2
interface bala {
    public void ba();
}
//定义四边形类
class Quadrangle {

}
//定义一个平行四边形类（假设需要draw方法），并实现 drwaTest 接口
class Rhomboid extends Quadrangle implements drwaTest{
    public void draw() {
        System.out.println("绘制平行四边形");
    }
}
//定义一个正方形类（假设需要draw方法和ba方法），并实现drwaTest接口与bala接口
class Square extends Quadrangle implements drwaTest, bala {
    public void draw() {
        System.out.println("绘制正方形");
    }
    public void ba() {
        System.out.println("balabala");
    }
}
//定义一个长方形类（不需要其他方法，单纯继承四边形类即可）
class Rectangle extends Quadrangle {
}
```

#### 2.3.1.4. 接口优点：
- 逻辑清晰，随意加减接口，灵活实现
- 精简代码，只需将子类所需的接口中的方法重写即可
- 子类不能继承多个抽象父类（不能多重继承），但子类却可添加多个接口

## 2.4. 异常
常见异常：空指针，数组溢出，被除数为0，…...，自定义异常等。

### 2.4.1. 自定义异常
```java
//自定义异常类型
class MyException extends Exception {
    private String message;
    public MyException(String errorMessage) {
        super(errorMessage);//调用父类构造函数
        this.message = errorMessage;
    }
    public String getMessage() {
        return message;
    }
}
```

### 2.4.2. 捕获异常
```java
public class Main {
    //定义可能会抛出异常的方法，在方法中抛出异常
    static int average(int num1, int num2) throws MyException{
        if (num1 < 0 || num2 < 0) {
            throw new MyException("数字不能为负");//若条件为真执行到throw，在throw抛出异常后，此函数后续部分都不会执行
        }
        if (num1 > 100 || num2 > 100) {
            throw new MyException("数字不能超过100");//若条件为真执行到throw，在throw抛出异常后，此函数后续部分都不会执行
        }
        return (num1 + num2) / 2;
    }

    public static void main(String[] args) {
        int x=102, y=5, z=0;
        boolean isExceptionFlag = true;//是否发生异常标志
        try {
            z = average(x, y);//可能抛出异常的代码，放在try{}内执行，若异常发生就不会执行try{}内的下方代码
            z += x / y;//可能会抛出除数为0异常
            isExceptionFlag = false;//当执行到此处，说明上方函数未发生异常
        } catch (MyException e) {
            // 若捕获到抛出的自定义异常，会执行下面代码
            System.out.println(e.getMessage());//输出异常携带的消息
        } catch (ArithmeticException e) {
            // 捕获异常类型2（除数为0异常），异常处理代码
            System.out.println("除数不能为0");
        } finally {
            //无论是否抛出异常，都会执行此块内代码
            if (isExceptionFlag)
                System.out.println("发生异常");
            else
                System.out.println("未发生异常");
        }
    }
}
/* 
1）当x=102, y=5时，运行结果：
数字不能超过100
发生异常
2）当x=10，y=0时，运行结果：
除数不能为0
发生异常
3）当x=10，y=5时，运行结果：
未发生异常
*/
```

## 2.5. Swing程序设计（跳过）

## 2.6. 集合类
集合类，又称容器。常见的集合类有：List集合, Set集合, Map集合，其中List与Set继承了Collection接口。
![常见集合类的继承关系](../../../../uploads/Inheritance-relationship-of-common-collection-classes.jpg)
**与数组区别**：
- 数组的长度固定，而集合的长度可变；
- 数组存放基本类型的数据，集合存放对象的引用。

### 2.6.1. List集合
List的接口常用的实现类有：**ArrayList**与**LinkedList**。
**ArrayList**：实现了可变长数组，允许保存所有元素，包括null，可根据索引快速访问数组内元素，但插入或删除元素时间较长。
**LinkedList**：采用链表结构存储元素（数组元素上限仅受可用内存限制），类似链表，插入删除元素较快，但随机访问都会从头结点开始顺序向下遍历，故随机访问较慢。
```java
List list1 = new ArrayList<>();
List<String> list2 = new LinkedList<>();

list1.add('a');//添加元素'a'，List元素下标与数组一样从0开始
list1.add('b');//添加元素'b'
list1.remove(1);//删除索引为1的元素
System.out.println(list1);
```

### 2.6.2. Set接口
Set接口的常用实现类有：**HashSet**与**TreeSet**
**HashSet**：由哈希表支持（实际上是一个HashMap实例），不保证Set的迭代顺序（不稳定），允许使用null元素
**TreeSet**：TreeSet实现的Set集合在遍历集合时按照自然顺序递增排序
```java
TreeSet<String> tree = new TreeSet<>();
tree.add("ZhangSan");
tree.add("LiSi");
tree.add("WangWu");

Iterator<String> it = tree.iterator();//Set集合中的所有对象的迭代器
//遍历Set集合
while (it.hasNext()) {
  String tmp = (String)it.next();
  System.out.println(tmp);
}

/* 运行结果（与插入顺序无关，自然递增）
LiSi
WangWu
ZhangSan
*/
```

### 2.6.3. List集合 vs Set集合
- List集合允许元素重复，而Set集合**不能包含重复对象**
- List集合元素顺序为插入顺序（类似数组），而Set集合不保证顺序
- List访问指定索引的元素<code>get(int index)</code>或<code>set<int index, Object obj></code>，而Set集合不能访问指定索引元素

###  2.6.4. Map集合
Map接口的常用实现类有**HashMap**(无序，允许null值)和**TreeMap**(升序，不允许null值)。
 Map提供key到value的映射，Map中不能包含相同的key，每个key只能映射一个value。Key还决定了存储对象在映射中的存储位置，但不是由key本身决定的，而是由key根据"散列技术"产生的散列码整数值（作为偏移量）。
```java
Map<Integer, String> map = new HashMap<Integer, String>();
map.put(1, "ZhangSan");
map.put(2, "LiSi");
map.put(3, "WangWu");
//遍历Map的Key值集合
Set<Integer> s = map.keySet();
Iterator<Integer> it = s.iterator();
while (it.hasNext()){
    System.out.println(it.next());
}
//遍历Map的Value值集合
Collection<String> c = map.values();
Iterator<String> it2 = c.iterator();
while (it2.hasNext()){
    System.out.println(it2.next());
}

/* 运行结果
1
2
3
ZhangSan
LiSi
WangWu
*/
```

## 2.7. 文件File

### 2.7.1. 文件的创建与删除
```java
File file = new File("/Users/haoleeson/Test/test.txt");//创建文件对象（于内存中）,绝对路径
File file1 = new File("/Users/haoleeson/Test/", "test2.txt");//在目录下 创建文件对象（于内存中）,绝对路径
if (file.exists()) {
    file.delete();//删除文件
    System.out.println(file.getName() + "文件已存在, 故删除");
} else {
    try {
        file.createNewFile();//创建该文件（于磁盘中）
        System.out.println(file.getName() + "文件不存在，故创建");
    } catch (IOException e) {
        e.printStackTrace();
    }
}
```

### 2.7.2. File文件的常用方法
```java
String FileName = file.getName();//获取文件名
boolean isReadable = file.canRead();//返回文件是否可读
boolean isWriteable = file.canWrite();//返回文件是否可写
boolean isFileExisted = file.exists();//返回文件是否在该目录（File类型记录路径）存在
long FileLength = file.length();//文件的大小（单位：字节）
String FileAbsolutePath = file.getAbsolutePath();//文件的绝对路径
String FileParentPath = file.getParent();//获取文件所在目录
boolean isAFile = file.isFile();//是否为普通文件（而非目录文件，或链接文件）
boolean isADirectory = file.isDirectory();//是否为一个目录文件
boolean isHiddened = file.isHidden();//判断文件是否为隐藏文件
long lastChangeTime = file.lastModified();//文件最后修改时间

System.out.println("lastChangeTime = " + lastChangeTime);
SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
System.out.println(file.getName() + "文件的最近修改时间为：" + dateFormat.format(new Date(lastChangeTime)));

/* 运行结果
lastChangeTime = 1555158024000
test.txt文件的最近修改时间为：2019-04-13 20:20:24
*/
```

### 2.7.3. 文件输入输出流

#### 2.7.3.1. FileInputStream与FileOutputStream类
操作磁盘文件，可满足简单的文件读写需求。但由于读写操作以字节或字节数组为单位，由于汉字占两个字节，若读取readBuff[]容量设置为单字节，或正好错开一字节会导致汉字乱码。
```java
File file = new File("/Users/haoleeson/Test/test.txt");//创建文件对象（于内存中）,绝对路径

//写文件测试
try {
    //创建FileOutputStream简单文件输出流对象
    FileOutputStream out = new FileOutputStream(file);
    //创建byte数组
    byte writeBuff[] = "写入如下字符串以测试简单文件输出流功能。".getBytes();
    out.write(writeBuff);//将数组中内容写入磁盘
    out.close();
} catch (FileNotFoundException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
}

//读文件测试
try {
    //创建FileOutputStream简单文件读取流对象
    FileInputStream in = new FileInputStream(file);
    byte readBuff[] = new byte[1024]; //创建大小为1KB的读取缓存
    int len = in.read(readBuff);//从文件中读取内容到readBuff数组，并返回读取的内容大小（单位：字节）
    System.out.println("读取到的内容如下：\n" + new String(readBuff, 0, len) + "<END>");//将读到的readBuff数组内Byte类型数据转换为String输出
    in.close();//关闭读取流
} catch (FileNotFoundException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
}

/* 运行结果
读取到的内容如下：
写入如下字符串以测试简单文件输出流功能。
<END>
*/
```

#### 2.7.3.2. FileReader与FileWriter类
能够避免FileInputStream与FileOutputStream类可能出现的汉字读写乱码现象。FileReader流顺序地读取文件，只要不关闭流，每次调用read()方法就顺序地读取源中的内容，直到源的末尾或流被关闭。
```java
File file = new File("/Users/haoleeson/Test/test.txt");//创建文件对象（于内存中）,绝对路径

//写文件操作
try {
    //创建FileWriter文件输出流对象
    FileWriter out = new FileWriter(file);
    String writerStr = "尝试写入如下字符串以测试FileWriter文件输入流功能。\n";
    out.write(writerStr);//将writerStr内容写入磁盘文件中(会清空原文件所有内容)
    out.close();//关闭写文件流
} catch (IOException e) {
    e.printStackTrace();
}

//读文件操作
try {
    //创建FileReader文件读取流对象
    FileReader in = new FileReader(file);
    char readBuff[] = new char[1024]; //创建char类型读取内容数组
    int len = in.read(readBuff);//从文件中读取内容到readBuff数组，并返回读取的内容char数组长度
    in.close();//关闭读文件流
    System.out.println("读取到的内容如下：\n" + new String(readBuff, 0, len) + "<END>");//将读到的readBuff数组内数据转换为String输出
    in.close();//关闭读取流
} catch (FileNotFoundException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
}

/* 运行结果
读取到的内容如下：
尝试写入如下字符串以测试FileWriter文件输入流功能。
<END>
*/
```

#### 2.7.3.3. 带缓存的输入/输出流
**BufferedInputStream**与**BufferedOutputStream**类。BufferedInputStream类可以对所有的InputStream类进行带缓存区的包装以达到性能的优化。
```java
BufferedInputStream(InputStream in);//创建一个带有32个字节的缓存流
BufferedInputStream(InputStream in, int size);//创建一个自定义大小的读取流缓存区
```
BufferedOutputStream类有一个flush()方法可以将缓存区内的数据强制输出到磁盘（无论缓存区满否）
```java
BufferedOutputStream(OutputStream out);//创建一个带有32字节的缓存区
BufferedOutputStream(OutputStream out, int size);//创建一个自定义大小的写出流缓存区
```
**BufferedReader**与**BufferedWriter**类
BufferedReader与BufferedWriter类分别继承Reader类与Writer类。这两个类同样具有内部缓存机制，并可以以行为为单位进行输入输出。
```java
File file = new File("/Users/haoleeson/Test/test.txt");//创建文件对象（于内存中）,绝对路径

//带缓存写文件操作
try {
    //创建FileWriter文件输出流对象
    FileWriter fileWriter = new FileWriter(file);
    //创建带缓存区的输出流
    BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
    String writerStr = "尝试写入如下字符串以测试带缓存区的输出流功能。";
    bufferedWriter.write(writerStr);//将writerStr内容写入缓存区（自动控制，缓存区满自动写入磁盘，避免频繁读写磁盘）
    bufferedWriter.newLine();//将换行符写入文件
    bufferedWriter.close();//关闭写缓存区流
    fileWriter.close();//关闭输出流
} catch (IOException e) {
    e.printStackTrace();
}

//带缓存区读文件操作
try {
    //创建FileReader文件读取流对象
    FileReader fileReader = new FileReader(file);
    //创建带缓存区的读取流
    BufferedReader bufferedReader = new BufferedReader(fileReader);
    String readStr = null;
    int row = 0;
    //如果文件的文本行不为null，则进入循环
    while((readStr = bufferedReader.readLine()) != null) {
        row++;
        System.out.println("读取到第"+ row + "行的内容为：" + readStr);
    }
    System.out.println("<END>");
    bufferedReader.close();//关闭读缓存区流
    fileReader.close();//关闭读取流
} catch (FileNotFoundException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
}

/* 运行结果
读取到第1行的内容为：尝试写入如下字符串以测试带缓存区的输出流功能。
<END>
*/
```
**BufferedReader**类的常用方法如下：
```java
int ch = bufferedReader.read();//读取单个字符(unicode两字节)
System.out.println("ch = " + (char)ch);//输出结果为：尝
String readStr = bufferedReader.readLine();//读取一行
```
**BufferedWriter**类的常用方法如下：
```java
bufferedWriter.write(writerStr, 0, writerStr.length());//写入字符串的某一索引区间内容（此处为全部写入）
bufferedWriter.flush();//强制将缓存区的内容写入到磁盘（不管缓存区满否）
bufferedWriter.newLine();//将换行符写入文件
```

#### 2.7.3.4. 数据输入输出流
**DataInputStream**与**DataOutputStream**类
```java
File file = new File("/Users/haoleeson/Test/test.txt");//创建文件对象（于内存中），绝对路径

//尝试数据输出流
try {
    FileOutputStream fileOutputStream = new FileOutputStream(file);
    DataOutputStream dataOutputStream = new DataOutputStream(fileOutputStream);
    //dataOutputStream.writeBytes("尝试以Byte格式写入内容。");
    //dataOutputStream.writeChars("尝试以Char格式写入内容。");
    dataOutputStream.writeUTF("尝试以UTF格式写入内容。");
    dataOutputStream.close();
    fileOutputStream.close();
} catch (FileNotFoundException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
}

//尝试数据输入流
try {
    FileInputStream fileInputStream = new FileInputStream(file);
    DataInputStream dataInputStream = new DataInputStream(fileInputStream);
    String readStr = dataInputStream.readUTF();//尝试以UTF格式读取文件内容
    System.out.println("以UTF格式读取的内容为: " + readStr + "<END>");
    dataInputStream.close();//关闭数据输入流
    fileInputStream.close();//关闭文件写入流
} catch (FileNotFoundException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
}

/* 运行结果
以UTF格式读取的内容为: 尝试以UTF格式写入内容。<END>
*/
```

#### 2.7.3.5. ZIP压缩输入/输出流（压缩/解压文件）
ZIP压缩管理文件（Zip archive）是一种十分典型的文件压缩形式。常用**ZipOutputStream**与**ZipInputStream**类来实现文件的**压缩**/**解压缩**。

##### 2.7.3.5.1. **压缩文件（ZipOutputStream类）**
若要将某个文件添加到ZIP压缩管理文件内，必须先写入待添加文件的目录进入点（待添加文件在ZIP文件内的位置），并且把待添加文件内容的位置移到此进入点说指的位置，然后再写入文件内容。
```java
import java.io.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

/** 压缩文件类
 * coder：haoleeson
 * Java
 * 20190414*/
public class ZipTest {
    /**
     * 加壳压缩文件函数
     * 输入参数：zipFileName -- 压缩后的文件名，inputFile -- 待压缩文件
     * */
    public void zipFile(String zipFileName, File inputFile) throws Exception {
        File unzipFile = new File(zipFileName);//获取待压缩文件 对象
        String Base = inputFile.getName();//得到待压缩文件名
        ZipOutputStream out = new ZipOutputStream(new FileOutputStream(zipFileName));//新建ZipOutputStream对象
        zip(out, inputFile, Base); //相对目录进入点为空
        out.close();//关闭压缩流
    }
    /**
     * 压缩文件核心函数
     * 输入参数：zipout - 压缩流、file - 待压缩文件、base - 目录进入点
     * 若为单个文件 - 直接拷贝压缩，若为目录文件 - 递归调用自身
     * */
    private void zip(ZipOutputStream zipout, File file, String base) throws Exception {
        //判断文件是否为目录文件
        if (file.isDirectory()) {
            //若问文件夹，列出待压缩文件夹内所有文件
            File[] fl = file.listFiles();//获取路径数组
            //循环遍历待压缩文件夹内的所有文件(可能存在多级文件夹)
            for (int i = 0; i < fl.length; i++) {
                String tmpBase = base + "/" + fl[i].getName();//路径写入点为
                zip(zipout, fl[i], tmpBase);//递归调
            }
        }
        //若为单个文件，直接拷贝压缩
        else {
            zipout.putNextEntry(new ZipEntry(base));//创建新的进入点
            //创建FileInputStream写出流对象
            FileInputStream in = new FileInputStream(file);
            int ch;
            System.out.println("压缩 " + base + " 位置的 " + file.getName() + " 文件 ...");//打印当前目录进入点
            //逐一字节拷贝压缩
            while ((ch = in.read()) != -1) {
                zipout.write(ch);//将字节写入当前ZIP条目
            }
            in.close();//关闭读取流
        }
    }

    public static void main(String[] args) {
        ZipTest zipTest = new ZipTest();
        //尝试压缩
        String zipFileName = "/Users/haoleeson/Downloads/Test.zip";//压缩后得到的文件名
        String inputFile = "/Users/haoleeson/Test/";//待压缩文件（可谓普通文件 或 目录文件）
        System.out.println("尝试压缩 " + inputFile + " 到 " + zipFileName + " ...");
        try {
            zipTest.zipFile(zipFileName, new File(inputFile));//调用加壳压缩文件函数
            System.out.println("压缩完成:)");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
/* 运行结果
尝试压缩 /Users/haoleeson/Test/ 到 /Users/haoleeson/Downloads/Test.zip ...
压缩 Test/test2.txt 位置的 test2.txt 文件 ...
压缩 Test/Second/test3.txt 位置的 test3.txt 文件 ...
压缩 Test/Second/Third/test4.txt 位置的 test4.txt 文件 ...
压缩 Test/Second/test3的副本.txt 位置的 test3的副本.txt 文件 ...
压缩 Test/test2的副本.txt 位置的 test2的副本.txt 文件 ...
压缩 Test/test.txt 位置的 test.txt 文件 ...
压缩完成:)
*/
```

##### 2.7.3.5.2. **解压缩文件（ZipInputStream类）**
若要从ZIP压缩管理文件内提取某个文件，要先找到待提取文件的目录进入点（该文件在ZIP文件内的位置），才能读取这个文件的内容。
```java
import java.io.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;
import java.util.zip.ZipInputStream;

/** 解压缩类
 * coder：haoleeson
 * Java
 * 20190414*/
public class UnzipTest {
    /**
     * 解压缩文件方法，解压到当前目录
     * 参数：unZipFileName -- 待解压缩文件名（含路径）
     * */
    void Unzip(String unZipFileName) throws Exception {
        File unzipFile = new File(unZipFileName);//获取待压缩文件 对象
        String finalPath = unzipFile.getParentFile() + "/";//得到待解压缩文件的绝对路径
        ZipFile zipFile = new ZipFile(unzipFile);//创建Zip压缩文件 对象
        ZipInputStream zipInputStream = new ZipInputStream(new FileInputStream(unzipFile));//实例化解压缩ZipInputStream对象
        ZipEntry entry;

        //迭代解压缩所有目录树上的文件（包括目录文件）
        while ((entry=zipInputStream.getNextEntry())!=null && !entry.isDirectory()) {
            File tmp = new File(finalPath + entry.getName());//解压出的文件路径
            //如果文件不存在
            if (!tmp.exists()) {
                tmp.getParentFile().mkdirs();//创建父类文件夹路径
                OutputStream writeStream = new FileOutputStream(tmp);//将文件目录中的文件放入输出流
                System.out.println("解压缩 " + tmp.getAbsolutePath() + " 文件 ...");
                //用输入流读取压缩文件中制定目录中的文件
                InputStream readStream = zipFile.getInputStream(entry);
                int ch = 0;
                while ((ch = readStream.read()) != -1) {
                    writeStream.write(ch);
                }
                writeStream.close();//关闭写文件流
                readStream.close();//关闭读文件流
            }
            zipInputStream.closeEntry();//关闭当前Entry
        }
        zipInputStream.close();//关闭解压缩流
        System.out.println("解压缩已完成:)");
    }

    public static void main(String[] args) {
        UnzipTest unzipTest = new UnzipTest();
        String unzipFileName = "/Users/haoleeson/Downloads/Test.zip";//待解压缩文件名（含路径）
        try {
            unzipTest.Unzip(unzipFileName);//尝试解压缩
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
/* 运行结果
解压缩 /Users/haoleeson/Downloads/Test/test2.txt 文件 ...
解压缩 /Users/haoleeson/Downloads/Test/Second/test3.txt 文件 ...
解压缩 /Users/haoleeson/Downloads/Test/Second/Third/test4.txt 文件 ...
解压缩 /Users/haoleeson/Downloads/Test/Second/test3的副本.txt 文件 ...
解压缩 /Users/haoleeson/Downloads/Test/test2的副本.txt 文件 ...
解压缩 /Users/haoleeson/Downloads/Test/test.txt 文件 ...
解压缩已完成:)
*/
```

## 2.8. 多线程
在Java中可通过继承java.lang.Thread类与实现java.lang.Runnable接口两种方式。

### 2.8.1. Theard类与Runnable类实现线程区别
Thread实现必须继承Thread类，而继承Runnable接口则更方便

### 2.8.2. 继承Thread类
```java
import java.lang.Thread;

public class TestThread extends Thread {
    public TestThread(String name) {
        super(name);//调用父类Thread构造函数，给线程命名
    }
    //重写run()方法实现线程执行的操作
    public void run() {
        int i = 0;
        while (++i < 5) {
            System.out.println(i + ":" + this.getName());
            //延时方式1：
//            for (long k=0; k<100000000; k++);//阻塞式延时，不推荐（占CPU）
            //延时方式2：
            try {
                Thread.sleep(1000);//线程休眠1秒，推荐（让出CPU）
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public static void main(String[] args) {
        int i = 0;
        Thread test1 = new TestThread("A");//定义线程"A"
        Thread test2 = new TestThread("BBB");//定义线程"BBB"
        test1.start();//启动线程"A"
        test2.start();//启动线程"BBB"
        while (true) {//主线程在while死循环内
            System.out.println((i++) + ":Main");//Main主线程执行
            try {
                Thread.sleep(600);//主线程延时
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if (i > 100) break;
        }
    }
}
/* 运行结果
1:A
1:BBB
0:Main
1:Main
2:BBB
2:A
2:Main
3:Main
3:A
3:BBB
4:Main
4:A
4:BBB
5:Main
6:Main
7:Main
...(主函数仍在while循环)...
*/
```
由此可知同一进程内的子线程，它们的运行先后顺序是随机的。

### 2.8.3. 实现Runnable接口
```java
import java.lang.Runnable;
import java.lang.Thread;

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
                    Thread.sleep(1000);//线程休眠1秒
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
        test1.start();//启动线程1（关联的对象“A”）
        test2.start();//启动线程2（关联的对象“BBB”）
    }
}
/* 运行结果
1:A
1:BBB
2:A
2:BBB
3:A
3:BBB
4:BBB
4:A
*/
```

### 2.8.4. 操作线程的方法

#### 2.8.4.1. 线程休眠
```java
try {
    Thread.sleep(1000);//线程休眠1秒
} catch (InterruptedException e) {
    e.printStackTrace();
}
```
sleep()方法通常在run()方法内循环使用，因sleep()方法的执行有可能抛出InterruptedException异常，所以需放在try-catch块中，该线程在1秒休眠结束后会进入**就绪态**（不一定是**运行态**）。

#### 2.8.4.2. 线程的加入（join()方法）
在当前线程A新建一个线程B，线程B调用join()方法，当线程A放弃CPU使用后执行线程B，只有线程B执行完毕后，才继续执行线程A。
```java
import java.lang.Runnable;
import java.lang.Thread;

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
                        threadB.join();      // 线程B调用join()方法
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    if (++countA > 5) break;
                }
            }
        });
        threadA.start();                     // 启动线程A

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
        threadB.start();                   // 启动线程B
    }
    public static void main(String[] args) {
        TestJoin t = new TestJoin();
    }
}
/* 运行结果
A: 0
B: 0
B: 1
B: 2
B: 3
B: 4
B: 5
A: 1
A: 2
A: 3
A: 4
A: 5
*/
```
**线程的中断**
提倡在线程run()方法中使用无限循环的形式，用一个布尔型标记控制循环的停止。（而不是JDK已废除的stop()方法）
```java
import static java.lang.Thread.sleep;

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
/* 运行结果
1. Hello...
2. Hello...
3. Hello...
*/
```

### 2.8.5. 线程的优先级
每个线程都具有各自的优先级，系统会从多个处于**就绪状态**选择优先级最高的线程进入运行状态（优先级较低的线程也有机会运行）。可用setPriority()方法调整线程优先级（优先级范围：1～10，设置需在线程执行start()前）

### 2.8.6. 线程同步

#### 2.8.6.1. 线程安全
线程安全问题源于：多个线程同时存取单一对象的数据。
```java
/**
 * 测试线程不安全实例
 * -- 多个线程同时读写单一对象数据时，可能引发的安全问题
 * eg. 未考虑线程安全的对线程买票（不安全）
 * */
public class TestThreadUnsafe implements Runnable {
    int leftNum = 5;//设置剩余票数
    int purchaseTime = 0;//统计买票次数

    @Override
    public void run(){
        int readValue;//定义读取值
        while(true){
            if ((readValue = leftNum) > 0) {
                try {
                    Thread.sleep(100);//线程休眠0.1秒, 模仿买票操作用时
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("ReadLeftNum = " + readValue + ", After Purchase leftNum = " + --leftNum);//购票，将剩余票数减一
                purchaseTime++;//统计已购买票次数变量 +1
            } else {
                break;
            }
        }
    }

    public static void main(String[] args) {
        TestThreadUnsafe testThreadUnsafe = new TestThreadUnsafe();//实例化类对象
        //以下实例化四个子线程
        Thread threadA = new Thread(testThreadUnsafe);
        Thread threadB = new Thread(testThreadUnsafe);
        Thread threadC = new Thread(testThreadUnsafe);
        Thread threadD = new Thread(testThreadUnsafe);
        System.out.println("不安全的多线程演示：\n总票数：" + testThreadUnsafe.leftNum);
        //启动四个子线程
        threadA.start();
        threadB.start();
        threadC.start();
        threadD.start();
        //主线程休眠
        try {
            Thread.sleep(3000);//主线程休眠3秒(足够这四个子线程买票)
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("总共买票次数：" + testThreadUnsafe.purchaseTime);
    }
}
/* 运行结果
不安全的多线程演示：
总票数：5
ReadLeftNum = 5, After Purchase leftNum = 4
ReadLeftNum = 5, After Purchase leftNum = 3
ReadLeftNum = 5, After Purchase leftNum = 2
ReadLeftNum = 5, After Purchase leftNum = 1
ReadLeftNum = 4, After Purchase leftNum = 0
ReadLeftNum = 3, After Purchase leftNum = -1
ReadLeftNum = 1, After Purchase leftNum = -2
ReadLeftNum = 1, After Purchase leftNum = -3
总共买票次数：8
*/
```
从运行结果可看出最后打印的剩余票数值为负值，这时因为有两个线程读取值的时候leftNum值时为1（满足leftNum>0）的时刻，已有其他线程进入"购票操作"只不过还未修改值，这就导致当最终这两个线程此时读到还有票，但等到其他线程完成修改值后（票数已为负），仍然执行-1操作导致票数为负。

#### 2.8.6.2. 线程同步机制

##### 2.8.6.2.1. synchronized (""){}同步块
```
//同步锁
synchronized (Object){
    //Do something...
}
```
考虑线程同步机制的多线程买票程序实现如下：
```java
/**
 * 测试线程安全-1
 * -- 多个线程同时读写单一对象数据时(加同步锁)，避免引发安全问题
 * eg. 对于多线程买票问题，考虑线程同步机制（安全）
 * */
public class TestThreadSafe implements Runnable{
    int leftNum = 5;//设置剩余票数
    int purchaseTime = 0;//统计买票次数

    @Override
    public void run() {
        int readValue;//定义读取值
        while(true){
            //同步锁
            synchronized (""){
                if((readValue = leftNum) > 0){
                    try {
                        Thread.sleep(100);//线程休眠0.1秒, 模仿买票操作用时
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println("ReadLeftNum = " + readValue + ", After Purchase leftNum = " + --leftNum);//购票，将剩余票数减一
                    purchaseTime++;//统计已购买票次数变量 +1
                } else {
                    break;
                }
            }
        }
    }

    public static void main(String[] args) {
        TestThreadSafe testThreadSafe = new TestThreadSafe();//实例化类对象
        //以下实例化四个子线程
        Thread threadA = new Thread(testThreadSafe);
        Thread threadB = new Thread(testThreadSafe);
        Thread threadC = new Thread(testThreadSafe);
        Thread threadD = new Thread(testThreadSafe);
        System.out.println("安全的有线程同步机制的多线程演示：\n总票数：" + testThreadSafe.leftNum);
        //启动四个子线程
        threadA.start();
        threadB.start();
        threadC.start();
        threadD.start();
        //主线程休眠
        try {
            Thread.sleep(3000);//主线程休眠3秒(足够这四个子线程买票)
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("总共买票次数：" + testThreadSafe.purchaseTime);
    }
}
/* 运行结果
安全的有线程同步机制的多线程演示：
总票数：5
ReadLeftNum = 5, After Purchase leftNum = 4
ReadLeftNum = 4, After Purchase leftNum = 3
ReadLeftNum = 3, After Purchase leftNum = 2
ReadLeftNum = 2, After Purchase leftNum = 1
ReadLeftNum = 1, After Purchase leftNum = 0
总共买票次数：5
*/
```
相比于上一个未考虑线程同步的例子来说，这个考虑线程同步只是将线程对关键的单一对象数据的存取操作放在了synchronized (""){}同步块内，Java的同步机制会保证单位时刻最多只有一个线程在执行同步块内的操作，所以能达到线程同步效果避免不安全。
synchronized关键字修饰的同步方法
```java
synchronized ElementType function(){
    //Do something...
}
```
考虑线程同步机制的多线程买票程序实现如下：
```java
/**
 * 测试线程安全-2
 * -- 多个线程同时读写单一对象数据时(加同步锁)，避免引发安全问题
 * eg. 对于多线程买票问题，考虑线程同步机制（安全）
 * */
public class TestThreadSafe2 implements Runnable{
    int leftNum = 5;//设置剩余票数
    int purchaseTime = 0;//统计买票次数

    //synchronized关键字修饰的"买一张票"的同步方法
    synchronized boolean purchaseAticket(){
        int readValue;//定义读取值
        if((readValue = leftNum) > 0){
            try {
                Thread.sleep(100);//线程休眠0.1秒, 模仿买票操作用时
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("ReadLeftNum = " + readValue + ", After Purchase leftNum = " + --leftNum);//购票，将剩余票数减一
            purchaseTime++;//统计已购买票次数变量 +1
            return true;//成功买票，返回true
        }
        return false;//买票失败，返回false
    }

    @Override
    public void run() {
        while(purchaseAticket());
    }

    public static void main(String[] args) {
        TestThreadSafe2 testThreadSafe = new TestThreadSafe2();//实例化类对象
        //以下实例化四个子线程
        Thread threadA = new Thread(testThreadSafe);
        Thread threadB = new Thread(testThreadSafe);
        Thread threadC = new Thread(testThreadSafe);
        Thread threadD = new Thread(testThreadSafe);
        System.out.println("安全的有线程同步机制的多线程演示：\n总票数：" + testThreadSafe.leftNum);
        //启动四个子线程
        threadA.start();
        threadB.start();
        threadC.start();
        threadD.start();
        //主线程休眠
        try {
            Thread.sleep(3000);//主线程休眠3秒(足够这四个子线程买票)
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("总共买票次数：" + testThreadSafe.purchaseTime);
    }
}
/* 运行结果
安全的有线程同步机制的多线程演示：
总票数：5
ReadLeftNum = 5, After Purchase leftNum = 4
ReadLeftNum = 4, After Purchase leftNum = 3
ReadLeftNum = 3, After Purchase leftNum = 2
ReadLeftNum = 2, After Purchase leftNum = 1
ReadLeftNum = 1, After Purchase leftNum = 0
总共买票次数：5
*/
```
与第二种用**synchronized (""){}**同步块用修饰不同之处在于，这种是通过**synchronized**关键字修饰的同步方法，单位时间内，最多只有一个线程执行该方法purchaseAticket()，所以能达到线程同步效果避免不安全。

## 2.9. 网络通信

### 2.9.1. 网络协议

#### 2.9.1.1. IP协议

IP是Internet Protocol的简称，它是一种网络协议。Internet采用的协议是TCP/IP协议。

#### 2.9.1.2. TCP传输控制协议(Transmission Control Protocol)

TCP协议是一种 以固接线为基础的协议，它提供两台计算机间可靠的数据传送。

特征：

- 保证数据能够确实送达
- 抵达的数据排列顺序与送出时的顺序相同

因此，TCP协议适合可靠性要求较高的场合（HTTP、FTP和Telnet等都需要使用可靠的通信频道）

#### 2.9.1.3. UDP用户数据协议(User Datagram Protocol)

UDP是无线连接通信协议，不保证可靠数据的传输。

特征：

- 能够向若干个目标发送数据
- 能够接收发自若干个源的数据
- 接收多个数据包时不保证接收数据包的顺序与源发送顺序相同

因此 ，UDP协议适合一些对数据准确性要求不高，对传输速度和时效要求非常高但允许小部分数据包丢失或传送顺序有所不同也不会严重损害需求的场合(如：网络聊天室、在线影片等)
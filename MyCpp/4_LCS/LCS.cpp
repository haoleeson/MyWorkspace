/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int MaxNum(int firstNum, int secondNum){
    return firstNum > secondNum ? firstNum : secondNum;
}

//定义数组结构体
struct matrix{
    int num;
    int direct;
};

typedef matrix Matrix;

int LCS(char *strA, char *strB, int lengthA, int lengthB, Matrix *resultMatrix[]){
    //若i = 0 或 j = 0， 返回 0
    if (lengthA == 0 || lengthB == 0) {
        return 0;
    }
    //初始化存储数组
    for (int i = 0; i <= lengthA; i++) {
        for (int j = 0; j <= lengthB; j++) {
            resultMatrix[i][j].num = 0; //设置所有默认的最长为0
            resultMatrix[i][j].direct = 1; //所有默认方向变成上 0斜上，1上，-1左
        }
    }
    for(int j=0; j<=lengthB; j++){
        resultMatrix[0][j].direct = -1;
    }
    for (int i = 0; i < lengthA; i++) {
        for (int j = 0; j < lengthB; j++) {
            //若字符串A，字符串B 末尾元素相同
            if (strA[i] == strB[j]) {
                resultMatrix[i+1][j+1].num = resultMatrix[i][j].num + 1;
                resultMatrix[i+1][j+1].direct = 0;
            }
            //否则，分别计算子问题求最大
            else{
                resultMatrix[i+1][j+1].num = MaxNum(resultMatrix[i+1][j].num, resultMatrix[i][j+1].num);
                resultMatrix[i+1][j+1].direct = resultMatrix[i+1][j].num > resultMatrix[i][j+1].num ? (-1) : 1;
            }
        }
    }
    return resultMatrix[lengthA][lengthB].num;
}

int main(int argc, const char * argv[]) {
    char strA[] = {"xzyzzyx"};
    char strB[] = {"zxyyzxz"};
//    char strA[] = {"MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCALLAAQANKESSSESFISRLLAIVAD"};
//    char strB[] = {"MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCTLLAAQANKENSNESFISRLLAIVAG"};
    
    int lengthA = (int)strlen(strA);
    int lengthB = (int)strlen(strB);
    Matrix *resultMatrix[lengthA+1];
    for (int i = 0; i <= lengthA; i++) {
        resultMatrix[i] = (Matrix*)malloc(sizeof(struct matrix)* (lengthB+1));
    }
    int max = LCS(strA, strB, lengthA, lengthB, resultMatrix);
    cout << "max = " << max << endl;
    vector<char> result_LCS;
//    //输出resultMatrix
//    for(int i=0; i<=lengthA; i++){
//        for(int j=0; j<=lengthB; j++){
//            if(i==0){
//                cout << "\t\t\t" << resultMatrix[i][j].direct<<","<<strB[j-1];
//            }else if(j==0){
//                cout << "\t\t\t" << resultMatrix[i][j].direct<<","<<strA[i-1];
//            }else{
//                cout << "\t\t\t" << resultMatrix[i][j].direct<<","<<resultMatrix[i][j].num<<","<<strA[i-1]<<","<<strB[j-1];
//            }
//        }
//        cout << endl;
//    }
    //便利二维数组，求解最长公共子序列
    //所有默认方向变成上 0斜上，1上，-1左
    int i=lengthA, j=lengthB;
    while(true){
        int k = resultMatrix[i][j].direct;
        switch (k){
            case 0:
//                cout << "(" << i << ", " << j << ") " << strA[i-1] << endl;
                result_LCS.push_back(strA[i-1]);
                i--;
                j--;
                break;
            case -1:
                j--;
                break;
            case 1:
                i--;
                break;
            default:
                cout << "something Error!!!" << endl;
                break;
        }
        if(i==0 || j==0) break;
    }
//    cout << "result_LCS.size()=" << result_LCS.size() << endl;
    //输出结果
    for(int i=result_LCS.size()-1; i>=0; i--){
        cout <<result_LCS[i];
    }
    return 0;
}

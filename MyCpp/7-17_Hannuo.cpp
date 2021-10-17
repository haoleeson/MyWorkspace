#include <iostream>
#include <math.h>
using namespace std;
//the flag to show GuoChen
#define isshowGuoChenFlag false
#define TheMaxNsize 100

//第0位置是柱子上的塔盘数目
int zhua[TheMaxNsize]= {0}, zhub[TheMaxNsize]= {0}, zhuc[TheMaxNsize]= {0};
//

char charis ( char x, int n );//左右字符出现顺序固定，且根据n值奇偶尔不同
void print ( char StartPillar, char EndPillar );//打印字符
void Hannuo ( int n );//Hannuo


int main (void) {
    int n;
    if(isshowGuoChenFlag)
        cout << "Input the Hannuo num :";
    cin >> n;
    zhua[0] = n;
    for( int i=1; i<=n; i++ ) {
        zhua[i] = n-i+1;
    }
    Hannuo ( n );
    return 0;
}

//左右字符出现顺序固定，且根据n值奇偶尔不同
char charis ( char x, int n ) {
    switch ( x ) {
        case'a':
            return(n%2==0)?'c':'b';
        case'b':
            return(n%2==0)?'a':'c';
        case'c':
            return(n%2==0)?'b':'a';
        default:
            return'0';
    }
}

//打印字符
void print ( char StartPillar, char EndPillar ) {
    if( StartPillar == 'a' ) {
        switch ( EndPillar ) {
            case'b':
                zhub[0]++;
                zhub[zhub[0]]=zhua[zhua[0]];
                zhua[zhua[0]]=0;
                zhua[0]--;
                break;
            case'c':
                zhuc[0]++;
                zhuc[zhuc[0]]=zhua[zhua[0]];
                zhua[zhua[0]]=0;
                zhua[0]--;
                break;
            default:
                break;
        }
    }
    if( StartPillar == 'b' ) {
        switch ( EndPillar ) {
            case'a':
                zhua[0]++;
                zhua[zhua[0]]=zhub[zhub[0]];
                zhub[zhub[0]]=0;
                zhub[0]--;
                break;
            case'c':
                zhuc[0]++;
                zhuc[zhuc[0]]=zhub[zhub[0]];
                zhub[zhub[0]]=0;
                zhub[0]--;
                break;
            default:
                break;
        }
    }
    if( StartPillar == 'c' ) {
        switch ( EndPillar ) {
            case'a':
                zhua[0]++;
                zhua[zhua[0]]=zhuc[zhuc[0]];
                zhuc[zhuc[0]]=0;
                zhuc[0]--;
                break;
            case'b':
                zhub[0]++;
                zhub[zhub[0]]=zhuc[zhuc[0]];
                zhuc[zhuc[0]]=0;
                zhuc[0]--;
                break;
            default:
                break;
        }
    }
    if(isshowGuoChenFlag) {
        cout << "\t|a: ";
        for( int i=1; i<=zhua[0]; i++) {
            cout << zhua[i] << " ";
        }
        cout << " |b: ";
        for( int i=1; i<=zhub[0]; i++) {
            cout << zhub[i] << " ";
        }
        cout << " |c: ";
        for(int i=1; i<=zhuc[0]; i++) {
            cout << zhuc[i] << " ";
        }
    }
    cout << endl;
}

//Hannuo
void Hannuo(int n) {
//分配2^n个空间
    bool* isrev;
    isrev = (bool*) malloc( sizeof(bool)*(int)pow(2,n) );
    for( int i=1; i<pow(2,n); i++ ) {
        isrev[i]=false;
    }
    //循环计算是否逆序
    for( int ci=2; ci<=n; ci++ ) {
        for( int zixh=(int)pow(2,ci-1); zixh<pow(2,ci); zixh+=4 )
            //初始值重复一次，自增值可加4，减少循环次数。
            isrev[zixh] = isrev[ (int)pow(2,ci) - zixh ];
        //该位置为中间位置，且奇次幂逆序，偶数幂不逆序
        isrev[ (int)pow(2,ci) ] = ( (ci-1)%2==0 ) ? false : true;
    }
    char StartPillar='a', EndPillar;
    EndPillar=( n%2==0 ? 'b' : 'c' );
    if(isshowGuoChenFlag)
        cout << "1\t";
    cout << StartPillar << "->" << EndPillar;
    print ( StartPillar, EndPillar );
    for( int k=2; k<pow(2,n); k++ ) {
        if ( k%2==0 ) {
            EndPillar = charis( StartPillar, n );
        } else {
            StartPillar = charis( EndPillar, n );
        }
        if(isshowGuoChenFlag)
            cout << k << "\t";
        if( isrev[k] ) {
            cout << EndPillar << "->" << StartPillar;
            print ( EndPillar, StartPillar );
        } else {
            cout << StartPillar << "->" << EndPillar;
            print ( StartPillar, EndPillar );
        }
    }
}


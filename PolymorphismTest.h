#ifndef POLYMORPHISMTEST_H_
#define POLYMORPHISMTEST_H_

/**参数多态**/
template<class T>
//基类：图形
class shape {
    public:
        /**过载多态：不带参数**/
        shape () {
            bottomLength = 0;
            height = 0;
        }
        /**过载多态：带1个参数**/
        shape ( T value ) {
            bottomLength = value;
            height = value;
        }
        /**过载多态：带2个参数**/
        shape ( T value1, T value2 ) {
            bottomLength = value1;
            height = value2;
        }
        //求图形面积
        virtual T getArea () {
            return bottomLength*height;
        }
    protected:
        T bottomLength; //底边长
        T height; //高
};

/**参数多态**/
template<class T>
//派生：三角形类
class Triangle : public shape<T> {
public:
    /**包含多态**/
    T getArea () {
        return ( this->bottomLength * this->height / 2 );
    }
    Triangle ( T value1, T value2 ) {
        this->bottomLength = value1;
        this->height = value2;
    }
};

/**参数多态**/
template<class T>
//派生：矩形类
class Rectangle : public shape<T> {
public:
    /**包含多态**/
    T getArea () {
        return ( this->bottomLength * this->height );
    }
    Rectangle ( T value1, T value2 ) {
        this->bottomLength = value1;
        this->height = value2;
    }
};

#endif



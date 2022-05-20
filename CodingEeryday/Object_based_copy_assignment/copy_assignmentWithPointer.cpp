#include <iostream>
#include <cstddef>
//4大函数中的拷贝赋值函数和析构函数，但是二者要建立在构造函数和拷贝构造函数基础上的
class Point{
    public: 
       int x;
       int y;
    //下面是编译器默认生成的拷贝构造函数
    Point(const Point& c)//成员初始化列表只能用于构造器
          :x(c.x),y(c.y)
    {

    }
    Point(int a,int b)
               :x(a),
                y(b)
    {
    }
    Point& operator =(const Point& c)
    {
       this->x=c.x;
       this->y=c.y;
       return *this;
    }
};
//一个空类相当于下面的四个函数的展开
class Rectangle
{
private:
    Point* m_leftUp;//类里的指针对象默认是堆指针
    int    m_length;
    int    m_width;
public:
 Rectangle(int x,int y,int length,int width)
          :m_leftUp(new Point{x,y}),//Point *m_leftUp=new Point{x,y};
           m_length(length),
           m_width(width)
  { }
 ~Rectangle()
  { 
      delete m_leftUp;
  }
  Rectangle(const Rectangle& rect)
           :m_leftUp{new Point(*(rect.m_leftUp))},//这个地方还是需要多练习，打个问号？
            m_length{rect.m_length},
            m_width{rect.m_width} 
            {
              std::cout<<"cop ctor"<<std::endl;
            }
  //赋值操作运算符，细分为4种情况
  Rectangle& operator=(const Rectangle& rect)//返回值是引用时候，非常少见，这是其中之一
    {   
      if(this==&rect)
      {
          return *this;//防止自己给自己赋值
      }                
                       //先拷贝一下基本数据成员
      this->m_length=rect.m_length;
      this->m_width=rect.m_width;
                       //
      if (rect.m_leftUp!=nullptr)
      {
          if (m_leftUp!=nullptr)
          {
                *m_leftUp=*(rect.m_leftUp);//这个语句非常的难，左侧一开始写成了*this
                                           //调用赋值操作符
                                           //堆指针对象的赋值方法
                                           //这个赋值不是为了传递指针地址而是value                                           
          }
          else
          {
                 m_leftUp=(new Point(*rect.m_leftUp));//如果当前对象m_leftUp为空，来啥地址的指针，要啥                                                      
                                                      //调用拷贝构造函数
                                                      //这里的*是解引用，而不是指针含义
                                                      //*rect.m_leftUp案例中告知了“.”运算符优先,"*"其次
          }
          
      }
      else
      {
          delete m_leftUp;//当前对象就算是nullptr，多删除一次也是没有关系的
          m_leftUp=nullptr;
      }
     return *this; 
   }
};
int main(int argc, char const *argv[])
{
    /* code */
    Rectangle r1(1,2,3,4);
    Rectangle r2{r1};
    Rectangle r3(2,4,6,8);
      r3=r1;
    //r3.operator=(r1);
      r2=r3=r1;
    //r2.operator=(r3.operator=(r1));
    return 0;
}

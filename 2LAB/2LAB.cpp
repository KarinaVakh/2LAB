#include <iostream>
#include <conio.h>
using namespace std;

class Point 
{
protected:
     int x, y; 
public:
    Point() //конструктор без параметров
    {
       
        x = 0;
        y = 0; 
        printf("Point(%d, %d)\n", x, y);
    }
    Point(int x, int y) //конструктор с параметрами
    {
      //  printf("Point(int x, int y)%d %d\n",x ,y );  
      printf("Point(%d, %d)\n",x ,y);
        this->x = x;
        this->y = y; 
    }
    Point(const Point& p) //конструктор копирования
    {
       
       printf("Point(const Point &p)\n");  
        x = p.x;
        y = p.y; 

    }
    ~Point() 
    {
        printf("~Point(%d, %d)\n", x, y); 
       // printf("~Point()\n");
    }

    void move(int dx, int dy) 
    {
        x = x + dx;
        y = y + dy;
    }

    void reset(); 
    
};

void Point::reset() 
{
    x = 0;
    y = 0;
}

class ColoredPoint :public Point 
{ 
protected:
    int color;

public:
    ColoredPoint() :Point() 
    {
        printf("ColoredPoint()\n");  
        color = 0; 
    }

    ColoredPoint(int x, int y, int color) :Point(x, y) 
    {
        printf("ColoredPoin(%d, %d, %d)\n", x, y, color);
       // printf("ColoredPoint(int x, int y, int color)\n");  
        this->color = color;
    }

    ColoredPoint(const ColoredPoint& p) 
    {
        printf("ColoredPoint(const Point &p)\n");  
        color = p.color;
         x = p.x;
        y = p.y; 
    }
    ~ColoredPoint()
    { 
        printf("~ColoredPoint(%d, %d color=%d)\n", x, y, color); 
      //  printf("~ColoredPoint()\n");
    }

    void change_color(int new_color) 
    {
        color = new_color;

    }
};


class Section
{  
protected:
    Point* p1; 
    Point* p2;
public:
    Section() 
    {
        printf("Section()\n");  
        p1 = new Point; // при создании отрезка по умолчанию отрезок должен сам себе создать 2 точки
        p2 = new Point;// конструктор создаст две точки с нулевыми координатами
    }

    Section(int x1, int y1, int x2, int y2)
    {
        printf("Section(int x1, int y1, int x2, int y2)\n"); 
        p1 = new Point(x1, y1);  //у точек уже есть конструкторы 
        p2 = new Point(x2, y2);
    }

    Section(const Section& s)
    {
        printf("Section(const Section &p)\n"); 
        // второй вариант копирования мы дожны ввзят тот отрезок котрый нам передли и  его первую точку  и создать тчную копию этой точки путем вызова констр копировани точки (s - обьект, п1  указатель на поинт поэтому мы долдны его разыменрваь*()
        p1 = new Point(*(s.p1));
        p2 = new Point(*(s.p2));
    }

    ~Section()
    { // деструктор
        delete p1;
        delete p2;
        printf("~Section()\n");
    }
};

class Ray 
{  
protected:
    Point p3;
public:
    Ray() 
    {
        printf("Ray()\n");  
        p3 = *new Point; 
    }

    Ray(int x, int y)
    {
        printf("Ray(int x, int y)\n");
        p3 = *new Point(x, y);  
    }

    Ray(const Ray& s)
    {
        printf(" Ray(const Ray& s)\n");  
       p3 = *new Point(s.p3);
    }

    ~Ray()
    { // деструктор
        printf("~Ray()\n");
    }
};


int main(int arg, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    { 
        cout << "Задаём объект статически\n";
        Point p; // задаем обьекты статически
        Point p2(10, 20); // задаем обьекты статически
        Point p3(p2);    
    }

    {
        cout << "\nЗадаём объект динамически\n";
        Point* p = new Point; // указатели динамически обьекты
        Point* p2 = new Point(10, 20); 
        Point* p3 = new Point(*p2);   
        delete p;
        delete p2; 
        delete p3;
    }

    
// для мув
    {
        cout << "\nМетод move\n";
        Point* p = new Point(1, 2); 
    p->reset();     
    p->move(10, 10); 
    delete p;
    // при удалении координаты точки другие
    }

    // для подкласса // при создании обьекта кдаса калор пинт сначал запуск конструктор поинта потом калор потом он удаляется и диструктор калор поинта и дистрк поинта
    {
       
        ColoredPoint* p = new ColoredPoint(1, 2, 42);  
        delete p;
    }


    {
        cout << "\nОбъект  ColoredPoint поместили в Point \n";
        Point* p = new ColoredPoint(1, 2, 42); 
        delete p;

    }

    {cout << "\nОбъект  ColoredPoint поместили в Point и Объект  ColoredPoint поместили в переменную своего собственного класса \n";
        Point* p1 = new ColoredPoint(1, 2, 42);    
        delete p1;
        ColoredPoint* p2 = new  ColoredPoint(1, 2, 42);
        delete p2;
    }

    {
        cout << "\nСоздаем отрезки Section (Поверхностное и глубокое копирование) \n";
        Section* s1 = new Section;
        Section* s2 = new   Section(*s1);//второй отрезок создаем как копию первого (*s1) - разыменование указтеля
        delete s1;
        delete s2;
       
    } 
        // 1 случ поверхностное коп
        //2 случ глубокое коп
        // последнне было композиция обьектов
 
    {
        cout << "\nСоздаем объекты Ray";
       Ray* p1 = new Ray; 
       Ray* p2 = new Ray(10, 20); 
      Ray *p3 = new Ray(*p1);
       delete p1;
       delete p2;
       delete p3;
    }

    _getch();
    return 0;
    }



  //  { ColoredPoint* p = new Point(1, 2, 42);  //если у нас есть переменная указатель на базовый класс то мы модем помесить в нее обьект потомка
   // delete p;  // когда мы создам переменную базовго класса и внее пытаемся помесить переменнуб потомка, то у нас не компилируется нельзя

  //  Point* p = new Point(1, 2, 42); //если сначала сделать обьект класса поинт и потом в переменню поместиь пе то оьект он создает нормально но при попытке поместит его адрес в пееменную указател на адрес потомка он не модет это сделать потому что правила приведения типов так не работают

   // ColoredPoint* p2 = p}
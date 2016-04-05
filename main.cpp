#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <clocale>

using namespace std;

class Str_type{
    private:
        int length; // длина строки
        char *p; // указатель на строку
    public:
        Str_type(); // конструктор по умолчанию
        Str_type(char *str);
        Str_type(const Str_type &obj); // конструктор копирования

        ~Str_type() {delete [] p;} // деструктор

        Str_type operator=(char *s); //Присваивание объекта Str_type другому объекту
        Str_type operator=(Str_type &obj); //Присваивание cтроки объекту Str_type

        Str_type operator+(char *s); // конкатенация строк в кавычках
        Str_type operator+(Str_type &obj); //конкатенация объектов класса Str_type

        // операторы сравнения строк в кавычках
        int operator==(char *s) {return !strcmp(p, s);} //если строки равны, то рез-т strcmp=0, поэтому ставим !
        int operator!=(char *s) {return strcmp(p, s);}
        int operator<(char *s) {return strcmp(p, s)<0;}
        int operator>(char *s) {return strcmp(p, s)>0;}
        int operator<=(char *s) {return strcmp(p, s)<=0;}
        int operator>=(char *s) {return strcmp(p, s)>=0;}

        // операторы сравнения объектов класса Str_Type
        int operator==(Str_type &obj) {return !strcmp(p, obj.p);} //если строки равны, то рез-т strcmp=0, поэтому ставим !
        int operator!=(Str_type &obj) {return strcmp(p, obj.p);}
        int operator<(Str_type &obj) {return strcmp(p, obj.p)<0;}
        int operator>(Str_type &obj) {return strcmp(p, obj.p)>0;}
        int operator<=(Str_type &obj) {return strcmp(p, obj.p)<=0;}
        int operator>=(Str_type &obj) {return strcmp(p, obj.p)>=0;}

        char operator[](int i) {return p[i];} //перегрузка индексирования или операция выделения символа


        friend ostream &operator<<(ostream &stream, Str_type &obj);

        friend void sort_string(Str_type **data);

};

// Конструктор по умолчанию
Str_type::Str_type()
{
    length = 1;
    p = new char[length];
    strcpy(p, "");
}

//инициализация строки в кавычках
Str_type::Str_type(char *str)
{
    length=strlen(str)+1;
    p = new char[length];
    strcpy(p, str);
}

//конструктор копирования. Инициализация с помощью объекта Str_type
Str_type::Str_type(const Str_type &obj)
{
    length=obj.length;
    p = new char[length];
    strcpy(p, obj.p);
}

//Присваивание строки объекту Str_type
Str_type Str_type::operator=(char *s)
{
    int len=strlen(s)+1;
    if(length<len) // помещается ли присваемый объект в участке, на который указывает p
    {
        delete [] p; // освобождаем старый участок
        p = new char[len];
        length=len;
    }
    strcpy(p,s);
    return *this; //указываем на объект класса, через который происходит вызов метода
                  // т.е. возвращаем присвоенную строку
}

//Присваивание объекта Str_type другому объекту
Str_type Str_type::operator=(Str_type &obj)
{
    Str_type tmp;
    if (length<obj.length)
    {
        delete []p;
        p = new char[obj.length];
        length=obj.length;
    }
    strcpy(p, obj.p);
    strcpy(tmp.p, obj.p);
    return tmp;
}


//Конкатенация строк в кавычках
Str_type Str_type::operator+(char *s)
{
    int len;
    Str_type tmp;

    delete [] tmp.p;

    len=strlen(s)+strlen(p)+1;
    tmp.length=len;
    tmp.p=new char[len];
    strcpy(tmp.p, p);
    strcat(tmp.p, s); //соединяем строки
    return tmp; //возвращаем общую строку
}

//Конкатенация объектов типа Str_type
Str_type Str_type::operator+(Str_type &obj)
{
    int len;
    Str_type tmp;

    delete [] tmp.p;

    len=strlen(obj.p)+strlen(p)+1;
    tmp.length=len;
    tmp.p=new char[len];
    strcpy(tmp.p, p);
    strcat(tmp.p, obj.p); //соединяем строки
    return tmp;
}

//Вывод строки. Перешрузка оператора вывода. Функции ввода/вывода не могут быть членами класса
//ostream &stream - ссылка на поток, который стоит слева от <<
//объявляем его дружественной функцией, чтобы иметь доступ к закрытым членам класса
ostream &operator<<(ostream &stream, Str_type &obj)
{
    stream<<obj.p;
    return stream;
}

int N=3; //количество элементов массива

void sort_string(Str_type **data)
{
    int flag;
    Str_type tmp;

    for (int i=N-1; i>=0; i--)
    {
        flag=1;
        for(int j=0; j<i; j++)
        {

            if (data[j]->length>data[j+1]->length)
            {
                strcmp(tmp.p, data[j]->p);
                strcmp(data[j]->p, data[j+1]->p);
                strcmp(data[j+1]->p, tmp.p);
                flag=0;

            }
        }
        if (flag==1)
            break;
    }

    for(int i=0; i<N;i++) //не сортируется
        cout<<*data[i]<<"\n";

}


int main()
{
    //setlocate(LC_ALL, "Rus");

    Str_type s1("string1");
    cout<<"s1 = "<<s1<<endl;

    Str_type s2(s1); //Инициализация с помощью объекта Str_type
    Str_type s3("string3");
    Str_type s4=s1+s3; //конкатенация строк объектов Str_type
    cout<<"s4 = "<<s4<<endl;

    s1=s3; // присваивание объекта объекту типа Str_type
    cout<<"s1 = "<<s1<<endl;

    s2="Hello"; // присваивание строки объекту типа Str_type
    Str_type s5=s2+" world"; //конкатенация строк в кавычках
    cout<<"s5 = "<<s5<<endl;

    //операции сравнения. слева всегда должен быть объект Str_type
    if(s1==s3) cout<<"Строки s1 и s3 равны. \n";
    if(s1!=s3) cout<<"Строки  s1 и s3 не равны. \n";
    if(s4>s5)  cout<<"Строка s4 больше строки s5. \n";
    if(s4<s5)  cout<<"Строка s4 меньше строки s5. \n";
    if(s4>=s5)  cout<<"Строка s4 больше или равна строки s5. \n";
    if(s4<=s5)  cout<<"Строка s4 меньше или равна строки s5. \n";


    if(s2=="Hello") cout<<"Строка s2 равна Hello. \n"; //сравнение со строкой в кавычках
    cout<<"s2[0] = "<<s2[0]<<endl;

    //Массив объектов
    Str_type **data;
    data = new Str_type*[N];
    data[0]=new Str_type("сортировка");
    data[1]=new Str_type("строк");
    data[2]=new Str_type("массива");
    sort_string(data);


    return 0;
}

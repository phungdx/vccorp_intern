#include<iostream>
using namespace std;

/*
Abstract Factory dùng khi ta có nhiều họ products khác nhau.

Trong ví dụ này: 
- Các products là button và Scrollbar
- Các họ là 2 themes: Dark và Light

*/

class Button
{
    // khai báo các methods
    
};

class ScrollBar
{
    // khai báo các methods
   
};

class Button
{
    // khai báo các methods
   
};

class ScrollBar
{
    // khai báo các methods
   
};

class LightButton : public Button
{
    // LightButton cần implement các methods khai báo bởi Button
  
};

class DarkButton : public Button
{
    // DarkButton cần implement các methods khai báo bởi Button
   
};

class LightScrollBar : public ScrollBar
{
    // LightScrollBar cần implement các methods khai báo bởi ScrollBar
   
};

class DarkScrollBar : public ScrollBar
{
    // DarkScrollBar cần implement các methods khai báo bởi ScrollBar
   
};


// khởi tạo class các tiện ích widget
class WidgetFactory
{
public:
    virtual ScrollBar* createScrollBar()=0; // interface tạo scrollbar
    virtual Button* createButton()=0; // interface tạo button
};


// class kế thừa với các widget là light theme
class LightThemeWidgetFactory : public WidgetFactory
{
public:
    ScrollBar* createScrollBar() {
        return new LightScrollBar();
    }

    Button* createButton() {
        return new LightButton();
    }
};


// class kế thừa với các widget là dark theme
class DarkThemeWidgetFactory : public WidgetFactory
{
public:
    ScrollBar* createScrollBar() {
        return new DarkScrollBar();
    }

    Button* createButton() {
        return new DarkButton();
    }
};




int main(){
    // light theme
    LightThemeWidgetFactory widgetFactory;
    WidgetFactory *factoryPtr = &widgetFactory;
    ScrollBar *scrollbar = factoryPtr->createScrollBar();
    Button *button = factoryPtr->createButton();

    // dark theme
    DarkThemeWidgetFactory widgetFactory;
    WidgetFactory *factoryPtr = &widgetFactory;
    ScrollBar *scrollbar = factoryPtr->createScrollBar();
    Button *button = factoryPtr->createButton();

    return 0;
}
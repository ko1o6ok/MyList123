#include "MyList.h"
int main()
{
    MyList<int> l;
    cout << l.empty() << endl;
    l.push_back(3);
    l.push_back(2);
    l.push_back(5);
    l.push_back(9);
    cout << l.empty() << endl;
    cout << l;

    l.reverse();
    cout << "Reversed: "<<l;

    l.del_last();
    cout << l;

    l.del_first();
    cout << l;

    l.push_back(5);
    cout << l;

    l.insert(9, 1);
    cout << l;

    cout << l.find(2)->value << endl;

}

#include "MyList.h"
int main()
{
    MyList<int> l;
    cout << l.empty() << endl;
    l.push_back(3);
    l.push_back(2);
    cout << l.empty() << endl;
    cout << l;
    l.del_last();
    cout << l;
    l.push_back(5);
    cout << l;
    l.insert(9, 1);
    cout << l;
    //cout << l.find(3);
}

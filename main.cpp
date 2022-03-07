#include <iostream>
#include <cstdlib>
#include <list>
#include "aloca.h"

using namespace std;


int main(){
    list<int> ji;
    ji.push_front(4);
    cout << ji.front() << endl;
    meualoc(5,6);
}
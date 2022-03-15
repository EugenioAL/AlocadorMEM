// list::size
#include <iostream>
#include <list>

using namespace std;

int main ()
{
  std::list<int> myints;

  list<int>::iterator it;
  it = myints.begin();

  cout << it;

  char *p, **pp, *s;
  p = (char*)malloc(100*sizeof(char));
  for(int i = 0; i < 100; i++){
    p[i] = 65 + i;
  }
  unsigned short int tam = 20299;
  char b = tam,c = tam >> 8;
  cout <<"c==" << c <<"b==" << b << endl;
  tam = (c << 8) + b;
  cout << tam << endl;

  if(p < p+2){
    cout << "Funciona: " << p - (p+2) << endl;
  }
  else{
    cout << "Não funciona: " << p-(p+2) << endl;
  }


  return 0;
}
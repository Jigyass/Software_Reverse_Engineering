/*
 * class_layout -- check layout of data members in a class that is devoid of
 * member functions.
 */
#include <iostream>
using namespace std;

class A
{
public:
  int X;
  char c;
  int Y;

public:
  virtual void setAll(int p, char q, int r){
    printf("Class A: setAll()\n");
    X = p;
    c = q;
    Y = r;
  }

  virtual void printAll(){
    printf("Class A: X = %d c = %c Y = %d\n", X, c, Y);
  }

  virtual void printA(){
    printf("Class A: X = %d c = %c Y = %d\n", X, c, Y);
  }
};

class B : public A
{
public:
  int P;
  char q;

public:
  virtual void setAll(int p1, char p2, int p3, int p4, char p5){
    printf("Class B: setAll()\n");
    X = p1;
    c = p2;
    Y = p3;
    P = p4;
    q = p5;
  }

  virtual void printAll(){
    printf("Class B: X = %d c = %c Y = %d P = %d q = %c\n",
	   X, c, Y, P, q);
  }

  virtual void printB(){
    printf("Class B: X = %d c = %c Y = %d P = %d q = %c\n",
	   X, c, Y, P, q);
  }
};

int main()
{
  A objA, *ptrA;
  B objB, *ptrB;
  
  //printf("Print objA\n");
  //objA.setAll(10, 'a', 20);
  //objA.printAll();

  //printf("Print objB\n");
  //objB.setAll(100, 'b', 200, 5, 'c');
  //objB.printAll();

  //printf("Print objA using 'struct A' pointer -- polymorphism\n");
  //ptrA = &objA;
  //ptrA->printAll();
  //ptrA->printA();
  // ptrA->printB(); // results in an error!

  printf("Print objB using 'struct A' pointer -- polymorphism\n");
  ptrA = &objB;
  ptrA->setAll(50, 'z', 50);
  // incorrect: ptrA->setAll(50, 'z', 50, 100, 'c');
  ptrA->printAll();
  ptrA->printA();
  // ptrA->printB(); // results in an error!

  printf("Print objA using 'struct B' pointer -- polymorphism\n");
  // ptrB = &objA; // not allowed!

  printf("Print objB using 'struct B' pointer -- polymorphism\n");
  ptrB = &objB;
  // ptrB->setAll(5, 'p', 5);
  ptrB->setAll(1, 'w', 2, 3, 'x');
  ptrB->printAll();
  ptrB->printA();
  ptrB->printB();

  printf("Dynamic allocation of 'B' assigned to pointer of 'A'\n");
  ptrA = new B();
  ptrA->printAll();
  ptrA->printA();
  // ptrA->printB();
  
  return 0;
}

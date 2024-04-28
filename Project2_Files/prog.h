/*
 * prog.h -- class definitions
 */

class A
{
public:
  int X;
  char c;
  int Y;

public:
  virtual void setAll(int p, char q, int r);
  virtual void printAll();
  virtual void printA();
};

class B : public A
{
public:
  int P;
  char q;

public:
  virtual void setAll(int p1, char p2, int p3, int p4, char p5);
  virtual void printAll();
  virtual void printB();
};

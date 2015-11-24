/**
 * \file Except.cpp
 */

#include "Except.hpp"


Exception::Exception(const Operation& x) 
{
   switch (x) {
     case _eval: msg = "attempt to evaluate a cell which is not conspair (including nil)"; break;
     case _define: msg = "attempt to define a non-symbol value"; break;
     case _:     msg = "illegal operator"; break; 
     case _ceiling: case _floor: {
          msg = "attempt to do ";
          msg += to_string(x);
          msg += " on a cell which is not double";
     } break;
     case _add: case _minus: case _times: case _divide: case _less: {
          msg = "attempt to do ";
          msg += to_string(x);
          msg += " on a cell which is not int or double";
     } break;
     case _lambda:
          msg = "invalid arguments for lambda";
     break;
     case _apply:
          msg = "cannot apply a value that is not a function";
     break;
   default: msg = "undefined error 1";
   }
}
	
Exception::Exception(const Operation& x, bool y) 
{
  msg = "too ";
  msg += (y)?"many ":"few ";
  msg +=  "arguements for ";
  msg +=  to_string(x);
}

Exception::Exception(const Operation& x, const string& s) 
{
  if (x == _eval) msg = "attempt to reference an undefined symbol \"";
  else if (x == _define) msg = "attempt to redefine a defined symbol \"";
  msg += s;
  msg += "\"";
}

Exception::Exception(const string& ch) 
{
  if (ch == "int") msg = "try to access the int member of a non-int Cell";
  else if (ch == "dou") msg = "try to access the double member of a non-double Cell";
  else if (ch == "sym") msg = "try to access the symbol member of a non-symbol Cell";
  else if (ch == "con") msg = "try to access the list member of a non-conspair Cell";
  else if (ch == "car") msg = "try to access the car member of a non-conspair Cell";
  else if (ch == "cdr") msg = "try to access the cdr member of a non-conspair Cell";
  else if (ch == "pro") msg = "try to access the function member of a non-procedure Cell";
  else if (ch == "0") msg = "try to divide by 0";
  else msg = ch;
}

logic_error Exception::logic() const {return logic_error(msg);}

runtime_error Exception::runtime() const {return runtime_error(msg);}



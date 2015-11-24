/**
 * \file Cell.cpp
 */

#include "Cell.hpp"
#include "Except.hpp"
#include "eval.hpp"

Cell* const nil = new ConsCell(NULL,NULL);
vector< hashtablemap<string,Cell*> > vars(1);

using namespace std;

////////////////////////////////////////////////////////////////////////////////
///Cell Functions
////////////////////////////////////////////////////////////////////////////////

Cell::~Cell() {}

bool Cell::is_int() const {return 0;}

bool Cell::is_double() const {return 0;}

bool Cell::is_symbol() const {return 0;}

bool Cell::is_cons() const {return 0;}

bool Cell::is_procedure() const {return 0;}

int Cell::get_int() const {throw Exception("int").runtime();}

double Cell::get_double() const {throw Exception("dou").runtime();}

std::string Cell::get_symbol() const {throw Exception("sym").runtime();}

Cell* Cell::get_car() const {throw Exception("car").runtime();}

Cell* Cell::get_cdr() const {throw Exception("cdr").runtime();}

Cell* Cell::get_formals() const {throw Exception("pro").runtime();}

Cell* Cell::get_body() const {throw Exception("pro").runtime();}

Operation Cell::translate_operation() const {return _;}

Cell* Cell::ceiling() const {throw Exception(_ceiling).runtime();}

Cell* Cell::floor() const {throw Exception(_floor).runtime();}

Cell* Cell::operator+(const Cell* const c) {throw Exception(_add).runtime();}

Cell* Cell::operator-(const Cell* const c) {throw Exception(_minus).runtime();}

Cell* Cell::operator*(const Cell* const c) {throw Exception(_times).runtime();}

Cell* Cell::operator/(const Cell* const c) {throw Exception(_divide).runtime();}

bool Cell::less(const Cell* const c) {throw Exception(_less).runtime();}

bool Cell::have_ith_cell(const int i) const {throw Exception("con").runtime();}

Cell* Cell::get_ith_cell(const int i) const {throw Exception("con").runtime();}

Cell* Cell::apply(Cell* const args) {throw Exception(_apply).runtime();}

////////////////////////////////////////////////////////////////////////////////
///IntCell Functions
////////////////////////////////////////////////////////////////////////////////

IntCell::IntCell(const int i):int_m(i) {}

bool IntCell::is_int() const {return 1;}

int IntCell::get_int() const {return int_m;}

Cell* IntCell::operator+(const Cell* const c)
{
  if (c -> is_int()) {
    int_m += c -> get_int();
  } else if (c -> is_double()) {
    Cell* result = new DoubleCell(int_m);
    proper_delete(this);
    return (*result) + c;
  } else throw Exception(_add).runtime();
  return this;
}

Cell* IntCell::operator-(const Cell* const c)
{
  if (c -> is_int()) {
    int_m -= c -> get_int();
  } else if (c -> is_double()) {
    Cell* result = new DoubleCell(int_m);
    proper_delete(this);
    return (*result) - c;
  } else throw Exception(_minus).runtime();
  return this;
}

Cell* IntCell::operator*(const Cell* const c)
{
  if (c -> is_int()) {
    int_m *= c -> get_int();
  } else if (c -> is_double()) {
    Cell* result = new DoubleCell(int_m);
    proper_delete(this);
    return (*result) * c;
  } else throw Exception(_times).runtime();
  return this;
}

Cell* IntCell::operator/(const Cell* const c)
{
  if (c -> is_int()) {
    if (c -> get_int() == 0) Exception("0").runtime();
    int_m /= c -> get_int();
  } else if (c -> is_double()) {
    Cell* result = new DoubleCell(int_m);
    proper_delete(this);
    return (*result) / c;
  } else throw Exception(_divide).runtime();
  return this;
}

bool IntCell::operator==(const Cell* const c) const
{
  if (c -> is_int()) return (int_m == c -> get_int());
  else return false;
}

bool IntCell::less(const Cell* const c)
{
  if (c -> is_int()) return (int_m < c -> get_int());
  if (c -> is_double()) return (int_m < c -> get_double());
  else throw Exception(_less).runtime();
}


bool IntCell::judge() const {return (int_m != 0);}

Cell* IntCell::copy_cell() {return this;}

void IntCell::print(std::ostream& os) const {os << setw(3) << int_m;}

////////////////////////////////////////////////////////////////////////////////
///DoubleCell Functions
////////////////////////////////////////////////////////////////////////////////

DoubleCell::DoubleCell(const double d):double_m(d) {}

bool DoubleCell::is_double() const {return 1;}

double DoubleCell::get_double() const {return double_m;}

Cell* DoubleCell::ceiling() const 
{
  int ceil = (int) double_m;	///@param ceil to calculate the ceiling of the double
  if (ceil < double_m) ceil++;
  return new IntCell(ceil);
}

Cell* DoubleCell::floor() const 
{
  int flor = (int) double_m;	///@param flor to calculate the floor of the double
  if (flor > double_m) flor--;
  return new IntCell(flor);
}

Cell* DoubleCell::operator+(const Cell* const c)
{
  if (c -> is_int()) {
    double_m += c -> get_int();
  } else if (c -> is_double()) {
    double_m += c -> get_double();
  } else throw Exception(_add).runtime();
  return this;
}

Cell* DoubleCell::operator-(const Cell* const c)
{
  if (c -> is_int()) {
    double_m -= c -> get_int();
  } else if (c -> is_double()) {
    double_m -= c -> get_double();
  } else throw Exception(_minus).runtime();
  return this;
}

Cell* DoubleCell::operator*(const Cell* const c)
{
  if (c -> is_int()) {
    double_m *= c -> get_int();
  } else if (c -> is_double()) {
    double_m *= c -> get_double();
  } else throw Exception(_times).runtime();
  return this;
}

Cell* DoubleCell::operator/(const Cell* const c)
{
  if (c -> is_int()) {
    if (c -> get_int() == 0) throw Exception("0").runtime();
    else double_m /= c -> get_int();
  } else if (c -> is_double()) {
    if (c -> get_double() == 0.0)  throw Exception("0").runtime();
    else double_m /= c -> get_double();
  } else throw Exception(_divide).runtime();
  return this;
}

bool DoubleCell::operator==(const Cell* const c) const
{
  if (c -> is_double()) return (double_m == c -> get_double());
  else return false;
}

bool DoubleCell::less(const Cell* const c)
{
  if (c -> is_int()) return (double_m < c -> get_int());
  if (c -> is_double()) return (double_m < c -> get_double());
  else throw Exception(_less).runtime();
}

bool DoubleCell::judge() const {return (double_m != 0.0);}

Cell* DoubleCell::copy_cell() {return this;}

void DoubleCell::print(std::ostream& os) const 
{
  os << setw(10) <<  setiosflags(ios::fixed) << setprecision(6) << double_m;
}

////////////////////////////////////////////////////////////////////////////////
///SymbolCell Functions
////////////////////////////////////////////////////////////////////////////////

SymbolCell::SymbolCell(const char* const s)
{
  symbol_m = new char[strlen(s)+1];
  strcpy(symbol_m,s);
}

SymbolCell::~SymbolCell() {delete[] symbol_m;}

bool SymbolCell::is_symbol() const {return 1;}

std::string SymbolCell::get_symbol() const {return string(symbol_m);}

bool SymbolCell::operator==(const Cell* const c) const
{
  if (c -> is_symbol()) return (string(symbol_m).compare(c -> get_symbol()) == 0);
  else return false;
}

bool SymbolCell::less(const Cell* const c)
{
  if (c -> is_symbol()) return (string(symbol_m) < c -> get_symbol());
  else throw Exception(_less).runtime();
}

bool SymbolCell::judge() const {return 1;}

Cell* SymbolCell::copy_cell() {return this;}

void SymbolCell::print(std::ostream& os) const {os << symbol_m;}

Operation SymbolCell::translate_operation() const
{
  string op = get_symbol();
  if (op == "+" ) return _add;
  else if (op == "-" ) return _minus;
  else if (op == "*" ) return _times;
  else if (op == "/" ) return _divide;
  else if (op == "ceiling" ) return _ceiling;
  else if (op == "floor" ) return _floor;
  else if (op == "if" ) return _if;
  else if (op == "quote" ) return _quote;
  else if (op == "cons" ) return _cons;
  else if (op == "car" ) return _car;
  else if (op == "cdr" ) return _cdr;
  else if (op == "nullp" ) return _nullp;
  else if (op == "listp" ) return _listp;
  else if (op == "define" ) return _define;
  else if (op == "<" ) return _less;
  else if (op == "not" ) return _not;
  else if (op == "eval" ) return _eval;
  else if (op == "print" ) return _print;
  else if (op == "lambda" ) return _lambda;
  else if (op == "apply" ) return _apply;
  else if (op == "let" ) return _let;
  else if (op == "procedurep") return _procedurep;
  else if (op == "symbolp") return _symbolp;
  else if (op == "doublep") return _doublep;
  else if (op == "intp") return _intp;
  else return _;
}


////////////////////////////////////////////////////////////////////////////////
///ConsCell Functions
////////////////////////////////////////////////////////////////////////////////

ConsCell::ConsCell(Cell* const my_car, Cell* const my_cdr):car_m(my_car),cdr_m(my_cdr) {}

bool ConsCell::is_cons() const {return 1;}

Cell* ConsCell::get_car() const {
  if (this == nil) throw Exception("car").runtime();
  return car_m;
}

Cell* ConsCell::get_cdr() const {
  if (this == nil) throw Exception("cdr").runtime();
  return cdr_m;
}

bool ConsCell::operator== (const Cell* const c) const
{
  if (this == nil) return (c == nil);
  else if (c -> is_cons()) return (this == c);
  else return false;
}

bool ConsCell::judge() const {return 1;}

void ConsCell::print(std::ostream& os) const
{
  if (this == nil) os << "()";
  else {
    os << '(';
    get_car() -> print(os);
    Cell* temp_cdr = get_cdr();
    while (temp_cdr != nil) {
      os << ' ';
      if (!temp_cdr -> is_cons()) {
        os << ". ";
        temp_cdr -> print(os);
        break;
      }
      temp_cdr-> get_car() -> print(os);
      temp_cdr = temp_cdr -> get_cdr();
    }
    os << ')';
  }
}

Cell* ConsCell::copy_cell() {return this;}

bool ConsCell::have_ith_cell(const int i) const
{
  if (i == 0) return (this != nil);
  if (cdr_m == nil) return false;
  return cdr_m -> have_ith_cell(i-1);
}

Cell* ConsCell::get_ith_cell(const int i) const
{
  if (i == 0) return get_car();
  if (cdr_m == nil) return nil;
  return cdr_m -> get_ith_cell(i-1);
}

////////////////////////////////////////////////////////////////////////////////
///ProcedureCell Functions
////////////////////////////////////////////////////////////////////////////////

ProcedureCell::ProcedureCell(Cell* const my_formals, Cell* const my_body):formals_m(my_formals),body_m(my_body) {}

bool ProcedureCell::is_procedure() const {return 1;}

bool ProcedureCell::judge() const {return 1;}

Cell* ProcedureCell::get_formals() const {return formals_m;}

Cell* ProcedureCell::get_body() const {return body_m;}

bool ProcedureCell::operator==(const Cell* const c) const
{
  if (c -> is_procedure()) return (this == c);
  else return false;
}

Cell* ProcedureCell::copy_cell() {return this;}

Cell* ProcedureCell::apply(Cell* const args) {
  hashtablemap<string, Cell*> arguements; ///@param arguements The hashtablemap holding local variables to be push into the stack
  Cell* curr_args = nil; ///@param curr_args Hold value of the second parameter of hashtablemap
  int i; ///@param i Hold he number of arguements(the length of args lis) 
  if (formals_m -> is_symbol()) { ///case of arbitrary number arguements(bonus)
    //count number of arguements and store in i
    for (i = 0; args -> have_ith_cell(i); i++) {}
    Cell* args_list[i];  ///@param args_list The array holding left-to-right evaluated arguements
    //evaluate from left to right the arguements
    for (int j = 0; j < i; ++j) {
      args_list[j] = eval(args -> get_ith_cell(j));
    }
    //construct from right to left a list holding the parameter values
    for (int j = i-1; j >= 0; --j) {
      curr_args = new ConsCell(args_list[j], curr_args);
    }
    //hashtablemap the symbol of formal to the list of args
    arguements.insert(pair<string,Cell*> (formals_m -> get_symbol(),curr_args));
  } else {
    for (i = 0; formals_m -> have_ith_cell(i); ++i) {
      Cell* curr_formal = formals_m -> get_ith_cell(i);  //@param curr_formals A pointer scaning through each formal
      if (!curr_formal -> is_symbol()) throw Exception(_lambda).runtime(); //error for non symbol formals
      string formal = curr_formal -> get_symbol(); //@param formal The symbol of the first parameter of hashtablemap
      if (arguements.count(formal)) throw Exception(_lambda).runtime(); //error for redefining formals
      //check whether the number of arguements is valid
      if (!args -> have_ith_cell(i)) throw Exception(_apply,false).runtime();
      //evaluate each corresponding arguement
      curr_args = eval(args -> get_ith_cell(i));
      //hashtablemap the current symbol to the d
      arguements.insert(pair<string,Cell*> (formal,curr_args));
    }
    //check whether the number of arguements is valid
    if (args -> have_ith_cell(i)) throw Exception(_apply,true).runtime();
  }

  vars.push_back(arguements); //push the hashtablemap into the stack(vector)
  Cell* result = nil;
  Cell* curr_body = body_m;
  while (!nullp(curr_body)) {
    result = eval(car(curr_body));
    curr_body = cdr(curr_body);
    if (!nullp(curr_body)) { //make sure apply return the last evaluated value
      proper_delete(result); result = nil; 
    } 
  }
  vars.pop_back(); //pop the hashtablemap from the stack
  return result;
}

void ProcedureCell::print(std::ostream& os) const
{
  os << "#<function>";
}

////////////////////////////////////////////////////////////////////////////////

void proper_delete(Cell* const c) {
  //   if (!(c == nil || c -> is_cons() || c -> is_procedure())) delete c;
}

string to_string(Operation x)
{
  switch (x){
    case _add: return "+"; break;
    case _minus: return "-"; break;
    case _times: return "*"; break;
    case _divide: return "/"; break;
    case _ceiling: return "ceiling"; break;
    case _floor: return "floor"; break;
    case _if: return "if"; break;
    case _quote: return "quote"; break;
    case _cons: return "cons"; break;
    case _car: return "car"; break;
    case _cdr: return "cdr"; break;    
    case _nullp: return "nullp"; break;
    case _listp: return "listp"; break;
    case _define: return "define"; break;
    case _less: return "<"; break;
    case _print: return "print"; break;
    case _eval: return "eval"; break;
    case _not: return "not"; break;
    case _lambda: return "lambda"; break;
    case _apply: return "apply"; break;
    case _let: return "let"; break;
    case _procedurep: return "procedurep"; break;
    case _intp: return "intp"; break;
    case _doublep: return "doublep"; break;
    case _symbolp: return "symbolp"; break;
    default: return "undefined";break;
  }
}



/**
 * \file eval.cpp
 *
 * A dummy implementation for example purposes.  Just barely enough is
 * implemented to allow the parser to run.  Merely returns the input
 * expression without evaluating it.
 */


#include "eval.hpp"
#include "Except.hpp"

/**
 * \brief Check whether a list has appropiate number of operands for an operation, throw true for too many and false for too few.
 * \param c The list to be operated.
 * \param x The operator
 */
void check_number_of_operands(Cell* const c,Operation x)
{
  try {
	switch (x){
	case _if: {  ///cases can have 2 or 3 operands.
	  if (!(c -> have_ith_cell(1) && c -> have_ith_cell(2))) throw false;
	  if (c -> have_ith_cell(4)) throw true;
	}
	  break;
	case _minus: case _divide:  ///cases cannot have 0 operands.
	  if (!c -> have_ith_cell(1)) throw false;
	  break;
	case _cons: case _define: case _apply: {  ///cases should have exactly 2 operands. 
	  if (!(c -> have_ith_cell(1) && c -> have_ith_cell(2))) {throw false;}
	  if (c -> have_ith_cell(3)) throw true;
	}
	  break;
	case _lambda: case _let: ///cases have 2 or more operands
	  if (!(c -> have_ith_cell(1) && c -> have_ith_cell(2))) {throw false;}
	  break;
	case _add: case _times: case _less:  ///cases having no requirement for operands. (Avoid misusing of function. Should not be excecuted.) 
	  break;
	default:	///cases should have exactly 1 operand. (
	  if (!c-> have_ith_cell(1)) throw false;
	  if (c -> have_ith_cell(2)) throw true;
        }
  }
  catch (bool y) {
    throw Exception(x,y).runtime();
  }
}

Cell* eval(Cell* const c) throw(exception)
{

 try {

   if (nullp(c)) throw Exception(_eval).runtime();  //error for null cell
  
   if (symbolp(c)) {
     string var = c -> get_symbol();  ///@param var the reference string
     vector< hashtablemap<string,Cell*> >::iterator p = vars.end();  ///@param p Scans the vector of hashtablemap form top to bottom
     do {
       --p;
       if (p -> count(var)) return (*p)[var] -> copy_cell();
     }
     while (p != vars.begin()); 
     throw Exception(_eval, var).runtime(); //error for undefined symbol
   }

   if (!listp(c)) return c -> copy_cell();

   Cell* get_operation = car(c); ///@param get_operation point to the cell holding operator of procedure.
   Operation operation = get_operation -> translate_operation();   
   
   if (operation == _ ) { //case of non-operator
     Cell* procedure = eval(get_operation); ///@param procedure Supposed to be a ProcedureCell to be applied. Error otherwise. 
     Cell* result = procedure -> apply(cdr(c));
     proper_delete(procedure); procedure = nil;     
     return result;
   }
  
   switch (operation) { //case of standard operator
   case _ceiling: {
     check_number_of_operands(c, _ceiling);
     Cell* ceiling_arguement = eval(c -> get_ith_cell(1));
     Cell* result = ceiling_arguement -> ceiling();
     proper_delete(ceiling_arguement); ceiling_arguement = nil;
     return result;
   }
     break;

   case _floor: {
     check_number_of_operands(c, _floor);
     Cell* floor_arguement = eval(c -> get_ith_cell(1));
     Cell* result = floor_arguement -> floor();
     proper_delete(floor_arguement); floor_arguement = nil;
     return result;
   }
     break;
		
   case _add: {
     Cell* result = make_int(0);
     for ( int i = 1 ; c -> have_ith_cell(i) ; i++ ) {
       Cell* new_operand = eval(c -> get_ith_cell(i));
       result = (*result) + new_operand;
       proper_delete(new_operand); new_operand = nil;
     }
     return result;
   }
     break;
	
   case _minus: {
     check_number_of_operands(c, _minus);
     Cell* result = make_int(0);
     Cell* new_operand = eval(c -> get_ith_cell(1));
     if (nullp(c -> get_ith_cell(2))) {
       result = (*result) - new_operand;
       proper_delete(new_operand); new_operand = nil;
       return result;
     } else {
       result = (*result) + new_operand;
       proper_delete(new_operand); new_operand = nil;
     }
     for ( int i = 2 ; !nullp(c -> get_ith_cell(i)) ; i++ ) {
       new_operand = eval(c -> get_ith_cell(i));
       result = (*result) - new_operand;
       proper_delete(new_operand); new_operand = nil;
     }
     return result;
   }
     break;

   case _times: {
     Cell* result = make_int(1);
     for ( int i = 1 ; c -> have_ith_cell(i) ; i++ ) {
       Cell* new_operand = eval(c -> get_ith_cell(i));
       result = (*result) * new_operand;
       proper_delete(new_operand); new_operand = nil;
     }
     return result;
   }
     break;

   case _divide: {
     check_number_of_operands(c, _divide);
     Cell* result = make_int(1);
     Cell* new_operand = eval(c -> get_ith_cell(1));
     if (nullp(c -> get_ith_cell(2))) {
       result = (*result) / new_operand;
       proper_delete(new_operand); new_operand = nil;
       return result;
     } else {
       result = (*result) * new_operand;
       proper_delete(new_operand);
       new_operand = nil;
     }
     for ( int i = 2 ; !nullp(c -> get_ith_cell(i)) ; i++ ) { 
       new_operand = eval(c -> get_ith_cell(i));
       result = (*result) / new_operand;
       proper_delete(new_operand); new_operand = nil;
     }
     return result;
   }
     break;
   
   case _if: {
     check_number_of_operands(c, _if);
     Cell* if_arguement = eval(c -> get_ith_cell(1));
     if (if_arguement -> judge()) {
       proper_delete(if_arguement); if_arguement = nil;
       if_arguement = eval(c -> get_ith_cell(2));
       return if_arguement;
     } else {
       proper_delete(if_arguement); if_arguement = nil;
       if_arguement = eval(c -> get_ith_cell(3));
       return if_arguement;
     }
   }
     break;
	
   case _quote: {
     check_number_of_operands(c, _quote);
     Cell* result = c -> get_ith_cell(1);
     return (result == nil) ? nil:result -> copy_cell(); //nil doesn't have its copy_cell
   }
     break;
	
   case _cons: {
     check_number_of_operands(c, _cons); 
     Cell* car = eval(c -> get_ith_cell(1));
     Cell* cdr = eval(c -> get_ith_cell(2));
     return cons(car,cdr);
   }
     break;
	
   case _car: {
     check_number_of_operands(c, _car);
     Cell* car = eval(c -> get_ith_cell(1)) -> get_car();
     return car;
   }
     break;
	
   case _cdr: {
     check_number_of_operands(c, _cdr);
     Cell* cdr = eval(c -> get_ith_cell(1)) -> get_cdr();
     return cdr;
   }
     break;
	
   case _nullp: {
     check_number_of_operands(c, _nullp);
     Cell* np_arguement = eval(c -> get_ith_cell(1));
     int np = nullp(np_arguement);
     proper_delete(np_arguement); np_arguement = nil;
     return make_int(np);
   }
     break;

   case _intp: {
     check_number_of_operands(c, _intp);
     Cell* ip_arguement = eval(c -> get_ith_cell(1));
     int ip = intp(ip_arguement);
     proper_delete(ip_arguement); ip_arguement = nil;
     return make_int(ip);
   }
     break;

   case _doublep: {
     check_number_of_operands(c, _doublep);
     Cell* dp_arguement = eval(c -> get_ith_cell(1));
     int dp = doublep(dp_arguement);
     proper_delete(dp_arguement); dp_arguement = nil;
     return make_int(dp);
   }
     break;

   case _symbolp: {
     check_number_of_operands(c, _symbolp);
     Cell* sp_arguement = eval(c -> get_ith_cell(1));
     int sp = symbolp(sp_arguement);
     proper_delete(sp_arguement); sp_arguement = nil;
     return make_int(sp);
   }
     break;

   case _procedurep: {
     check_number_of_operands(c, _procedurep);
     Cell* pp_arguement = eval(c -> get_ith_cell(1));
     int pp = procedurep(pp_arguement);
     proper_delete(pp_arguement); pp_arguement = nil;
     return make_int(pp);
   }
     break;

   case _listp: {
     check_number_of_operands(c, _listp);
     Cell* lp_arguement = eval(c -> get_ith_cell(1));
     int lp = listp(lp_arguement);
     proper_delete(lp_arguement); lp_arguement = nil;
     return make_int(lp);
   }
     break;

   case _define: { //define a value at the end(current level) of the stack
     vector< hashtablemap<string,Cell*> >::iterator p = vars.end();
     --p;
     check_number_of_operands(c, _define);
     Cell* var_operand = c -> get_ith_cell(1);
     if (!symbolp(var_operand)) throw Exception(_define).runtime(); //error for defining non-symbol
     string var = var_operand -> get_symbol();
     if (p -> count(var)) throw Exception(_define, var).runtime(); //error for redefining
     var_operand = eval(c -> get_ith_cell(2));  
     p = vars.end();
     --p;
     p -> insert(pair<string,Cell*> (var,var_operand));
     return nil;
   }
     break;

   case _less: {
     /**
      * \param lhs the left hand side of <
      * \param rhs the right hand side of <
      */
     bool result = 1;
     if (! c -> have_ith_cell(1)) return make_int(result);
     Cell* lhs = eval(c -> get_ith_cell(1));
     if (! c -> have_ith_cell(2)) {
       if (intp(lhs) || doublep(lhs) || symbolp(lhs)) return make_int(result);
       else throw Exception(_less).runtime();
     }
     Cell* rhs;
     for ( int i = 2 ; c -> have_ith_cell(i) ; i++ ) {
       rhs = eval(c -> get_ith_cell(i));
       result = (result && lhs -> less(rhs));
       proper_delete(lhs);
       lhs = rhs;
       rhs = nil;
     }
     proper_delete(lhs); lhs = nil;
     return make_int(result);
   }
     break;

   case _not: {
     check_number_of_operands(c, _not);
     Cell* nt_arguement = eval(c -> get_ith_cell(1));
     int nt = nt_arguement -> judge();
     nt = not(nt);
     proper_delete(nt_arguement); nt_arguement = nil;
     return make_int(nt);
   }
     break;

   case _print: {
     check_number_of_operands(c, _print);
     Cell* pt = eval(c -> get_ith_cell(1));
     cout << *pt << endl;
     proper_delete(pt); pt = nil;
     return nil;
   }
     break;

   case _eval: {
     check_number_of_operands(c, _eval);
     Cell* eval_operand = eval(c -> get_ith_cell(1));
     Cell* result = eval(eval_operand);
     proper_delete(eval_operand); eval_operand = nil;
     return result;
   }
     break;

   case _lambda: {
     check_number_of_operands(c, _lambda);
     Cell* formals = c -> get_ith_cell(1);
     if (symbolp(formals)) return lambda(formals,cdr(cdr(c))); //case of function with arbitrary number of arguements
     //safe check that 
     if (!listp(formals)) throw Exception(_lambda).runtime();
     for (int i = 0; formals -> have_ith_cell(i); ++i) {
        if (!formals -> get_ith_cell(i) -> is_symbol()) throw Exception(_lambda).runtime();
     }
     return lambda(formals, cdr(cdr(c)));
   }
     break;

   case _apply: {
     check_number_of_operands(c, _apply);
     Cell* procedure = c -> get_ith_cell(1);
     Cell* arguements = eval(c -> get_ith_cell(2));    
     Operation op_ = procedure -> translate_operation();
     if (op_ != _) { //allow to do apply on basic operators
       //count number of arguements
       int i;
       for (i = 0; arguements -> have_ith_cell(i) ; ++i) {}
       Cell* new_args = nil; ///@param new_args A new list of arguements with each arg protected by (quote arg) because they are going to be evaled again.
       for (int j = i-1 ; j >= 0 ; --j) {
	 new_args = cons(cons(make_symbol("quote"),cons(arguements -> get_ith_cell(j), nil)),new_args);
       }
       //evaluate a new list in the usual form of preorder
       return eval(cons(make_symbol(to_string(op_).data()),new_args));
     } else {
       procedure = eval(procedure);
       Cell* result = procedure -> apply(arguements);
       proper_delete(arguements); arguements = nil;
       proper_delete(procedure); procedure = nil;
       return result;
     }
   }
     break;

   case _let: {
     check_number_of_operands(c, _let);
     Cell* let_list = c -> get_ith_cell(1);
     Cell* body = cdr(cdr(c));
     Cell* formals = nil;
     Cell* args = nil;
     for (int i = 0; let_list -> have_ith_cell(i); ++i) { //eval from right to left and list the formals and args
       formals = cons(let_list -> get_ith_cell(i) -> get_ith_cell(0), formals);
       args = cons(let_list -> get_ith_cell(i) -> get_ith_cell(1), args);
     }
     Cell* result = lambda(formals,body) -> apply(args);
     return result;
   }
     break;
 
   }
 }
 catch (...) {
	 throw;
 }
}


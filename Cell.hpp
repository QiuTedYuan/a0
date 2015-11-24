/**
 * \mainpage COMP2012H Lab Programming Assignment 7, Fall 2014
 *
 * \author QIU Yuan
 * \author 20175552
 * \author yqiuac@connect.ust.hk
 * \author LA1
 *
 * \date 17/11/2014
 *
 * Instructor: <a href="http://www.cs.ust.hk/~dekai/">Dekai Wu</a>
 * Due: in lab by CASS
 */

/**
 * \file Cell.hpp
 *
 * Encapsulates the abstract interface for a concrete class-based
 * implementation of cells for a cons list data structure.
 * \note parse.cpp has been modefied to allow quote using '
 */

#ifndef CELL_HPP
#define CELL_HPP

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "hashtablemap.hpp"
#include <vector>

using namespace std;

/**
  * \enum Operation to denote the type of operators.
  */
enum Operation {_,_cons,_car,_cdr,_add,_minus,_times,_divide,_ceiling,_floor,_if,_quote,_nullp,_listp,_define,_less,_not,_print,_eval,_lambda,_apply,_let,_procedurep,_symbolp,_doublep,_intp};

/**
 * \class Cell
 * \brief Abstract base class Cell
 */
class Cell
{
public:

  /**
   * \brief Virtual distructor to Cell
   */
  virtual ~Cell ();

  /**
   * \brief Check if this is an int cell.
   * \return 0 for non-int Cells.
   */
  virtual bool is_int() const;

  /**
   * \brief Check if this is a double cell.
   * \return 0 for non-double Cells.
   */
  virtual bool is_double() const;

  /**
   * \brief Check if this is a symbol cell.
   * \return 0 for non-symbol Cells.
   */
  virtual bool is_symbol() const;

  /**
   * \brief Check if this is a cons cell.
   * \return 0 for non-conspair Cells.
   */
  virtual bool is_cons() const;
  
  /**
   * \brief Check if this is a procedure cell.
   * \return 0 for non-procedure Cells.
   */
  virtual bool is_procedure() const;

  /**
   * \brief Accessor (error if this is not an int cell).
   * \return Throw out an error for non-int Cells.
   */
  virtual int get_int() const;

  /**
   * \brief Accessor (error if this is not a double cell).
   * \return Throw out an error for non-double Cells.
   */
  virtual double get_double() const;

  /**
   * \brief Accessor (error if this is not a symbol cell).
   * \return Throw out an error for non-symbol Cells.
   */
  virtual std::string get_symbol() const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Throw out an error for non-conspair Cells.
   */
  virtual Cell* get_car() const;

  /**
     * \brief Accessor (error if this is not a cons cell).
     * \return Throw out an error for non-conspair Cells.
     */
  virtual Cell* get_cdr() const;

  /**
   * \brief Accessor (error if this is not a procedure cell).
   * \return Formals.
   */
  virtual Cell* get_formals() const;

  /**
    * \brief Accessor (error if this is not a procedure cell).
    * \return Body.
    */
  virtual Cell* get_body() const;

  /**
   * \brief Translate certain symbol to the enum of operation.
   * \return Throw out an error for non-symbol Cells.
   */ 
  virtual Operation translate_operation() const;

  /**
   * \brief Do ceiling on a double cell (error if not)
   * \return Throw out an error for non-double Cells.
   */
  virtual Cell* ceiling() const;
  
  /**
   * \brief Do floor on a double cell (error if not)
   * \return Throw out an error for non-double Cells.
   */
  virtual Cell* floor() const;

  /**
   * \brief Add a cell to the existed cell
   * \return Throw out an error for non-int and non-double Cells.
   */
  virtual Cell* operator+(const Cell* const c);
  
  /**
   * \brief Minus a cell wrt the existed cell
   * \return Throw out an error for non-int and non-double Cells.
   */
  virtual Cell* operator-(const Cell* const c);
  
  /**
   * \brief Times a cell to the existed cell
   * \return Throw out an error for non-int and non-double Cells.
   */
  virtual Cell* operator*(const Cell* const c);
  
  /**
   * \brief Divide a cell wrt the existed cell
   * \return Throw out an error for non-int and non-double Cells.
   */
  virtual Cell* operator/(const Cell* const c);

  /**
   * \brief Compair whether two Cells are equal based on location.
   * \return The boolean according to the scheme specification.
   */    
  virtual bool operator==(const Cell* const c) const = 0;

  /**
   * \brief compare cell c with the existed cell
   * \return Throw out an error for non-int and non-double Cells.
   */
  virtual bool less(const Cell* const c);

  /**
   * \brief Judge the if value for the cell
   * \return True iff the value represents true.
   */
  virtual bool judge() const = 0;

  /**
   * \brief Check where there is an i-th cell.(this when i == 0)
   * \return Throw out an error for non-conspair Cells.
   */
  virtual bool have_ith_cell(const int i) const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return Throw out an error for non-conspair Cells.
   */
  virtual Cell* get_ith_cell(const int i) const;

  /**
   * \brief Deep copy the original Cell to a new one.
   * \return A new constracted cell.
   */
  virtual Cell* copy_cell() = 0;

  /**
   * \brief Apply a function.
   * \return Error for non-procedure cell.
   */
  virtual Cell* apply(Cell* const args);

  /**
   * \brief Print contents.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const = 0;

};

/**
 * \class IntCell
 * \brief Derived class from cell to hold the int value.
 */
class IntCell: public Cell
{
public:

  /**
   * \brief Constructor to make int cell.
   */ 
  IntCell(const int i);

  /**
   * \brief Check if this is an int cell.
   * \return True for this is an int cell.
   */
  virtual bool is_int() const;

  /**
   * \brief Accessor.
   * \return The value in this int cell.
   */
  virtual int get_int() const;
  
  /**
   * \brief Add a cell to the existed cell
   * \return The original cell added by c.
   */
  virtual Cell* operator+(const Cell* const c);
  
  /**
   * \brief Minus a cell wrt the existed cell
   * \return The original cell minused by c.
   */
  virtual Cell* operator-(const Cell* const c);
  
  /**
   * \brief Times a cell to the existed cell
   * \return The original cell multiplied by c.
   */
  virtual Cell* operator*(const Cell* const c);
  
  /**
   * \brief Divide a cell wrt the existed cell
   * \return The original cell divided by c.
   */
  virtual Cell* operator/(const Cell* const c);
  
  /**
   * \brief Compair whether two Cells are equal based on location.
   * \return The boolean according to the scheme specification.
   */    
  virtual bool operator==(const Cell* const c) const;

  /**
   * \brief compare cell c with the existed cell
   * \return True iff this is less than c.
   */
  virtual bool less(const Cell* const c);


  /**
   * \brief Judge the if value for the cell
   * \return True iff the int is not 0.
   */
  virtual bool judge() const;

  /**
   * \brief Deep copy the original Cell to a new one.
   * \return A new constracted Intcell.
   */
  virtual Cell* copy_cell();

  /**
   * \brief Print the int value.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:

  /**
   * \param int_m to store the int value.
   */
  int int_m;

};

/**
 * \class DoubleCell
 * \brief Derived class from cell to hold the double value.
 */
class DoubleCell: public Cell
{
public:

  /**
   * \brief Constructor to make double cell.
   */ 
  DoubleCell(const double d);

  /**
   * \brief Check if this is a double cell.
   * \return True for this is a double cell.
   */
  virtual bool is_double() const;

  /**
   * \brief Accessor.
   * \return The value in this double cell.
   */
  virtual double get_double() const;

  /**
   * \brief Do ceiling on a double cell
   * \return A new constracted cell holding the Celliling value.
   */
  virtual Cell* ceiling() const;

  /**
   * \brief Do floor on a double cell (error if not)
   * \return A new constracted cell holding the Floor value.
   */
  virtual Cell* floor() const;
  
  /**
   * \brief Add a cell to the existed cell
   * \return The original cell added by c.
   */
  virtual Cell* operator+(const Cell* const c);
  
  /**
   * \brief Minus a cell wrt the existed cell
   * \return The original cell minused by c.
   */
  virtual Cell* operator-(const Cell* const c);
  
  /**
   * \brief Times a cell to the existed cell
   * \return The original cell multiplied by c.
   */
  virtual Cell* operator*(const Cell* const c);
  
  /**
   * \brief Divide a cell wrt the existed cell
   * \return The original cell divided by c.
   */
  virtual Cell* operator/(const Cell* const c);
 
  /**
   * \brief Compair whether two Cells are equal based on location.
   * \return The boolean according to the scheme specification.
   */    
  virtual bool operator==(const Cell* const c) const;
 
  /**
   * \brief compare cell c with the existed cell
   * \return True iff this is less than c.
   */
  virtual bool less(const Cell* const c);

  /**
   * \brief Judge the if value for the cell
   * \return True iff double is not 0.0.
   */
  virtual bool judge() const;

  /**
   * \brief Deep copy the original Cell to a new one.
   * \return A new constracted double cell.
   */
  virtual Cell* copy_cell();

  /**
   * \brief Print the double value.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:

  /**
   * \param double_m to store the double value.
   */
  double double_m;

};

/**
 * \class SymbolCell
 * \brief Derived class from cell to hold the symbol value.
 */
class SymbolCell: public Cell
{
public:

  /**
   * \brief Constructor to make symbol cell.
   */ 
  SymbolCell(const char* const s);

  /**
   * \brief Destructor to delete a symbol cell.
   */ 
  virtual ~SymbolCell();

  /**
   * \brief Check if this is a symbol cell.
   * \return True for this is a symbol cell.
   */
  virtual bool is_symbol() const;

  /**
   * \brief Accessor.
   * \return The symbol string in this symbol cell.
   */
  virtual std::string get_symbol() const;

  /**
   * \brief Translate certain symbol to the enum of operation.
   * \return An Operation type holding the operator.
   */ 
  virtual Operation translate_operation() const;

  /**
   * \brief Compair whether two Cells are equal based on location.
   * \return The boolean according to the scheme specification.
   */    
  virtual bool operator==(const Cell* const c) const;
 
  /**
   * \brief compare cell c with the existed cell
   * \return True iff this is less than c.
   */
  virtual bool less(const Cell* const c);

  /**
   * \brief Judge the if value for the cell
   * \return True.
   */
  virtual bool judge() const;

  /**
   * \brief Deep copy the original Cell to a new one.
   * \return A new constracted symbol cell.
   */
  virtual Cell* copy_cell();

  /**
   * \brief Print the symbol.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:

  /**
   * \param symbol_m to store the symbol value.
   */
  char* symbol_m;

};

/**
 * \class ConsCell
 * \brief Derived class from cell to hold the conspair.
 */
class ConsCell: public Cell
{
public:

  /**
   * \brief Constructor to make cons cell.
   */ 
  ConsCell(Cell* const my_car, Cell* const my_cdr);

  /**
   * \brief Check if this is a cons cell.
   * \return True iff this is a cons cell.
   */
  virtual bool is_cons() const;

  /**
   * \brief Accessor.
   * \return First child cell.
   */
  virtual Cell* get_car() const;

  /**
    * \brief Accessor.
    * \return Rest child cell.
    */
  virtual Cell* get_cdr() const;

  /**
   * \brief Compair whether two Cells are equal based on location.
   * \return The boolean according to the scheme specification.
   */    
  virtual bool operator==(const Cell* const c) const;

  /**
   * \brief Judge the if value for the cell
   * \return True.
   */
  virtual bool judge() const;

  /**
   * \brief Check where there is an i-th cell.(this when i == 0)
   * \return True iff there is an ith cell.
   */
  virtual bool have_ith_cell(const int i) const;

  /**
   * \brief Accessor (error if this is not a cons cell).
   * \return i-th cdr cell. (car when i == 0)
   */
  virtual Cell* get_ith_cell(const int i) const;

  /**
   * \brief Deep copy the original Cell to a new one.
   * \return A new constracted conspair Cell.
   */
  virtual Cell* copy_cell();

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:
  /**
   * \param car_m to store the car.
   * \param cdr_m to store the cdr.
   */
  Cell* car_m;
  Cell* cdr_m;
};

/**
 * \class ProcedureCell
 * \brief Derived class from cell to hold the procedure.
 */
class ProcedureCell: public Cell 
{
public:
  
  /**
   * \brief Constructor to make procedure cell.
   */ 
  ProcedureCell(Cell* const my_formals, Cell* const my_body);

  /**
   * \brief Check if this is a procedure cell.
   * \return 1 for procedure Cells.
   */
  virtual bool is_procedure() const;

  /**
   * \brief Accessor.
   * \return Formals.
   */
  virtual Cell* get_formals() const;

  /**
    * \brief Accessor.
    * \return Body.
    */
  virtual Cell* get_body() const;

  /**
   * \brief Compair whether two Cells are equal based on location.
   * \return The boolean according to the scheme specification.
   */    
  virtual bool operator==(const Cell* const c) const;

  /**
   * \brief Judge the if value for the cell
   * \return True.
   */
  virtual bool judge() const;

  /**
   * \brief Deep copy the original Cell to a new one.
   * \return A new constracted procedure Cell.
   */
  virtual Cell* copy_cell();

  /**
   * \brief Apply a function.
   * \return Result cell.
   */
  virtual Cell* apply(Cell* const args);

  /**
   * \brief Print the subtree rooted at this cell, in s-expression notation.
   * \param os The output stream to print to.
   */
  virtual void print(std::ostream& os = std::cout) const;

private:
  /**
   * \param formals_m to store the formals.
   * \param body_m to store the body.
   */
  Cell* formals_m;
  Cell* body_m;
};

/**
 * \brief Properly delete the Cell given it's not nil.
 * \param c The cell to be deleted.
 */
void proper_delete(Cell* const c);

/**
 * \brief Change an operator back to its symbol form.
 * \return The symbol form of operator.
 */
string to_string(Operation x);

extern Cell* const nil;
extern vector< hashtablemap<string,Cell*> > vars;

#endif //CELL_HPP

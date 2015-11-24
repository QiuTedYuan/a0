/**
 * \file Except.hpp
 *
 * Deal with exceptions that occur either in eval or Cell.
 */

#ifndef EXCEPT_HPP
#define EXCEPT_HPP

#include <stdexcept>
#include "Cell.hpp"

using namespace std;

/**
 * \class Exception
 * \brief A class that involves in processing error message.
 */
class Exception 
{
public:

  /**
   * \brief Constructor dealing with mismatching of Cell type, also involved in illegal operator (when operation is _).
   * \param x The operation in which the error occurs.
   */ 
  Exception(const Operation& x);

  /**
   * \brief Constructor dealing with invalid number of arguements.
   * \param x The operation in which the error occurs.
   * \param y True if there are too many arguements and false if too few.
   */
  Exception(const Operation& x, bool y);

  /**
   * \brief Construcor dealing with definition of symbols.
   * \param x The operation in which the error occurs.
   * \param s The symbol not defined in eval or already defined in define.
   */
  Exception(const Operation& x, const string& s);

  /**
   * \brief Constructor for symbol related error.
   * \param c error for x cell is denoted by the first letter of x, and '0' denotes dividing by 0.
   */
  Exception(const string& ch);

  /** 
   *\ brief Output the error message belonging to logic error.
   *\ return a logic_error containing message.
   */
  logic_error logic() const;

  /**
   * \brief Output the error message belonging to runtime error.
   * \return a runtime_error containing message.
   */
  runtime_error runtime() const;



private:

  /**
   * \param msg Store the error message.
   */
  string msg;

};

extern Cell* const nil;

#endif //EXCEPT_HPP

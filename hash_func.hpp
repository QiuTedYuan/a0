#ifndef HASH_FUNC_HPP
#define HASH_FUNC_HPP

#include <string>
using std::string;

typedef unsigned int     size_type;

/**
 * \brief A hash fuction dealing with char array.
 * \param s The array to be hashed.
 * \param D The divisor i.e. size of table.
 * \return The hash value.
 */
inline size_type _hash(const char* s,size_type D)
{
  size_type result = 0;
  for (;*s;++s) {
    result = (2*result + *s)%D;
  }
  return result;
}

/**
 * \class hash
 * \brief A functor to do hash on different types.
 * \todo More explicit specialization of function templates to better distinguish between possible values.
 */
template <typename Key>
class hash
{
public:
  /**
   * \brief Default constructor holding the divisor value.
   * \param divisor The divisor i.e. size of table
   */
  hash(size_type divisor):D(divisor) {}

  /**
   * \brief Copy constructor
   * \param x The value to be copied.
   */
  hash(const hash<Key>& x):D(x.D) {}

  /**
   * \brief Copy assignment operator
   * \param x The value to be copied.
   */
  hash<Key>& operator=(const hash<Key>& x) {
    D = x.D;
    return *this;
  }
  
  /**
   * \brief The general hash function.
   * \param x The key to be hashed.
   */
  size_type operator()(const Key& x) const;

private:

  ///param D hold the divisor.
  size_type D;
};

template <typename Key>
inline size_type hash<Key>::operator() (const Key& x) const {
  size_type len = sizeof(Key);
  char* char_array = new char[len];
  memcpy(char_array, &x, len);
  size_type result = _hash(char_array,D);
  delete[] char_array;
  return result;
}

template <>
inline size_type hash<string>::operator() (const string& x) const {
  return _hash(x.c_str(),D);
}

typedef char* char_pointer;

template <>
inline size_type hash<char_pointer>::operator() (const char_pointer& x) const {
  return _hash(x,D);
}

typedef const char* const_char_pointer;

template <>
inline size_type hash<const_char_pointer>::operator() (const const_char_pointer& x) const {
  return _hash(x,D);
}


#endif //HASH_FUNC_HPP

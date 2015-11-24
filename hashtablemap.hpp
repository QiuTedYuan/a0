#ifndef HASHTABLEMAP_HPP
#define HASHTABLEMAP_HPP

#include "hash_func.hpp"
#include "bstmap.hpp"
#include <iterator>
using std::pair;

/**
 * \class hashtablemap
 * \brief An implementation of hash table map using separate chaining.
 * \brief For each bucket, a binary search tree is used.
 * \brief Users are allowed to give their desired divisor when constructing.
 * \todo Implement to find the prime so that the user can type in size.
 * \todo Allowing users to pass their own hash functions.
 */
template <class Key, class T>
class hashtablemap
{
  typedef hashtablemap<Key, T>     Self;

public:
  typedef Key                key_type;
  typedef T                  data_type;
  typedef T                  mapped_type;
  typedef pair<const Key, T> value_type;
  typedef unsigned int       size_type;
  typedef int                difference_type;
  typedef bstmap<Key, T>     node_type;
  typedef typename bstmap<Key,T>::iterator node_iterator;

public:
  /**
   * \class iterator
   * \brief An input iterator for the map
   */
  class iterator {
    // your iterator definition goes here
    typedef std::input_iterator_tag iterator_category;

    friend class hashtablemap;

  public:
    /**
     * \brief Defaulst constructor
     */
    iterator():map_m(NULL),bucket_m(0) {}

    /**
     * \brief Constructor with member values
     * \param map The current hash table map.
     * \param bucket The bucket pointing to.
     * \note Represents end() when bucket = D.
     * \param it The itrator of the bstmap pointing to the exact value.
     * \note represents end() when it pointing to the begin of bucket D.
     */
    iterator(Self* map,size_type bucket, node_iterator it):map_m(map),bucket_m(bucket),it_m(it) {}

    /**
     * \brief Copy constructr
     */
    iterator(const iterator& q):map_m(q.map_m),bucket_m(q.bucket_m),it_m(q.it_m) {}
    
    /**
     * \brief Copy assignment operator
     */
    iterator& operator=(const iterator& q) {
      map_m = q.map_m;
      bucket_m = q.bucket_m;
      it_m = q.it_m;
      return (*this);
    }

    /**
     * \brief Comparison operator==
     * \param q The iterator to be compared.
     * \return True iff pointing to same key.
     */
    bool operator==(const iterator& q) const { return (map_m == q.map_m && bucket_m == q.bucket_m && it_m == q.it_m); }

    /**
     * \brief Comparison operator!=
     * \param q The iterator to be compared.
     * \return True iff pointing to different key
     */
    bool operator!=(const iterator& q) const { return (map_m != q.map_m || bucket_m != q.bucket_m || it_m != q.it_m); }

    /**
     * \brief Dereference operator*
     * \return A reference to the pair of key and mapped data.
     */
    value_type& operator*() { return *it_m; }

    /**
     * \brief Dereference operator->
     * \return A pointer to the pair of key and mapped data.
     */
    value_type* operator->() { return &(*it_m); }

    /**
     * \brief pre-increment operator
     * \return a reference to the iterator opinting to the next data.
     */
    iterator& operator++() {
      ++it_m;
      if (it_m != map_m -> table_m[bucket_m].end()) { return *this;
      } else {
	while (bucket_m < map_m -> D){
	  ++bucket_m;
	  if (!map_m -> table_m[bucket_m].empty()) {
	    it_m = map_m -> table_m[bucket_m].begin();
	    return *this;
	  }
	}
	it_m = map_m -> table_m[bucket_m].begin();
	return *this;
      }
    }

    /**
     * \brief post-increment operator
     * \return a reference to the iterator opinting to the original data.
     */
    iterator operator++(int) {
      iterator ret(*this);
      ++it_m;
      if (it_m != map_m -> table_m[bucket_m].end()) { return ret;
      } else {
	while (bucket_m < map_m -> D){
	  ++bucket_m;
	  if (!map_m -> table_m[bucket_m].empty()) {
	    it_m = map_m -> table_m[bucket_m].begin();
	    return ret;
	  }
	}
	it_m = map_m -> table_m[bucket_m].begin();
	return ret;
      }
    }

  private:
    ///@param map_m The hash table map
    Self* map_m;

    ///@param bucket_m Current current bucket
    size_type bucket_m;

    ///@param it_m Current bstmap iterator pointing to the key
    node_iterator it_m;
  };

  /**
   * \class const_iterator
   * \brief An input const_iterator for the map
   */
  class const_iterator {
    // like iterator, but points to a const

    typedef std::input_iterator_tag iterator_category;

    friend class hashtablemap;

  public:
    /**
     * \brief Defaulst constructor
     */
    const_iterator():map_m(NULL),bucket_m(0) {}

    /**
     * \brief Constructor with member values
     * \param map The current hash table map.
     * \param bucket The bucket pointing to.
     * \note Represents end() when bucket = D.
     * \param it The itrator of the bstmap pointing to the exact value.
     * \note represents end() when it pointing to the begin of bucket D.
     */
    const_iterator(const Self* map,size_type bucket, node_iterator it):map_m(map),bucket_m(bucket),it_m(it) {}

    /**
     * \brief Copy constructor
     */
    const_iterator(const const_iterator& q):map_m(q.map_m),bucket_m(q.bucket_m),it_m(q.it_m) {}

    /**
     * \brief Copy assignment operator
     */
    const_iterator& operator=(const const_iterator& q) {
      map_m = q.map_m;
      bucket_m = q.bucket_m;
      it_m = q.it_m;
      return (*this);
    }

    /**
     * \brief Comparison operator==
     */
    bool operator==(const const_iterator& q) const { return (map_m == q.map_m && bucket_m == q.bucket_m && it_m == q.it_m); }

    /**
     * \brief Comparison operator!=
     */
    bool operator!=(const const_iterator& q) const { return (map_m != q.map_m || bucket_m != q.bucket_m || it_m != q.it_m); }

    /**
     * \brief Const dereference operator*
     */
    const value_type& operator*() const { return *it_m; }

    /**
     * \brief Const dereference operator->
     */
    const value_type* operator->() const { return &(*it_m); }

    /**
     * \brief pre-increment operator
     */
    const_iterator& operator++() {
      ++it_m;
      if (it_m != map_m -> table_m[bucket_m].end()) { return *this;
      } else {
	while (bucket_m < map_m -> D){
	  ++bucket_m;
	  if (!empty(map_m -> table_m[bucket_m])) {
	    it_m = map_m -> table_m[bucket_m].begin();
	    return *this;
	  }
	}
	it_m = table_m[bucket_m].begin();
	return *this;
      }
    }

    /**
     * \brief post-increment operator
     */
    const_iterator operator++(int) {
      const_iterator ret(*this);
      ++it_m;
      if (it_m != map_m -> table_m[bucket_m].end()) { return ret;
      } else {
	while (bucket_m < map_m -> D){
	  ++bucket_m;
	  if (!empty(map_m -> table_m[bucket_m])) {
	    it_m = map_m -> table_m[bucket_m].begin();
	    return ret;
	  }
	}
	it_m = table_m[bucket_m].begin();
	return ret;
      }
    }

  private:
    ///@param map_m Const hash table map
    const Self* map_m;

    ///@param bucket_m Current bucket
    size_type bucket_m;

    ///@param it_m Current bstmap iterator pointing to the key
    node_iterator it_m;
  };

public:
  /**
   * /brief default constructor to create an empty map
   * /brief An default divisor is set to be a prime 1543.
   * /todo Design a function to find the proper prime depending on divisor.
   */
  hashtablemap(size_type divisor = 1543):D(divisor),size_m(0),hash_m(divisor){
    table_m = new node_type[D+1];
  }

  /**
   * /brief overload copy constructor to do a deep copy
   */
  hashtablemap(const Self& x):D(x.D),size_m(x.size_m),hash_m(D){
    table_m = new node_type[D+1];
    for (int i = 0; i < D; ++i) {
      table_m[i] = x.table_m[i];
    }
  }

  /**
   * /brief destructor
   */
  ~hashtablemap(){
    delete[] table_m;
  }

  /**
   * /brief overload assignment to do a deep copy
   */
  Self& operator=(const Self& x) {
    D = x.D;
    hash_m = x.hash_m;
    size_m = x.size_m;
    table_m = new node_type[D+1];
    for (int i = 0; i < D; ++i) {
      table_m[i] = x.table_m[i];
    }
  }

  // accessors:
  iterator begin() {
    if (size_m == 0) { return end();
    } else {
      for (int i = 0; i < D; ++i) {
	if (!table_m[i].empty()) return iterator(this,i,table_m[i].begin());
      }
    }
  }

  const_iterator begin() const {
    if (size_m == 0) { return end();
    } else {
      for (int i = 0; i < D; ++i) {
	if (!table_m[i].empty()) return const_iterator(this,i,table_m[i].begin());
      }
    }
  }
  iterator end() { return iterator(this,D,table_m[D].end()); }

  const_iterator end() const { return const_iterator(this,D,table_m[D].end()); }
  bool empty() const { return size_m == 0; }

  size_type size() const { return size_m; }

  // insert/erase
  pair<iterator,bool> insert(const value_type& x) {
    size_type index = hash_m(x.first);
    pair<node_iterator, bool> result = table_m[index].insert(x);
    if (result.second) ++size_m;
    return pair<iterator,bool>(iterator(this,index,result.first), result.second);
  }

  void erase(iterator pos) {
    if (pos == end()) return;
    table_m[pos.bucket_m].erase(pos.it_m);
    --size_m;
  }

  size_type erase(const Key& x) {
    iterator it = find(x);
    if (it == end()) { return 0;
    } else {
      erase(it);
      return 1;
    }
  }

  ///@todo If allow change of D, should make change to clear
  void clear() {
    delete[] table_m;
    size_m = 0;
    table_m = new node_type[D+1];
  }

  // map operations:
  iterator find(const Key& x) {
    size_type index = hash_m(x);
    node_iterator result = table_m[index].find(x);
    if (result == table_m[index].end()) return end();
    else return iterator(this, index, result);
  }

  const_iterator find(const Key& x) const {
    size_type index = hash_m(x);
    node_iterator result = table_m[index].find(x);
    if (result == table_m[index].end()) return end();
    else return const_iterator(this, index, result);
  }

  size_type count(const Key& x) const { return find(x) != end(); }

  T& operator[](const Key& k) {
    iterator p = find(k);
    if (p != end()) return (*p).second;
    else {
      p = insert(value_type(k,T())).first;
      return (*p).second;
    }
  }

private:

  ///@param D The divisor and the capacity for different values of the map
  size_type D;

  ///@param size_m number of current elements in the map
  size_type size_m;

  ///@param table_m An array of size D and bstmap as each node to hold value pairs
  node_type* table_m;

  ///@param The hash function by taking in the D value
  hash<Key> hash_m;

  friend class iterator;
  friend class const_iterator;
};



#endif //HASHTABLEMAP_HPP

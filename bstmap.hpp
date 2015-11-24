#ifndef BSTMAP_HPP
#define BSTMAP_HPP

#include <utility>
#include <cstddef>
#include <iterator>

using std::pair;

/**
 * \class node
 * \brief A node in the bstmap basd on assumption that every node is a subtree.
 * \brief parent pointer is used for convenience.
 */
template <class Key, class T>
class node
{
public:
  typedef node<Key, T> node_type;
  typedef pair<const Key, T> value_type;

  node():leftc(NULL),rightc(NULL),parent(NULL){}

  node(const value_type& x, node_type* left = NULL, node_type* right = NULL):data_m(x),leftc(left),rightc(right),parent(NULL){
    if (leftc) leftc->parent = this;
    if (rightc) rightc->parent = this;
  }

  node(const node_type& x):data_m(x.data_m) {
    if (x.leftc) {
      leftc = new node(*(x.leftc));
      leftc -> parent = this;
    } else leftc = NULL;
    if (x.rightc) {
      rightc = new node(*(x.rightc));
      rightc -> parent = this;
    } else rightc = NULL;
  }

  ~node() {
    if (leftc) delete leftc;
    if (rightc) delete rightc;
  }

  node_type& operator=(const node_type& x){
    data_m = x.data_m;
    if (x.leftc) {
      leftc = new node(*(x.leftc));
      leftc -> parent = this;
    } else leftc = NULL;
    if (x.rightc) {
      rightc = new node(*(x.rightc));
      rightc -> parent = this;
    } else rightc = NULL;
  }

  bool operator<(const node_type& x) const{
    return (data_m.first < x.data_m.first);
  }

  bool operator>(const node_type& x) const{
    return (data_m.first > x.data_m.first);
  }

  bool operator==(const node_type& x) const{
    return (data_m.first == x.data_m.first);
  }

  bool operator!=(const node_type& x) const{
    return (data_m.first != x.data_m.first);
  }

  const Key& get_key() const { return data_m.first;}
  T& get_data() {return data_m.second;}
  value_type& get_value() {return data_m;}
  node_type* get_left() const {return leftc;}
  node_type* get_right() const {return rightc;}
  node_type* get_parent() const {return parent;}
  void set_data(const T& x) {data_m.second = x;}
  void set_left(node_type* x) {leftc = x; if (x) x->set_parent(this);}
  void set_right(node_type* x) {rightc = x; if (x) x->set_parent(this);}
  void set_parent(node_type*x) {parent = x;}

  node_type* min() {
    node_type* x = this;
    while (x -> leftc != NULL) {
      x = x -> leftc;
    }
     return x;
  }

  node_type* max() {
    node_type* x = this;
    while (x -> rightc != NULL) {
      x = x -> rightc;
    }
     return x;
  }

private:
  value_type data_m;
  node_type* leftc;
  node_type* rightc;
  node_type* parent;

};

/**
 * \class bstmap
 * \brief A binaray search tree map
 * \todo Haven't considered to balance the tree.
 */
template <typename Key, typename T>
class bstmap
{
  typedef bstmap<Key, T>        Self;
  typedef node<Key,T>           node_type;

public:
  typedef Key                      key_type;
  typedef T                        data_type;
  typedef T                        mapped_type;
  typedef pair<const Key, T>       value_type;
  typedef unsigned int             size_type;
  typedef int                      difference_type;

  /**
   * \class _iterator
   * \brief Implementation for iterator and const iterators using templates.
   */
  template <typename val_T, typename base_T>
  class _iterator {
    // your iterator definition goes here
    typedef std::input_iterator_tag iterator_category;
    typedef val_T value_type;
    typedef val_T* pointer;
    typedef val_T& reference;

    friend class bstmap;

  public:

    _iterator(base_T* q = NULL):p(q) {}
    _iterator(const _iterator& q):p(q.p) {}
    _iterator& operator=(const _iterator& q) {
      p = q.p;
      return *this;
    }

    reference operator*() {return p -> get_value();}
    pointer operator->() {return &(p -> get_value());}

    bool operator==(const _iterator& q) const {return p == q.p;}
    bool operator!=(const _iterator& q) const {return p != q.p;}

    _iterator& operator++() {
      if (p) {
	if (p -> get_right()) {
	  p = p -> get_right() -> min();
	} else {
	  node_type* par = p->get_parent();
	  while ((par != NULL) && (par -> get_right() == p)){
	      p = par;
	      par = par -> get_parent();
	  }
	  p = par; 
	}
      }
      return (*this);
    }
    _iterator operator++(int) {
      _iterator ret(*this);
      if (p) {
	if (p -> get_right()) {
	  p = p -> get_right() -> min();
	} else {
	  node_type* par = p->get_parent();
	  while ((par != NULL) && (par -> get_right() == p)){
	      p = par;
	      par = par -> get_parent();
	  }
	  p = par; 
	}
      }
      return ret;
    }

  private:
    base_T* p;
  };

  typedef _iterator<value_type, node_type> iterator;
  typedef _iterator<const value_type,const node_type> const_iterator;
  
public:
  // default constructor to create an empty map
  bstmap():root(NULL),size_m(0) {}

  // overload copy constructor to do a deep copy
  bstmap(const Self& x):size_m(x.size_m){
    root = (x.root)?(new node_type(*(x.root))):NULL;
  }
  ~bstmap() { clear();}

  // overload assignment to do a deep copy
  Self& operator=(const Self& x) {
    root = (x.root)?(new node_type(*(x.root))):NULL;
    size_m = x.size_m;
    return (*this);
  }

  // accessors:
  iterator begin() {
    return (root)?iterator(root -> min()):iterator();
  }

  const_iterator begin() const {
    return (root)?const_iterator(root -> min()):const_iterator();
  }

  iterator end() {
    return iterator();
  }

  const_iterator end() const {
    return const_iterator();
  }

  bool empty() const {return root == NULL;}
  size_type size() const {
    return size_m;
  }

  // insert/erase
  pair<iterator,bool> insert(const value_type& x) {
    node_type new_node(x);
    node_type* p = root;
    node_type* pp = NULL;
    while (p) {
      pp = p;
      if (new_node < *p) p = p -> get_left();
      else if  (new_node > *p) p = p -> get_right();
      else return pair<iterator,bool>(iterator(p),false);
    }
    if (root) {
      if (new_node < *pp) pp -> set_left( p = new node_type(x) );
      else pp -> set_right( p = new node_type(x) );
    } else root =  p = new node_type(x);
    ++size_m;
    return pair<iterator,bool>(iterator(p),true);
  }
  
  void erase(iterator pos) {
    node_type* x = pos.p;
    if (!x) return;
    if (x->get_left() && x->get_right()) {
      iterator succ = ++pos;
      node_type* s = succ.p;
      node_type* xp = x-> get_parent();
      node_type* xl = x-> get_left(); x->set_left(NULL);
      node_type* xr = x-> get_right(); x -> set_right(NULL);
      node_type* c = new node_type(s->get_value());
      c->set_parent(xp);
      c->set_left(xl);
      c->set_right(xr);
      if (x == root) root = c;
      else {
	if (x == xp->get_left()) xp->set_left(c);
	else xp->set_right(c);
      }
      delete x;
      x = s;
    }
    node_type* c;
    if (x->get_left()) {
      c = x-> get_left();
      x -> set_left(NULL);
    } else {
      c = x-> get_right();
      x -> set_right(NULL);
    }
    if (x == root) {
      root = c;
      if (c) c -> set_parent(NULL);
    } else {
      if (x == x->get_parent()->get_left()) x->get_parent()->set_left(c);
      else x->get_parent()->set_right(c);
    }
    delete x;
    --size_m;
  }

  size_type erase(const Key& x) {
    iterator p(find(x));
    if (p == end()) return 0;
    else {
      erase(p);
      return 1;
    }
  }
  void clear() {
    delete root;
    root = NULL;
    size_m = 0;
  }

  // map operations:
  iterator find(const Key& x) {
    node_type* p = root;
    bool y = (root != NULL);
    while (y) {
      if (p -> get_key() == x){
	return iterator(p);
      } else if (p -> get_key() > x) {
	if (p -> get_left()) p = p -> get_left();
	else y = false;
      } else {
        if (p -> get_right()) p = p -> get_right();
	else y = false;
      }
    }
    if (!y) return iterator();
  }

  const_iterator find(const Key& x) const {
    node_type* p = root;
    bool y = (root != NULL);
    while (y) {
      if (p -> get_key() == x){
	return const_iterator(p);
      } else if (p -> get_key() > x) {
	if (p -> get_left()) p = p -> get_left();
	else y = false;
      } else {
        if (p -> get_right()) p = p -> get_right();
	else y = false;
      }
    }
    if (!y) return const_iterator();
  }

  size_type count(const Key& x) const {
    return (find(x) != end());
  }

  T& operator[](const Key& k) {
      iterator p = find(k);
      if (p != end()) return (*p).second;
      else {
        p = insert(value_type(k,T())).first;
	return (*p).second;
      }
  }
private:
  node_type* root;
  size_type size_m;
};

#endif //BSTMAP_HPP


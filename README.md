# var - A Part of Oliver

The 'var' class represents an immutable fully functional object wrapper. It will accept any object assigned to by the assignment operator '='. Example: 
```
var a = 42;
```
Instances of 'var' can be reassign new values.  The immutability of the class is in the data assigned to the instance of 'var'.  It can not be changed without a copy being made.  Multiple instance of 'var' can reference 'a' in the example.  If a gets a new value, all of the other instances of 'var' would still point to the original '42' assign to 'a'.  While 'a' simply points to the new value.

The fundamental structure of the 'var' data type was inspired and extended from a presentation entitled: Title: Value Semantics and Concept-based Polymorphism By - Sean Parent (http://sean-parent.stlab.cc/papers-and-presentations)

A 'node', 'term', and 'expression', classes are also defined.  

The 'node' class is simply a Lisp like node, which can be used to create other data type with immutability.  While the 'term' class only differs in that it tracks the number of nodes within the term. 

The 'expression' class is defined by two 'term's, to create a [Real Time Queue](https://en.wikipedia.org/wiki/Real-time_queue) deque.   
```
    var a = Olly::expression(0, 1, 2, 3, 4, 5, 6, 7);
    var b = (a, 8, 9, 10L, std::string("string"));
    var c = b.join(a);
```
Should produce an output of:
```
    a = (0 1 2 3 4 5 6 7)
    b = (0 1 2 3 4 5 6 7 8 9 10 string)
    c = ((0 1 2 3 4 5 6 7) 0 1 2 3 4 5 6 7 8 9 10 string)
```
**Note** - That commas, are overridden to append data to the end of expressions.

### Object Manipulation

Object managed by a 'var' can be directly manipulated by overriding the 'var' 'interface_type' class methods, using friend methods outlined below.  It is highly recommended to override the first grouping of functions.  While the rest should be overwritten as needed.  
```
    template<typename T>            
    std::string     _type_(const T& self);                              //  Type Name          
    std::string      _cat_(const T& self);                              //  Category Name  
    bool              _is_(const T& self);                              //  Boolean Conversion  
    void             _str_(std::stringstream& out, const T& self);      //  String Conversion  
    void            _repr_(std::stringstream& out, const T& self);      //  String Representation  
    double          _comp_(const T& self, var other);                   //  Comparison Between Variables  

    var             _b_and_(const T& self, var other);                  //  Logical Conjunction  
    var             _b_or_ (const T& self, var other);                  //  Logical Inclusive Disjunction  
    var             _b_xor_(const T& self, var other);                  //  Logical Exclusive Disjunction  
    var             _b_neg_(const T& self);                             //  Negation  
    var             _u_add_(const T& self);                             //  Unary Addition  
    var             _u_neg_(const T& self);                             //  Unary Compliment  

    var               _add_(const T& self, var other);                  //  Addition or Concatenation  
    var               _sub_(const T& self, var other);                  //  Subtraction or Division  
    var               _mul_(const T& self, var other);                  //  Multiplication  
    var               _div_(const T& self, var other);                  //  Division  
    var               _mod_(const T& self, var other);                  //  Modulation  
    var             _f_div_(const T& self, var other);                  //  Floor Division  
    var               _rem_(const T& self, var other);                  //  Remainder                         
    var               _pow_(const T& self, var other);                  //  Raise to Power of  
    var              _root_(const T& self, var other);                  //  Reduce to Power of  

    bool             _has_(const T& self, var other);                   //  Check if an object has an element  
    std::size_t     _size_(const T& self);                              //  Length Of  
    var             _lead_(const T& self);                              //  Lead Element Of  
    var             _last_(const T& self);                              //  Last Element Of  
    var             _join_(const T& self, var other);                   // Prepend Lead Element Of  
    var             _link_(const T& self, var other);                   // Prepend Lead Element Of  
    var             _next_(const T& self);                              //  Drop The Leading Element  
    var             _prev_(const T& self);                              //  Drop The Leading Element  
    var             _reverse_(const T& self);                           //  Reverse The Elements Of  

    var              _get_(const T& self, var other);                   //  Retrieve A Selection From  
    var              _set_(const T& self, var other, var val);          //  Set A Selection Of  
    var              _del_(const T& self, var other);                   //  Remove A Selection From  

    std::size_t           _hash_(const T& self);                        //  Hash Value  
    OP_CODE            _op_code_(const T& self);                        //  Return An Operation Code 
    bool            _is_nothing_(const T& self);                        //  Determine If A Var Is Undefined 
    std::string           _help_(const T& self);                        //  Return A Help String 
```
For example in the 'node' class the overrides look like this.
```
    friend std::string   _type_(const node& self);
    friend bool            _is_(const node& self);
    friend double        _comp_(const node& self, const var& other);

    friend void            _str_(std::stringstream& out, const node& self);
    friend void           _repr_(std::stringstream& out, const node& self);

    friend std::size_t    _size_(const node& self);
    friend var            _lead_(const node& self);
    friend var            _join_(const node& self, const var& other);
    friend var            _next_(const node& self);
    friend var         _reverse_(const node& self);
```
**Note** - Be care full of large collections, stored within a 'var'.  Each manipulation will require a copy of the entire collection.  Instead using a functional version of the collection, in which single nodes are being manipulated, will provide faster performance. 

### Data Access
The data held by a 'var' can be accessed by a templated cast, and copy method.  If cast to an invalid type, a null_ptr is returned.  Else if copied to an invalid type a default constructor of the type copied to is returned.   

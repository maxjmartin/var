# var - A Part of Oliver

The 'var' class represents an immutable object wrapper. It will accept any object assigned to by the assignment operator '='. Example: var a = 42;

The 'var' class supports both a functional and object oriented API. But it requires that any object utilizing its API override a series of functions described below, in order to utilize run-time polymorphism without object inheritance, through the 'var' API.

The var object itself is not immutable.  It can be reassign data types after being initialized.  The data is manages is immutable, in that a copy of the data type must be created first, to then be manipulated.  Then reassign to a 'var', or another instance of the data type.  

The 'var' class also supports both pass by reference and pass by value. Any object it holds can be safely cast to a pointer of the object type. If the type cast is made to an incorrect data type then a std::null_ptr is returned instead.

All object can also be copied to another instance of the type safely. If an incorrect type is specified, an instance of that type will still be made using the default construction for the type being copied.

The fundamental structure of the 'var' data type was inspired and extended from a presentation entitled: Title: Value Semantics and Concept-based Polymorphism By - Sean Parent (http://sean-parent.stlab.cc/papers-and-presentations)

The 'node', 'term', and 'expression', classes are also made as part of 'var'.

The 'node' class is simply a Lisp like node, which can be used to create other data type with immutability.

The 'term' class is almost identical to the 'node' class. The primary difference between the two, is that a 'term' keeps track of the length of 'node's it manages.

The 'expression' class is a fully immutable double ended que implemented using 'terms'. It is designed with an overloading of the comma operator so to allow data to be appended to any 'expression' in a common sense way. Examples:
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
The 'expression' class was initial design using a std::vector<var>.  But due it it needing to be copied at every manipulation, the performance was slowed down considerably. By using Lisp like nodes only the index to manipulated requires being copied, instead of a whole vector.  

Additional data types will be added to this project, like immutable persistent maps.  'var' is a work in progress, and will receive updates as needed.  

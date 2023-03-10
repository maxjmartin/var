#pragma once

/*********************************************************************/
//
//			Copyright 2022 Max J. Martin
//
//			This file is part of Oliver.
// 
//			Oliver is free software : you can redistribute it
//			and /or modify it under the terms of the GNU General
//			Public License as published by the Free Software
//			Foundation, either version 3 of the License, or
//			(at your option) any later version.
//			
//			Oliver is distributed in the hope that it will be
//			useful, but WITHOUT ANY WARRANTY; without even the
//			implied warranty of MERCHANTABILITY or FITNESS FOR
//			A PARTICULAR PURPOSE.See the GNU General Public
//			
//			You should have received a copy of the GNU General
//			Public License along with Oliver.If not, see
//			< https://www.gnu.org/licenses/>.
//			
/*********************************************************************/

#include "Components/sys/config.h"
#include "Components/sys/OP_CODES.h"

namespace Olly {

    /********************************************************************************************/
    //
    //                                'var' Class Definition
    //
    //          The 'var' class represents an immutable object wrapper.  It will accept
    //          any object assigned to by the assignment operator '='.
    //              Example:  var a = 42;
    //
    //          The 'var' class supports both a functional and object oriented API.
    //          But it requires that any object utilizing its API override a series of
    //          functions described below, in order to utilize run-time polymorphism
    //          without object inheritance, through the 'var' API.
    //
    //          The 'var' class also supports both pass by reference and pass by value.
    //          Any object it holds can be safely cast to a pointer of the object type.
    //          If the type cast is made to an incorrect data type then a std::nothing_ptr
    //          is returned instead.
    // 
    //          All object can also be copied to another instance of the type safely.  If
    //          an incorrect type is specified, an instance of that type will still be 
    //          made using the default construction for the type being copied.  
    //
    //          The fundamental structure of the 'var' data type was inspired and extended
    //          from a presentation entitled:
    //                 Title: Value Semantics and Concept-based Polymorphism
    //                 By - Sean Parent
    //                 (http://sean-parent.stlab.cc/papers-and-presentations)
    //
    //          The class is defined using explicit inclusion instantiation, a class
    //          declaration is defined, followed by the class definition.
    //
    /********************************************************************************************/

    const enum class OP_CODE;

    class var {
        struct interface_type;

    public:

        var();
        template <typename T>          var(T  x);
        template <typename T>          var(T* x);

        friend std::ostream& operator<<(std::ostream& stream, var n);

        template <typename T> const T* cast()       const;  // Cast the object as an instance of the specified type.
        template <typename T>       T  copy()       const;  // Get a copy of the objects as a specified type.

        Text                id()                    const;  // Return the std::typeid string of the object.
        bool           is_type(var other)           const;  // Compare two objects by typeid.
        std::size_t       hash()                    const;  // Get the hash of an object.

        Text              type()                    const;  // The class generated type name.
        Text               cat()                    const;  // The class generated category name.
        bool                is()                    const;  // Is or is not the object defined.
        void               str(Text_Stream& out)    const;  // String representation of the object.
        void              repr(Text_Stream& out)    const;  // Recreatable text representation of an object.

        operator bool()                             const;

        double            comp(var other)           const;  // Compare two objects. 0 = equality, > 0 = grater than, < 0 = less than, NAN = not same type.
        bool                eq(var other)           const;  // Equal to.
        bool                ne(var other)           const;  // Not equal to.
        bool                ge(var other)           const;  // Greater than equal to.
        bool                le(var other)           const;  // Less than equal to.
        bool                gt(var other)           const;  // Greater than.
        bool                lt(var other)           const;  // Less than.

        bool    operator==(var other)               const;
        bool    operator!=(var other)               const;
        bool    operator>=(var other)               const;
        bool    operator> (var other)               const;
        bool    operator<=(var other)               const;
        bool    operator< (var other)               const;

        var              b_and(var other)           const;  // Binary and.
        var               b_or(var other)           const;  // Binary or.
        var              b_xor(var other)           const;  // Binary exclusive or.
        var              b_neg()                    const;  // Binary negation.

        var         operator&(var other)            const;
        var         operator|(var other)            const;
        var         operator^(var other)            const;
        var         operator~()                     const;

        var              u_add()                    const;  // Addition identity.
        var              u_neg()                    const;  // Unary compliment.

        var                add(var other)           const;  // Addition.
        var                sub(var other)           const;  // Subtraction.
        var                mul(var other)           const;  // Multiplication.
        var                div(var other)           const;  // Division.
        var                mod(var other)           const;  // Modulus.

        var          operator+()                    const;
        var          operator-()                    const;

        var          operator+(var other)           const;
        var          operator-(var other)           const;
        var          operator*(var other)           const;
        var          operator/(var other)           const;
        var          operator%(var other)           const;

        var              f_div(var other)           const;  // Floor divide.
        var                rem(var other)           const;  // Remainder.
        var                pow(var other)           const;  // Raise to the power of.
        var               root(var other)           const;  // Reduce to the root of.

        bool               has(var other)           const;  // Determine if an object has an element.
        std::size_t       size()                    const;  // Size of an object.
        var               lead()                    const;  // Lead element of an object.
        var               last()                    const;  // Last element of an object.
        var               join(var other)           const;  // Place an object as the lead element.
        var               link(var other)           const;  // Place an object as the lead element.
        var               next()                    const;  // Remove the lead element from an object.
        var               prev()                    const;  // Remove the lead element from an object.

        var         operator>>(var other)           const;
        var         operator<<(var other)           const;

        var          operator,(var other)           const;

        var                get(var key)             const;  // Get an element from a collection.
        var                set(var key, var val)    const;  // Set the value of an element in a collection.
        var                del(var key)             const;  // Delete an element from a collection.

        var            reverse()                    const;  // Reverse the order of an object's elements.

        OP_CODE        op_code()                    const;
        bool        is_nothing()                    const;
        bool      is_something()                    const;
        Text              help()                    const;  // Define a string description of the object.

        // TODO: add capture of arguments to pass to a function.
        // TODO: figure out how to incorporate expression iteration.

    private:

        struct interface_type {

            /********************************************************************************************/
            //
            //                              'interface_type' Class Definition
            //
            //       A simple interface description allowing redirection of the 'var' data type.
            //
            /********************************************************************************************/

            virtual ~interface_type() {};

            virtual operator bool()                           const = 0;

            virtual void*           _vptr()                         = 0;
            virtual Text            _id()                     const = 0;
            virtual std::size_t     _hash()                   const = 0;

            virtual Text            _type()                   const = 0;
            virtual Text            _cat()                    const = 0;
            virtual bool            _is()                     const = 0;
            virtual void            _str(Text_Stream& out)    const = 0;
            virtual void            _repr(Text_Stream& out)   const = 0;

            virtual double          _comp(var other)          const = 0;

            virtual var             _b_and(var other)         const = 0;
            virtual var             _b_or(var other)          const = 0;
            virtual var             _b_xor(var other)         const = 0;
            virtual var             _b_neg()                  const = 0;

            virtual var             _u_add()                  const = 0;
            virtual var             _u_neg()                  const = 0;

            virtual var             _add(var other)           const = 0;
            virtual var             _sub(var other)           const = 0;
            virtual var             _mul(var other)           const = 0;
            virtual var             _div(var other)           const = 0;
            virtual var             _mod(var other)           const = 0;

            virtual var             _f_div(var other)         const = 0;
            virtual var             _rem(var other)           const = 0;
            virtual var             _pow(var other)           const = 0;
            virtual var             _root(var other)          const = 0;

            virtual bool            _has(var other)           const = 0;
            virtual std::size_t     _size()                   const = 0;
            virtual var             _lead()                   const = 0;
            virtual var             _last()                   const = 0;
            virtual var             _join(var other)          const = 0;
            virtual var             _link(var other)          const = 0;
            virtual var             _next()                   const = 0;
            virtual var             _prev()                   const = 0;

            virtual var             _reverse()                const = 0;

            virtual var             _get(var key)             const = 0;
            virtual var             _set(var key, var val)    const = 0;
            virtual var             _del(var key)             const = 0;

            virtual Text            _help()                   const = 0;
            virtual bool            _is_nothing()             const = 0;
            virtual OP_CODE         _op_code()                const = 0;
        };

        template <typename T>
        struct data_type : interface_type {

            /******************************************************************************************/
            //
            //                                 'data_type' Class Definition
            //
            //             The interface implementation of the 'interface_type' data type.
            //             Defining a shared const pointer of the data type passed to it.
            //
            /******************************************************************************************/

            data_type(T val);
            virtual ~data_type();

            operator bool()                          const;

            void*           _vptr()                       ;
            Text            _id()                    const;
            std::size_t     _hash()                  const;

            Text            _type()                  const;
            Text            _cat()                   const;
            bool            _is()                    const;
            void            _str(Text_Stream& out)   const;
            void            _repr(Text_Stream& out)  const;

            double         _comp(var other)          const;

            var            _b_and(var other)         const;
            var            _b_or(var other)          const;
            var            _b_xor(var other)         const;
            var            _b_neg()                  const;

            var            _u_add()                  const;
            var            _u_neg()                  const;

            var            _add(var other)           const;
            var            _sub(var other)           const;
            var            _mul(var other)           const;
            var            _div(var other)           const;
            var            _mod(var other)           const;

            var            _f_div(var other)         const;
            var            _rem(var other)           const;
            var            _pow(var other)           const;
            var            _root(var other)          const;

            bool           _has(var other)           const;
            std::size_t    _size()                   const;
            var            _lead()                   const;
            var            _last()                   const;
            var            _join(var other)          const;
            var            _link(var other)          const;
            var            _next()                   const;
            var            _prev()                   const;

            var            _get(var key)             const;
            var            _set(var key, var val)    const;
            var            _del(var key)             const;

            var            _reverse()                const;

            Text           _help()                   const;
            bool           _is_nothing()             const;
            OP_CODE        _op_code()                const;

            T              _data;
        };

        std::shared_ptr<const interface_type> _self;
    };




    /********************************************************************************************/
    //
    //                                 'nothing' Class Definition
    //
    //          A basic class definition of the value of nothing.  This is used within
    //          'var' class implementation to return a result of nothing for results
    //          which have either conflicting types, or in some cases as the default to
    //          return unless overridden.
    //
    //          This class also demonstrates the basic function methods that should be
    //          over written for proper object behavior.
    //
    /********************************************************************************************/

    class nothing {

    public:

        friend Text          _type_(const nothing& self);
        friend bool            _is_(const nothing& self);
        friend double        _comp_(const nothing& self, var other);

        friend void           _str_(Text_Stream& out, const nothing& self);
        friend void          _repr_(Text_Stream& out, const nothing& self);

        friend bool    _is_nothing_(const nothing& self);
    };




    /********************************************************************************************/
    //
    //                                Support Function Declarations
    //
    //          These definitions add a few useful and some necessary support functions.
    //
    /********************************************************************************************/

    Text  str(var a);          // Convert any 'var' to a Text.
    Text repr(var a);          // Convert any 'var' to a Text representation of the 'var'.

    var pop_lead(var& exp);    // Remove and return the lead element from an ordered expression.
    var pop_last(var& exp);    // Remove and return the last element from an ordered expression.



    
    /********************************************************************************************/
    //
    //                               'node' Class Definition
    //
    //          The node class is implemented using Lisp inspired data nodes.  It
    //          is used to define the data sets as in Lisp.  
    //
    /********************************************************************************************/

    class node {

        var _data;
        var _next;

    public:

        node();
        node(var obj);

        friend Text          _type_(const node& self);
        friend bool            _is_(const node& self);
        friend double        _comp_(const node& self, const var& other);

        friend void            _str_(Text_Stream& out, const node& self);
        friend void           _repr_(Text_Stream& out, const node& self);

        friend std::size_t    _size_(const node& self);
        friend var            _lead_(const node& self);
        friend var            _join_(const node& self, const var& other);
        friend var            _next_(const node& self);
        friend var         _reverse_(const node& self);
    };

    /********************************************************************************************/
    //
    //                               'term' Class Definition
    //
    //          The term class is implemented using Lisp inspired data nodes.  It
    //          is used to define the data sets as in Lisp.  
    //
    /********************************************************************************************/

    class term {

        var         _term;
        std::size_t _size;

    public:

        term();
        term(var x);

        friend Text           _type_(const term& self);
        friend bool             _is_(const term& self);
        friend double         _comp_(const term& self, const var& other);

        friend void            _str_(Text_Stream& out, const term& self);
        friend void           _repr_(Text_Stream& out, const term& self);

        friend std::size_t    _size_(const term& self);
        friend var            _lead_(const term& self);
        friend var            _join_(const term& self, const var& other);
        friend var            _next_(const term& self);
        friend var         _reverse_(const term& self);
    };

    /********************************************************************************************/
    //
    //                               'expression' Class Definition
    //
    //          The expression class is implemented using Lisp inspired data nodes.  It
    //          is used to define the data sets as in Lisp.  
    //
    /********************************************************************************************/

    class expression {

        var _lead;
        var _last;

        static const std::size_t balance_limit = 2;

    public:

        expression();
        expression(var x);
        template<typename T, typename... Args>
        expression(T x, Args... args);
        virtual ~expression();

        friend Text           _type_(const expression& self);
        friend bool             _is_(const expression& self);
        friend double         _comp_(const expression& self, const var& other);

        friend void            _str_(Text_Stream& out, const expression& self);
        friend void           _repr_(Text_Stream& out, const expression& self);

        friend std::size_t    _size_(const expression& self);
        friend var            _lead_(const expression& self);
        friend var            _last_(const expression& self);
        friend var            _join_(const expression& self, const var& other);
        friend var            _link_(const expression& self, const var& other);
        friend var            _next_(const expression& self);
        friend var            _prev_(const expression& self);
        friend var         _reverse_(const expression& self);

        friend var             _add_(const expression& self, const var& other);

        template<typename... Args>
        void link(const var& other, Args... args);
        void link(const var& other);
        void link();

        void balance();
        void balance(var& a, var& b);
    };




    /********************************************************************************************/
    //
    //                      'var' Class Function Default Template API.
    //
    //           The following function templates define the over-ridable functions which
    //           may be used to tailor the behavior of any object held within a 'var'.
    //
    //           Each function defined here defines the default behavior of each function
    //           which is invoked if a function is not overwritten for a defined class.
    //
    /********************************************************************************************/


    template<typename T>            /****  Hash Value  ****/
    std::size_t _hash_(const T& self);

    template<typename T>
    std::size_t _hash_(const T& self) {
        return DEFAULT_HASH_FUNCTION(repr(self));
    }


    template<typename T>            /****  Type Name  ****/
    Text _type_(const T& self);

    template<typename T>
    Text _type_(const T& self) {
        return typeid(self).name();
    }


    template<typename T>            /****  Category Name  ****/
    Text _cat_(const T& self);

    template<typename T>
    Text _cat_(const T& self) {
        return "uncategorized";
    }


    template<typename T>            /****  Boolean Conversion  ****/
    bool _is_(const T& self);

    template<typename T>
    bool _is_(const T& self) {
        return false;
    }


    template<typename T>            /****  String Conversion  ****/
    void _str_(Text_Stream& out, const T& self);

    template<typename T>
    void _str_(Text_Stream& out, const T& self) {

        // TODO: handle object based on stream availability.
        // 
        //constexpr bool n = is_streamable<std::stringstream, T>::value;

        //if (n) {
        //    out << self;
        //}
        //else {
        //    out << "object<" << &self << "," << _type_(self) << ">";
        //}

        // out << "object<" << &self << "," << _type_(self) << ">";

        out << self;
    }


    template<typename T>            /****  String Representation  ****/
    void _repr_(Text_Stream& out, const T& self);

    template<typename T>
    void _repr_(Text_Stream& out, const T& self) {
        out << str(nothing());
    }


    template<typename T>            /****  Comparison Between Variables  ****/
    double _comp_(const T& self, var other);

    template<typename T>
    double _comp_(const T& self, var other) {
        return NOT_A_NUMBER;
    }


    template<typename T>            /****  Logical Conjunction  ****/
    var _b_and_(const T& self, var other);

    template<typename T>
    var _b_and_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Logical Inclusive Disjunction  ****/
    var _b_or_(const T& self, var other);

    template<typename T>
    var _b_or_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Logical Exclusive Disjunction  ****/
    var _b_xor_(const T& self, var other);

    template<typename T>
    var _b_xor_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Negation  ****/
    var _b_neg_(const T& self);

    template<typename T>
    var _b_neg_(const T& self) {
        return self;
    }


    template<typename T>            /****  Unary Addition  ****/
    var _u_add_(const T& self);

    template<typename T>
    var _u_add_(const T& self) {
        return var();
    }


    template<typename T>            /****  Unary Compliment  ****/
    var _u_neg_(const T& self);

    template<typename T>
    var _u_neg_(const T& self) {
        return var();
    }


    template<typename T>            /****  Addition or Concatenation  ****/
    var _add_(const T& self, var other);

    template<typename T>
    var _add_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Subtraction or Division  ****/
    var _sub_(const T& self, var other);

    template<typename T>
    var _sub_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Multiplication  ****/
    var _mul_(const T& self, var other);

    template<typename T>
    var _mul_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Division  ****/
    var _div_(const T& self, var other);

    template<typename T>
    var _div_(const T& self, var other) {
        return var();
    }

    template<typename T>            /****  Modulation  ****/
    var _mod_(const T& self, var other);

    template<typename T>
    var _mod_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Floor Division  ****/
    var _f_div_(const T& self, var other);

    template<typename T>
    var _f_div_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Remainder  ****/
    var _rem_(const T& self, var other);

    template<typename T>
    var _rem_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Raise to Power of  ****/
    var _pow_(const T& self, var other);

    template<typename T>
    var _pow_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Reduce to Power of  ****/
    var _root_(const T& self, var other);

    template<typename T>
    var _root_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Check if an object has an element  ****/
    bool _has_(const T& self, var other);

    template<typename T>
    bool _has_(const T& self, var other) {
        return false;
    }


    template<typename T>            /****  Length Of  ****/
    std::size_t _size_(const T& self);

    template<typename T>
    std::size_t _size_(const T& self) {
        return 0;
    }


    template<typename T>            /****  Lead Element Of  ****/
    var _lead_(const T& self);

    template<typename T>
    var _lead_(const T& self) {
        return var();
    }


    template<typename T>            /****  Lead Element Of  ****/
    var _last_(const T& self);

    template<typename T>
    var _last_(const T& self) {
        return var();
    }


    template<typename T>            /**** Prepend Lead Element Of  ****/
    var _join_(const T& self, var other);

    template<typename T>
    var _join_(const T& self, var other) {
        return var();
    }


    template<typename T>            /**** Prepend Lead Element Of  ****/
    var _link_(const T& self, var other);

    template<typename T>
    var _link_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Drop The Leading Element  ****/
    var _next_(const T& self);

    template<typename T>
    var _next_(const T& self) {
        return var();
    }


    template<typename T>            /****  Drop The Leading Element  ****/
    var _prev_(const T& self);

    template<typename T>
    var _prev_(const T& self) {
        return var();
    }


    template<typename T>            /****  Reverse The Elements Of  ****/
    var _reverse_(const T& self);

    template<typename T>
    var _reverse_(const T& self) {
        return var();
    }


    template<typename T>            /****  Retrieve A Selection From  ****/
    var _get_(const T& self, var other);

    template<typename T>
    var _get_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Set A Selection Of  ****/
    var _set_(const T& self, var other, var val);

    template<typename T>
    var _set_(const T& self, var other, var val) {
        return var();
    }


    template<typename T>            /****  Remove A Selection From  ****/
    var _del_(const T& self, var other);

    template<typename T>
    var _del_(const T& self, var other) {
        return var();
    }


    template<typename T>            /****  Return An Operation Code ****/
    OP_CODE _op_code_(const T& self);

    template<typename T>
    OP_CODE _op_code_(const T& self) {
        return OP_CODE::nothing_op;
    }


    template<typename T>            /****  Determine If A Var Is Undefined ****/
    bool _is_nothing_(const T& self);

    template<typename T>
    bool _is_nothing_(const T& self) {
        return false;
    }


    template<typename T>            /****  Return A Help String ****/
    Text _help_(const T& self);

    template<typename T>
    Text _help_(const T& self) {
        return "No object documentation available.";
    }


    std::ostream& operator<<(std::ostream& stream, var n) {

        Text_Stream out;

        out.copyfmt(stream);

        n.str(out);

        stream << out.str();

        return stream;
    }




    /********************************************************************************************/
    //
    //                                 'nothing' Class Implementation
    //
    /********************************************************************************************/

    Text _type_(const nothing& self) {
        return "nothing";
    }

    bool _is_(const nothing& self) {
        return false;
    }

    double _comp_(const nothing& self, var other) {
        return NOT_A_NUMBER;
    }

    void _str_(Text_Stream& out, const nothing& self) {
        out << "nothing";
    }

    void _repr_(Text_Stream& out, const nothing& self) {
        out << "nothing";
    }

    bool _is_nothing_(const nothing& self) {
        return true;
    }




    /********************************************************************************************/
    //
    //                                'var' Class Implementation
    //
    /********************************************************************************************/

    var::var() : _self(std::make_shared<data_type<Olly::nothing>>(Olly::nothing())) {
    }

    template <typename T>
    var::var(T x) : _self(std::make_shared<data_type<T>>(std::move(x))) {
    }

    template <typename T>
    var::var(T* x) : _self(std::make_shared<data_type<T>>(x)) {
    }

    template <typename T>
    const T* var::cast() const {

        var n = T{};

        if (is_type(n)) {

            const T* p = static_cast<T*>(const_cast<interface_type*>(_self.get())->_vptr());

            if (p) {
                return p;
            }
        }

        return nullptr;
    }

    template <typename T> 
    T var::copy() const {

        T n = T{};

        if (is_type(n)) {

            const T* p = static_cast<T*>(const_cast<interface_type*>(_self.get())->_vptr());

            if (p) {
                n = *p;
            }
        }

        return n;
    }

    Text var::id() const {
        return _self->_id();
    }

    bool var::is_type(var other) const {
        return _self->_id() == other._self->_id();
    }

    std::size_t var::hash() const {
        return _self->_hash();
    }

    Text var::type() const {
        return _self->_type();
    }

    Text var::cat() const {
        return _self->_cat();
    }

    bool var::is() const {
        return const_cast<interface_type*>(_self.get())->_is();
    }

    void var::str(Text_Stream& out) const {
        _self->_str(out);
    }

    void var::repr(Text_Stream& out) const {
        _self->_repr(out);
    }

    double var::comp(var other) const {
        return _self->_comp(other);
    }

    bool var::eq(var other) const {
        return (comp(other) == 0.0 ? true : false);
    }

    bool var::ne(var other) const {
        return (comp(other) != 0.0 ? true : false);
    }

    bool var::ge(var other) const {
        return (comp(other) >= 0.0 ? true : false);
    }

    bool var::le(var other) const {
        return (comp(other) <= 0.0 ? true : false);
    }

    bool var::gt(var other) const {
        return (comp(other) > 0.0 ? true : false);
    }

    bool var::lt(var other) const {
        return (comp(other) < 0.0 ? true : false);
    }

    var var::b_and(var other) const {
        return _self->_b_and(other);
    }

    var var::b_or(var other) const {
        return _self->_b_or(other);
    }

    var var::b_xor(var other) const {
        return _self->_b_xor(other);
    }

    var var::b_neg() const {
        return _self->_b_neg();
    }

    var var::operator&(var other) const {
        return b_and(other);
    }

    var var::operator|(var other) const {
        return b_or(other);
    }

    var var::operator^(var other) const {
        return b_xor(other);
    }

    var var::operator~() const {
        return b_neg();
    }

    var var::u_add() const {
        return _self->_u_add();
    }

    var var::u_neg() const {
        return _self->_u_neg();
    }

    var var::add(var other) const {
        return _self->_add(other);
    }

    var var::sub(var other) const {
        return _self->_sub(other);
    }

    var var::mul(var other) const {
        return _self->_mul(other);
    }

    var var::div(var other) const {
        return _self->_div(other);
    }

    var var::mod(var other) const {
        return _self->_mod(other);
    }

    var var::operator+() const {
        return u_add();
    }

    var var::operator-() const {
        return u_neg();
    }

    var var::f_div(var other) const {
        return _self->_f_div(other);
    }

    var var::rem(var other) const {
        return _self->_rem(other);
    }

    var var::pow(var other) const {
        return _self->_pow(other);
    }

    var var::root(var other) const {
        return _self->_root(other);
    }

    bool var::has(var other) const {
        return _self->_has(other);
    }

    std::size_t var::size() const {
        return _self->_size();
    }

    var var::lead() const {
        return _self->_lead();
    }

    var var::last() const {
        return _self->_last();
    }

    var var::join(var other) const {
        return _self->_join(other);
    }

    var var::link(var other) const {
        return _self->_link(other);
    }

    var var::next() const {
        return _self->_next();
    }

    var var::prev() const {
        return _self->_prev();
    }

    var var::operator>>(var other) const {

        std::size_t shift = other.copy<std::size_t>();

        var a{ *this };

        while (shift--) {

            a = a.next();
        }

        return a;
    }

    var var::operator<<(var other) const {

        std::size_t shift = other.copy<std::size_t>();

        var a{ *this };

        while (shift--) {
            a = a.prev();
        }

        return a;
    }

    var var::operator,(var other) const {
        return link(other);
    }

    var var::reverse() const {
        return _self->_reverse();
    }

    var var::get(var other) const {
        return _self->_get(other);
    }

    var var::set(var other, var val) const {
        return _self->_set(other, val);
    }

    var var::del(var other) const {
        return _self->_del(other);
    }

    OP_CODE var::op_code() const {
        return _self->_op_code();
    }

    bool var::is_nothing() const {
        return _self->_is_nothing();
    }

    bool var::is_something() const {
        return !_self->_is_nothing();
    }

    Text var::help() const {
        return _self->_help();
    }

    var::operator bool() const {
        return is();
    }

    bool var::operator==(var other) const {
        return eq(other);
    }

    bool var::operator!=(var other) const {
        return ne(other);
    }

    bool var::operator>=(var other) const {
        return ge(other);
    }

    bool var::operator> (var other) const {
        return gt(other);
    }

    bool var::operator<=(var other) const {
        return le(other);
    }

    bool var::operator< (var other) const {
        return lt(other);
    }

    var var::operator+(var other) const {
        return add(other);
    }

    var var::operator-(var other) const {
        return sub(other);
    }

    var var::operator*(var other) const {
        return mul(other);
    }

    var var::operator/(var other) const {
        return div(other);
    }

    var var::operator%(var other) const {
        return mod(other);
    }




    /********************************************************************************************/
    //
    //                                'data_type' Class Implementation
    //
    /********************************************************************************************/

    template <typename T>
    var::data_type<T>::data_type(T val) : _data(std::move(val)) {
    }

    template<typename T>
    var::data_type<T>::~data_type() {
    }

    template <typename T>
    var::data_type<T>::operator bool() const {
        return _is();
    }

    template <typename T>
    void* var::data_type<T>::_vptr() {
        return &_data;
    }

    template <typename T>
    Text var::data_type<T>::_id() const {
        return typeid(_data).name();
    }

    template <typename T>
    std::size_t var::data_type<T>::_hash() const {
        return _hash_(_data);
    }

    template <typename T>
    Text var::data_type<T>::_type() const {
        return _type_(_data);
    }

    template <typename T>
    Text var::data_type<T>::_cat() const {
        return _cat_(_data);
    }

    template <typename T>
    bool var::data_type<T>::_is() const {
        return _is_(_data);
    }

    template <typename T>
    void var::data_type<T>::_str(Text_Stream& out) const {
        _str_(out, _data);
    }

    template <typename T>
    void var::data_type<T>::_repr(Text_Stream& out) const {
        _repr_(out, _data);
    }

    template <typename T>
    double var::data_type<T>::_comp(var other) const {
        return _comp_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_b_and(var other) const {
        return _b_and_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_b_or(var other) const {
        return _b_or_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_b_xor(var other) const {
        return _b_xor_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_b_neg() const {
        return _b_neg_(_data);
    }

    template<typename T>
    inline var var::data_type<T>::_u_add() const {
        return _u_add_(_data);
    }

    template<typename T>
    inline var var::data_type<T>::_u_neg() const {
        return _u_neg_(_data);
    }

    template <typename T>
    var var::data_type<T>::_add(var other) const {
        return _add_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_sub(var other) const {
        return _sub_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_mul(var other) const {
        return _mul_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_div(var other) const {
        return _div_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_mod(var other) const {
        return _mod_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_f_div(var other) const {
        return _f_div_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_rem(var other) const {
        return _rem_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_pow(var other) const {
        return _pow_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_root(var other) const {
        return _root_(_data, other);
    }

    template <typename T>
    bool var::data_type<T>::_has(var other) const {
        return _has_(_data, other);
    }

    template <typename T>
    std::size_t var::data_type<T>::_size() const {
        return _size_(_data);
    }

    template <typename T>
    var var::data_type<T>::_lead() const {
        return _lead_(_data);
    }

    template <typename T>
    var var::data_type<T>::_last() const {
        return _last_(_data);
    }

    template <typename T>
    var var::data_type<T>::_join(var other) const {
        return _join_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_link(var other) const {
        return _link_(_data, other);
    }

    template <typename T>
    var var::data_type<T>::_next() const {
        return _next_(_data);
    }

    template <typename T>
    var var::data_type<T>::_prev() const {
        return _prev_(_data);
    }

    template <typename T>
    var var::data_type<T>::_reverse() const {
        return _reverse_(_data);
    }

    template <typename T>
    var var::data_type<T>::_get(var key) const {
        return _get_(_data, key);
    }

    template <typename T>
    var var::data_type<T>::_set(var key, var val) const {
        return _set_(_data, key, val);
    }

    template <typename T>
    var var::data_type<T>::_del(var key) const {
        return _del_(_data, key);
    }

    template <typename T>
    Text var::data_type<T>::_help() const {
        return _help_(_data);
    }

    template <typename T>
    bool var::data_type<T>::_is_nothing() const {
        return _is_nothing_(_data);
    }

    template <typename T>
    OP_CODE var::data_type<T>::_op_code() const {
        return _op_code_(_data);
    }




    /********************************************************************************************/
    //
    //                            Basic Primitive Implementations
    //
    /********************************************************************************************/

    Text str(var a) {
        /*
            Convert a 'var' to its string representation.
        */

        Text_Stream stream;

        stream << std::boolalpha;

        if (a.type() == "format") {
            /*
                The 'format' data type must be printed using
                its string representation, else it would only
                impart its formatting to the stream instead of
                being printed to it.
            */
            a.repr(stream);
        }
        else {
            a.str(stream);
        }

        return stream.str();
    }

    Text repr(var a) {
        /*
            Convert a 'var' to its representation as a string.
        */

        Text_Stream stream;

        stream << std::boolalpha;

        a.repr(stream);

        return stream.str();
    }

    var pop_lead(var& exp) {

        var a = exp.lead();

        exp = exp.next();

        return a;
    }

    var pop_last(var& exp) {

        var a = exp.last();

        exp = exp.prev();

        return a;
    }




    /********************************************************************************************/
    //
    //                                 'node' Class Implementation
    //
    /********************************************************************************************/

    node::node() : _data(), _next() {
    }

    node::node(var object) : _data(object), _next() {
    }

    std::string _type_(const node& self) {
        return "node";
    }

    bool _is_(const node& self) {
        return self._data.is_something();
    }

    double _comp_(const node& self, const var& other) {

        const node* ptr = other.cast<node>();

        if (ptr) {

            var a = self;
            var b = *ptr;

            while (a.is() && b.is()) {

                if (a.lead() != b.lead()) {
                    return NOT_A_NUMBER;
                }

                a = a.next();
                b = b.next();
            }

            if (!a.is() && !b.is()) {
                return 0.0;
            }
        }

        return NOT_A_NUMBER;
    }

    void _str_(Text_Stream& out, const node& self) {

        if (!_is_(self)) {
            return;
        }

        var e(self);

        while (e.is()) {
            e.lead().str(out);

            e = e.next();

            out << " ";
        }
    }

    void _repr_(Text_Stream& out, const node& self) {

        if (!_is_(self)) {
            return;
        }

        var e(self);

        while (e.is()) {
            e.lead().repr(out);

            e = e.next();

            out << " ";
        }
    }

    std::size_t _size_(const node& self) {

        if (!_is_(self)) {
            return 0;
        }

        std::size_t size = 1;

        var next = self._next;

        while (next.is()) {

            size += 1;

            next = next.next();
        }

        return size;
    }

    var _lead_(const node& self) {
        return self._data;
    }

    var _join_(const node& self, const var& other) {

        if (other.is_nothing()) {
            return self;
        }

        node a(other);

        if (_is_(self)) {

            a._next = self;
        }

        return a;
    }

    var _next_(const node& self) {

        if (self._next.is_nothing()) {
            return node();
        }

        return self._next;
    }

    var _reverse_(const node& self) {

        if (self._next.is_nothing()) {
            return self;
        }

        var a = node();

        var next = self;

        while (next.is()) {

            a = a.join(next.lead());

            next = next.next();
        }

        return a;
    }




    /********************************************************************************************/
    //
    //                                 'term' Class Implementation
    //
    /********************************************************************************************/

    term::term() : _term(node()), _size(0) {
    }

    term::term(var x) : _term(node(x)), _size(_term.size()) {
    }

    std::string _type_(const term& self) {
        return "term";
    }

    bool _is_(const term& self) {
        return self._size;
    }

    double _comp_(const term& self, const var& other) {

        const term* ptr = other.cast<term>();

        if (ptr) {

            if (self._size == ptr->_size) {

                return self._term.comp(ptr->_term);
            }
        }

        return NOT_A_NUMBER;
    }

    void _str_(Text_Stream& out, const term& self) {

        out << "(";

        if (self._term.is()) {

            self._term.str(out);
            out.seekp(-1, out.cur);
        }

        out << ")";
    }

    void _repr_(Text_Stream& out, const term& self) {

        out << "(";

        if (self._term.is()) {

            self._term.repr(out);
            out.seekp(-1, out.cur);
        }

        out << ")";
    }

    std::size_t _size_(const term& self) {
        return self._size;
    }

    var _lead_(const term& self) {
        return self._term.lead();
    }

    var _join_(const term& self, const var& other) {

        if (other.is_nothing()) {
            return self;
        }

        term a{ self };

        a._term = a._term.join(other);
        a._size += 1;

        return a;
    }

    var _next_(const term& self) {

        if (!_is_(self)) {
            return term();
        }

        term a{ self };

        a._term = a._term.next();
        a._size -= 1;

        return a;
    }

    var _reverse_(const term& self) {

        if (self._term.is_nothing()) {
            return self;
        }

        term a;

        a._term = self._term.reverse();
        a._size = self._size;

        return a;
    }




    /********************************************************************************************/
    //
    //                                 'expression' Class Implementation
    //
    /********************************************************************************************/

    expression::expression() : _lead(term()), _last(term()) {
    }

    expression::expression(var x) : _lead(term()), _last(term(x)) {
    }

    template<typename T, typename... Args>
    expression::expression(T x, Args... args) : _lead(term()), _last(term()) {

        link(x);
        link(args...);
    }

    expression::~expression() {
    }

    std::string _type_(const expression& self) {
        return "expression";
    }

    bool _is_(const expression& self) {
        return self._lead.size() || self._last.size();
    }

    double _comp_(const expression& self, const var& other) {

        const expression* ptr = other.cast<expression>();

        if (ptr) {

            return self._lead == ptr->_lead && self._last == ptr->_last;
        }

        return NOT_A_NUMBER;
    }

    void _str_(Text_Stream& out, const expression& self) {

        if (!_is_(self)) {
            out << "()";
            return;
        }

        out << "(";

        var e(self._lead);

        while (e.is()) {
            e.lead().str(out);

            e = e.next();

            out << " ";
        }

        e = self._last.reverse();

        while (e.is()) {
            e.lead().str(out);

            e = e.next();

            out << " ";
        }

        out.seekp(-1, out.cur);

        out << ")";
    }

    void _repr_(Text_Stream& out, const expression& self) {

        if (!_is_(self)) {
            out << "()";
            return;
        }

        out << "(";

        var e(self._lead);

        while (e.is()) {
            e.lead().repr(out);

            e = e.next();

            out << " ";
        }

        e = self._last.reverse();

        while (e.is()) {
            e.lead().repr(out);

            e = e.next();

            out << " ";
        }

        out.seekp(-1, out.cur);

        out << ")";
    }

    std::size_t _size_(const expression& self) {
        return self._lead.size() + self._last.size();
    }

    var _lead_(const expression& self) {

        if (self._lead.is()) {
            return self._lead.lead();
        }

        return self._last.reverse().lead();
    }

    var _last_(const expression& self) {

        if (self._last.is()) {
            return self._last.lead();
        }

        return self._lead.reverse().lead();
    }

    var _join_(const expression& self, const var& other) {

        if (other.is_nothing()) {
            return self;
        }

        expression a{ self };

        if (!a._last.is()) {

            a._last = a._last.join(other);
        }
        else {
            a._lead = a._lead.join(other);
        }

        a.balance();

        return a;
    }

    var _link_(const expression& self, const var& other) {

        if (other.is_nothing()) {
            return self;
        }

        expression a{ self };

        if (!a._lead.is()) {

            a._lead = a._lead.join(other);
        }
        else {
            a.link(other);
        }

        return a;
    }

    var _next_(const expression& self) {

        if (!_is_(self)) {
            return expression();
        }

        expression a{ self };

        a.balance();

        if (!a._lead.is()) {

            a._lead = a._lead.join(pop_lead(a._last));
        }

        a._lead = a._lead.next();

        return a;
    }

    var _prev_(const expression& self) {

        if (!_is_(self)) {
            return expression();
        }

        expression a{ self };

        a.balance();

        if (!a._last.is()) {

            a._last = a._last.join(pop_lead(a._lead));
        }

        a._last = a._last.next();

        return a;
    }

    var _reverse_(const expression& self) {

        expression a{ self };

        std::swap(a._lead, a._last);

        return a;
    }

    var _add_(const expression& self, const var& other) {

        const expression* ptr = other.cast<expression>();

        if (ptr) {

            var a{ self };
            var b{ *ptr };

            while (b.is()) {

                a = a.link(pop_lead(b));
            }

            return a;
        }

        return nothing();
    }

    template<typename ...Args>
    void expression::link(const var& other, Args... args) {

        link(other);

        link(args...);
    }

    void expression::link(const var& other) {

        _last = _last.join(other);

        balance();
    }

    void expression::link() {
    }

    void expression::balance() {

        if ((_lead.size() / balance_limit) > _last.size()) {

            balance(_last, _lead);
        }

        else if ((_last.size() / balance_limit) > _lead.size()) {

            balance(_lead, _last);
        }
    }

    void expression::balance(var& a, var& b) {

        std::vector<var> buffer;

        auto limit = (b.size() / balance_limit);

        while (limit--) {

            buffer.push_back(pop_lead(b));
        }

        var t = a.reverse();

        a = b.reverse();
        b = term();

        for (auto i = buffer.crbegin(); i != buffer.crend(); ++i) {

            b = b.join(*i);
        }

        while (t.is()) {
            a = a.join(pop_lead(t));
        }
    }
}
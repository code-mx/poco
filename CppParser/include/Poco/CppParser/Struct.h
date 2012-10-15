//
// Struct.h
//
// $Id: //poco/1.4/CppParser/include/Poco/CppParser/Struct.h#1 $
//
// Library: CppParser
// Package: SymbolTable
// Module:  Struct
//
// Definition of the Struct class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef CppParser_Struct_INCLUDED
#define CppParser_Struct_INCLUDED


#include "Poco/CppParser/CppParser.h"
#include "Poco/CppParser/NameSpace.h"
#include <vector>
#include <set>


namespace Poco {
namespace CppParser {


class Function;


class CppParser_API Struct: public NameSpace
	/// This class represents a struct or class declaration.
{
public:
	enum Flags
	{
		FN_TEMPLATE = 1,
		FN_INLINE   = 2, // when the whole class is inlined in a c++ file
		FN_TEMPLATE_SPECIALIZATION = 4
	};
	
	struct Base
	{
		Symbol::Access access;
		bool           isVirtual;
		std::string    name;
		Struct*        pClass;
	};
	
	typedef std::vector<Base>           BaseClasses;
	typedef BaseClasses::const_iterator BaseIterator;
	typedef std::vector<Struct*>        StructVec;
	typedef StructVec::const_iterator   DerivedIterator;
	typedef std::vector<Function*>      Functions;
	typedef std::set<Function*>         FunctionSet;
	typedef std::set<Struct*>           StructSet;

	Struct(const std::string& decl, bool isClass, NameSpace* pNameSpace);
		/// Creates the Struct.

	~Struct();
		/// Destroys the Struct.

	void addBase(const std::string&, Symbol::Access access, bool isVirtual);
		/// Adds a base class.
				
	BaseIterator baseBegin() const;
		/// Returns an iterator for iterating over all base classes.
		
	BaseIterator baseEnd() const;
		/// Returns an iterator for iterating over all base classes.
	
	void fixupBases();
		/// Adds pointers for all base classes.

	void addDerived(Struct* pClass);
		/// Adds a derived class.

	DerivedIterator derivedBegin() const;
		/// Returns an iterator for iterating over all derived classes.

	DerivedIterator derivedEnd() const;
		/// Returns an iterator for iterating over all derived classes.

	const std::string& declaration() const;
		/// Returns the declaration.
	
	int flags() const;
		/// Returns the struct's flags.

	void makeInline();
		/// Changes the class to a inline class, i.e. definition and implementation are hidden in a cpp file.

	bool isInline() const;
		/// Returns true if the complete class is inlined in a cpp file.

	void constructors(Functions& functions) const;
		/// Returns all constructors, sorted by their parameter count.
	
	Function* destructor() const;
		/// Returns the destructor, or NULL if no
		/// destructor is defined.

	void methods(Symbol::Access access, Functions& functions) const;
		/// Returns all functions with the given access.
	
	void inheritedMethods(FunctionSet& functions) const;
		/// Returns all inherited methods.
	
	void bases(std::set<std::string>& bases) const;
		/// Returns all base classes.
		
	void derived(StructSet& derived) const;
		/// Returns all derived classes.	
		
	Function* findFunction(const std::string& signature) const;
		/// Finds a function with the given signature.
		
	bool hasVirtualDestructor() const;
		/// Returns true if the class CppParser_API or one if its base classes
		/// has a virtual destructor.

	bool isClass() const;
		/// Returns true iff the struct was declared as class.
		
	bool isDerived() const;
		/// Returns true iff the struct or class is derived from another struct or class.

	Symbol::Kind kind() const;
	std::string toString() const;
	
private:
	std::string _decl;
	BaseClasses _bases;
	StructVec   _derived;
	int         _flags;
	bool        _isClass;
};


//
// inlines
//
inline const std::string& Struct::declaration() const
{
	return _decl;
}


inline int Struct::flags() const
{
	return _flags;
}


inline bool Struct::isClass() const
{
	return _isClass;
}


inline void Struct::makeInline()
{
	_flags |= FN_INLINE;
}


inline bool Struct::isInline() const
{
	return (_flags & FN_INLINE) != 0;
}


inline bool Struct::isDerived() const
{
	return !_bases.empty();
}


} } // namespace Poco::CppParser


#endif // CppParser_Struct_INCLUDED

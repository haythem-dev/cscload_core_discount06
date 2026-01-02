//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      macros for convenience class elements
 *  \author     Bischof Bjoern
 *  \date       08.01.2010
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CLASS_INFO_MACRO_H
#define GUARD_CLASS_INFO_MACRO_H

//-------------------------------------------------------------------------------------------------//
// macro definition section
//-------------------------------------------------------------------------------------------------//
#define CLASSNAME_DECL						   static const basar::ConstString CLASSNAME;
#define CLASSNAME_DEF( CLASS )	               const basar::ConstString CLASS::CLASSNAME = #CLASS;
#define METHODNAME_DEF( CLASS, FUNNAME )       static basar::ConstString fun = #CLASS"::"#FUNNAME"()";	

#endif	// end GUARD_CLASS_INFO_MACRO_H

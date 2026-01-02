#ifndef __MACRO_H__
#define __MACRO_H__ __MACRO_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROJECT KD2ORDER
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define __FUNCTION__(funname) const char* const fun = /* (char*) */#funname;	

// NDEBUG: for debugging
#ifndef NDEBUG
	// VERBOSE-LEVEL
	#if defined VERBOSE
		#define DEBUG_PRINTF(level, msg) if( level <= VERBOSE ){ printf msg ; }
	//#else
	//	#define DEBUG_PRINTF(level, msg)
	#endif
	#define DEBUG_ENTER( fun ) DEBUG_PRINTF( 2, \
                                                 ( "=== ENTER %-40s (%-20s:%5d) ============================\n", fun, __FILE__, __LINE__ ))
	#define DEBUG_LEAVE(fun) DEBUG_PRINTF( 2, \
							( "=== LEAVE %-40s (%-20s:%5d) ============================\n", fun, __FILE__, __LINE__ ))
	#define DEBUG_RETURN(fun, fmt, val) printf( "\tRETURN %s (RC:>"fmt"<)\n", fun, val );	

	//#define PERSISTENCE
	#ifdef PERSISTENCE
		#define PERSIST_PRINTF( fun, loc, m_PersState, msg )	char* sp##loc; \
												switch( m_PersState ){\
													case NKDBsn::NOT_DELETED:	sp##loc = "NOT_DELETED";\
																				break;\
													case NKDBsn::NOT_UPDATED:	sp##loc = "NOT_UPDATED";\
																				break;\
													case NKDBsn::NOT_INSERTED:	sp##loc = "NOT_INSERTED";\
																				break;\
													case NKDBsn::NOT_SELECTED:	sp##loc = "NOT_SELECTED";\
																				break;\
													case NKDBsn::STATELESS:		sp##loc = "STATELESS";\
																				break;\
													case NKDBsn::TO_SELECT:		sp##loc = "TO_SELECT";\
																				break;\
													case NKDBsn::TO_INSERT:		sp##loc = "TO_INSERT";\
																				break;\
													case NKDBsn::TO_UPDATE:		sp##loc = "TO_UPDATE";\
																				break;\
													case NKDBsn::TO_DELETE:		sp##loc = "TO_DELETE";\
																				break;\
													case NKDBsn::SELECTED:		sp##loc = "SELECTED";\
																				break;\
													case NKDBsn::INSERTED:		sp##loc = "INSERTED";\
																				break;\
													case NKDBsn::UPDATED:		sp##loc = "UPDATED";\
																				break;\
													case NKDBsn::DELETED:		sp##loc = "DELETED";\
																				break;\
													default:					sp##loc = "default(err)";\
																				break;\
												} \
												printf( "PersistFun:%s %s: SqlState:>%s<: %s\n", fun, #loc, sp##loc, msg );
		#else
			#define PERSIST_PRINTF(fun, loc, m_PersState, msg)
		#endif
#else 
    #define DEBUG_PRINTF(level, msg)
	//#define __FUNCTION__(funname) 
	#define DEBUG_ENTER( fun )
	#define DEBUG_LEAVE( fun )
	#define DEBUG_RETURN(fun, fmt, val) 
	#define PERSIST_PRINTF(fun, loc, m_PersState, msg)
#endif

#define COUT(msg) cout << left << setw(40) << #msg << ": >" << msg << "<" << endl;
#define COUT_BOOL(msg) cout << boolalpha << left << setw(40) << #msg << ": >" << msg << "<" << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////
//  Declare Macro
/////////////////////////////////////////////////////////////////////////////////////////////////
#define PP_DC_CLASSVERSION(CLASS)                \
public:                                          \
	static const char* const getVersion();       \
private:                                         \
	static const char* const m_spVersion;
// Member 'm_spVersion' should consist of 4 segments:
// --------------------------------------------------------------------
// 1. MAJOR-segment:	conversion / generation
// 2. MINORS-segment:	compatibility: existing interface was changed
// 3. EXTEND-segment:	new Interfaces / feature
// 4. BUILD-segment:	eliminate error / implementation improved

/////////////////////////////////////////////////////////////////////////////////////////////////
// Define Macro
/////////////////////////////////////////////////////////////////////////////////////////////////
#define PP_DF_CLASSVERSION(CLASS)                \
const char* const CLASS::getVersion()            \
{                                                \
	return m_spVersion;                          \
}

#endif /* __MACRO_H__ */

#ifndef GUARD_UTIL_EXCEPTION_HANDLER_H
#define GUARD_UTIL_EXCEPTION_HANDLER_H

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace util
{
    class BaseException;
}

//-------------------------------------------------------------------------------------------------//
// class declaration section
//-------------------------------------------------------------------------------------------------//
namespace util
{
class ExceptionHandler
{
public:
	static void processAccessorException(
		basar::Exception & e, 
		const log4cplus::Logger & logger,
		basar::ConstString functionName, 
		const basar::VarString & executeMethod, 
		basar::ConstString file, 
		basar::Int32 line 
			);

    static void processBasarException( basar::Exception & e,  const log4cplus::Logger& logger, basar::ConstString functionName, basar::ConstString file, const basar::Int32 line );
	static void processReasonException( util::BaseException & e,  const log4cplus::Logger& logger, basar::ConstString functionName, basar::ConstString file, const basar::Int32 line );

	~ExceptionHandler();

private:
	ExceptionHandler();
};

} // end namespace util

#endif // GUARD_UTIL_EXCEPTION_HANDLER_H

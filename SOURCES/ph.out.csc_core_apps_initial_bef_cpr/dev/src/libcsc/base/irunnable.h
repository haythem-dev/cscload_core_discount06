#ifndef GUARD_LIBCSC_BASE_IRUNNABLE_H
#define GUARD_LIBCSC_BASE_IRUNNABLE_H

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace libcsc {
namespace base {
	class IRunnable
	{        
	public:
		virtual ~IRunnable(){};
		virtual void run() = 0;
	};
} // namespace base
} // namespace libcsc

#endif // GUARD_LIBCSC_BASE_IRUNNABLE_H
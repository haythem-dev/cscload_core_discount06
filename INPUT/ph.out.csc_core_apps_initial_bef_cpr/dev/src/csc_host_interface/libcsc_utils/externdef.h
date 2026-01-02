#ifndef GUARD_LIBCSC_UTILS_CSC_SIGNALHANDLER_H32
#define GUARD_LIBCSC_UTILS_CSC_SIGNALHANDLER_H32

extern "C"
{
  void handleSIG(int sig)
  {
      libcsc_utils::SignalHandlerBase::handleSignals(sig);
  }

}

#endif


using Csc.Base;
using System;
using System.Diagnostics;
using Thrift;
using Thrift.Protocol;
using Thrift.Transport;

namespace Phoenix
{
    public class CscServiceClient : IDisposable
    {
        private CscServiceConfig _cscServiceConfig;
        private TSocket _transport;
        private bool _sessionEstablished;

        private Stopwatch _StopWatch = new Stopwatch();

        public long _DurationDispose = 0;
        public long _DurationTransportOpen = 0;
        public long _DurationOpenSession = 0;
        public long _DurationCloseSession = 0;
        public long _DurationTransportClose = 0;


        private void startStopWatch()
        {
            _StopWatch.Reset();
            _StopWatch.Start();
        }

        private long stopStopWatchAndGetDuration()
        {
            _StopWatch.Stop();
            return _StopWatch.ElapsedMilliseconds;
        }


        public void Dispose()
        {
            try
            {
                startStopWatch();
                    Instance.Dispose();
                    _transport.Dispose();
                _DurationDispose = stopStopWatchAndGetDuration();
            }
            catch{}
        }

        public Csc.Service.CscServiceBatch.Client Instance { get; private set; }

        public CscServiceClient(CscServiceConfig config)
        {
            _cscServiceConfig = config;
            _sessionEstablished = false;
        }

        ~CscServiceClient()
        {
            try
            {
                Close();
                Dispose();
            }
            catch { }
        }

        public void Open(int timeout)
        {
            if (Instance != null)
            {
                return;
            }

            try
            {

                startStopWatch();

                    _transport = new TSocket(_cscServiceConfig.Server, _cscServiceConfig.Port, timeout);
                    var protocol = new TBinaryProtocol(_transport);
                    Instance = new Csc.Service.CscServiceBatch.Client(protocol);
                    _transport.Open();

                _DurationTransportOpen = stopStopWatchAndGetDuration();
            }
            catch (TApplicationException)
            {
                throw;
            }
            catch (Exception)
            {
                throw;
            }
        }

        public void OpenAndConnect(int timeout = 2000)
        {
            Open(timeout);
            var request = new Csc.Base.SessionRequest { Uid = _cscServiceConfig.UId, DeviceName = _cscServiceConfig.DeviceName };
            Csc.Base.SessionResponse response;

            try
            {
                startStopWatch();

                    response = Instance.openSession(request);
                    _transport.Timeout = 0;

                _DurationOpenSession = stopStopWatchAndGetDuration();
            }
            catch (TApplicationException)
            {
                throw;
            }
            catch (Exception)
            {
                throw;
            }
            if (isError(response.RetValue))
            {
                throw new CscServiceClientException("Connection error");
            }
            _sessionEstablished = true;
        }

        public void Close()
        {
            if (_sessionEstablished)
            {
                disconnect();
            }
            if ((_transport != null) && _transport.IsOpen)
            {
                try
                {
                    startStopWatch();
                        _transport.Close();
                    _DurationTransportClose = stopStopWatchAndGetDuration();

                    _transport = null;
                    Instance = null;


                }
                catch (Exception)
                {
                    throw;
                }
            }
        }

        private void disconnect()
        {
            Csc.Base.SessionResponse response;
            try
            {
                startStopWatch();
                    response = Instance.closeSession();
                _DurationCloseSession = stopStopWatchAndGetDuration();
            }
            catch (TApplicationException)
            {
                throw;
            }
            catch (Exception)
            {
                throw;
            }
            if (isError(response.RetValue))
            {
                //logger.Warn("disconnect(): CSCService disconnection error: {0} {1}", response.RetValue.ErrorCode, response.RetValue.ErrorMessage);
            }
            _sessionEstablished = false;
        }

        private bool isError(ReturnStruct retValue)
        {
            return ((retValue != null) && retValue.ErrorCode.HasValue && (retValue.ErrorCode != 0));
        }
    }
}

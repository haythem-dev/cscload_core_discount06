using System;

namespace Phoenix
{
    public class CscServiceClientException : Exception
    {
        public CscServiceClientException() : base()
        {
        }

        public CscServiceClientException(string message) : base(message)
        {
        }
    }
}

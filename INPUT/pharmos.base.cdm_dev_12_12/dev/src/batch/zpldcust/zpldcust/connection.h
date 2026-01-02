//----------------------------------------------------------------------------
/*! \file   connection.h
 *  \brief  connection class for zpldcust
 *  \author	Frank Naumann
 *  \date   25.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_CONNECTION_H
#define GUARD_CONNECTION_H

//----------------------------------------------------------------------------

namespace zpldcust {

//---------------------------------------------------------------------------

/*! \brief connection-class.
 *  \throw BasarExceptions
 */
class Connection
{

public:	
  /*! \brief std-constructor.
   *  \throw no-throw
   */
  Connection();

  /*! \brief std-destructor.
   *  \throw no-throw
   */
  virtual ~Connection();

  /*! \brief start connecting.
   *  \throw no-throw
   */
  void connect();

  /*! \brief disconnect open connection.
   *  \throw no-throw
   */
  void disconnect();

  /*! \brief get the current informix connection.
   *  \return Reference to current informix connection; used to create an instance of an accessor definition
   *  \throw no-throw
   */
  const ConnectionRef getInfxConnection() const;

	/*! \brief get the current cics connection.
   *  \return Reference to current cics connection; used to create an instance of an accessor definition.
   *  \throw no-throw
   */
  const ConnectionRef getCicsConnection() const;

private:
  /*! \brief copy constructor.
   *  \param r the connection to copy.
   *  \throw no-throw
   */
  Connection(const Connection& r);

  /*! \brief assign operator.
   *  \param r the connection to assign.
   *  \throw no-throw
   */
  Connection& operator=(const Connection& r);

  ConnectionRef::DatabaseInfo m_DbInfoInfx; //!< info to infx connection
  ConnectionRef               m_InfxConn;   //!< reference to infx connection

  ConnectionRef::DatabaseInfo m_DbInfoCics; //!< info to cics connection
  ConnectionRef               m_CicsConn;   //!< reference to cics connection

  /*! \brief set connection infos to m_DbInfoInfx.
   *  \throw no-throw
   */
  void setInfxDbInfo();

  /*! \brief set connection infos to m_DbInfoCics.
   *  \throw no-throw
   */
  void setCicsDbInfo();
};

//----------------------------------------------------------------------------

} // namespace zpldcust

//----------------------------------------------------------------------------

#endif // GUARD_CONNECTION_H

//----------------------------------------------------------------------------

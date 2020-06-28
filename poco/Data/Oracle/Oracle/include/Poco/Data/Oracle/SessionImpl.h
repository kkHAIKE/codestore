#pragma once

#include "Poco/Data/Oracle/Oracle.h"
#include <Poco/Data/AbstractSessionImpl.h>

namespace Poco {
namespace Data {
namespace Oracle {

class Oracle_API SessionImpl :
	public Poco::Data::AbstractSessionImpl<SessionImpl>
{
public:
	explicit SessionImpl(const std::string& connectionString);
	virtual ~SessionImpl(void);

	virtual Poco::Data::StatementImpl* createStatementImpl();
	/// Returns an SQLite StatementImpl

	virtual void begin();
	/// Starts a transaction

	virtual void commit();
	/// Commits and ends a transaction

	virtual void rollback();

	/// Aborts a transaction
	virtual void close();
	/// Closes the connection.

	virtual bool isConnected();
	/// Returns true iff session is connected, false otherwise.

	virtual bool isTransaction();
	//是否在事务中
	/// Returns true iff a transaction is a transaction is in progress, false otherwise.

	void autoCommit(const std::string&, bool val);
	/// Sets autocommit property for the session.

	bool isAutoCommit(const std::string& name="");
	/// Returns autocommit property value.

protected:
	OCI_Connection *_conn;
	int _inTransaction;
	bool _isAutoCommit;
};

}}}
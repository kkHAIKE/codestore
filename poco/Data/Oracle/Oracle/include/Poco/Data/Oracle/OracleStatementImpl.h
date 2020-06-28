#pragma once

#include "Poco/Data/Oracle/Oracle.h"
#include "Poco/Data/Oracle/Binder.h"
#include "Poco/Data/Oracle/Extractor.h"
#include "Poco/Data/Oracle/OracleColumn.h"
#include <Poco/Data/StatementImpl.h>

namespace Poco {
namespace Data {
namespace Oracle {

class Oracle_API OracleStatementImpl :
	public Poco::Data::StatementImpl
{
public:
	explicit OracleStatementImpl(OCI_Connection *conn,bool &isAutoCommit);
	virtual ~OracleStatementImpl(void);

protected:
	virtual Poco::UInt32 columnsReturned() const;
	/// Returns number of columns returned by query.		

	virtual const MetaColumn& metaColumn(Poco::UInt32 pos) const;
	/// Returns column meta data.

	virtual bool hasNext();
	/// Returns true if a call to next() will return data.

	virtual void next();
	/// Retrieves the next row from the resultset.
	/// Will throw, if the resultset is empty.

	virtual bool canBind() const;
	/// Returns true if a valid statement is set and we can bind.

	virtual void compileImpl();
	/// Compiles the statement, doesn't bind yet

	virtual void bindImpl();
	/// Binds parameters

	virtual AbstractExtractor& extractor();
	/// Returns the concrete extractor used by the statement.

	virtual AbstractBinder& binder();
	/// Returns the concrete binder used by the statement.
protected:
	enum
	{
		NEXT_DONTKNOW,
		NEXT_TRUE,
		NEXT_FALSE
	};

	SharedPtr<Binder> _binder;
	SharedPtr<Extractor> _extractor;

	OCI_Statement *_stmt;
	int _hasNext;
	std::vector<SharedPtr<OracleColumn>> _meta;
	bool& _isAutoCommit;
};

}}}
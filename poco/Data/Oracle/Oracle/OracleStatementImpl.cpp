#include "Poco/Data/Oracle/OracleStatementImpl.h"
#include "Poco/Data/Oracle/OracleException.h"

#include <ocilib.h>

namespace Poco {
namespace Data {
namespace Oracle {

OracleStatementImpl::OracleStatementImpl(OCI_Connection *conn,bool &isAutoCommit):
_stmt(NULL),_hasNext(NEXT_DONTKNOW),_isAutoCommit(isAutoCommit)
{
	_stmt=OCI_StatementCreate(conn);

	OCI_SetBindMode(_stmt,OCI_BIND_BY_POS);
	OCI_AllowRebinding(_stmt,true);
}

OracleStatementImpl::~OracleStatementImpl(void)
{
	OCI_StatementFree(_stmt);
}

Poco::UInt32 OracleStatementImpl::columnsReturned() const
{
	return _meta.size();
}

const MetaColumn& OracleStatementImpl::metaColumn(Poco::UInt32 pos) const
{
	poco_assert(pos>=0 && pos<_meta.size());

	return *_meta[pos];
}

bool OracleStatementImpl::hasNext()
{
	if (_hasNext == NEXT_DONTKNOW)
	{
		if (_meta.size() == 0)
		{
			return false;
		}
		if(OCI_GetStatementType(_stmt)!=OCI_CST_SELECT)
		{
			return false;
		}
		OCI_Resultset *res=OCI_GetResultset(_stmt);
		poco_assert(res);
		
		if (OCI_FetchNext(res))
		{
			_hasNext = NEXT_TRUE;
			return true;
		}

		_hasNext = NEXT_FALSE;
		return false;
	}
	else if (_hasNext == NEXT_TRUE)
	{
		return true;
	}

	return false;
}

void OracleStatementImpl::next()
{
	if(hasNext())
	{
		std::size_t pos = 0;

		Poco::Data::AbstractExtractionVec::iterator it = extractions().begin();
		Poco::Data::AbstractExtractionVec::iterator itEnd = extractions().end();	
		for (; it != itEnd; ++it)
		{
			(*it)->extract(pos);
			pos += (*it)->numOfColumnsHandled();
		}

		_hasNext = NEXT_DONTKNOW;
	}
}

bool OracleStatementImpl::canBind() const
{
	if (!bindings().empty())
		return (*bindings().begin())->canBind();

	return false;
}

void OracleStatementImpl::compileImpl()
{
	_meta.clear();

	std::string sql=toString();
	int c=1;
	size_t fnd=0;
	while(fnd=sql.find('?'),fnd!=std::string::npos)
	{
		sql.replace(fnd,1,format(":%d",c++));
	}

	OCI_Describe(_stmt,sql.c_str());
	
	if(OCI_GetStatementType(_stmt)==OCI_CST_SELECT)
	{
		OCI_Resultset *res=OCI_GetResultset(_stmt);
		poco_assert(res);

		DWORD n=OCI_GetColumnCount(res);
		for(int i=0;i<n;++i)
		{
			_meta.push_back(SharedPtr<OracleColumn>(new OracleColumn(res,i)));
		}
	}

	_binder=new Binder(_stmt);
	_extractor=new Extractor(_stmt,_meta);
}

void OracleStatementImpl::bindImpl()
{
	Poco::Data::AbstractBindingVec& binds = bindings();
	if (!binds.empty())
	{
		std::size_t pos = 0;

		Poco::Data::AbstractBindingVec::iterator it    = binds.begin();
		Poco::Data::AbstractBindingVec::iterator itEnd = binds.end();
		for (; it != itEnd && (*it)->canBind(); ++it)
		{
			(*it)->bind(pos);
			pos += (*it)->numOfColumnsHandled();
		}
	}
	
	OCI_Execute(_stmt);

	std::vector<SharedPtr<COCILong>>& longs=_binder->GetBindLong();
	if(!longs.empty())
	{
		std::vector<SharedPtr<COCILong>>::iterator it=_binder->GetBindLong().begin();
		std::vector<SharedPtr<COCILong>>::iterator itEnd=_binder->GetBindLong().end();

		for (; it != itEnd; ++it)
		{
			(*it)->write();
		}
		longs.clear();
	}
	
	if(OCI_GetStatementType(_stmt)!=OCI_CST_SELECT && _isAutoCommit)
		OCI_Commit(OCI_StatementGetConnection(_stmt));
}

AbstractExtractor& OracleStatementImpl::extractor()
{
	return *_extractor;
}

AbstractBinder& OracleStatementImpl::binder()
{
	return *_binder;
}

}}}
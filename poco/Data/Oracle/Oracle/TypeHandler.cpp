#include "Poco\Data\Oracle\TypeHandler.h"
#include "Poco\Data\Oracle\Binder.h"


namespace Poco{
namespace Data{

// namespace Oracle{
// 	OracleBindHelpper::OracleBindHelpper(OracleBindHelpperType type,void* data)
// }

std::size_t TypeHandler<Oracle::OracleBindHelpper>::size()
{
	return 1;
}

void TypeHandler<Oracle::OracleBindHelpper>::bind(std::size_t pos, const Oracle::OracleBindHelpper& obj, AbstractBinder* pBinder)
{
	poco_assert_dbg (pBinder != 0);

	dynamic_cast<Oracle::Binder*>(pBinder)->bind(pos,obj);
}

void TypeHandler<Oracle::OracleBindHelpper>::prepare(std::size_t pos, const Oracle::OracleBindHelpper& obj, AbstractPreparation* pPrepare){}

void TypeHandler<Oracle::OracleBindHelpper>::extract(std::size_t pos, Oracle::OracleBindHelpper& obj, const Oracle::OracleBindHelpper& defVal, AbstractExtractor* pExt){}
}}
#pragma once

#include "Poco/Data/Oracle/Oracle.h"
#include <Poco\Data\TypeHandler.h>

namespace Poco{
namespace Data{

namespace Oracle{
typedef enum _OracleBindHelpperType{
	ORACLE_BLONG,//0
	ORACLE_CLONG,//1

	ORACLE_BLOB,//2
	ORACLE_CLOB,//3
	ORACLE_NCLOB,//4

	ORACLE_INTERVAL_YM,//5
	ORACLE_INTERVAL_DS//6
}OracleBindHelpperType;

class OracleBindHelpper
{
public:
	OracleBindHelpper(OracleBindHelpperType type,void* data):_type(type),_data(data){}

	OracleBindHelpperType _type;
	void*	_data;
};
}

class AbstractBinder;
class AbstractPreparation;
class AbstractExtractor;

template <>
class Oracle_API TypeHandler<class Oracle::OracleBindHelpper>
{
public:
    static std::size_t size();

    static void bind(std::size_t pos, const Oracle::OracleBindHelpper& obj, AbstractBinder* pBinder);

    static void prepare(std::size_t pos, const Oracle::OracleBindHelpper& obj, AbstractPreparation* pPrepare);

    static void extract(std::size_t pos, Oracle::OracleBindHelpper& obj, const Oracle::OracleBindHelpper& defVal, AbstractExtractor* pExt);
};

}}
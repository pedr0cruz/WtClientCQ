// ResultSetModel.cpp
// Representa el Modelo en el MVC del ResultSet
// Se conecta con el CQ y contruye la tabla de elementos JSON del RS

#include <boost/algorithm/string/replace.hpp>

#include "ResultSetModel.h"
#include "CQJSON.h"

// Constructor
ResultSetModel::ResultSetModel(WObject* parent) : WStandardItemModel(parent)
{
#ifdef MyDEBUG
	cqSession = CQJSONdummy::getInstance();
#else
	cqSession = CQJSON::getInstance();
#endif
	cqSession->UserLogon("admin", "", "SAMPL", "SAMPLCNX");
}

// Llena el WorkSpace desde el CQ
bool ResultSetModel::fillModel(string QueryName)
{
	Json::Object JsonObject, JsonCQ, JsonQuery, JsonColumn, JsonRow, result;

	if (!cqSession->IsConnected()) return FALSE;

	WString JsonRequest = JS({ "clearquest": { "db": "SAMPL", "repo" : "SAMPLCNX", "login" : "admin", "query" : { "name": "{1}" }} });
	string JsonQueryResult = cqSession->JSONExecuteQuery(JsonRequest.arg(QueryName).toUTF8());
	Json::parse(JsonQueryResult, result);

	JsonCQ = result.get("clearquest");
	string status = JsonCQ.get("status");
	if (status != "ok") return FALSE;
	JsonQuery = JsonCQ.get("query");
	Json::Array JsonColumns = JsonQuery.get("columns");
	Json::Array JsonRows = JsonQuery.get("rows");
	int numColumns = JsonQuery.get("numcolumns").toNumber();
	int numRows = JsonQuery.get("numrows").toNumber();

	// Llenamos las cabeceras
	invisibleRootItem()->setRowCount(0);
	invisibleRootItem()->setColumnCount(0);
	insertColumns(0, numColumns);
	for (int col = 0; col < numColumns; col++){
		JsonColumn = JsonColumns[col];
		WString colname = JsonColumn.get("name");
		setHeaderData(col, colname.toUTF8()); // Para WViewTable
		wTableHeader.push_back( colname.toUTF8() ); // Para WTable
	}
	// Llenamos las filas y columnas
	insertRows(0, numRows);
	wTableData.resize(numRows); // Para WTable
	for (int row = 0; row < numRows; row++){
		JsonRow = JsonRows[row];
		wTableData[row].resize(numColumns); // Para WTable
		//fileModel_->insertRows(fileModel_->rowCount(), row + 1 - fileModel_->rowCount());
		for (unsigned col = 0; col < numColumns; col++){
			Json::Object JsonColumn = JsonColumns[col];
			WString colname = JsonColumn.get("name");
			boost::any data(Wt::WString::fromUTF8(JsonRow.get(colname.toUTF8())));
			setData(row, col, data);
			WString coltype = JsonColumn.get("type");
			wTableData[row][col] = JsonRow.get(colname.toUTF8()); // Para WTable
		}
	}
}
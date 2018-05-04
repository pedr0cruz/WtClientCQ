/// CQJSON.cpp: Clase de integración con ClearQuest con protocolo JSON (JavaScript Object Notation)
/// TO-DO
/// Hacer metodos para utilizar la variable "entity" (SetFieldValue, etc.)

#include "stdafx.h"

#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>
#include <iostream>
#include <vector>
#include <algorithm>    ///< std::find
#include <sstream>
#include "CQJSON.h"

using namespace std;
using namespace _com_util;
using namespace Wt;

// #define MyDEBUG

CQJSON *CQJSON::instance = 0;	///< Se comporta como un singleton (GoF)

void _main_()
{
	CQJSON cqSession;
	cqSession.UserLogon("admin", "", "SAMPL", "SAMPLCNX");
//	cout << cqSession.JSONUserLogon(JS({ "clearquest":{ "db":"SAMPL", "repo":"SAMPLCNX", "login":"admin", "password":""} })) << endl;
	cout << "Conectado = " << cqSession.IsConnected() << endl;

//	cout << cqSession.GetEntity("Defect", "SAMPL00000001");
//	cout << cqSession.JSONGetEntity(JS({ "clearquest":{ "type":"Defect", "id":"SAMPL00000001"}})) << endl;

//	cout << cqSession.GetFieldValue("headline") << endl;
//	cout << cqSession.JSONGetFieldStringValues(JS({ "clearquest":{ "type":"Defect", "id":"SAMPL00000001", "fields":[ "headline", "priority" ]}})) << endl;

	/* Ejecuta un query 
	cqSession.ExecuteQuery("Public Queries/All Defects");
	cout << cqSession.JSONExecuteQuery(JS({ "clearquest": { "db": "SAMPL", "repo" : "SAMPLCNX", "login" : "admin",
		"query" : { "name": "Public Queries/All Defects" }} }));
	*/
	/* Query con parametros 
	cout << cqSession.JSONExecuteQuery(JS({ "clearquest": { "db": "SAMPL", "repo" : "SAMPLCNX", "login" : "admin",
		"query" : { "name": "Public Queries/Keyword Search",
				"params" : [{"value1": "cancel", "operator" : "LIKE"},{ "value1":"user", "operator":"LIKE"}] }}}));
	*/
	/* Elementos del Workspace
	cqSession.GetAllWorkspaceList();
	cout << cqSession.JSONGetAllWorkspaceList(JS({ "clearquest": { "db": "SAMPL", "repo" : "SAMPLCNX", "login" : "admin" } }));
	*/
	cout << cqSession.JSONGetAllFolderList(JS({ "clearquest": { "db": "SAMPL", "repo" : "SAMPLCNX", "login" : "admin" } }));

	//Ejemplo JSON
	/*string jsonStr =
	"{"
	"  \"first\" : 1,"
	"  \"second\" : true,"
	"  \"third\" : null,"
	"  \"fourth\" : false,"
	"  \"fifth\" : 1.25,"
	"  \"sixth\" : 2.418980221897202e90,"
	"  \"seventh\" : 2.713877091499598e75,"
	"  \"eight\" : \"a string type value\","
	"  \"ninth\" : {"
	"    \"sub-first\" : 1,"
	"    \"sub-second\" : 2"
	"  },"
	"  \"tenth\" : ["
	"    true,"
	"    false,"
	"    null,"
	"    666"
	"  ]"
	"}";

	Json::Object result;
	Json::parse(jsonStr, result);
	cerr << "Size: " << result.size() << endl; // Size: 10

	int first = result.get("first");
	cerr << "Int: " << first << endl;

	bool second = result.get("second");
	cerr << "Bool: " << second << endl;

	Json::Value third = result.get("third");
	cerr << "Es NULL: " << third.isNull() << endl;

	bool fourth = result.get("fourth");
	cerr << "Bool: " << fourth << endl;

	double fifth = result.get("fifth");
	cerr << "Double: " << fifth << endl;

	double sixth = result.get("sixth");
	cerr << "Double: " << sixth << endl;

	double seventh = result.get("seventh");
	cerr << "Double: " << seventh << endl;

	WString eight = result.get("eight");
	cerr << "String: " << eight << endl;

	Json::Object ninth = result.get("ninth");
	cerr << "Objeto: {" << WString(ninth.get("sub-first").toString()) << ", " << WString(ninth.get("sub-second").toString()) << "}" << endl;

	Json::Array tenth = result.get("tenth");
	cerr << "Array: [0]=" << bool(tenth[0].toBool()) << ", [1]= " << bool(tenth[1].toBool()) << ", [3]= " << int(tenth[3].toNumber()) << endl;

	return "";
	*/

	system("PAUSE");
}

/// Constructor
CQJSON::CQJSON()
{
    /// La clase utiliza COM, es necesario inicializar las bibliotecas COM
	CoInitialize(0); // Debe estar en el constructor de la clase
/*
	// Conexion a la session de ClearQuest
	IOAdSessionPtr session;
	session.CreateInstance("ClearQuest.Session");
	try {
		session->UserLogon(_bstr_t("admin"),
			_bstr_t(""),
			_bstr_t("SAMPL"),
			_variant_t(1), // shared session
			_bstr_t("SAMPLCNX"));
	}
	catch (...) { //_com_err &e) {
		cout << "UserLogon() error:" << endl;
		return;
	}

	// Obtener el primer elemento de tipo Defect
	IOAdEntityPtr entity;
	_variant_t fieldnames;
	//	BSTR element;
	SAFEARRAY* pSafeArray = NULL;
	_variant_t * raw; // Puntero directo a la data de un SafeArray
	_bstr_t wrapper;  // Para obtener un btr de un variant
	try {
		entity = session->GetEntity(_bstr_t("Defect"), _bstr_t("SAMPL00000001"));

		// Obtener los campos de la Entidad
		fieldnames = entity->GetFieldNames();
		pSafeArray = V_ARRAY(&fieldnames);
		// Accede directamente a la memoria del SafeArray el cual contiene un arreglo de variant donde cada uno es un bstr
		HRESULT hr = SafeArrayAccessData(pSafeArray, (void **)&raw);
		// Iterar la lista de campos si se accedio correctamente a los datos
		if (SUCCEEDED(hr)) {
			long lowerBound, upperBound;  // get array bounds
			SafeArrayGetLBound(pSafeArray, 1, &lowerBound); // Desde
			SafeArrayGetUBound(pSafeArray, 1, &upperBound); // Hasta

			long cnt_elements = upperBound - lowerBound + 1; // Cantidad de elementos
			for (int i = 0; i < cnt_elements; ++i) {  // iterate through returned values
				const _bstr_t wrapper(raw[i]);
				cout << "element " << i << ": value = " << wrapper << endl;
			}
			SafeArrayUnaccessData(pSafeArray);
		}
		SafeArrayDestroy(pSafeArray);
	}
	catch (...){
		cout << "Error in Entity";
		return;
	}

*/
	// CoUninitialize(); // Debe estar en el destructor de la clase
}

/// Destructor
CQJSON::~CQJSON()
{
    ///  Libera los recursos usados por el sistema COM
    CoUninitialize();
}
 
/// Patrón Singleton: Devuelve siempre la misma instancia cuando se contruye
CQJSON *CQJSON::getInstance()
{
	if (! instance)	{
		instance = new CQJSON();
	}
	return instance;
}

/// UserLogon : Conexion al ClearQuest
/// @param login_name
/// @param password
/// @param database_name
/// @param database_set
bool CQJSON::UserLogon(const char* login_name, const char* password, const char* database_name, const char* database_set)
{
	// Conexion a la session de ClearQuest
	session.CreateInstance("ClearQuest.Session");
	try {
		session->UserLogon(_bstr_t(login_name),
			_bstr_t(password),
			_bstr_t(database_name),
			_variant_t(2), // not shared session
			_bstr_t(database_set));
		bConectado = true;
	}
	catch (...) { //_com_err &e) {
		session = NULL;
		bConectado = false;
	}
	return bConectado;
}

/* JSONUserLogon: Realiza el logueo al Clearquest y actualiza la variable "bConnected"
<!--CQ / JSON ENTER-->
{ "clearquest":{ "db":"SAMPL", "repo":"SAMPLCNX", "login":"admin", "password":""} }
<!--CQ / JSON RETURNS-->
{ "clearquest":{ "status":"ok", "description":"Conexion exitosa" }}
{ "clearquest":{ "status":"error", "description":"Error..." }}
*/
string CQJSON::JSONUserLogon(const char* JSON_connection)
{
	Json::Object conexion, result;
	try {
		Json::parse(JSON_connection, result);
        // Valida que se ha enviado un comando de CQ
		if ( !result.contains("clearquest") )
			return jsonError("Error en el objeto de entrada");
	}
	catch (Json::ParseError& e) {
		string error = e.what();
		return jsonError(error);
	}
	// Obtener los elementos de la conexion
	conexion = result.get("clearquest");
	string cLogin			= conexion.get("login").toString().orIfNull("");
	string cPassword		= conexion.get("password").toString().orIfNull("");
	string cRepo			= conexion.get("repo").toString().orIfNull("");
	string cDb				= conexion.get("db").toString().orIfNull("");
#ifdef MyDEBUG
	cerr << "Login = " << cLogin << ", Pass = " << cPassword << ", Repo = " << cRepo << ", Db = " << cDb << endl;
#endif
	// Valida que tenga todos los datos
	if (cLogin.empty() || cRepo.empty() || cDb.empty() )
		return jsonError("Error en el objeto de entrada");
	// Intenta la conexion
	if (!UserLogon(cLogin.c_str(), cPassword.c_str(), cDb.c_str(), cRepo.c_str()))
		return jsonError("Error de conexión con los datos ingresados");
	// Conexion exitosa
	bConectado = true;
	return jsonOK("Conexion exitosa");
}

/// GetEntity: Carga en variable entity un registro
/// @param record_type
/// @param display_name
bool CQJSON::GetEntity(const char* record_type, const char *display_name)
{
    if (!session) {
        return false;
    }
	try {
		entity = session->GetEntity(_bstr_t(record_type), _bstr_t(display_name));
	}
	catch (...){ 
		entity = NULL;
		return false;
	}
    return true;
}

/* JSONGetEntity: Lee y guarda en "entity" un registro
<!--CQ / JSON ENTER-->
{ "clearquest":{ "type":"Defect", "id":"SAMPL00000001"}}
<!--CQ / JSON RETURNS-->
{ "clearquest":{ "status":"ok", "description":"Carga exitosa" }}
{ "clearquest":{ "status":"error", "description":"Error..." }}
*/
string CQJSON::JSONGetEntity(const char* JSON_entity)
{
	Json::Object conexion, result;
	// Valida que se ha enviado un comando de CQ
	try {
		Json::parse(JSON_entity, result);
		if (!result.contains("clearquest")) return jsonError("Error en el objeto de entrada");
	}
	catch (Json::ParseError& e) {
		return jsonError(e.what());
	}
	// Obtener los elementos de la conexion
	conexion = result.get("clearquest");
	string record_type = conexion.get("type").toString().orIfNull("");
	string record_id = conexion.get("id").toString().orIfNull("");
	if( record_type.empty() || record_id.empty() )
		return jsonError("Error en el objeto de entrada");
#ifdef MyDEBUG
	//	printf("record_type = %s, record_id = %s, Repo = %s, Db = %s\n", record_type, record_id);
#endif
	if( !GetEntity(record_type.c_str(), record_id.c_str()) )
		return jsonError("No se obtuvo el elemento");
	// Conexion exitosa
	return jsonOK("Carga exitosa");
}

/// GetFieldNames: Carga en memoria los nombres de todos los campos de la entidad actual
bool CQJSON::GetFieldNames()
{
	_variant_t fieldnames;
    SAFEARRAY* pSafeArray = nullptr;
	_variant_t* raw = nullptr; // Puntero directo a la data de un SafeArray
	_bstr_t wrapper;  // Para obtener un btr de un variant

	// Obtener los campos de la Entidad
	fieldnames = entity->GetFieldNames();
	pSafeArray = V_ARRAY(&fieldnames);
	// Accede directamente a la memoria del SafeArray el cual contiene un arreglo de variant donde cada uno es un bstr
	HRESULT hr = SafeArrayAccessData(pSafeArray, (void **)&raw);
	// Iterar la lista de campos si se accedio correctamente a los datos
	if (SUCCEEDED(hr)) {
		long lowerBound, upperBound;  // get array bounds
		SafeArrayGetLBound(pSafeArray, 1, &lowerBound); // Desde
		SafeArrayGetUBound(pSafeArray, 1, &upperBound); // Hasta

		long cnt_elements = upperBound - lowerBound + 1; // Cantidad de elementos
		string saFields[1];
		for (int i = 0; i < cnt_elements; ++i) {  // iterate through returned values
			const _bstr_t wrapper(raw[i]);
			cout << "element " << i << ": value = " << wrapper << endl;
		}
		SafeArrayUnaccessData(pSafeArray);
	}
	else {
		return false;
	}
	SafeArrayDestroy(pSafeArray);
    return true;
}

/* JSONGetFieldValue
<!--CQ / JSON ENTER-->
{ "clearquest":{ "type":"Defect", "id":"SAMPL00000001", "fields":[ "headline", "priority" ]}}
<!--CQ / JSON RETURNS-->
{ "clearquest": {"type":"Defect", "id" : "SAMPL00000001", "status" : "ok", "descript
ion" : "Conexion exitosa", "count" : 2, "values" : [{"headline":"spelling error"},{"priority":"3-Normal Queue"}] } }
*/
string CQJSON::JSONGetFieldStringValues(const char* JSON_fields)
{
	Json::Object conexion, result;
	WString respuesta;

	// Valida que se ha enviado un comando de CQ
	try {
		Json::parse(JSON_fields, result);
		if (!result.contains("clearquest")) return jsonError("Error en el objeto de entrada");
	}
	catch (Json::ParseError& e) {
		return jsonError(e.what());
	}
	// Obtener los elementos de la conexion
	conexion = result.get("clearquest");
	string record_type = conexion.get("type").toString().orIfNull("");
	string record_id = conexion.get("id").toString().orIfNull("");
	Json::Array record_fields = conexion.get("fields");
	// Valida que se enviaron todos los datos
	if (record_type.empty() || record_id.empty() || record_fields.empty() )
		return jsonError("Error en el objeto de entrada");
	// Intenta la conexion
	if( !GetEntity(record_type.c_str(), record_id.c_str()) )
		return jsonError( "No se pudo obtener el elemento" );
	try{
		// Construye un arreglo JSON de objetos de tipo [{campo:valor},{...}]
		string arFields;
		for (unsigned index = 0; index < record_fields.size();){
#ifdef MyDEBUG
			cerr << "Array: [" << index << "]=" << string(record_fields[index].toString()) << endl;
#endif
			string fieldname = string(record_fields[index].toString());
			arFields += "{\"" + fieldname + "\":\"" + escapeJsonString(GetFieldValue(fieldname.c_str())) + "\"}";
			if( ++index < record_fields.size() ) arFields += ",";  // Evita poner una ultima coma
#ifdef MyDEBUG
			cerr << arFields << endl;
#endif
		}
		// Aqui se usa JS() para evitar tantas "\""
		// Parametros: {1}=tipo, {2}=id, {3}=cantidad, {4} = [{"campo":"valor"},{...}] Ej: "priority":"3 - Normal"]
		respuesta = JS({ "clearquest": {"type":"{1}", "id" : "{2}", "status" : "ok", "description" : "Conexion exitosa", "count" : {3}, "values" : [{4}] } });
		// Le pone argumentos a la respuesta
		respuesta = respuesta.arg(record_type).arg(record_id).arg(record_fields.size()).arg(arFields).toUTF8();

		Json::parse(respuesta.toUTF8(), result); // Prueba de parsing
		respuesta = Json::serialize(result);
	}
	catch (...) {
		return jsonError("Error al ejecutar la consulta");
	}
	return respuesta.toUTF8();
}

/// GetFieldValue: Obtiene el campo del registro almancenado en entity
/// @param field Nombre del campo cuyo valor se desea conocer
char* CQJSON::GetFieldValue(const char* field)
{
    if (!session || !entity) {
        return NULL;
    }
    _bstr_t b;
    try {
		b = entity->GetFieldStringValue( _bstr_t(field) );
		return ConvertBSTRToString(b);
	}
	catch (...) {
        return NULL;
    }
}

/* JSONSetFieldValues
<!--CQ / JSON ENTER-->
{ "clearquest": {"type":"Defect", "id" : "SAMPL00000001", "action" : "Modify", "values" : [{"headline":"spelling errors"},{"priority":"3-Normal Queues"}] } }
<!--CQ / JSON RETURNS-->
{ "clearquest":{ "status":"ok", "description":"Carga exitosa" }}
{ "clearquest":{ "status":"error", "description":"Error..." }}
*/
string CQJSON::JSONSetFieldValues(const char* JSON_fields)
{
	Json::Object conexion, result, field;
	WString respuesta;

	if (!session || !entity) return jsonError("Error: no está conectado."); // Valida la conexion y la entidad
	// Valida que se ha enviado un comando de CQ
	try {
		Json::parse(JSON_fields, result);
		if (!result.contains("clearquest")) return jsonError("Error en el objeto de entrada");
	}
	catch (Json::ParseError& e) {
		return jsonError(e.what());
	}
	// Obtener los elementos de la conexion
	conexion = result.get("clearquest");
	string record_type = conexion.get("type").toString().orIfNull("");
	string record_id = conexion.get("id").toString().orIfNull("");
	string record_action = conexion.get("action").toString().orIfNull("");
	Json::Array record_fields = conexion.get("values");
	// Valida que se enviaron todos los datos
	if (record_type.empty() || record_id.empty() || record_action.empty() || record_fields.empty())
		return jsonError("Error en el objeto de entrada");
	// Intenta la conexion
	if (!GetEntity(record_type.c_str(), record_id.c_str()))
		return jsonError("No se pudo obtener el elemento");
	try{
		if (!EditEntity(record_action.c_str())) return jsonError("No se pudo obtener el elemento");
		// Lee un arreglo JSON de objetos de tipo [{campo:valor},{...}]
		for (unsigned index = 0; index < record_fields.size(); ++index){
			// field = {campo:valor}
			field = record_fields[index];
			// Obtiene el nombre del campo
			set<string>setField = field.names();
			// Usa el nombre del campo para obtener el valor
			for (const auto& name : setField){ // Recorre la lista de nombres, que es solo de uno
				string fieldname = name;
				string fieldvalue = field.get(name);
				// Actualiza los campos de la entidad
				SetFieldValue(fieldname.c_str(), fieldvalue.c_str());
#ifdef MyDEBUG
				cerr << fieldname << " = " << fieldvalue << endl;
#endif
			}
		}
		// Validamos para Commit o Reverse
		char* validation = ValidateEntity();
		if (!validation){
			CommitEntity();
		}
		else{
			RevertEntity();
			return jsonError(validation);
		}
	}
	catch (...) {
		return jsonError("Error al ejecutar la consulta");
	}
	return respuesta.toUTF8();
}

/* SetFieldValue: Obtiene el campo del registro almancenado en entity */
char* CQJSON::SetFieldValue(const char* field, const char* value)
{
	_bstr_t b;
	if (!session || !entity) return NULL;
	try {
		b = entity->SetFieldValue(_bstr_t(field), value);
		return ConvertBSTRToString(b);
	}
	catch (...){ return NULL; }
}

/* ExecuteQuery: Recibe una ruta de Query y devuelve una representacion del resultado */
string CQJSON::ExecuteQuery(char* query)
{
	IWkspcMgrPtr workspace;
	IOAdQueryDefPtr querydef;
	IOAdResultSetPtr resultset;
	_variant_t valor;
	_bstr_t b;
	ostringstream coutput;

	// Conexion a la session de ClearQuest
	try {
		workspace = session->GetWorkSpace(); // Creating a workspace
/*
		# You should have a query named "All Defects" under Public Queries folder
		# Display fields should be in the order - id, State, Headline
		# Filter of the query should be set to "where state = Submitted"
		# This query must be configured correctly on a ClearQuest Client
		# This script simply runs this query, gets the same results and puts into a html file
		# The user logged in should have "Public Folder" privileges.A user can use "Personal" queries also

		# Returns the QueryDef associated with the specified query. 
		my $querydef = $workspace->GetQueryDef("Public Queries/All Submitted"); */
		querydef = workspace->GetQueryDef(query);
/*
		# Creating the resultset and getting the total number of records in the result
		my $resultset = $session->BuildResultSet($querydef);
		$resultset->EnableRecordCount();
		$resultset->Execute();
		$recordCount = $resultset->GetRecordCount(); */
		resultset = session->BuildResultSet(querydef);
		resultset->EnableRecordCount();
		resultset->Execute();
		unsigned long RowsCount = resultset->GetRecordCount();
		unsigned long FieldsCount = resultset->GetNumberOfColumns();
#ifdef MyDEBUG
		cout << "Cantidad de records: " << RowsCount << endl;
		cout << "Cantidad de columnas: " << FieldsCount << endl;
#endif
		/*
		# Iterate through the resultset to fetch information for each record
		for ($i = 0; $i < $recordCount; $i++) {
			$status = $resultset->MoveNext();

			# Column 1 is used by ClearQuest itself.Resultset starts with Column 2.
			# Please check the results of your query in client
			# Make sure these fields correspond to the correct column
			
			$ClearQuestID[$i] = $resultset->GetColumnValue(2);
			$Headline[$i] = $resultset->GetColumnValue(3);
			$Project[$i] = $resultset->GetColumnValue(4);
			$State[$i] = $resultset->GetColumnValue(5);

		}*/
		unsigned int iColumnsCount = resultset->GetNumberOfColumns(); // Numero de columnas
		vector<string> sColumnNames; // Arreglo para almacenar los nombres de Cabeceras
		// Almacena un vector con todos los nombres de cabeceras
		for (unsigned int i = 2; i <= iColumnsCount; i++){
			valor = resultset->GetColumnLabel(i);
			const _bstr_t columnValue(valor);
			sColumnNames.push_back(ConvertBSTRToString(columnValue));
			coutput << "\"" << sColumnNames[i - 2] << "\" ";
		}
		coutput << endl;
		// Recorre las filas y columnas
		for (unsigned int i = 0; i < RowsCount; i++){  // Filas
			resultset->MoveNext();
			for (unsigned int iField = 2; iField <= iColumnsCount; iField++) { // Columnas
				valor = resultset->GetColumnValue(iField);
				const _bstr_t fieldValue(valor);
				coutput << "\"" << ConvertBSTRToString(fieldValue) << "\" ";
			}
			coutput << endl;
		}
#ifdef MyDEBUG
		cout << coutput.str();
#endif
	}
	catch (...) { return NULL; }
	return coutput.str();
}

/* JSONExecuteQuery: Ejecuta un query existente, con o sin parametros
<!--CQ / JSON ENTER-->
{ "clearquest": { "db": "SAMPLE", "repo": "SAMPLE", "login": "cq_user", 
					"query": { "name": "Personal Queries/All Defects",
				// opcional // "params": [{"value1": "cq_user","operator": "EQ"},
											{"value1": "2010-04-23 00:00:00","operator": "BETWEEN","value2": "2010-04-23 23:59:59"
}]}}}
<!--CQ / JSON RETURNS-->
{ "clearquest": { "db": "SAMPLE", "repo": "SAMPLE", "login": "cq_user", 
					"query": {  "numrows":3, "name": "Personal Queries/All Defects","status": "ok",
								"columns": { "count": "3", "column": ["id","state","headline"]},
								"lines": [  {"row": "1","id": "dev2800007311","State": "Submitted","headline": "Headline String"},
											{"row": "2", ...},
											{"row": "3", ...}
]}}}
*/
string CQJSON::JSONExecuteQuery(string JSON_query)
{	
	IWkspcMgrPtr workspace;
	IOAdQueryDefPtr querydef;
	IOAdResultSetPtr resultset;
	_variant_t valor;
	_bstr_t b;
	
	WString respuesta;
#ifndef CONEXION
	Json::Object conexion, result;
	// Valida que se ha enviado un comando de CQ
	try {
		Json::parse(JSON_query, result);
		if (!result.contains("clearquest")) return jsonError("Error en el objeto de entrada");
	}
	catch (Json::ParseError& e) {
		return jsonError(e.what());
	}
	// Obtener los elementos de la conexion
	conexion = result.get("clearquest");
	string cLogin = conexion.get("login").toString().orIfNull("");
	string cPassword = conexion.get("password").toString().orIfNull("");
	string cRepo = conexion.get("repo").toString().orIfNull("");
	string cDb = conexion.get("db").toString().orIfNull("");
	if (!IsConnected()){ // ¿Requiere conexion?
		// Valida que se enviaron todos los datos
		if (cLogin.empty() || cRepo.empty() || cDb.empty())
			return jsonError("Error en el objeto de entrada: no contiene los datos de conexion");
		// Intenta la conexion
		if (!UserLogon(cLogin.c_str(), cPassword.c_str(), cDb.c_str(), cRepo.c_str()))
			return jsonError("Error de conexión con los datos ingresados");
	}
#endif
	// Comienza la operacion
	try {
		Json::Object queryJson = conexion.get("query");
		string queryName = queryJson.get("name").toString().orIfNull("");
		workspace = session->GetWorkSpace(); // Crea un workspace
		querydef = workspace->GetQueryDef(_bstr_t(queryName.c_str())); //
		resultset = session->BuildResultSet(querydef);
		resultset->EnableRecordCount();

		// Incluye los parámetros del query
		unsigned long numParams = resultset->GetNumberOfParams();
		if (numParams){ // Tiene parametros
#ifdef MyDEBUG
			cerr << "ResultSet has " << numParams << " dynamic filters\n";
#endif
			// Obtiene y verifica los parametros
			Json::Array paramsJson = queryJson.get("params"); // Arreglo Json de parametros
			if (paramsJson.empty() || paramsJson.size() != numParams) // La cantidad de param es ok?
				jsonError("Error en número de parametros del query");
			Json::Object paramObj;
			for (unsigned int i = 1; i <= numParams; i++){
				resultset->ClearParamValues(i); // limpia el parametro
				paramObj = paramsJson[i-1]; // Obtiene un elemento del arreglo de parametros, comenzando en 0
				// Operador
				string paramOperator = paramObj.get("operator").toString().orIfNull(""); // Toma el atributo operator
				resultset->SetParamComparisonOperator(i, GetCompOperator(paramOperator.c_str())); // Establece el operador
				// Valor1
				if (paramObj.contains("value1")){ // Si hay un primer parametro...
					string paramValue = paramObj.get("value1").toString().orIfNull(""); // Toma el primer valor1
					resultset->AddParamValue(i, paramValue.c_str());  // Establece el primer valor1
				}
				// Valor2
				if (paramObj.contains("value2")){ // Busca el segundo valor
					string paramValue = paramObj.get("value1").toString().orIfNull("");
					resultset->AddParamValue(i, paramValue.c_str()); // Establece, si hay, el segundo valor2
				}
			}
		}
#ifdef MyDEBUG
		cerr << resultset->GetSQL() << endl;
#endif
		// Ejecucion y resultados
		resultset->Execute();
		unsigned int RowsCount = resultset->GetRecordCount();  // Registros
		unsigned int iColumnsCount = resultset->GetNumberOfColumns(); // Numero de columnas + DBID (restar 1)
#ifdef MyDEBUG
		cout << "Cantidad de records: " << RowsCount << endl;
		cout << "Cantidad de columnas: " << iColumnsCount << endl;
#endif
		// Construye un arreglo JSON de columnas [header1, header2,...]
		string arColumns = "[";
		for (unsigned index = 2; index <= iColumnsCount; index++){
			string columnname = resultset->GetColumnLabel(index); // Obtiene un nombre de columna
			unsigned long columntype = resultset->GetColumnType(index);
			arColumns += "{\"name\":\"" + columnname + "\", \"type\":\"" + GetColumnType(columntype) + "\"}";
			arColumns += (index == iColumnsCount) ? "]" : ","; // Sigue coma o fin (])
#ifdef MyDEBUG
			cerr << arColumns << endl;
#endif
		}
		// Construye el arreglo de filas [ {"row": "1","id": "dev2800007311",... }, {...} ]
		string arLines = "[";
		if (RowsCount == 0) arLines += "]"; // Arreglo vacio
		else for (unsigned int i = 0; i < RowsCount;){  // Filas
			WString sRow = ("{ \"row\":{1}, {2} }"); // Parametro 1 es el numero de fila, el 2 la lista de datos
			resultset->MoveNext();
			string line; // Se llema con la lista de valores: "field":"value", "field":"value",...
			for (unsigned int iField = 2; iField <= iColumnsCount; iField++ ) { // Columnas
				valor = resultset->GetColumnValue(iField);
				const _bstr_t fieldValue(valor);
				string sColumn = resultset->GetColumnLabel(iField); // Nombre de columna sin el DBID
				string sValue = ConvertBSTRToString(fieldValue);
				line += "\"" + sColumn + "\":\"" + escapeJsonString(sValue) + "\"";
				if (iField < iColumnsCount) line += ",";  // Evita poner una ultima coma
			}
			arLines += sRow.arg(i + 1).arg(line).toUTF8(); //  Nro de fila, empezando en 1 + linea de valores
			arLines += (++i == RowsCount) ? "]" : ","; // Sigue coma o fin (])
		}
		/* RESPUESTA FINAL */
		// Aqui se usa JS() para evitar tantas "\""
		// Parametros: {1}=db, {2}=repo, {3}=login, {4}=passw, {5}=numrows,{6}=queryname, {7}=numcols
		//				{8}= columnlist:["id", "state",...], {9}=lines:[{row,data},{row,data}]
		respuesta = JS({ "clearquest": { "db":"{1}", "repo" : "{2}", "login" : "{3}", "password" : "{4}", "status" : "ok",
			"query" : {  "numcolumns" : "{5}", "numrows" : "{6}", "name" : "{7}",
			"columns" : {8}, "rows" : {9} } } });

		// Le pone argumentos a la respuesta
		respuesta = respuesta.arg(cDb).arg(cRepo).arg(cLogin).arg(cPassword).
			arg(iColumnsCount-1).arg(RowsCount).arg(queryName).arg(arColumns).arg(arLines);

		Json::parse(respuesta.toUTF8(), result); // Prueba de parsing
		respuesta = Json::serialize(result);
//		cerr << respuesta;
	}
	catch (...) { 
		return jsonError( "Error al ejecutar la consulta" );
	}
	return respuesta.toUTF8();
 }

 /* GetAllWorkspaceList : Devuelve una lista de todos los elementos publicos y privados del workspace */
 vector<string> CQJSON::GetAllWorkspaceList()
 {
	 _variant_t querynames;
	 SAFEARRAY* pSafeArray = NULL;
	 IWkspcMgrPtr workspace;
	 _variant_t * raw; // Puntero directo a la data de un SafeArray
	 _bstr_t wrapper;  // Para obtener un btr de un variant
	 vector<string> vQueryNames; // Arreglo para almacenar los nombres de Query

	 if (!session) return vQueryNames;  // Retorna vacio si no hay session activa

	 workspace = session->GetWorkSpace(); // Creating a workspace
	 // Obtener los campos de la Entidad
	 querynames = workspace->GetAllQueriesList();
	 pSafeArray = V_ARRAY(&querynames);
	 // Accede directamente a la memoria del SafeArray el cual contiene un arreglo de variant donde cada uno es un bstr
	 HRESULT hr = SafeArrayAccessData(pSafeArray, (void **)&raw);
	 // Iterar la lista de campos si se accedio correctamente a los datos
	 if (SUCCEEDED(hr)) {
		 long lowerBound, upperBound;  // get array bounds
		 SafeArrayGetLBound(pSafeArray, 1, &lowerBound); // Desde
		 SafeArrayGetUBound(pSafeArray, 1, &upperBound); // Hasta

		 long cnt_elements = upperBound - lowerBound + 1; // Cantidad de elementos
		 string saFields[1];
		 for (int i = 0; i < cnt_elements; ++i) {  // iterate through returned values
			 const _bstr_t wrapper(raw[i]);
#ifdef MyDEBUG
//			 cout << "element " << i << ": value = " << wrapper << endl;
#endif
			 vQueryNames.push_back(ConvertBSTRToString(wrapper)); // Almacena en el vector
		 }
	 }
	 SafeArrayDestroy(pSafeArray);
	 return vQueryNames;
 }

// GetWorkspaceList : Devuelve la lista de elementos del workspece, pudiendo indicar el folder y el tipo
// Donde: folder = 1 : public queries, 2 : personal queries, 3 : all public and personal queries
//		  tipo = "LIST" : consultas, "CHART" : graficos, "REPORT" : reportes
 vector<string> CQJSON::GetWorkspaceList( int folder, string tipo )
 {
	 _variant_t querynames;
	 SAFEARRAY* pSafeArray = NULL;
	 IWkspcMgrPtr workspace;
	 _variant_t * raw; // Puntero directo a la data de un SafeArray
	 _bstr_t wrapper;  // Para obtener un btr de un variant
	 vector<string> vQueryNames; // Arreglo para almacenar los nombres de Query

	 if (!session) return vQueryNames;  // Retorna vacio si no hay session activa

	 workspace = session->GetWorkSpace(); // Creating a workspace
	 // Obtener las llstas de tipo y folder solicitado
	 if (tipo == "LIST")
		 querynames = workspace->GetQueryList(folder); // Obtiene queries
	 else if (tipo == "CHART")
		 querynames = workspace->GetChartList(folder); // Obtiene graficos
	 else if (tipo == "REPORT")
		 querynames = workspace->GetReportList(folder); // Obtiene graficos
	 else return vQueryNames; // Si no es el tipo, retorno vacio

	 pSafeArray = V_ARRAY(&querynames);
	 // Accede directamente a la memoria del SafeArray el cual contiene un arreglo de variant donde cada uno es un bstr
	 HRESULT hr = SafeArrayAccessData(pSafeArray, (void **)&raw);
	 // Iterar la lista de campos si se accedio correctamente a los datos
	 if (SUCCEEDED(hr)) {
		 long lowerBound, upperBound;  // get array bounds
		 SafeArrayGetLBound(pSafeArray, 1, &lowerBound); // Desde
		 SafeArrayGetUBound(pSafeArray, 1, &upperBound); // Hasta

		 long cnt_elements = upperBound - lowerBound + 1; // Cantidad de elementos
		 string saFields[1];
		 for (int i = 0; i < cnt_elements; ++i) {  // iterate through returned values
			 const _bstr_t wrapper(raw[i]);
#ifdef MyDEBUG
//			 cout << "element " << i << ": value = " << wrapper << endl;
#endif
			 vQueryNames.push_back(ConvertBSTRToString(wrapper)); // Almacena en el vector
		 }
	 }
	 SafeArrayDestroy(pSafeArray);
	 return vQueryNames;
 }

 /* JSONGetAllWorkspaceList: Obtiene un JSON con dos arreglos, uno de public queries y otro de personal queries
 <!--CQ / JSON ENTER-->
 { "clearquest": { "db": "SAMPLE", "repo": "SAMPLE", "login": "cq_user",... }} // Opcional, solo si requiere conexion
  <!--CQ / JSON RETURNS-->
 { "clearquest": { "db": "SAMPLE", "repo": "SAMPLE", "login": "cq_user",
 		"publicfolder"  :{ "queries":[], "charts":[], "reports":[] },
		"personalfolder":{ "queries":[], "charts":[], "reports":[] }} 
Utiliza el metodo: JSONGetWorkspaceList, el cual devuelve cada uno de los arreglos JSON
*/
 string CQJSON::JSONGetAllWorkspaceList(char* JSON_connection)
 {
	 WString respuesta;
	 Json::Object conexion, result;
#ifndef CONNECTION
	// Valida que se ha enviado un comando de CQ
	try {
		Json::parse(JSON_connection, result);
		if (!result.contains("clearquest")) return jsonError("Error en el objeto de entrada");
	}
	catch (Json::ParseError& e) {
		return jsonError(e.what());
	}
	// Obtener los elementos de la conexion
	conexion = result.get("clearquest");
	string cLogin = conexion.get("login").toString().orIfNull("");
	string cPassword = conexion.get("password").toString().orIfNull("");
	string cRepo = conexion.get("repo").toString().orIfNull("");
	string cDb = conexion.get("db").toString().orIfNull("");
	if (!IsConnected()){ // ¿Requiere conexion?
			// Valida que se enviaron todos los datos
		if (cLogin.empty() || cRepo.empty() || cDb.empty())
			return jsonError("Error en el objeto de entrada: no contiene los datos de conexion");
		// Intenta la conexion
		if (!UserLogon(cLogin.c_str(), cPassword.c_str(), cDb.c_str(), cRepo.c_str()))
			return jsonError("Error de conexión con los datos ingresados");
	}
#endif
	/* RESPUESTA FINAL */
	// Aqui se usa JS() para evitar tantas "\""
	// Parametros: {1}=db, {2}=repo, {3}=login, {4}=passw, 
	//				{5}=arreglo listas publicas,{6}=arreglo de graficos publicos, {7}=arreglo de reports publicos
	//				{8}=arreglo listas privadas,{8}=arreglo de graficos privados, {10}=arreglo de reports privados
	respuesta = JS({ "clearquest":{ "db":"{1}", "repo" : "{2}", "login" : "{3}", "password" : "{4}", "status" : "ok",
		"publicfolder"  :{ "queries":{5}, "charts":{6}, "reports":{7} },
		"personalfolder":{ "queries":{8}, "charts":{9}, "reports":{10}}
		}});
	try{
		// Le pone argumentos a la respuesta
		respuesta = respuesta.arg(cDb).arg(cRepo).arg(cLogin).arg(cPassword).
			arg(JSONGetWorkspaceList(1, "LIST")).arg(JSONGetWorkspaceList(1, "CHART")).arg(JSONGetWorkspaceList(1, "REPORT")).
			arg(JSONGetWorkspaceList(2, "LIST")).arg(JSONGetWorkspaceList(2, "CHART")).arg(JSONGetWorkspaceList(2, "REPORT"));

		Json::parse(respuesta.toUTF8(), result); // Prueba de parsing
		respuesta = Json::serialize(result);
	} catch (...) {
		 return jsonError("Error al ejecutar la consulta");
	}
	return respuesta.toUTF8();
}

 /* JSONGetFolderList : dados un folder y un tipo devuelve un arreglo de elementos 
  [{"path":"Public Queries/All Defects","name":"All Defects", "folder":"Public Queries", "type":"LIST"}, {...}]	 
	Donde:  folder = 1 : public queries, 2 : personal queries, 3 : all public and personal queries
			type = "LIST" : consultas, "CHART" : graficos, "REPORT" : reportes */
string CQJSON::JSONGetWorkspaceList(int folder, char* type)
 {
	 vector<string> querylist;
	 // llenamos la lista de elementos
	 querylist = GetWorkspaceList( folder, type ); // Obtiene la lista de elementos
	 unsigned  cantQueries = querylist.size();
	 string reportPublicList = "[";
	 if (querylist.size() == 0) reportPublicList += "]"; // Arreglo vacio
	 else for (unsigned index = 0; index < cantQueries;){
		 WString sRow = ("{ \"path\":\"{1}\", \"name\":\"{2}\", \"folder\":\"{3}\", \"type\":\"{4}\" }"); // 
		 string query = querylist[index];
		 string queryfolder = query.substr(0, query.rfind('/')); // Nombre del elemento
		 string queryname = query.substr(query.rfind('/') + 1);  // Folder del elemento
		 reportPublicList += sRow.arg(query).arg(queryname).arg(queryfolder).arg(type).toUTF8(); //  Crea un elemento
		 reportPublicList += (++index == cantQueries) ? "]" : ","; // Sigue coma o fin (]) ??
	 }
#ifdef MyDEBUG
//	 cerr << endl << "PUBLIC " << type << "S: " << reportPublicList << endl;
#endif
	 return reportPublicList;
 }

/* JSONGetAllFolderList: Obtiene un JSON con dos arreglos, uno de public folders y otro de personal folders
<!--CQ / JSON ENTER-->
{ "clearquest": { "db": "SAMPLE", "repo": "SAMPLE", "login": "cq_user",... }} // Opcional, solo si requiere conexion
<!--CQ / JSON RETURNS-->
{ "clearquest": { "db": "SAMPLE", "repo": "SAMPLE", "login": "cq_user",
		"publicfolder":[ { "folder":"Public Queries", "name":"Defects by State", "path":"Aging charts", "type":"FOLDER" }, {...} ],
		"personalfolder": [{...},{...}] }}
Utiliza el metodo: GetAllWorkspaceList, el cual devuelve cada un arreglo de todo el workspace 
*/
string CQJSON::JSONGetAllFolderList(char* JSON_connection)
{
	WString respuesta;
	Json::Object conexion, result;
#ifndef CONNECTION
	// Valida que se ha enviado un comando de CQ
	try {
		Json::parse(JSON_connection, result);
		if (!result.contains("clearquest")) return jsonError("Error en el objeto de entrada");
	}
	catch (Json::ParseError& e) {
		return jsonError(e.what());
	}
	// Obtener los elementos de la conexion
	conexion = result.get("clearquest");
	string cLogin = conexion.get("login").toString().orIfNull("");
	string cPassword = conexion.get("password").toString().orIfNull("");
	string cRepo = conexion.get("repo").toString().orIfNull("");
	string cDb = conexion.get("db").toString().orIfNull("");
	if (!IsConnected()){ // ¿Requiere conexion?
		// Valida que se enviaron todos los datos
		if (cLogin.empty() || cRepo.empty() || cDb.empty())
			return jsonError("Error en el objeto de entrada: no contiene los datos de conexion");
		// Intenta la conexion
		if (!UserLogon(cLogin.c_str(), cPassword.c_str(), cDb.c_str(), cRepo.c_str()))
			return jsonError("Error de conexión con los datos ingresados");
	}
#endif
	vector<string> querylist, folderList;
	// llenamos la lista de elementos
	querylist = GetAllWorkspaceList(); // Obtiene la lista de elementos
	//querylist = GetWorkspaceList(1, "CHART");
	unsigned cantQueries = querylist.size();
	string PublicList = "[", PersonalList = "[";
	if (querylist.size() == 0) { PublicList += "]"; PersonalList += "]"; }// Arreglo vacio
	else for (unsigned index = 0; index < cantQueries; index++){
		string query = querylist[index];
		// Obtiene el tipo de folder
		string mainfolder = query.substr(0, query.find('/')); // Personal o Public folder
		query = query.substr(query.find('/')); // Le quito el main folder
		query = query.substr(0, query.rfind('/')); // Le quito el nombre del elemento
		// Obtiene el nombre y path del folder
		string foldername = query.substr(query.rfind('/') + 1);  // Folder a guardar
		string folderpath = query.substr(query.find('/') + 1, query.rfind('/') - query.find('/') - 1); // Nombre del elemento
		if (foldername == folderpath) folderpath = ""; // Ultimo padre
		// Incluye el folder en la lista si no lo esta aun
		while (!foldername.empty() &&
				find(begin(folderList), end(folderList), mainfolder+folderpath+foldername) == end(folderList)){ // es nuevo...
			folderList.push_back(mainfolder+folderpath+foldername);  // Lo guardo en el vector y el arreglo JSON
			WString sRow = ("{ \"name\":\"{1}\", \"path\":\"{2}\", \"folder\":\"{3}\", \"type\":\"{4}\" }"); // 
			if (mainfolder == "Public Queries")
				 PublicList   += sRow.arg(foldername).arg(folderpath).arg(mainfolder).arg("FOLDER").toUTF8() + ","; //  Crea un elemento
			else PersonalList += sRow.arg(foldername).arg(folderpath).arg(mainfolder).arg("FOLDER").toUTF8() + ","; //  Crea un elemento
			// Recorre el resto de la ruta creando sus papas
			query = query.substr(0, query.rfind('/')); // Le quito el ultimo elemento, ya esta guardado
			// Obtiene el nombre y path del folder
			foldername = query.substr(query.rfind('/') + 1);  // Folder a guardar
//			query = query.substr(0, query.rfind('/')); // Quito el folder name
			folderpath = query.substr(query.find('/') + 1, query.rfind('/') - query.find('/') - 1); // Nombre del elemento
			if (foldername == folderpath) folderpath = ""; // Ultimo padre
		}
	} // else for
	if (PublicList.back() == ',') PublicList.back() = ' '; // Elimina la ultima coma
	if (PersonalList.back() == ',') PersonalList.back() = ' '; // Elimina la ultima coma
	PublicList += "]"; PersonalList += "]"; // Cierra el arreglo JSON
	
	/* RESPUESTA FINAL */
	// Aqui se usa JS() para evitar tantas "\""
	// Parametros: {1}=db, {2}=repo, {3}=login, {4}=passw, 
	//			   {5}=arreglo folders publicos,{6}=arreglo de folders personales
	respuesta = JS({ "clearquest":{ "db":"{1}", "repo" : "{2}", "login" : "{3}", "password" : "{4}", "status" : "ok",
									"publicfolder":{5}, "personalfolder":{6}}});
	try{// Le pone argumentos a la respuesta
		respuesta = respuesta.arg(cDb).arg(cRepo).arg(cLogin).arg(cPassword).arg(PublicList).arg(PersonalList);
		Json::parse(respuesta.toUTF8(), result); // Prueba de parsing
		respuesta = Json::serialize(result);
	}
	catch (...) {
		return jsonError("Error al ejecutar la consulta");
	}
	return respuesta.toUTF8();
}

/*********************** ENTITY *******************************/
/* EditEntity: Inicia una acción de la entidad */
char* CQJSON::EditEntity(const char* action)
{
	_bstr_t b;
	if (!session || !entity) return NULL;
	try {
		b = session->EditEntity(entity, _bstr_t(action));
		return ConvertBSTRToString(b);
	}
	catch (...){ return NULL; }
}

/* ValidateEntity: Valida la acción iniciada de la entidad */
char* CQJSON::ValidateEntity()
{
	_bstr_t b;
	if (!session || !entity) return "";
	try {
		b = entity->Validate();
		return ConvertBSTRToString(b);
	}
	catch (...){ return ""; }
}

/* CommitEntity: Registra los cambios de la acción iniciada de la entidad */
char* CQJSON::CommitEntity()
{
	_bstr_t b;
	if (!session || !entity) return NULL;
	try {
		b = entity->Commit();
		return ConvertBSTRToString(b);
	}
	catch (...){ return NULL; }
}

/* RevertEntity: Cancela los cambios de la acción iniciada de la entidad */
char* CQJSON::RevertEntity()
{
	_bstr_t b;
	if (!session || !entity) return NULL;
	try {
		b = entity->Revert();
		return ConvertBSTRToString(b);
	}
	catch (...){ return NULL; }
}

/* ClearEntity: limpia la variable entity obligando a cargar nuevamente */
void CQJSON::ClearEntity()
{
	entity = NULL;
}

/******************* CQENTITY *********************/
string CQEntity::GetEntity(const char* JSON_entity)
{
	if (session.IsConnected()){
		return session.JSONGetEntity(JSON_entity);
	}
}
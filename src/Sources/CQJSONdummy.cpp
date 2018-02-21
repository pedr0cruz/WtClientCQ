/* CQJSONdummy_CPP: Clase de integración con ClearQuest con protocolo JSON (JavaScript Object Notation) */
/* TO-DO
- Hacer metodos para utilizar la variable "entity" (SetFieldValue, etc.)
*/
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>
#include <iostream>
#include <vector>
#include <algorithm>    // std::find
#include <sstream>
#include "CQJSONdummy.h"

using namespace std;
//using namespace _com_util;
using namespace Wt;

// #define MyDEBUG

CQJSONdummy *CQJSONdummy::instance = 0;	// Se comporta como un singleton (GoF)

void _main_dummy()
{
	CQJSONdummy cqSession;
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

// Constructor
CQJSONdummy::CQJSONdummy()
{
//	CoInitialize(0); // Debe estar en el constructor de la clase
}

// Destructor
CQJSONdummy::~CQJSONdummy()
{// CoUninitialize(); // Debe estar en el destructor de la clase
}
 
// Devuelve siempre la misma instancia cuando se contruye
CQJSONdummy *CQJSONdummy::getInstance()
{
	if (!instance)	{
		instance = new CQJSONdummy();
	}
	return instance;
}

// UserLogon : Conexion al ClearQuest
bool CQJSONdummy::UserLogon(const char* login_name, const char* password, const char* database_name, const char* database_set)
{
	// Conexion a la session de ClearQuest
	return bConectado = true;
}

/* JSONUserLogon: Realiza el logueo al Clearquest y actualiza la variable "bConnected"
<!--CQ / JSON ENTER-->
{ "clearquest":{ "db":"SAMPL", "repo":"SAMPLCNX", "login":"admin", "password":""} }
<!--CQ / JSON RETURNS-->
{ "clearquest":{ "status":"ok", "description":"Conexion exitosa" }}
{ "clearquest":{ "status":"error", "description":"Error..." }}
*/
string CQJSONdummy::JSONUserLogon(const char* JSON_connection)
{
	// Conexion exitosa
	bConectado = true;
	return jsonOK("Conexion exitosa");
}

/* GetEntity: Carga en variable entity un registro */
bool CQJSONdummy::GetEntity(const char* record_type, const char *display_name)
{
	return true;
}

/* JSONGetEntity: Lee y guarda en "entity" un registro
<!--CQ / JSON ENTER-->
{ "clearquest":{ "type":"Defect", "id":"SAMPL00000001"}}
<!--CQ / JSON RETURNS-->
{ "clearquest":{ "status":"ok", "description":"Carga exitosa" }}
{ "clearquest":{ "status":"error", "description":"Error..." }}
*/
string CQJSONdummy::JSONGetEntity(const char* JSON_entity)
{
	// Conexion exitosa
	return jsonOK("Carga exitosa");
}

/* GetFieldNames: Devuelve los nombres de todos los campos de la entidad en memoria*/
bool CQJSONdummy::GetFieldNames()
{
		return true;
}

/* JSONGetFieldValue
<!--CQ / JSON ENTER-->
{ "clearquest":{ "type":"Defect", "id":"SAMPL00000001", "fields":[ "headline", "priority" ]}}
<!--CQ / JSON RETURNS-->
{ "clearquest": {"type":"Defect", "id" : "SAMPL00000001", "status" : "ok", "descript
ion" : "Conexion exitosa", "count" : 2, "values" : [{"headline":"spelling error"},{"priority":"3-Normal Queue"}] } }
*/
string CQJSONdummy::JSONGetFieldStringValues(const char* JSON_fields)
{
	Json::Object conexion, result;
	WString respuesta;

	respuesta = JS({ "clearquest": {"type":"Defect", "id" : "SAMPL00000001", "status" : "ok", "description" : "Conexion exitosa", "count" : 2, "values" : [{"headline":"spelling error"},{"priority":"3 - Normal Queue"}] } });

	return respuesta.toUTF8();
}

/* GetFieldValue: Obtiene el campo del registro almancenado en entity */
char* CQJSONdummy::GetFieldValue(const char* field)
{
	return "valor";
}

/* ExecuteQuery: Recibe una ruta de Query y devuelve una representacion del resultado */
string CQJSONdummy::ExecuteQuery(char* query)
{
	ostringstream coutput;
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
string CQJSONdummy::JSONExecuteQuery(string JSON_query)
{	
	Json::Object conexion, result;
	// Obtiene el nombre del Query
	Json::parse(JSON_query, result);
	conexion = result.get("clearquest");
	Json::Object queryJson = conexion.get("query");
	string queryName = queryJson.get("name").toString().orIfNull("");


	WString respuesta;
/*		respuesta = JS({ "clearquest": { "db":"{1}", "repo" : "{2}", "login" : "{3}", "password" : "{4}", "status" : "ok",
			"query" : {  "numcolumns" : "{5}", "numrows" : "{6}", "name" : "{7}",
			"columns" : {8}, "rows" : {9} } } });
*/
	//  Query: All Customers
	if (queryName.find("All Customers") )
	respuesta = JS({ "clearquest" : { "db" : "SAMPL", "login" : "admin", "password" : "", 
		"query" : { "columns" :[{ "name" : "Name", "type" : "STRING" }, 
		{ "name" : "Company", "type" : "STRING" }, { "name" : "CallTrackingID", "type" : "STRING" }, 
		{ "name" : "Email", "type" : "STRING" }], "name" : "Public Queries/Customers/All Customers", "numcolumns" : "4", 
		"numrows" : "10", "rows" : [{ "CallTrackingID" : "Reqid00014582", "Company" : "FooBar Company", 
		"Email" : "annej@foobar.com", "Name" : "Anne Johnson", "row" : 1 }, { "CallTrackingID" : "CallID90049308", 
		"Company" : "Phone Company", "Email" : "drogers@phone.com", "Name" : "Dale Rogers", "row" : 2 }, 
		{ "CallTrackingID" : "Reqid00000345", "Company" : "Foo Company", "Email" : "ehawk@FooCompany.com", 
		"Name" : "Ethan Hunt", "row" : 3 }, { "CallTrackingID" : "Reqid00423951", "Company" : "Software Company", 
		"Email" : "janesmith@softwarecompany.com", "Name" : "Jane Smith", "row" : 4 }, 
		{ "CallTrackingID" : "CallID00098733", "Company" : "Child Software Company", 
		"Email" : "jlee@childsoft.com", "Name" : "Joe Lee", "row" : 5 }, { "CallTrackingID" : "Reqid00089347", 
		"Company" : "XYZ Company", "Email" : "johnsmith@xzycompany.com", "Name" : "John Smith", "row" : 6 }, 
		{ "CallTrackingID" : "CallID00018735", "Company" : "Clothing Company", "Email" : "natalie.adams@clothing.com", 
		"Name" : "Natalie Adams", "row" : 7 }, { "CallTrackingID" : "CallID00068732", "Company" : "Toy Company", 
		"Email" : "", "Name" : "Randy Doe", "row" : 8 }, { "CallTrackingID" : "Reqid00549035", 
		"Company" : "Flower Company", "Email" : "ssimon@flower.com", "Name" : "Scott Simon", "row" : 9 }, 
		{ "CallTrackingID" : "Reqid00073529", "Company" : "Consulting Inc.", "Email" : "slewis@consulting.com", 
		"Name" : "Stacey Lewis", "row" : 10 }] }, "repo" : "SAMPLCNX", "status" : "ok" } });
	
	// Query: Email Rules
	if (queryName.find("All Email Rules"))
		respuesta = JS({ "clearquest" : { "db" : "SAMPL", "login" : "admin", "password" : "", "query" :
		{ "columns" :[{ "name" : "Name", "type" : "STRING" }, { "name" : "Entity_Def", "type" : "STRING" }, 
		{ "name" : "Filter_Query", "type" : "STRING" }], "name" : "Public Queries/Email Rules/All Email Rules", 
		"numcolumns" : "3", "numrows" : "4", "rows" : [{ "Entity_Def" : "Defect", "Filter_Query" : "", 
		"Name" : "Closures", "row" : 1 }, { "Entity_Def" : "Defect", "Filter_Query" : "", 
		"Name" : "Modifications", "row" : 2 }, { "Entity_Def" : "Defect", "Filter_Query" : "", 
		"Name" : "New Submissions", "row" : 3 }, { "Entity_Def" : "Defect", "Filter_Query" : "", 
		"Name" : "Resolutions", "row" : 4 }] }, "repo" : "SAMPLCNX", "status" : "ok" } });

	// Query: My Hot List
	if (queryName.find("My Hot List"))
		respuesta = JS({ "clearquest" : { "db" : "SAMPL", "login" : "admin", "password" : "", "query" :
		{ "columns" :[{ "name" : "id", "type" : "STRING" }, { "name" : "State", "type" : "STRING" }, 
		{ "name" : "Headline", "type" : "STRING" }], "name" : "Public Queries/My Hot List", "numcolumns" : "3", 
		"numrows" : "0", "rows" : [] }, "repo" : "SAMPLCNX", "status" : "ok" } });

	return respuesta.toUTF8();
 }

 /* GetAllWorkspaceList : Devuelve una lista de todos los elementos publicos y privados del workspace */
 vector<string> CQJSONdummy::GetAllWorkspaceList()
 {
	 vector<string> vQueryNames; // Arreglo para almacenar los nombres de Query
	 return vQueryNames;
 }

// GetWorkspaceList : Devuelve la lista de elementos del workspece, pudiendo indicar el folder y el tipo
// Donde: folder = 1 : public queries, 2 : personal queries, 3 : all public and personal queries
//		  tipo = "LIST" : consultas, "CHART" : graficos, "REPORT" : reportes
 vector<string> CQJSONdummy::GetWorkspaceList( int folder, string tipo )
 {
	 vector<string> vQueryNames; // Arreglo para almacenar los nombres de Query
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
 string CQJSONdummy::JSONGetAllWorkspaceList(char* JSON_connection)
 {
	 WString respuesta;
	// Parametros: {1}=db, {2}=repo, {3}=login, {4}=passw, 
	//				{5}=arreglo listas publicas,{6}=arreglo de graficos publicos, {7}=arreglo de reports publicos
	//				{8}=arreglo listas privadas,{8}=arreglo de graficos privados, {10}=arreglo de reports privados

	respuesta = JS({ "clearquest" : { "db" : "", "login" : "", "password" : "", 
		"personalfolder" : { "charts" :[], "queries" : [
			{ "folder" : "Personal Queries/Aging Charts", "name" : "All Defects", "path" : "Personal Queries/Aging Charts/All Defects", "type" : "LIST" }], "reports" : [] }, 
		"publicfolder" : { "charts" :[{ "folder" : "Public Queries/Aging Charts", "name" : "Defect Aging by State", "path" : "Public Queries/Aging Charts/Defect Aging by State", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Aging Charts/Open", "name" : "High (2) 7 Day", "path" : "Public Queries/Aging Charts/Open/High (2) 7 Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Aging Charts/Open", "name" : "Priorities (2) 7 Day", "path" : "Public Queries/Aging Charts/Open/Priorities (2) 7 Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Aging Charts/Open", "name" : "Priorities (4) 30 Day", "path" : "Public Queries/Aging Charts/Open/Priorities (4) 30 Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Aging Charts/Open", "name" : "High (4) 30 Day", "path" : "Public Queries/Aging Charts/Open/High (4) 30 Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Aging Charts", "name" : "Submitted (2) 7 Day", "path" : "Public Queries/Aging Charts/Submitted (2) 7 Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Aging Charts", "name" : "Closed (4) 30 Day", "path" : "Public Queries/Aging Charts/Closed (4) 30 Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Aging Charts", "name" : "Submitted (4) 30 Day", "path" : "Public Queries/Aging Charts/Submitted (4) 30 Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Trend Charts", "name" : "Defect State Transitions by Mont", "path" : "Public Queries/Trend Charts/Defect State Transitions by Mont", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Trend Charts", "name" : "Defect Counts by State, Day", "path" : "Public Queries/Trend Charts/Defect Counts by State, Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Trend Charts", "name" : "Defect State Transitions by Week", "path" : "Public Queries/Trend Charts/Defect State Transitions by Week", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Trend Charts", "name" : "Defect Counts by State, Month", "path" : "Public Queries/Trend Charts/Defect Counts by State, Month", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Trend Charts", "name" : "Defect State Transitions by Day", "path" : "Public Queries/Trend Charts/Defect State Transitions by Day", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Trend Charts/Submitted/Opened", "name" : "Resolved", "path" : "Public Queries/Trend Charts/Submitted/Opened/Resolved", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Trend Charts/Submitted", "name" : "Resolved", "path" : "Public Queries/Trend Charts/Submitted/Resolved", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Trend Charts", "name" : "Defect Counts by State, Week", "path" : "Public Queries/Trend Charts/Defect Counts by State, Week", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts", "name" : "All Defects by Owner", "path" : "Public Queries/Distribution Charts/All Defects by Owner", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts", "name" : "Active Defects by Owner", "path" : "Public Queries/Distribution Charts/Active Defects by Owner", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts/Defects By Owner", "name" : "State", "path" : "Public Queries/Distribution Charts/Defects By Owner/State", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts/Defects by Priority", "name" : "Owner", "path" : "Public Queries/Distribution Charts/Defects by Priority/Owner", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts/Defects by Priority", "name" : "Severity", "path" : "Public Queries/Distribution Charts/Defects by Priority/Severity", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts/Defects by State", "name" : "Priority", "path" : "Public Queries/Distribution Charts/Defects by State/Priority", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts/Defects by State", "name" : "Severity", "path" : "Public Queries/Distribution Charts/Defects by State/Severity", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts", "name" : "All Defects by Severity", "path" : "Public Queries/Distribution Charts/All Defects by Severity", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts", "name" : "Active Defects by Priority", "path" : "Public Queries/Distribution Charts/Active Defects by Priority", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts", "name" : "Active Defects by Severity", "path" : "Public Queries/Distribution Charts/Active Defects by Severity", "type" : "CHART" }, 
			{ "folder" : "Public Queries/Distribution Charts", "name" : "Defect Count by Priority", "path" : "Public Queries/Distribution Charts/Defect Count by Priority", "type" : "CHART" }], 
			"queries" : [{ "folder" : "Public Queries/Customers", "name" : "All Customers", "path" : "Public Queries/Customers/All Customers", "type" : "LIST" }, 
			{ "folder" : "Public Queries", "name" : "Keyword Search", "path" : "Public Queries/Keyword Search", "type" : "LIST" }, 
			{ "folder" : "Public Queries", "name" : "My To Do List", "path" : "Public Queries/My To Do List", "type" : "LIST" }, 
			{ "folder" : "Public Queries", "name" : "All Defects", "path" : "Public Queries/All Defects", "type" : "LIST" }, 
			{ "folder" : "Public Queries/Email Rules", "name" : "All Email Rules", "path" : "Public Queries/Email Rules/All Email Rules", "type" : "LIST" }, 
			{ "folder" : "Public Queries", "name" : "Needs Verification", "path" : "Public Queries/Needs Verification", "type" : "LIST" }, 
			{ "folder" : "Public Queries/Reports", "name" : "State Query", "path" : "Public Queries/Reports/State Query", "type" : "LIST" }, 
			{ "folder" : "Public Queries", "name" : "My Hot List", "path" : "Public Queries/My Hot List", "type" : "LIST" }], 
			"reports" : [{ "folder" : "Public Queries/Reports", "name" : "Defect Summary (All)", "path" : "Public Queries/Reports/Defect Summary (All)", "type" : "REPORT" }, 
			{ "folder" : "Public Queries/Reports", "name" : "Defect Detail (State)", "path" : "Public Queries/Reports/Defect Detail (State)", "type" : "REPORT" }, 
			{ "folder" : "Public Queries/Reports", "name" : "Defect Summary (State)", "path" : "Public Queries/Reports/Defect Summary (State)", "type" : "REPORT" }, 
			{ "folder" : "Public Queries/Reports", "name" : "Defect Notes (All)", "path" : "Public Queries/Reports/Defect Notes (All)", "type" : "REPORT" }, 
			{ "folder" : "Public Queries/Reports", "name" : "Defect Detail (All)", "path" : "Public Queries/Reports/Defect Detail (All)", "type" : "REPORT" }] }, 
			"repo" : "", "status" : "ok" } });
	return respuesta.toUTF8();
}

 /* JSONGetFolderList : dados un folder y un tipo devuelve un arreglo de elementos 
  [{"path":"Public Queries/All Defects","name":"All Defects", "folder":"Public Queries", "type":"LIST"}, {...}]	 
	Donde:  folder = 1 : public queries, 2 : personal queries, 3 : all public and personal queries
			type = "LIST" : consultas, "CHART" : graficos, "REPORT" : reportes */
string CQJSONdummy::JSONGetWorkspaceList(int folder, char* type)
 {
	 string reportPublicList;
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
string CQJSONdummy::JSONGetAllFolderList(char* JSON_connection)
{
	WString respuesta;
	Json::Object conexion, result;

	/* RESPUESTA FINAL */
	// Aqui se usa JS() para evitar tantas "\""
	// Parametros: {1}=db, {2}=repo, {3}=login, {4}=passw, 
	//			   {5}=arreglo folders publicos,{6}=arreglo de folders personales
	/*respuesta = JS({ "clearquest": { "db": "SAMPLE", "repo" : "SAMPLE", "login" : "cq_user",
		"publicfolder" : [{ "folder":"Public Queries", "name" : "Defects by State", "path" : "Aging charts", "type" : "FOLDER" }, { ... }],
		"personalfolder" : [] } });*/
	respuesta = JS({ "clearquest" : { "db" : "", "login" : "", "password" : "", 
		"personalfolder" : [
		{ "folder" : "Personal Queries", "name" : "Aging Charts", "path" : "", "type" : "FOLDER" }], 
		"publicfolder" : [
		{ "folder" : "Public Queries", "name" : "Aging Charts", "path" : "", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Open", "path" : "Aging Charts", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Customers", "path" : "", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Distribution Charts", "path" : "", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Defects By Owner", "path" : "Distribution Charts", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Defects by Priority", "path" : "Distribution Charts", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Defects by State", "path" : "Distribution Charts", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Email Rules", "path" : "", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Reports", "path" : "", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Trend Charts", "path" : "", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Opened", "path" : "Trend Charts/Submitted", "type" : "FOLDER" }, 
		{ "folder" : "Public Queries", "name" : "Submitted", "path" : "Trend Charts", "type" : "FOLDER" }], "repo" : "", "status" : "ok" } });

	return respuesta.toUTF8();
}

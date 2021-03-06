/* CQJSON_HPP: Clase de integración con ClearQuest con protocolo JSON (JavaScript Object Notation) */
#ifndef CQJSON_INCLUDED
#define CQJSON_INCLUDED
/*

#include <iostream>
#include <string>
*/
#include <Wt\WString>

//#pragma once
#import "C:\\Program Files (x86)\\IBM\\RationalSDLC\\ClearQuest\\cqole.dll" no_namespace auto_rename
using namespace std;
using namespace Wt;


class CQJSON
{
private:
	IOAdSessionPtr session = NULL;
	IOAdEntityPtr  entity  = NULL;
	bool bConectado = false;	// Indica que la conexion ya se ha establecido con la BD con UserLogon
	int GetCompOperator(const char *name) { // Codigos de los operadores de querys
		char* CompOperators[] = { "\0", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "LIKE", "NOT_LIKE", "BETWEEN", "NOT_BETWEEN", "IS_NULL", "IS_NOT_NULL", "IN", "NOT_IN", "\0" };
		for (int i = 1; CompOperators[i]; i++) if (!strcmp(name, CompOperators[i]))	return i; return 0;
	}
	string GetColumnType(unsigned long type) { // Codigos de los tipo de datos de las columnas
		char* CTypes[] = { "\0", "STRING", "MULTILINE", "BINARY", "LONG", "DATETIME", "DOUBLE", "\0" };
		return CTypes[type];
	}

	string GetParameters(IOAdResultSetPtr);
public:
	CQJSON();
	~CQJSON();

	// UserLogon: permite la conexión a una BD de usuario
	bool UserLogon(const char* login_name, const char* password, const char* database_name, const char* database_set);
	string JSONUserLogon(const char* JSON_connection);
	
	// GetEntity: obtiene un registro y lo guarda en entity. Recibe el tipo de registro y el DbId
	bool GetEntity( const char* record_type, const char *display_name);
	string JSONGetEntity(const char* JSON_entity);
	
	// GetFieldValue: Obtiene el campo del registro almancenado en entity
	char* GetFieldValue(const char* field);
	
	string JSONGetFieldStringValues(const char* JSON_field);
	
	string ExecuteQuery(char* query);
	string JSONExecuteQuery(char* JSON_query);

	// Devuelve la lista de nombres de queries, graficos y reportes del workspace
	vector<string> GetAllWorkspaceList();
	// Devuelve la lista de elementos del workspece, pudiendo indicar el folder y el tipo
	vector<string> GetWorkspaceList(int folder, string tipo);
	string JSONGetWorkspaceList(int folder, char* type);
	string JSONGetAllWorkspaceList(char* JSON_connection);

	string JSONGetAllFolderList(char* JSON_connection);

	bool GetFieldNames();
	bool IsConnected() { return bConectado; }
	
	// Devuelve un Json de exito
	string jsonOK(WString msg) {
		string msgerr = WString("{\"clearquest\": {\"status\":\"ok\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
		return msgerr;
	}

	// Devuelve un Json de error
	string jsonError(WString msg) {
		string msgerr = WString("{\"clearquest\": {\"status\":\"error\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
		return msgerr;

		// Intentando construir un Json programaticamente, hasta ahora nada
/*		Json::Object errmsg, obj;
		Json::Value v(Json::ObjectType), result;

		obj["status"] = WString("error");
		obj.insert( make_pair("desc", msg) );
		v = &obj;

		errmsg["clearquest"] = WString(Json::serialize(obj)); // OK
		string generated = Json::serialize(errmsg);
		cerr << generated;
*/
	}

	// Convierte los caracteres de Escape segun JSON 
	// Nota: la misma funcion la realiza WString::jsStringLiteral, cambiarlo y probarlo
	string escapeJsonString(const string& input) {
		std::ostringstream ss;
		for (auto iter = input.cbegin(); iter != input.cend(); iter++) {
			//C++98/03:
			//for (std::string::const_iterator iter = input.begin(); iter != input.end(); iter++) {
			switch (*iter) {
			case '\\': ss << "\\\\"; break;	case '"': ss << "\\\""; break; case '/': ss << "\\/"; break;
			case '\b': ss << "\\b"; break;  case '\f': ss << "\\f"; break; case '\n': ss << "\\n"; break;
			case '\r': ss << "\\r"; break;  case '\t': ss << "\\t"; break; default: ss << *iter; break;
			}
		}
		return ss.str();
	}
};

#endif // CQJSON_INCLUDED
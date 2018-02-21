/* CQJSONdummy_HPP: Clase de integración con ClearQuest con protocolo JSON (JavaScript Object Notation) */
#ifndef CQJSONdummy_INCLUDED
#define CQJSONdummy_INCLUDED

#include <iostream>
#include <string>

#include <Wt\Wstring>

#define JS(...) #__VA_ARGS__

// #pragma once
// #import "C:\\Program Files (x86)\\IBM\\RationalSDLC\\ClearQuest\\cqole.dll" no_namespace auto_rename

//using namespace Wt;

using namespace std; 

class CQJSONdummy
	{
	private:
		static CQJSONdummy *instance; // Unica instancia global
		//IOAdSessionPtr session = NULL;
		//IOAdEntityPtr  entity = NULL;
		char* session = NULL;
		char*  entity = NULL;
		bool bConectado = false;	// Indica que la conexion ya se ha establecido con la BD con UserLogon
		int GetCompOperator(const char *name) { // Codigos de los operadores de querys
			char* CompOperators[] = { "\0", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "LIKE", "NOT_LIKE", "BETWEEN", "NOT_BETWEEN", "IS_NULL", "IS_NOT_NULL", "IN", "NOT_IN", "\0" };
			for (int i = 1; CompOperators[i]; i++) if (!strcmp(name, CompOperators[i]))	return i; return 0;
		}
		string GetColumnType(unsigned long type) { // Codigos de los tipo de datos de las columnas
			char* CTypes[] = { "\0", "STRING", "MULTILINE", "BINARY", "LONG", "DATETIME", "DOUBLE", "\0" };
			return CTypes[type];
		}

//		std::string GetParameters(IOAdResultSetPtr);
	public:
		CQJSONdummy();
		CQJSONdummy( const char* login_name, const char* password, const char* database_name, const char* database_set ){
			UserLogon(login_name, password, database_name, database_set); 	}
		~CQJSONdummy();
		static CQJSONdummy *getInstance(); // Devuelve siempre la misma instancia

		// UserLogon: permite la conexión a una BD de usuario
		bool UserLogon(const char* login_name, const char* password, const char* database_name, const char* database_set);
		std::string JSONUserLogon(const char* JSON_connection);

		// GetEntity: obtiene un registro y lo guarda en entity. Recibe el tipo de registro y el DbId
		bool GetEntity(const char* record_type, const char *display_name);
		std::string JSONGetEntity(const char* JSON_entity);

		// GetFieldValue: Obtiene el campo del registro almancenado en entity
		char* GetFieldValue(const char* field);

		std::string JSONGetFieldStringValues(const char* JSON_field);

		std::string ExecuteQuery(char* query);
		std::string JSONExecuteQuery(string JSON_query);

		// Devuelve la lista de nombres de queries, graficos y reportes del workspace

		vector<string> GetAllWorkspaceList();
		// Devuelve la lista de elementos del workspece, pudiendo indicar el folder y el tipo
		vector<string> GetWorkspaceList(int folder, std::string tipo);

		std::string JSONGetWorkspaceList(int folder, char* type);
		std::string JSONGetAllWorkspaceList(char* JSON_connection);

		std::string JSONGetAllFolderList(char* JSON_connection);

		bool GetFieldNames();
		bool IsConnected() { return bConectado; }

		// Devuelve un Json de exito
		std::string jsonOK(Wt::WString msg) {
			std::string msgerr = Wt::WString("{\"clearquest\": {\"status\":\"ok\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
			return msgerr;
		}

		// Devuelve un Json de error
		std::string jsonError(Wt::WString msg) {
			std::string msgerr = Wt::WString("{\"clearquest\": {\"status\":\"error\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
			return msgerr;
		}

		// Convierte los caracteres de Escape segun JSON 
		// Nota: la misma funcion la realiza Wstd::string::jsstd::stringLiteral, cambiarlo y probarlo
		std::string escapeJsonString(const std::string& input) {
			std::ostringstream ss;
			for (auto iter = input.cbegin(); iter != input.cend(); iter++) {
				//C++98/03:
				//for (std::std::string::const_iterator iter = input.begin(); iter != input.end(); iter++) {
				switch (*iter) {
				case '\\': ss << "\\\\"; break;	case '"': ss << "\\\""; break; case '/': ss << "\\/"; break;
				case '\b': ss << "\\b"; break;  case '\f': ss << "\\f"; break; case '\n': ss << "\\n"; break;
				case '\r': ss << "\\r"; break;  case '\t': ss << "\\t"; break; default: ss << *iter; break;
				}
			}
			return ss.str();
		}
		//		return input.jsstd::stringLiteral();
	};

typedef CQJSONdummy  CQJSON;

//} // namespace
#endif CQJSONdummy_INCLUDED

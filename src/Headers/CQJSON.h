/* CQJSON_HPP: Clase de integración con ClearQuest con protocolo JSON (JavaScript Object Notation) */
#ifndef CQJSON_INCLUDED
#define CQJSON_INCLUDED

#include <iostream>
#include <string>

#include <Wt\Wstring>

#define JS(...) #__VA_ARGS__

#pragma once
#import "C:\\Program Files (x86)\\IBM\\RationalSDLC\\ClearQuest\\cqole.dll" no_namespace auto_rename

//using namespace Wt;

using namespace std; 


/// CQJSON: ClearQuest client class which uses a JSON interface
///
/// This class is a ClearQuest client class which uses a JSON interface to communicate
/// with the application view, which renders the received JSON data (and sends back
/// data using the corresponding WT widgets according to the data type).
///
class CQJSON
	{
	private:
		///	singleton (unique global instance)
		static CQJSON *instance;
		IOAdSessionPtr session = NULL;
		IOAdEntityPtr  entity = NULL;
		bool bConectado = false;	// Indica que la conexion ya se ha establecido con la BD con UserLogon
		int GetCompOperator(const char *name) { // Codigos de los operadores de querys
			char* CompOperators[] = { "\0", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "LIKE", "NOT_LIKE", "BETWEEN", "NOT_BETWEEN", "IS_NULL", "IS_NOT_NULL", "IN", "NOT_IN", "\0" };
			for (int i = 1; CompOperators[i]; i++) if (!strcmp(name, CompOperators[i]))	return i; return 0;
		}
		string GetColumnType(unsigned long type) { // Codigos de los tipo de datos de las columnas
			char* CTypes[] = { "\0", "STRING", "MULTILINE", "BINARY", "LONG", "DATETIME", "DOUBLE", "\0" };
			return CTypes[type];
		}

		std::string GetParameters(IOAdResultSetPtr);
	public:
		CQJSON();
		CQJSON( const char* login_name, const char* password, const char* database_name, const char* database_set ){
			UserLogon(login_name, password, database_name, database_set); 	}
		~CQJSON();
		/// Devuelve siempre la misma instancia
		static CQJSON *getInstance(); 

		/// UserLogon: permite la conexión a una BD de usuario
		bool UserLogon(const char* login_name, const char* password, const char* database_name, const char* database_set);
		std::string JSONUserLogon(const char* JSON_connection);

		std::string ExecuteQuery(char* query);
		std::string JSONExecuteQuery(string JSON_query);

		/// Devuelve la lista de nombres de queries, graficos y reportes del workspace
		vector<string> GetAllWorkspaceList();
		
		/// Devuelve la lista de elementos del workspece, pudiendo indicar el folder y el tipo
		vector<string> GetWorkspaceList(int folder, std::string tipo);

		std::string JSONGetWorkspaceList(int folder, char* type);
		std::string JSONGetAllWorkspaceList(char* JSON_connection);

		std::string JSONGetAllFolderList(char* JSON_connection);

		bool GetFieldNames();
		bool IsConnected() { return bConectado; }

		/// Devuelve un Json de exito
		std::string jsonOK(Wt::WString msg) {
			std::string msgerr = Wt::WString("{\"clearquest\": {\"status\":\"ok\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
			return msgerr;
		}

		/// Devuelve un Json de error
		std::string jsonError(Wt::WString msg) {
			std::string msgerr = Wt::WString("{\"clearquest\": {\"status\":\"error\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
			return msgerr;

			// Intentando construir un Json programaticamente, hasta ahora nada
			/*		Json::Object errmsg, obj;
					Json::Value v(Json::ObjectType), result;

					obj["status"] = Wstd::string("error");
					obj.insert( make_pair("desc", msg) );
					v = &obj;

					errmsg["clearquest"] = Wstd::string(Json::serialize(obj)); // OK
					std::string generated = Json::serialize(errmsg);
					cerr << generated;
					*/
		}

		/// Convierte los caracteres de Escape segun JSON 
		/// Nota: la misma funcion la realiza Wstd::string::jsstd::stringLiteral, cambiarlo y probarlo
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
	

		/*********************** ENTITY *******************************/
		/// GetEntity: obtiene un registro y lo guarda en entity. Recibe el tipo de registro y el DbId
		bool GetEntity(const char* record_type, const char *display_name);
		string JSONGetEntity(const char* JSON_entity);

		/// GetFieldValue: Obtiene el campo del registro almancenado en entity
		char* GetFieldValue(const char* field);
		string JSONGetFieldStringValues(const char* JSON_field);

		/// SetFieldValue: Setea un campo del registro almancenado en entity
		char* SetFieldValue(const char* field, const char* value);
		string JSONSetFieldValues(const char* JSON_fields);

		/// EditEntity: Inicia una acción de la entidad
		char* EditEntity(const char* action);

		/// ValidateEntity: Valida la acción iniciada de la entidad
		char* ValidateEntity();

		/// CommitEntity: Registra los cambios de la acción iniciada de la entidad
		char* CommitEntity();

		/// RevertEntity: Cancela los cambios de la acción iniciada de la entidad
		char* RevertEntity();

		/// ClearEntity: limpia la variable entity obligando a cargar nuevamente
		void ClearEntity();

};

class CQEntity{
private:
	CQJSON session;
	IOAdEntityPtr  entity = NULL;
public:
	/// Constructor
	CQEntity(CQJSON jSession) { session = jSession; }
	~CQEntity(){ entity = NULL; }

	/// GetEntity: obtiene un registro y lo guarda en entity. Recibe el tipo de registro y el DbId
	string GetEntity(const char* JSON_entity);

	/// GetFieldValue: Obtiene el campo del registro almancenado en entity
	string GetFieldStringValues(const char* JSON_field);

	/// SetFieldValue: Setea un campo del registro almancenado en entity
	string SetFieldValues(const char* JSON_fields);

	/// EditEntity: Inicia una acción de la entidad 
	char* Edit(const char* action);

	/// ValidateEntity: Valida la acción iniciada de la entidad 
	char* Validate();

	/// CommitEntity: Registra los cambios de la acción iniciada de la entidad 
	char* Commit();

	/// RevertEntity: Cancela los cambios de la acción iniciada de la entidad
	char* Revert();

	/// ClearEntity: limpia la variable entity obligando a cargar nuevamente
	void Clear();
};

//} // namespace
#endif CQJSON_INCLUDED

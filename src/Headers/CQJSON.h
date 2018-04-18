/// CQJSON.h
/// Clase de integración con ClearQuest con protocolo 
/// JSON (JavaScript Object Notation)

#ifndef CQJSON_H
#define CQJSON_H

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include <Wt\Wstring>

#define JS(...) #__VA_ARGS__

//#import "C:\\Program Files (x86)\\IBM\\RationalSDLC\\ClearQuest\\cqole.dll" no_namespace auto_rename

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

        /// Puntero a sesión de ClearQuest
		IOAdSessionPtr session = NULL;
        /// Puntero a entidad de ClearQuest
        IOAdEntityPtr  entity = NULL;

        /// Indica que la conexion ya se ha establecido con la BD con UserLogon
        bool bConectado = false;

        /// Devuelve el indide del código de operador de consulta especificado como argumento
        int GetCompOperator(const char *name)
        {
            // Codigos de los operadores de querys
			char* CompOperators[] = { "\0", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "LIKE", "NOT_LIKE", "BETWEEN", "NOT_BETWEEN", "IS_NULL", "IS_NOT_NULL", "IN", "NOT_IN", "\0" };
			for (int i = 1; CompOperators[i]; i++) if (!strcmp(name, CompOperators[i]))	return i; return 0;
		}

        /// Devuelve el código de operador de consulta que corresponde al indice especificado
        std::string GetColumnType(unsigned long type)
        {
			char* CTypes[] = { "\0", "STRING", "MULTILINE", "BINARY", "LONG", "DATETIME", "DOUBLE", "\0" };
			return CTypes[type];
		}

        /// FIXME HACK PENDIENTE Devuelve ... de ClearQuest
		std::string GetParameters(IOAdResultSetPtr);

	public:
        /// Constructor implícito (sin argumentos)
        CQJSON();
        /// Constructor con argumentos para conectarse a base de datos
        CQJSON (const char* login_name, const char* password,
                const char* database_name, const char* database_set)
        {
			UserLogon(login_name, password, database_name, database_set);
        }
        /// Destructor
		virtual ~CQJSON();

        /// Devuelve siempre la misma instancia (patrón Singleton)
        static CQJSON *getInstance();

		/// UserLogon: permite la conexión a una BD de usuario
		bool UserLogon(const char* login_name, const char* password, const char* database_name, const char* database_set);
        /// JSONUserLogon: Usa JSON para la conexión a una BD de usuario
        std::string JSONUserLogon(const char* JSON_connection);

		/// Ejecuta la consulta especificada
        std::string ExecuteQuery(char* query);
        /// Ejecuta la consulta especificada usando JSON
        std::string JSONExecuteQuery(std::string JSON_query);

		/// Devuelve la lista de nombres de queries, graficos y reportes del workspace
        std::vector <std::string> GetAllWorkspaceList();
		
		/// Devuelve la lista de elementos del workspece, pudiendo indicar el folder y el tipo
		std::vector <std::string> GetWorkspaceList(int folder, std::string tipo);

        /// Devuelve cadena con datos de Workspace ... 
        /// Para el comentario: FIXME, HACK PENDIENTE
        std::string JSONGetWorkspaceList(int folder, char* type);
        /// Devuelve cadena con datos de Workspace ... usando JSON
        /// Para el comentario: FIXME, HACK PENDIENTE
        std::string JSONGetAllWorkspaceList(char* JSON_connection);

        /// Devuelve lista de carpetas del Workspace ... usando JSON
        /// Para el comentario: FIXME, HACK PENDIENTE
        std::string JSONGetAllFolderList(char* JSON_connection);

        /// Obtiene nombre de los campos
        bool GetFieldNames();
        /// Devuelve si está conectado (como usuario) o no
        bool IsConnected() { return bConectado; }

		/// Devuelve un Json de exito
		std::string jsonOK(Wt::WString msg)
        {
			std::string msgerr = Wt::WString("{\"clearquest\": {\"status\":\"ok\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
			return msgerr;
		}

		/// Devuelve un Json de error
		std::string jsonError(Wt::WString msg)
        {
			std::string msgerr = Wt::WString("{\"clearquest\": {\"status\":\"error\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
			return msgerr;
/*		
            // Intentando construir un Json programaticamente, hasta ahora nada
            Json::Object errmsg, obj;
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
		std::string escapeJsonString(const std::string& input)
        {
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
	

		/// *********************** ENTITY ******************************
		/// GetEntity: obtiene un registro y lo guarda en entity. Recibe el tipo de registro y el DbId
		bool GetEntity(const char* record_type, const char *display_name);
        /// GetEntity: obtiene un registro y lo guarda en entity usando JSON. Recibe el tipo de registro y el DbId
        std::string JSONGetEntity(const char* JSON_entity);

		/// GetFieldValue: Obtiene el campo del registro almancenado en entity
		char* GetFieldValue(const char* field);

        /// Devuelve valores de campo de JSON
        std::string JSONGetFieldStringValues(const char* JSON_field);

		/// SetFieldValue: Setea un campo del registro almancenado en entity
		char* SetFieldValue(const char* field, const char* value);
		std::string JSONSetFieldValues(const char* JSON_fields);

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

class CQEntity {
private:
	CQJSON session;
	IOAdEntityPtr  entity = NULL;
public:
	/// Constructor
	CQEntity(CQJSON jSession) { session = jSession; }
	~CQEntity(){ entity = NULL; }

	/// GetEntity: obtiene un registro y lo guarda en entity. Recibe el tipo de registro y el DbId
	std::string GetEntity(const char* JSON_entity);

	/// GetFieldValue: Obtiene el campo del registro almancenado en entity
    std::string GetFieldStringValues(const char* JSON_field);

	/// SetFieldValue: Setea un campo del registro almancenado en entity
    std::string SetFieldValues(const char* JSON_fields);

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

#endif CQJSON_H

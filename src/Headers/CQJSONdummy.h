/// CQJSONdummy.h
/// Clase de integración con ClearQuest con protocolo
/// JSON (JavaScript Object Notation)

#ifndef CQJSONdummy_H
#define CQJSONdummy_H

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include <Wt\Wstring>

#define JS(...) #__VA_ARGS__

/// Se omite la importación de los tipos especificados en esta
/// biblioteca. Este archivo ofrece solamente las funciones
/// básicas para poner a punto el resto del sistema sin tener
/// que tener instaladas las bibliotecas de ClearQuest.
/// Se deja la línea comentada como referencia.
/// #import "C:\\Program Files (x86)\\IBM\\RationalSDLC\\ClearQuest\\cqole.dll" no_namespace auto_rename

/// CQJSON: ClearQuest client class which uses a JSON interface
///
/// This class is a ClearQuest client class which uses a JSON interface to communicate
/// with the application view, which renders the received JSON data (and sends back
/// data using the corresponding WT widgets according to the data type).
///
class CQJSONdummy
{
private:
    ///	singleton (unique global instance)
    static CQJSONdummy *instance;

	//IOAdSessionPtr session = NULL;
    /// Reemplaza el puntero IOAdSessionPtr de ClearQuest
    char* session = NULL;
    //IOAdEntityPtr  entity = NULL;
    /// Reemplaza el puntero IOAdEntityPtr de ClearQuest
    char*  entity = NULL;

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
    //std::string GetParameters(IOAdResultSetPtr);

public:
    /// Constructor implícito (sin argumentos)
	CQJSONdummy();
    /// Constructor con argumentos para conectarse a base de datos
    CQJSONdummy(const char* login_name, const char* password,
                const char* database_name, const char* database_set)
    {
		UserLogon(login_name, password, database_name, database_set);
    }
    /// Destructor
    virtual ~CQJSONdummy();
    
    /// Devuelve siempre la misma instancia (patrón Singleton)
    static CQJSONdummy *getInstance();

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
    /// Para esta clase SIEMPRE va a estar conectado
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
	}

	/// Convierte los caracteres de Escape segun JSON 
	/// Nota: la misma funcion la realiza Wstd::string::jsstd::stringLiteral, cambiarlo y probarlo
	std::string escapeJsonString(const std::string& input)
    {
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
	//		return input.jsstd::stringLiteral();

    /// *********************** ENTITY ******************************
    /// Obtiene un registro y lo guarda en entity. Recibe el tipo de registro y el DbId
    bool GetEntity(const char* record_type, const char *display_name);
    /// Obtiene un registro y lo guarda en entity usando JSON. Recibe el tipo de registro y el DbId
    std::string JSONGetEntity(const char* JSON_entity);

    /// Obtiene el campo del registro almancenado en entity
    char* GetFieldValue(const char* field);

    /// Devuelve los valores de texto de un campo JSON
    std::string JSONGetFieldStringValues(const char* JSON_field);

};

#endif CQJSONdummy_H

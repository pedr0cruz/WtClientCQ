/// CQJSONdummy.h
/// Clase de integración con ClearQuest con protocolo JSON (JavaScript Object Notation)

#ifndef CQJSONdummy_H
#define CQJSONdummy_H

#include <iostream>
#include <sstream>
#include <string>

#include <Wt\Wstring>

#define JS(...) #__VA_ARGS__

// #pragma once
// #import "C:\\Program Files (x86)\\IBM\\RationalSDLC\\ClearQuest\\cqole.dll" no_namespace auto_rename

//using namespace Wt;
//using namespace std; 

/// Clase CQJSONdummy cuya responsabilidad es comunicarse con el servidor y
/// recibir la respuesta. Implementa el patrón Singleton. Esta es una
/// variante que no necesita los encabezados de ClearQuest y esa funcionalidad
/// es reeemplazada por funciones que no hacen nada, o muy poco.
class CQJSONdummy
{
private:
    /// SingletonGoF: Una sola instancia global
	static CQJSONdummy *instance;

	//IOAdSessionPtr session = NULL;
	//IOAdEntityPtr  entity = NULL;

	char* session = NULL;
	char* entity  = NULL;
    /// Indica que la conexion ya se ha establecido con la BD con UserLogon
	bool bConectado = false;
    /// Retorna el índice del operador especificado según una tabla interna de operadores de querys
	int GetCompOperator(const char *name)
    {
        char* CompOperators[] = { "\0", "EQ", "NEQ", "LT", "LTE", "GT", "GTE", "LIKE", "NOT_LIKE", 
                        "BETWEEN", "NOT_BETWEEN", "IS_NULL", "IS_NOT_NULL", "IN", "NOT_IN", "\0" };
        for (int i = 1; CompOperators[i]; i++) {
            if (0 == strcmp(name, CompOperators[i])) {
                return i;
            }
        }
        return 0;
    }
    /// Retorna el nombre del tipo de dato especificado por el índice recibido
	std::string GetColumnType(unsigned long type)
    {
		char* CTypes[] = { "\0", "STRING", "MULTILINE", "BINARY", "LONG", "DATETIME", "DOUBLE", "\0" };
		return CTypes[type];
	}

//	std::string GetParameters(IOAdResultSetPtr);

public:
    /// Constructor
	CQJSONdummy();
    /// Constructor con parámetros para identificar a un usuario y conectarlo a una base de datos
    CQJSONdummy(const char* login_name, const char* password, const char* database_name, const char* database_set)
    {
		UserLogon(login_name, password, database_name, database_set);
    }
    /// Destructor
	virtual ~CQJSONdummy();
	
    /// Devuelve siempre la misma instancia
    static CQJSONdummy *getInstance();

	/// UserLogon: permite la conexión a una BD de usuario
	bool UserLogon(const char* login_name, const char* password, const char* database_name, const char* database_set);
    /// TODO, FIX, FIXME, PENDIENTE, Comentario pendiente
	std::string JSONUserLogon(const char* JSON_connection);

	// GetEntity: obtiene un registro y lo guarda en entity. Recibe el tipo de registro y el DbId
	bool GetEntity(const char* record_type, const char *display_name);
    /// TODO, FIX, FIXME, PENDIENTE, Comentario pendiente
    std::string JSONGetEntity(const char* JSON_entity);

	/// GetFieldValue: Obtiene el campo del registro almancenado en entity
	char* GetFieldValue(const char* field);

    /// TODO, FIX, FIXME, PENDIENTE, Comentario pendiente
    std::string JSONGetFieldStringValues(const char* JSON_field);

    /// Ejecuta la consulta especificada como argumento
    std::string ExecuteQuery(char* query);
    /// TODO, FIX, FIXME, PENDIENTE, Comentario pendiente
    std::string JSONExecuteQuery(const std::string JSON_query);

	/// Devuelve la lista de nombres de queries, graficos y reportes del workspace
	std::vector<std::string> GetAllWorkspaceList();

    /// Devuelve la lista de elementos del workspece, pudiendo indicar el folder y el tipo
	std::vector<std::string> GetWorkspaceList(int folder, std::string tipo);
    /// TODO, FIX, FIXME, PENDIENTE, Comentario pendiente
    std::string JSONGetWorkspaceList(int folder, char* type);

    /// Devuelve la lista de nombres de queries, graficos y reportes del workspace usando JSON 
    std::string JSONGetAllWorkspaceList(char* JSON_connection);
    /// TODO, FIX, FIXME, PENDIENTE, Comentario pendiente
    std::string JSONGetAllFolderList(char* JSON_connection);

    /// Obtiene los nombres de los campos ??? FIXME HACK TODO
    bool GetFieldNames();
    /// Devuelve el estado de conexión. Esta variante SIEMPRE va devolver TRUE porque
    /// no utiliza la conexión a ClearQuest, sin autentificar al usuario.
	bool IsConnected() { return bConectado; }

	/// Devuelve el Json que corresponde una operación exitosa
	std::string jsonOK(Wt::WString msg)
    {
		std::string msgerr = Wt::WString("{\"clearquest\": {\"status\":\"ok\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
		return msgerr;
	}

    /// Devuelve el Json que corresponde a un error
    std::string jsonError(Wt::WString msg)
    {
		std::string msgerr = Wt::WString("{\"clearquest\": {\"status\":\"error\", \"description\":\"{1}\"}}").arg(msg).toUTF8();
		return msgerr;
	}

	/// Convierte los caracteres de Escape segun JSON 
	/// Nota: FIXME, PENDIENTE, TEST, HACK, la misma funcion 
    /// la realiza Wstd::string::jsstd::stringLiteral, cambiarlo y probarlo
	std::string escapeJsonString(const std::string& input)
    {
		std::ostringstream ss;
		for (auto iter = input.cbegin(); iter != input.cend(); iter++) {
			//C++98/03:
			//for (std::std::string::const_iterator iter = input.begin(); iter != input.end(); iter++) {
			switch (*iter) {
			case '\\':  ss << "\\\\";   break;
            case '"':   ss << "\\\"";   break;
            case '/':   ss << "\\/";    break;
			case '\b':  ss << "\\b";    break;
            case '\f':  ss << "\\f";    break;
            case '\n':  ss << "\\n";    break;
			case '\r':  ss << "\\r";    break;
            case '\t':  ss << "\\t";    break;
            default:    ss << *iter;    break;
			}
		}
		return ss.str();
	}
	//		return input.jsstd::stringLiteral();
};

//} // namespace

#endif CQJSONdummy_H

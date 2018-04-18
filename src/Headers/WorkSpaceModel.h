// WorskSpaceModel.h
//

#ifndef WORKSPACE_MODEL_H
#define WORKSPACE_MODEL_H

#include <Wt/WObject>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WModelIndex>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>

#ifdef MyDEBUG
#include "CQJSONdummy.h"
#else
#include "CQJSON.h"
#endif

///	WorkSpaceModel: Main Application Model.
/// This class inherits from a WT WStandardItemModel to implement 
/// a custom model.
class WorkSpaceModel : public Wt::WStandardItemModel ///< Guarda un modelo personalizado
{
public:
    /// Constructor
    WorkSpaceModel(Wt::WObject* parent);

    /// Destructor
    ~WorkSpaceModel();

    /// Llena el modelo con los datos del árbol
    bool fillModel();

protected:

#ifdef MyDEBUG
    /// Puntero a Objeto que se comunica con el servidor
    /// y que se implementa con el patrón Singleton. 
    /// Esta es una variante de la clase que no utiliza
    /// ni necesita Las bibliotecas de ClearQuest.
    CQJSONdummy* cqSession;
#else
    /// Puntero a Objeto que se comunica con el servidor
    /// y que se implementa con el patrón Singleton. 
    CQJSON* cqSession;
#endif

    ///  Elemento seleccionado
	Wt::WModelIndex wsItem_;
	/// Mapas para la descripcion de los elementos del WS
	std::map<std::string, Wt::WString> wsNameMap_;
    std::map<std::string, Wt::WStandardItem*> wsItemMap_;
    std::map<std::string, Wt::Json::Object*> jsonObjectMap_;

private:
    Wt::WStandardItem* createFolderItem(const Wt::WString& location, const std::string& wsId = std::string());
    Wt::WStandardItem* createElementItem(const Wt::WString& location, const std::string& wsId = std::string(), Wt::Json::Object &joItem = Wt::Json::Value());
};

#endif /// WORKSPACE_MODEL_H

/// WorskSpaceModel.h

#ifndef WORKSPACE_MODEL_H
#define WORKSPACE_MODEL_H

#pragma once

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
#   include "CQJSONdummy.h"
#else
#   include "CQJSON.h"
#endif

///	Main Application Model. This class inherits from 
/// WT::WStandardItemModel to implement a custom model.
class WorkSpaceModel : public Wt::WStandardItemModel
{
public:
    /// Constructor
    /// @param parent Wt::WObject* Puntero a objeto padre en el ciclo de vida del objeto
    WorkSpaceModel(Wt::WObject* parent);

    /// Destructor
    ~WorkSpaceModel();

    /// Actualiza modelo con los datos del árbol
    /// @return true en caso de éxito, false en caso de error
    bool fillModel();

protected:
    ///  DATOS ESPECÍFICOS de cada vista

    /// Puntero a Objeto que se comunica con el servidor y se implementa 
    /// con el patrón Singleton (GoF) para tener una sola instancia. 
#ifdef MyDEBUG
    /// Variante de la clase que no utiliza ni necesita Las bibliotecas de ClearQuest
    CQJSONdummy* cqSession;
#else
    /// Variante de la clase que utiliza y NECESITA Las bibliotecas de ClearQuest
    CQJSON* cqSession;
#endif

    ///  Elemento seleccionado
	Wt::WModelIndex wsItem_;

    /// Mapas para la descripcion de los elementos del WS
	std::map<std::string, Wt::WString> wsNameMap_;
    std::map<std::string, Wt::WStandardItem*> wsItemMap_;
    std::map<std::string, Wt::Json::Object*> jsonObjectMap_;

    /// FIN de DATOS ESPECÍFICOS de cada vista

private:
    Wt::WStandardItem* createFolderItem(const Wt::WString& location, const std::string& wsId = std::string());
    Wt::WStandardItem* createElementItem(const Wt::WString& location, const std::string& wsId = std::string(), Wt::Json::Object &joItem = Wt::Json::Value());
};

#endif /// WORKSPACE_MODEL_H

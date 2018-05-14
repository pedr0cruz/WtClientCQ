/// ResultSetsModel.h

#ifndef RESULTSETS_MODEL_H
#define RESULTSETS_MODEL_H

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
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

///	ResultSetsModel: Stores the data for a custom model. This class 
/// inherits from WStandardItemModel to implement a custom model.
class ResultSetsModel : public Wt::WStandardItemModel
{
public:
    /// Constructor
    /// @param parent Wt::WObject* Puntero a objeto padre en el ciclo de vida del objeto
    ResultSetsModel(Wt::WObject *parent);

    /// Destructor
    virtual ~ResultSetsModel();

    /// Selecciona la pestaña especificada
    /// @param selectedTabIndex int Indice de la pestaña actual, por defecto es 0
    /// @return bool true en caso de que haya cambio de pestaña, false en caso contrario
    bool fillModel(int selectedTabIndex = 0);

protected:
    ///  DATOS ESPECÍFICOS de cada modelo

    /// Puntero a Objeto que se comunica con el servidor y que se implementa con el patrón
    /// Singleton (GoF), pues se crea una sola instancia.
#ifdef MyDEBUG
    /// Variante de la clase que no utiliza ni necesita las bibliotecas de ClearQuest
    CQJSONdummy* cqSession;
#else
    /// Variante de la clase que utiliza y NECESITA las bibliotecas de ClearQuest
    CQJSON* cqSession;
#endif

    /// Solamente es necesario guardar la pestaña activa, 
    /// el modelo de cada pestaña guarda su estado.
    int currentTabIndex_;

    /// FIN de DATOS ESPECÍFICOS de cada modelo
};

#endif /// RESULTSETS_MODEL_H

// ResultSetsModel.h
//

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

///	ResultSetsModel: Stores the data for a custom model.
/// This class inherits from WStandardItemModel to implement
/// a custom model.
class ResultSetsModel : public Wt::WStandardItemModel ///< Guarda un modelo personalizado
{
public:
    /// Constructor.
    ResultSetsModel(Wt::WObject *parent);

    /// Destructor
    virtual ~ResultSetsModel();

    /// Selecciona la pestaña especificada
    bool fillModel(int selectedTabIndex = 0);

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

    /// Solamente es necesario guardar la pestaña activa, 
    /// el modelo de cada pestaña guarda su estado.
    int currentTabIndex_;
};

#endif /// RESULTSETS_MODEL_H

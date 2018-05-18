/// RecordSetsModel.h

#ifndef RECORDSETS_MODEL_H
#define RECORDSETS_MODEL_H

#include <Wt/WObject>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WModelIndex>
//#include <Wt/Json/Parser>
//#include <Wt/Json/Serializer>
//#include <Wt/Json/Object>
//#include <Wt/Json/Array>
//#include <Wt/Json/Value>

#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

///	Stores the data for a custom model. This class inherits 
/// from WStandardItemModel to implement a custom model.
class RecordSetsModel : public Wt::WStandardItemModel
{
public:
    /// Constructor
    /// @param rows Initial number of rows of the model
    /// @param cols Initial number of columns of the model
    /// @param parent Wt::WObject* Puntero a objeto padre para el ciclo de vida del objeto
    RecordSetsModel(int rows, int cols, Wt::WObject *parent);

    /// Destructor
    virtual ~RecordSetsModel();

    /// Actualiza el modelo asociado
    /// @param selectedTabIndex int Actualiza indice de pestaña seleccionada, por defecto 0
    /// @return bool true en caso de cambio de pestaña, false si se mantiene la misma
    bool fillModel(int selectedTabIndex = 0);

protected:

    /// DATOS ESPECÍFICOS de cada modelo

#ifdef MyDEBUG
    CQJSONdummy* cqSession;
#else
    CQJSON* cqSession;
#endif

    /// Solamente es necesario guardar la pestaña activa, 
    /// el modelo de cada pestaña guarda su estado.
    int currentTabIndex_;

    /// FIN de DATOS ESPECÍFICOS de cada modelo
};

#endif /// RECORDSETS_MODEL_H

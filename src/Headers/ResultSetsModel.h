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
/// This class inherits from WStandardItemModel to implement a custom model.
class ResultSetsModel : public Wt::WStandardItemModel ///< Guarda un modelo personalizado
{
public:

#ifdef MyDEBUG
	CQJSONdummy* cqSession;
#else
	CQJSON* cqSession;
#endif

    /// Constructor.
    ResultSetsModel(Wt::WObject *parent);

    /// Destructor
    virtual ~ResultSetsModel();

protected:
    /// Solamente es necesario guardar la pestaña activa, el modelo de cada pestaña guarda su estado
    int currentTabIndex_;
};


#endif /// RESULTSETS_MODEL_H

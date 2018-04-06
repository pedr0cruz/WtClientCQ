#ifndef RECORDSETS_MODEL_H
#define RECORDSETS_MODEL_H

#include <Wt/WObject>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WModelIndex>

#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

///	RecordSetsModel: Stores the data for a custom model.
/// This class inherits from WStandardItemModel to implement a custom model.
class RecordSetsModel : public Wt::WStandardItemModel ///< Guarda un modelo personalizado
{
public:

#ifdef MyDEBUG
    CQJSONdummy* cqSession;
#else
    CQJSON* cqSession;
#endif

    /// Constructor
	RecordSetsModel(Wt::WObject *parent);

    /// Destructor
    virtual ~RecordSetsModel();

protected:
	/// Solamente es necesario guardar la pesta�a activa, el modelo de cada pesta�a guarda su estado
    int currentTabIndex_;
};

#endif /// RECORDSETS_MODEL_H

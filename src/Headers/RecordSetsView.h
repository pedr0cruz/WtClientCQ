///  RecordSetsView.h

#ifndef RECORDSETS_VIEW_H
#define RECORDSETS_VIEW_H

#include <Wt/WContainerWidget>
#include <Wt/WTabWidget>

#include "TabWidget.h"
#include "RecordSetsModel.h"

///	Shows the data from the associated model. Inherits from WTabWidget 
/// to implement a view with tabs derived from WTabWidget.
class RecordSetsView : public Wt::WTabWidget
{
public:
    /// Constructor
    /// @param parent Wt::WContainerWidget* Puntero a objeto padre contenedor
    RecordSetsView(Wt::WContainerWidget *parent = 0);

    /// Destructor
    virtual ~RecordSetsView();

    /// Establece el modelo para esta vista
    /// @param model RecordSetsModel* Puntero a objeto de clase RecordSetsModel que implementa el modelo
    void setModel(RecordSetsModel* model);

private:
    ///  DATOS ESPECÍFICOS de cada tipo de vista

    RecordSetsModel* model_;

    /// FIN de DATOS ESPECÍFICOS de cada tipo de vista
};

#endif /// RECORDSETS_VIEW_H

// MyTreeViewModel.h

#pragma once

#include <Wt/WObject>
#include <Wt/WStandardItemModel>
#include <Wt/WStandardItem>
#include <Wt/WModelIndex>
#include <Wt/WModelIndex>
#include <Wt/Json/Parser>
#include <Wt/Json/Serializer>
#include <Wt/Json/Object>
#include <Wt/Json/Array>
#include <Wt/Json/Value>


class MyTreeViewModel 
//    : public Wt::WAbstractItemModel
    : public Wt::WStandardItemModel
{
public:
    MyTreeViewModel(Wt::WObject *parent);
    virtual ~MyTreeViewModel();

    //bool fillModel();

public:

#if 0
    /// Aqui vienen las funciones que deben ser implementadas

    /// Returns the child index for the given row and column
    virtual Wt::WModelIndex index(int row, int col, const Wt::WModelIndex & parent = Wt::WModelIndex()) const;

    /// Returns the parent for a model index
    virtual Wt::WModelIndex parent(const Wt::WModelIndex & index) const;

    /// methods that allow one to navigate the model
    virtual int columnCount(const Wt::WModelIndex & parent = Wt::WModelIndex()) const;

    /// Returns the number of rows 
    virtual int rowCount(const Wt::WModelIndex & parent = Wt::WModelIndex()) const;

    /// return the data for an item
    //cpp17::any Wt::WAbstractItemModel::data(const WModelIndex &  index, ItemDataRole role = ItemDataRole::Display) const;
    virtual boost::any data(const Wt::WModelIndex & index, Wt::ItemDataRole role = Wt::ItemDataRole::DisplayRole)  const;

    /// return row and column header data (optional)
    virtual boost::any headerData (int section, 
        Wt::Orientation orientation = Wt::Orientation::Horizontal, 
        Wt::ItemDataRole role = Wt::ItemDataRole::DisplayRole
        ) const;

    /// to indicate data options
    virtual Wt::WFlags<Wt::ItemFlag> flags(const Wt::WModelIndex & index) const;

#endif

protected:
    bool fillModel();

private:
    Wt::WStandardItem* createFolderItem(const Wt::WString& location, const std::string& wsId = std::string());
    Wt::WStandardItem* createElementItem(const Wt::WString& location, const std::string& wsId = std::string(), Wt::Json::Object &joItem = Wt::Json::Value());

    ///  Elemento seleccionado
    Wt::WModelIndex wsItem_;

    /// Mapas para la descripcion de los elementos del WS
    std::map<std::string, Wt::WString> name_map_;
    std::map<std::string, Wt::WStandardItem*> item_map_;
    std::map<std::string, Wt::Json::Object*> json_object_map_;

//    std::vector<int> columns_per_row_;
};

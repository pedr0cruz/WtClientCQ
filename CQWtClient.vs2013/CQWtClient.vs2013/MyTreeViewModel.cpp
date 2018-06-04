// ResultSetsModel.cpp

#include "stdafx.h"

#include "MyTreeViewModel.h"

#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

using std::string;
using namespace Wt;

MyTreeViewModel::MyTreeViewModel(Wt::WObject *parent) 
//  : Wt::WAbstractItemModel(parent)
    : WStandardItemModel(parent)
{
}


MyTreeViewModel::~MyTreeViewModel()
{
}

#if 0

// Returns the child index for the given row and column
WModelIndex MyTreeViewModel::index(int row, int col, const Wt::WModelIndex & parent) const
{
    return WAbstractItemModel::index(row, col, parent);
}

// Returns the parent for a model index
WModelIndex MyTreeViewModel::parent(const Wt::WModelIndex & index) const
{
    return WAbstractItemModel::parent(index);
}

// methods that allow one to navigate the model
int MyTreeViewModel::columnCount(const Wt::WModelIndex & parent) const
{
    auto row = parent.row();
    if (row < 0 || row >= columns_per_row_.size()) {
        return -1;
    }
    return columns_per_row_[row];

}

// Returns the number of rows 
int MyTreeViewModel::rowCount(const Wt::WModelIndex & parent) const
{
    //return WAbstractItemModel::rowCount(parent);
    return 1;
}

// return the data for an item
//cpp17::any Wt::WAbstractItemModel::data(const WModelIndex &  index, ItemDataRole role = ItemDataRole::Display) const;
boost::any MyTreeViewModel::data(const Wt::WModelIndex & index, Wt::ItemDataRole role)  const
{
    return WAbstractItemModel::data(index, role);
}

// return row and column header data (optional)
boost::any MyTreeViewModel::headerData(int section, Wt::Orientation orientation, Wt::ItemDataRole role) const
{
    return WAbstractItemModel::headerData(section, orientation, role);
}

// to indicate data options
Wt::WFlags<Wt::ItemFlag> MyTreeViewModel::flags(const Wt::WModelIndex & index) const
{
    return WAbstractItemModel::flags(index);
}

#endif

// Crea un elemento folder en el modelo
WStandardItem* MyTreeViewModel::createElementItem(const WString& location,
    const std::string& folderId, Json::Object &joItem)
{
    WStandardItem *result = new WStandardItem(location);
    Json::Object *json = new Json::Object(joItem);

    result->setData(boost::any(folderId));
    result->setFlags(result->flags() | ItemIsSelectable);
    result->setFlags(result->flags() | ItemIsDragEnabled); // Flag para notificación de nuevo folder
    name_map_[folderId] = location;	// AL fiinal quitar esto
    //	  folderItemMap_[folderId] = result;	// AL fiinal quitar esto
    json_object_map_[folderId] = json;

    result->setIcon("icons/file.gif");
    return result;
}

// Crea un elemento query en el modelo
WStandardItem* MyTreeViewModel::createFolderItem(const WString& location,
    const std::string& folderId)
{
    WStandardItem *result = new WStandardItem(location);

    if (!folderId.empty()) {
        result->setData(boost::any(folderId));
        result->setFlags(result->flags() | ItemIsDropEnabled); // No se necesita
        result->setFlags(result->flags().clear(ItemIsDragEnabled));
        name_map_[folderId] = location; // Al fiinal quitar esto
        item_map_[folderId] = result;
    }
    else
        result->setFlags(result->flags().clear(ItemIsSelectable));

    result->setIcon("icons/folder.gif");
    return result;
}

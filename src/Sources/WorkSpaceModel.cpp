// WorkSpaceModel.cpp
// Representa el Modelo en el MVC del WorkSpace
// Se conecta con el CQ y contruye el arbol de elementos JSON del WS

#include <boost/algorithm/string/replace.hpp>

#include "WorkSpaceModel.h"

//#include "CQJSON.h"
#ifdef MyDEBUG
#	include "CQJSONdummy.h"
#else
#	include "CQJSON.h"
#endif

// Constructor
WorkSpaceModel::WorkSpaceModel(WObject* parent) : 
										WStandardItemModel(0, 1, parent)
{
#ifdef MyDEBUG
	cqSession = CQJSONdummy::getInstance();
#else
	cqSession = CQJSON::getInstance();
#endif
	cqSession->UserLogon("admin", "", "SAMPL", "SAMPLCNX");
}

// Llena el WorkSpace desde el CQ
bool WorkSpaceModel::fillModel()
{
	WStandardItem *level1, *level2, *level3, *level4;

	if (!cqSession->IsConnected()) return false; // Comprueba el CQ

	// Para colocar el par de iconos de las carpetas
	//Wt::WIconPair *folderIcon = new WIconPair("icons/yellow-folder-closed.png",
	//		"icons/yellow-folder-open.png", false);
	// WTreeNode *node = new WTreeNode("Furniture", folderIcon);

	Json::Object JsonObject, result;
	string JsonFolderList = cqSession->JSONGetAllFolderList(JS({ "clearquest": {} }));
	Json::parse(JsonFolderList, result);

	/*{ "clearquest": { "db": "SAMPLE", "repo" : "SAMPLE", "login" : "cq_user",
	"publicfolder" : [{ "folder":"Public Queries", "name" : "Defects by State", "path" : "Aging charts", "type" : "FOLDER" }, { ... }],
	"personalfolder" : [{...}, { ... }] }}*/
	JsonObject = result.get("clearquest");
	Json::Array publicFolders = JsonObject.get("publicfolder");

	// level1 = "Principal"
	//folderModel_->appendRow(level1 = createFolderItem("Principal"));
	level1 = invisibleRootItem();
	wsItemMap_["Public_Queries"] = level1; // Puntero a Principal
	for (unsigned index = 0; index < publicFolders.size(); /*index++*/){
		Json::Object aFolder = publicFolders[index];
		string sPath = WString(aFolder.get("path")).toUTF8();
		string sName = WString(aFolder.get("name")).toUTF8();
		if (sPath == "") {// Pertenece al padre
			string folderName = WString(aFolder.get("name")).toUTF8(); // Nombre
			string folderID = WString(aFolder.get("folder")).toUTF8() + "/" + folderName;
			boost::algorithm::replace_all(folderID, " ", "_"); // ID sin espacios
			level1->appendRow(level2 = createFolderItem(folderName, folderID));
			publicFolders.erase(publicFolders.begin() + index);
			//publicFolders[index] = Json::Value(); // Elimina el elemento del arreglo
		}
		else index++;
		// Guardar en otro arreglo de 2 nivel y despues en un arreglo de 3 nivel hasta el 5to
	}
	// Nivel 2 recorre el nivel 1 para ver si tiene algun hijo
	for (auto index1 = 0; index1 < level1->rowCount(); index1++){
		level2 = level1->child(index1);
		WString sLevel2 = level2->text();
		// Recorrer nuevamente el arreglo que quedo
		for (unsigned index2 = 0; index2 < publicFolders.size(); /*index2++*/){
			Json::Object aFolder = publicFolders[index2];
			if (!aFolder.empty()){
				WString sPath2 = WString(aFolder.get("path")).toUTF8();
				if (sPath2 == sLevel2) {// Pertenece al padre
					string folderName = WString(aFolder.get("name")).toUTF8(); // Nombre
					string folderID = WString(aFolder.get("folder")).toUTF8() + "/" + sPath2.toUTF8() + "/" + folderName;
					boost::algorithm::replace_all(folderID, " ", "_"); // ID sin espacios
					level2->appendRow(level3 = createFolderItem(folderName, folderID));
					publicFolders.erase(publicFolders.begin() + index2);
				}
				else index2++;
			}
		}
	}
	// Nivel 3: recorre el arreglo que queda para ver donde lo debo poner
	for (unsigned index3 = 0; index3 < publicFolders.size(); index3++){
		Json::Object aFolder = publicFolders[index3];
		string sPath3 = WString(aFolder.get("path")).toUTF8(); // Obtendo la ruta
		string sPath3level1 = sPath3.substr(0, sPath3.find('/')); // Obtengo el nivel1
		sPath3 = sPath3.substr(sPath3.find('/') + 1); // Obtendo el nivel2
		// Busco en el nivel 1
		for (auto index1 = 0; index1 < level1->rowCount(); index1++){
			level2 = level1->child(index1);
			WString level2name = level2->text();
			if (level2name == sPath3level1) {  // Encontro el padre
				for (auto index2 = 0; index2 < level2->rowCount(); index2++){
					level3 = level2->child(index2);
					WString sLevel3 = level3->text();
					// Recorrer nuevamente el arreglo que quedo
					// Buscamos en el map
					if (sPath3 == sLevel3){ // Pertenece al hijo
						string folderName = WString(aFolder.get("name")).toUTF8(); // Nombre
						string folderID = WString(aFolder.get("folder")).toUTF8() + "/" + sPath3 + "/" + folderName;
						boost::algorithm::replace_all(folderID, " ", "_"); // ID sin espacios
						level3->appendRow(level4 = createFolderItem(folderName, folderID));
						publicFolders.erase(publicFolders.begin() + index3);
					}
				}
			}
		}
	}
	// Agrega queries, charts y reports    
	string JsonQueyList = cqSession->JSONGetAllWorkspaceList(JS({ "clearquest": {} }));
	Json::parse(JsonQueyList, result);
	// To-Do: Chequear posibles errores en la respuesta

	Json::Object joCQ = result.get("clearquest");
	Json::Object joFolder = joCQ.get("publicfolder");
	Json::Array publicQueries = joFolder.get("queries");
	for (unsigned index = 0; index < publicQueries.size(); index++){
		Json::Object aQuery = publicQueries[index];
		string sName = WString(aQuery.get("name")).toUTF8();
		string sFolder = WString(aQuery.get("folder")).toUTF8();
		string sPath = WString(aQuery.get("path")).toUTF8();
		boost::algorithm::replace_all(sFolder, " ", "_"); // Path sin espacios
		WStandardItem *aFolder = wsItemMap_[sFolder]; // Obtiene el folder del mapa
		aFolder->appendRow(createElementItem(sName, sPath, aQuery));	// Agrega el elemento al folder
	}

	setHeaderData(0, Horizontal, boost::any(std::string("Explorador")));

	return true;
}

// Crea un elemento folder en el modelo
WStandardItem* WorkSpaceModel::createElementItem(const WString& location,
	const std::string& folderId, Json::Object &joItem)
{
	WStandardItem *result = new WStandardItem(location);
	Json::Object *json = new Json::Object(joItem);

	result->setData(boost::any(folderId));
	result->setFlags(result->flags() | ItemIsSelectable);
	result->setFlags(result->flags() | ItemIsDragEnabled); // Flag para notificación de nuevo folder
	wsNameMap_[folderId] = location;	// AL fiinal quitar esto
	//	  folderItemMap_[folderId] = result;	// AL fiinal quitar esto
	jsonObjectMap_[folderId] = json;

	result->setIcon("icons/file.gif");
	return result;
}

// Crea un elemento query en el modelo
WStandardItem* WorkSpaceModel::createFolderItem(const WString& location,
	const std::string& folderId)
{
	WStandardItem *result = new WStandardItem(location);

	if (!folderId.empty()) {
		result->setData(boost::any(folderId));
		result->setFlags(result->flags() | ItemIsDropEnabled); // No se necesita
		result->setFlags(result->flags().clear(ItemIsDragEnabled));
		wsNameMap_[folderId] = location; // Al fiinal quitar esto
		wsItemMap_[folderId] = result;
	}
	else 	
		result->setFlags(result->flags().clear(ItemIsSelectable));

	result->setIcon("icons/folder.gif");
	return result;
}

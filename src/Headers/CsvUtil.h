/// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2008 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef CSV_UTIL_H_
#define CSV_UTIL_H_

#include <iostream>

namespace Wt {
  class WObject;
  class WAbstractItemModel;
  class WStandardItemModel;
}

/// Lee datos en formato CSV de corriente de datos de entrada (istream)
/// @param f std::istream& Corriente de datos de entrada
/// @param model Puntero a modelo que consumirá los datos
/// @param numRows Cantidad de filas a leer. El valor por defecto es -1, que lee todas
/// @param firstLineIsHeaders Si true (valor por defecto) la primera fila son los nombres de las columnas
extern void readFromCsv(std::istream& f, Wt::WAbstractItemModel *model,
                        int numRows = -1, bool firstLineIsHeaders = true);

/// Convierte datos en formato CSV de corriente de datos de entrada (istream) a modelo
/// @param csvFile const std::string&  Cadena de texto que es el nombre del archivo a leer
/// @param parent Puntero a objeto de clase Wt::WObject o derivada que es el padre del modelo a crear
/// @param firstLineIsHeaders Si true (valor por defecto) la primera fila son los nombres de las columnas
/// @return Puntero a instancia de clase Wt::WStandardItemModel * que es el modelo creado
extern Wt::WStandardItemModel *csvToModel(const std::string& csvFile,
                                            Wt::WObject *parent,
                                            bool firstLineIsHeader = true);

#endif // CSV_UTIL_H_

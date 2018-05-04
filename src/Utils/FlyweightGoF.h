//  Flyweight.h
//  Patron de Diseño Flyweight

#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#pragma once

class FlyweightGoF
{
public:
	FlyweightGoF();
	virtual ~FlyweightGoF();
};

/// Clase FlyweightFactory: Define la funcionalidad necesaria para crear una clase 
/// 
///
class FlyweightFactoryGoF
{
public:
	/// Un objeto ligero para cada columna y uno para cada fila,
	/// con este enumerador se especifica el tipo de objeto.
	enum FlyweightType { FW_COL, FW_ROW };
    /// Función virtual que será llamada desde las instancias de la clase Decorator
	virtual FlyweightGoF* getFlyweight(FlyweightType) = 0;
protected:
};

#endif // #ifndef FLYWEIGHT_H

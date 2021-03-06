/*
 *  PhysicalObjectFactory.h
 *  roborobo
 *
 *  Created by Nicolas on 25/4/2014.
 *
 */

#ifndef PHYSICALOBJECTFACTORY_H
#define PHYSICALOBJECTFACTORY_H

class PhysicalObject;

class PhysicalObjectFactory
{
	private :
				static int _clumpId_A;
				static int _clumpId_B;
        static int _nextId;

	public :
				static void makeObjectNormal( int type = 0 ); // default type is zero. Properties file value always override.
        static void makeObject( int type = 0, bool clumped = false ); // default type is zero. Properties file value always override.
        static int getNextId();
        static int getNbOfTypes();



};

#endif

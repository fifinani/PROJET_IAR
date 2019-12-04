/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef IARWORLDOBSERVER_H
#define IARWORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class IARWorldObserver : public WorldObserver
{
	protected:
		
	public:
		IARWorldObserver( World *__world );
		~IARWorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif


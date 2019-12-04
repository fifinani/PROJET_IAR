/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#ifndef EXO1WORLDOBSERVER_H
#define EXO1WORLDOBSERVER_H

#include "Observers/WorldObserver.h"

class World;

class Exo1WorldObserver : public WorldObserver
{
	protected:
		
	public:
		Exo1WorldObserver( World *__world );
		~Exo1WorldObserver();
				
		void initPre();
        void initPost();

        void stepPre();
        void stepPost();
		
};

#endif


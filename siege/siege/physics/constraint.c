#define SG_BUILD_LIBRARY
#include <siege/physics/constraint.h>
#include <siege/modules/physics.h>

#include <stdlib.h>

void sgPhysicsConstraintDestroy(SGPhysicsConstraint* constraint)
{
    if(constraint == NULL)
        return;

    /*if(_sg_modPhysics.sgmPhysicsConstraintDestroy != NULL)
        _sg_modPhysics.sgmPhysicsConstraintDestroy(constraint->handle);*/

    free(constraint);
}

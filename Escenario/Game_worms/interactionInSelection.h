#ifndef INTERACTIONINSELECTION_H
#define INTERACTIONINSELECTION_H

#include "thread.h"
#include "protocol.h"
#include "mapSelection.h"

class InteractionInSelection: Thread
{
public:
    explicit InteractionInSelection(Protocol* protocol, MapSelection* selection);

    void run();

private:
    Protocol* protocol;
    MapSelection selection;
};

#endif

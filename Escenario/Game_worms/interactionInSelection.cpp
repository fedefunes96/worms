#include "interactionInSelection.h"

InteractionInSelection::InteractionInSelection(Protocol *protocol, MapSelection *selection)
{
    this->protocol = protocol;
    this->selection = selection;
}

void InteractionInSelection::run()
{
    int8_t id;
    int8_t cantMax;
    int8_t cantActual;
    protocol->recvRoomCaratc(&id,&cantMax,&cantActual);
    std::string s;
    s<<cantActual;
    s<< '/';
    s<<cantMax;
    this->selection.adjustView(id,s);
}

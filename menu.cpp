#include <U8g2lib.h>
#include "menu.h"

void IMenu::setParentMenu(IMenu *parent)
{
    _parent = parent;
}

const char **IMenu::options()
{
    return opts;
}

void IMenu::reactivate()
{
}



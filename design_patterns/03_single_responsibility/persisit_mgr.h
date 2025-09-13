#ifndef _FREDRIC_PERSISIT_MGR_H_
#define _FREDRIC_PERSISIT_MGR_H_

#include "journal.h"

struct PersisitMgr {
    static void save(Journal const& j, std::string const& file_name);
};
#endif
/*
 * Copyright (C) 2005-2008 MaNGOS <http://www.mangosproject.org/>
 *
 * Copyright (C) 2008 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef TRINITYCORE_COMMON_H
#define TRINITYCORE_COMMON_H

// config.h needs to be included 1st
// TODO this thingy looks like hack ,but its not, need to
// make separate header however, because It makes mess here.
#ifdef HAVE_CONFIG_H
// Remove Some things that we will define
// This is in case including another config.h
// before trinity config.h
#ifdef PACKAGE
#undef PACKAGE
#endif //PACKAGE
#ifdef PACKAGE_BUGREPORT
#undef PACKAGE_BUGREPORT
#endif //PACKAGE_BUGREPORT
#ifdef PACKAGE_NAME
#undef PACKAGE_NAME
#endif //PACKAGE_NAME
#ifdef PACKAGE_STRING
#undef PACKAGE_STRING
#endif //PACKAGE_STRING
#ifdef PACKAGE_TARNAME
#undef PACKAGE_TARNAME
#endif //PACKAGE_TARNAME
#ifdef PACKAGE_VERSION
#undef PACKAGE_VERSION
#endif //PACKAGE_VERSION
#ifdef VERSION
#undef VERSION
#endif //VERSION
# include "config.h"
#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION
#undef VERSION
#endif //HAVE_CONFIG_H

#include "Define.h"

#include "Debugging/Errors.h"

#if COMPILER == COMPILER_MICROSOFT

#pragma warning(disable:4996)

#ifndef __SHOW_STUPID_WARNINGS__

#pragma warning(disable:4244)

#pragma warning(disable:4267)

#pragma warning(disable:4800)

#pragma warning(disable:4018)

#pragma warning(disable:4311)

#pragma warning(disable:4305)

#pragma warning(disable:4005)
#endif                                                      // __SHOW_STUPID_WARNINGS__
#endif                                                      // __GNUC__

#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <signal.h>

#if PLATFORM == PLATFORM_WINDOWS
#define STRCASECMP stricmp
#else
#define STRCASECMP strcasecmp
#endif

#include <set>
#include <list>
#include <string>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>
#include <memory>

#include "Threading/LockedQueue.h"

#if PLATFORM == PLATFORM_WINDOWS
#  define FD_SETSIZE 4096
// XP winver - needed to compile with standard leak check in MemoryLeaks.h
// uncomment later if needed
//#define _WIN32_WINNT 0x0501
#  include <ws2tcpip.h>
//#undef WIN32_WINNT
#else
#  include <sys/types.h>
#  include <sys/ioctl.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <unistd.h>
#  include <netdb.h>
#endif

#if COMPILER == COMPILER_MICROSOFT

#include <float.h>

#define snprintf _snprintf
#define atoll _atoi64
#define vsnprintf _vsnprintf
#define strdup _strdup
#define llabs _abs64

#else

#define stricmp strcasecmp
#define strnicmp strncasecmp

#endif

inline float finiteAlways(float f) { return std::isfinite(f) ? f : 0.0f; }

inline unsigned long atoul(char const* str) { return strtoul(str, nullptr, 10); }
inline unsigned long long atoull(char const* str) { return strtoull(str, nullptr, 10); }

#define STRINGIZE(a) #a

enum TimeConstants
{
    SECOND = 1,
    MINUTE = 60,
    HOUR   = MINUTE*60,
    DAY    = HOUR*24,
    WEEK   = DAY*7,
    MONTH  = DAY*30,
    YEAR   = MONTH*12,
    IN_MILLISECONDS = 1000
};

enum AccountTypes
{
    SEC_PLAYER         = 0,
    SEC_GAMEMASTER1    = 1,
    SEC_GAMEMASTER2    = 2,
    SEC_GAMEMASTER3    = 3,
    SEC_ADMINISTRATOR  = 4,
    SEC_SUPERADMIN     = 5,
    SEC_CONSOLE        = 6, // must be always last in list, accounts must have less security level always also
};
/*
enum GMGroups
{
    GMGROUP_VIDEO   = 1, //can't see invisible units/gobjects
    GMGROUP_ANIM    = 2, //normal gm minus some commands
    GMGROUP_PTRGM   = 3, //only gm if CONFIG_TESTSERVER_ENABLE
    GMGROUP_TESTER  = 4, //can only spectate to track bugs
    GMGROUP_SPY     = 5, //can't be seen by other gm's with lesser ranks
};
*/
enum LocaleConstant
{
    LOCALE_enUS = 0,
    LOCALE_koKR = 1,
    LOCALE_frFR = 2,
    LOCALE_deDE = 3,
    LOCALE_zhCN = 4,
    LOCALE_zhTW = 5,
    LOCALE_esES = 6,
    LOCALE_esMX = 7,
    LOCALE_ruRU = 8
};

const uint8 TOTAL_LOCALES = 9;
#define MAX_LOCALE 8
#define MAX_ACCOUNT_TUTORIAL_VALUES 8

#define DEFAULT_LOCALE LOCALE_enUS

extern char const* localeNames[TOTAL_LOCALES];

LocaleConstant GetLocaleByName(const std::string& name);

typedef std::vector<std::string> StringVector;

// we always use stdlibc++ std::max/std::min, undefine some not C++ standard defines (Win API and some pother platforms)
#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif

#define MAX_QUERY_LEN 32*1024

namespace Trinity
{
    //! std::make_unique implementation (TODO: remove this once C++14 is supported)
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique(Args&& ...args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif


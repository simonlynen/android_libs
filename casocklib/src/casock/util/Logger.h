/*
 * casocklib - An asynchronous communication library for C++
 * ---------------------------------------------------------
 * Copyright (C) 2010 Leandro Costa
 *
 * This file is part of casocklib.
 *
 * casocklib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * casocklib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with casocklib. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file casock/util/Logger.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_UTIL__LOGGER_H_
#define __CASOCKLIB__CASOCK_UTIL__LOGGER_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdio>

#include <string>

#ifdef USE_THREADS
#include "casock/util/Lockable.h"
#endif

#include "casock/util/types.h"


typedef enum e_debug_level
{
  SILENT        =-1,
  NO_DEBUG      = 0,
  LOW_LEVEL     = 1,
  MEDIUM_LEVEL  = 2,
  HIGH_LEVEL    = 3,
  MAX_LEVEL     = 4,
  DISABLE       = 5
} e_debug;

#define  LOGGER  Logger::getInstance ()
#define LOGMSG  Logger::getInstance ()->print


#ifdef USE_THREADS
class Logger : private Lockable
#else
class Logger
#endif
{
  public:
    static  Logger*  getInstance ();
    static  void  finalize ();

  protected:
    Logger (const Logger&);
    Logger (const e_debug &debug = NO_DEBUG,
        const std::string &log_file = "", FILE *pFP = NULL);

  public:
    virtual  ~Logger ();

  protected:
    Logger& operator=(const Logger& rLogger);

  private:
    void  openLogFile ();
    void  closeLogFile ();

  public:
    void  setDebugLevel (e_debug debug);
    void  setLogFile (const std::string &file);
    void  print (e_debug debug, char *msg, ...);

  public:
#ifdef USE_MEM_SIZE
    virtual  const  uint64  getMemSize ()  const;
#endif

  private:
    static  Logger*  mspInstance;

  private:
    e_debug     m_debug_level;
    std::string m_log_file;
    FILE*       mpFP;

  public:
    static  const uint32  MSG_BUFF_SIZE     = BUFSIZ;  
    static  const uint32  DATE_BUFF_SIZE    = 32;  
#ifndef HAVE_SYS_SYSCALL_H
  #ifdef _LP64
    static  const uint32  GETTID_SYSCALL_ID = 186;
  #else
    static  const uint32  GETTID_SYSCALL_ID = 224;
  #endif
#endif
};

#endif // __CASOCKLIB__CASOCK_UTIL__LOGGER_H_

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
 * \file examples/proactor/asio/ftp/FTPFile.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__EXAMPLES_FTP__FTP_FILE_H_
#define __CASOCKLIB__EXAMPLES_FTP__FTP_FILE_H_

#include <string>
#include <sstream>
#include <fstream>

namespace examples {
  namespace ftp {
    class FTPFile
    {
      public:
        FTPFile (const std::string& name) : mName (name) , mSize (0), mBuffer (NULL) { }

        void setSize (const size_t& size) { mSize = size; }
        void setBuffer (char* buffer) { mBuffer = buffer; }

        const char* getBuffer () const { return mBuffer; }
        const size_t& getSize () const { return mSize; }

        void save ()
        {
          std::ofstream os (mName.c_str (), std::ios::binary);
          os.write (mBuffer, mSize);
          os.close ();
        }

        const std::string toString ()
        {
          std::stringstream ss;

          ss << "name [";
          ss << mName;
          ss << "], size [";
          ss << mSize;
          ss << "]";

          return ss.str ();
        }

      private:
        std::string mName;
        size_t      mSize;
        char*       mBuffer;
    };
  }
}

#endif // #define __CASOCKLIB__EXAMPLES_FTP__FTP_FILE_H_

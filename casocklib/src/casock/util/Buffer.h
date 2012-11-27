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
 * \file casock/util/Buffer.h
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#ifndef __CASOCKLIB__CASOCK_UTIL__BUFFER_H_
#define __CASOCKLIB__CASOCK_UTIL__BUFFER_H_

#include <cstring>

namespace casock {
	namespace util {
		class Buffer
		{
			public:
				Buffer (const size_t& size = DEFAULT_SIZE);
				Buffer (const char* buff, const size_t& size);
				Buffer (const Buffer& rBuffer);
				virtual ~Buffer ();

			public:
				Buffer& operator=(const Buffer& rBuffer);
				const bool operator==(const char* buff) const;

			public:
				const size_t& size () const;
				const char* data () const;
        char* buff (const size_t& offset = 0);
				void clear ();

			private:
				size_t m_size;
				char* m_buff;

			public:
				static const size_t DEFAULT_SIZE = 1024;
		};
	}
}

#endif // __CASOCKLIB__CASOCK_UTIL__BUFFER_H_

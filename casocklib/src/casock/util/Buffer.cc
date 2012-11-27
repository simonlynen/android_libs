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
 * \file casock/util/Buffer.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/util/Buffer.h"

namespace casock {
	namespace util {
		const size_t Buffer::DEFAULT_SIZE;

		Buffer::Buffer (const size_t& s)
			: m_size (s), m_buff (new char[m_size])
		{
			clear ();
		}

		Buffer::Buffer (const char* buff, const size_t& s)
			: m_size (s), m_buff (new char[m_size])
		{
			strncpy (m_buff, buff, m_size);
		}

		Buffer::Buffer (const Buffer& rBuffer)
			: m_size (rBuffer.size ()), m_buff (new char[m_size])
		{
			*this = rBuffer;
		}

		Buffer::~Buffer ()
		{
			delete[] m_buff;
		}

		Buffer& Buffer::operator=(const Buffer& rBuffer)
		{
			strncpy (m_buff, rBuffer.data (), m_size);
			return *this;
		}

		const bool Buffer::operator==(const char* buff) const
		{
			return ! strncmp (m_buff, buff, m_size);
		};

		const size_t& Buffer::size () const
		{
			return m_size;
		}

		const char* Buffer::data () const
		{
			return m_buff;
		}

		char* Buffer::buff (const size_t& offset)
		{
			return m_buff + offset;
		}

		void Buffer::clear ()
		{
			bzero (m_buff, m_size);
		}
	}
}

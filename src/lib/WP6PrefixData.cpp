/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpd
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2002 William Lachance (wrlach@gmail.com)
 * Copyright (C) 2002-2003 Marc Maurer (uwog@uwog.net)
 *
 * For minor contributions see the git repository.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU Lesser General Public License Version 2.1 or later
 * (LGPLv2.1+), in which case the provisions of the LGPLv2.1+ are
 * applicable instead of those above.
 *
 * For further information visit http://libwpd.sourceforge.net
 */

/* "This product is not manufactured, approved, or supported by
 * Corel Corporation or Corel Corporation Limited."
 */

#include "WP6PrefixData.h"

#include <vector>

#include "WP6PrefixIndice.h"
#include "WP6PrefixDataPacket.h"
#include "WP6FontDescriptorPacket.h"
#include "WP6DefaultInitialFontPacket.h"
#include "libwpd_internal.h"

WP6PrefixData::WP6PrefixData(librevenge::RVNGInputStream *input, WPXEncryption *encryption, const int numPrefixIndices) :
	m_prefixDataPacketHash(),
	m_prefixDataPacketTypeHash(),
	m_defaultInitialFontPID((-1))
{
	if (!numPrefixIndices)
	{
		WPD_DEBUG_MSG(("WordPerfect: constructing called without any prefix\n"));
		return;
	}
	unsigned short i;
	std::vector<WP6PrefixIndice> prefixIndiceArray;
	prefixIndiceArray.reserve(numPrefixIndices - 1);
	for (i=1; i<numPrefixIndices; i++)
	{
		WPD_DEBUG_MSG(("WordPerfect: constructing prefix indice 0x%x\n", i));
		prefixIndiceArray.emplace_back(input, encryption, i);
	}

	for (i=1; i<numPrefixIndices; i++)
	{
		WPD_DEBUG_MSG(("WordPerfect: constructing prefix packet 0x%x\n", i));
		auto prefixDataPacket = WP6PrefixDataPacket::constructPrefixDataPacket(input, encryption, prefixIndiceArray[(i-1)]);
		if (prefixDataPacket)
		{
			m_prefixDataPacketHash[i] = prefixDataPacket;
			m_prefixDataPacketTypeHash.insert(std::make_pair(prefixIndiceArray[i-1].getType(), prefixDataPacket));
			if (dynamic_cast<WP6DefaultInitialFontPacket *>(prefixDataPacket.get()))
				m_defaultInitialFontPID = i;
		}
	}
}

WP6PrefixData::~WP6PrefixData()
{
}

const WP6PrefixDataPacket *WP6PrefixData::getPrefixDataPacket(const int prefixID) const
{
	auto pos = m_prefixDataPacketHash.find(prefixID);
	if (pos != m_prefixDataPacketHash.end())
		return pos->second.get();
	else
		return nullptr;
}

std::pair<MPDP_CIter, MPDP_CIter> WP6PrefixData::getPrefixDataPacketsOfType(const int type) const
{
	std::pair<MPDP_CIter, MPDP_CIter> tempPair = m_prefixDataPacketTypeHash.equal_range(type);

	return tempPair;
}
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */

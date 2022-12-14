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
 * Copyright (C) 2002 Marc Maurer (uwog@uwog.net)
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

#ifndef WP6OUTLINESTYLEPACKET_H
#define WP6OUTLINESTYLEPACKET_H
#include "WP6PrefixDataPacket.h"
#include "WP6FileStructure.h"
#include "WP6Listener.h"

class WP6OutlineStylePacket : public WP6PrefixDataPacket
{
public:
	WP6OutlineStylePacket(librevenge::RVNGInputStream *input, WPXEncryption *encryption, int id, unsigned dataOffset, unsigned dataSize);
	~WP6OutlineStylePacket() override;
	void _readContents(librevenge::RVNGInputStream *input, WPXEncryption *encryption) override;
	void parse(WP6Listener *listener) const override;

private:
	unsigned short m_numPIDs;
	unsigned short m_outlineHash;
	unsigned char m_numberingMethods[WP6_NUM_LIST_LEVELS];
	unsigned char m_outlineFlags;
	unsigned char m_tabBehaviourFlag;
};
#endif /* WP6OUTLINESTYLEPACKET_H */
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */

/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* libwpd
 * Version: MPL 2.0 / LGPLv2.1+
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Major Contributor(s):
 * Copyright (C) 2004 Marc Maurer (uwog@uwog.net)
 * Copyright (C) 2005-2006 Fridrich Strba (fridrich.strba@bluewin.ch)
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

#ifndef WP3VARIABLELENGTHGROUP_H
#define WP3VARIABLELENGTHGROUP_H

#include "WP3Part.h"

class WPXEncryption;

class WP3VariableLengthGroup : public WP3Part
{
public:
	WP3VariableLengthGroup(); // WP3VariableLengthGroup should _never_ be constructed, only its inherited classes
	~WP3VariableLengthGroup() override {}

	static WP3VariableLengthGroup *constructVariableLengthGroup(librevenge::RVNGInputStream *input, WPXEncryption *encryption, const unsigned char group);

	static bool isGroupConsistent(librevenge::RVNGInputStream *input, WPXEncryption *encryption, const unsigned char group);

protected:
	void _read(librevenge::RVNGInputStream *input, WPXEncryption *encryption);
	virtual void _readContents(librevenge::RVNGInputStream * /* input */, WPXEncryption * /* encryption */) {} // we don't always need more information than that provided generically

	unsigned char getSubGroup() const
	{
		return m_subGroup;
	}
	unsigned short getSize() const
	{
		return m_size;
	}

private:
	unsigned char m_subGroup;
	unsigned short m_size;
};

#endif /* WP3VARIABLELENGTHGROUP_H */
/* vim:set shiftwidth=4 softtabstop=4 noexpandtab: */

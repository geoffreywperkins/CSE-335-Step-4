/**
 * \file ResetFan.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * 
 */

#pragma once
#include "TileVisitor.h"
#include "TileFan.h"

/**
 * Derived from TileVisitor
 * runs the fan method ResetFan(), which resets the fan to 0 plays
 */
class CResetFan :
	public CTileVisitor
{
public:
	CResetFan();
	virtual ~CResetFan();

	/** Visit a CTileFan object
	 * \param fan Fan we are visiting */
	void CResetFan::VisitFan(CTileFan * fan) { fan->ResetFan(); }
};


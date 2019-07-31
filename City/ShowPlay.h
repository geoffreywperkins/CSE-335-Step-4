/**
 * \file ShowPlay.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * header file for the showplay visitor
 */

#pragma once
#include "TileVisitor.h"
#include "TileFan.h"

/**
 * Derived from TileVisitor
 * runs the fan method ShowPlay(), which adds to the fan's play count
 */
class CShowPlay :
	public CTileVisitor
{
public:
	CShowPlay();
	virtual ~CShowPlay();

	/** Visit a CTileFan object
	 * \param fan Fan we are visiting */
	void CShowPlay::VisitFan(CTileFan * fan) { fan->ShowPlay(); }
};

/**
 * \file BuildingCounter.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Header file for the visitor that counts buildings
 */

#pragma once
#include "TileVisitor.h"

/**
 * Derived from TileVisitor
 * keeps a count of the number of buildings it finds
 */
class CBuildingCounter :
	public CTileVisitor
{
public:
	CBuildingCounter();
	virtual ~CBuildingCounter();

	/** Get the number of buildings
	 * \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

	/** Visit a CTileBuilding object
	 * \param building Building we are visiting */
	void CBuildingCounter::VisitBuilding(CTileBuilding *building)
	{
		mNumBuildings++;
	}

private:
	/// Buildings counter
	int mNumBuildings = 0;
};

/**
 * \file FanCounter.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * Header file for the fan counting tile visitor
 */

#pragma once
#include "TileVisitor.h"


 /**
  * Keeps a count of the number of fans it finds
  */
class CFanCounter :
	public CTileVisitor
{
public:
	CFanCounter();
	virtual ~CFanCounter();

	/** Get the number of Fans
	 * \returns Number of Fans */
	int GetNumFans() const { return mNumFans; }

	/** Visit a CTileFan object
	 * \param Fan Fan we are visiting */
	void CFanCounter::VisitFan(CTileFan *Fan)
	{
		mNumFans++;
	}

private:
	/// Fans counter
	int mNumFans = 0;
};


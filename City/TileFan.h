/**
 * \file TileFan.h
 *
 * \author Geoffrey Witherington-Perkins
 *
 * header file for the Fan Tile
 */

#pragma once
#include "Tile.h"

/**
 * Class for the michigan fan tile
 */
class CTileFan :
	public CTile
{
public:
	CTileFan(CCity *city);

	///  Default constructor (disabled)
	CTileFan() = delete;

	///  Copy constructor (disabled)
	CTileFan(const CTileFan &) = delete;

	~CTileFan();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/**  Draw this item
	* \param graphics The graphics context to draw on */
	virtual void Draw(Gdiplus::Graphics *graphics) override;

	void LoadImage(std::unique_ptr<Gdiplus::Bitmap>& image, std::wstring name);

	void Update(double elapsed);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitFan(this); }

	/** Increment mPlayCount */
	void ShowPlay() { mPlayCount++; }

	/** Reset mPlayCount and mRunX to 0 */
	void ResetFan() 
	{ 
		mPlayCount = 0;
		mRunX = 0;
	}

private:
	/// Tracks how many plays the fan has been shown
	int mPlayCount = 0;

	/// Speed of the fan
	double mSpeedX = 0;

	/// Distance run
	double mRunX = 0;

	/// The image of the left pointing hand
	std::unique_ptr<Gdiplus::Bitmap> mFanImage1;

	/// The image of the right pointing hand
	std::unique_ptr<Gdiplus::Bitmap> mFanImage2;
};


#include "stdafx.h"
#include "TileFan.h"

using namespace std;
using namespace Gdiplus;

/// How much we offset drawing the tile to the left of the center
const int OffsetLeft = 64;

/// How much we offset drawing the tile above the center
const int OffsetDown = 32;

/// Max speed in X direction in pixels per second
const double MaxSpeedX = 100;

/// Min speed in X direction in pixels per second
const double MinSpeedX = -100;

/// Image for background
const std::wstring TileBackground = L"grass.png";

/// Image for background
const std::wstring MichiganFan1 = L"umguy1.png";

/// Image for background
const std::wstring MichiganFan2 = L"umguy2.png";


/** Constructor
* \param city The city this is a member of
*/
CTileFan::CTileFan(CCity *city) : CTile(city)
{
	SetImage(TileBackground);

	LoadImage(mFanImage1, MichiganFan1);
	LoadImage(mFanImage2, MichiganFan2);

	mSpeedX = MinSpeedX + ((double)rand() / RAND_MAX) * (MaxSpeedX - MinSpeedX);
}


/**
*  Destructor
*/
CTileFan::~CTileFan()
{
}


/**  Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileFan::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"fan");
	itemNode->SetAttribute(L"file", GetFile());

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileFan::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L""));
}


/**
*  Draw our tile
* \param graphics The graphics context to draw on
*/
void CTileFan::Draw(Gdiplus::Graphics *graphics)
{
	CTile::Draw(graphics);

	// if mPlays is 0, this condition will be true, and it will use the first fan image
	// if mPlays is > 0, the condition will be false, and it'll use the second
	if (!mPlayCount)
	{
		int wid = mFanImage1->GetWidth();
		int hit = mFanImage1->GetHeight();

		graphics->DrawImage(mFanImage1.get(),
			(int)(GetX() - OffsetLeft), (int)(GetY() + OffsetDown - hit),
			wid, hit);
	}
	// if shown 3 or more plays, start moving
	else if (mPlayCount >= 3)
	{
		int wid = mFanImage1->GetWidth();
		int hit = mFanImage1->GetHeight();

		graphics->DrawImage(mFanImage2.get(),
			(int)(GetX() + mRunX - OffsetLeft), (int)(GetY() + OffsetDown - hit),
			wid, hit);
	}
	else
	{
		int wid = mFanImage2->GetWidth();
		int hit = mFanImage2->GetHeight();

		graphics->DrawImage(mFanImage2.get(),
			(int)(GetX() - OffsetLeft), (int)(GetY() + OffsetDown - hit),
			wid, hit);
	}
	
}


/**
* Load an image into a bitmap
* \param image Image pointer to load
* \param name Filename to load from
*/
void CTileFan::LoadImage(std::unique_ptr<Gdiplus::Bitmap> &image, wstring name)
{
	wstring filename = ImagesDirectory + name;
	image = std::unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
	if (image->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filename;
		AfxMessageBox(msg.c_str());
	}
}


/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileFan::Update(double elapsed)
{
	CTile::Update(elapsed);

	// when the Surrender Cobra is running...
	// mSpeedX is a constant pixels per second running speed...
	if (mPlayCount >= 3)
	{
		mRunX += mSpeedX * elapsed;
	}
}
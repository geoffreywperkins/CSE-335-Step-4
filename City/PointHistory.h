/**
* \file PointHistory.cpp
*
* \author Charles Owen
*
* Class that maintains a collection of Point objects in order.
*/

#pragma once
#include <memory>

/**
 * Class that maintains a collection of Point objects in order.
 */
class CPointHistory
{
public:
	CPointHistory();
	virtual ~CPointHistory();

	void Add(Gdiplus::Point p);

protected:
	/**
	* Nested class that stores up to five points in a bin.
	*/
	class MiniTreeNode
	{
	public:
		/// Maximum number of points we can put into a bin
		const static int MaxPoints = 5;

		/**
		 * Constructor
		 * \param point The point for node
		 */
		MiniTreeNode(Gdiplus::Point point) : mPoint(point) {}

		/// Destructor
		virtual ~MiniTreeNode() {}

		bool Add(Gdiplus::Point point, std::shared_ptr<MiniTreeNode> me);

		/// Set the stored point
		/// \param point Point to save
		void Set(Gdiplus::Point point) { mPoint = point; }

		/// Get a stored point
		/// \return Stored point value
		Gdiplus::Point Get() { return mPoint; }

		/// Get the next bin in the list
		/// \return Pointer to next bin or null if none
		std::shared_ptr<MiniTreeNode> GetNext() { return mNext; }

		/// Get the left subtree
		/// \return Pointer to left subtree or null if none
		std::shared_ptr<MiniTreeNode> GetLeft() { return mLeft; }

		/// Get the right subtree
		/// \return Pointer to right subtree or null if none
		std::shared_ptr<MiniTreeNode> GetRight() { return mRight; }

		/// Get the parent node
		/// \return Pointer to parent node or null if none
		std::shared_ptr<MiniTreeNode> GetParent() { return mParent.lock(); }

		/// Set the next bin in the list
		/// \param next Next pointer to set
		void SetNext(std::shared_ptr<MiniTreeNode> next) { mNext = next; }

	private:
		/// The point stored in this tree node.
		Gdiplus::Point mPoint;

		/// Parent of this MiniTree or null if root tree
		std::weak_ptr<MiniTreeNode> mParent;

		/// Left sub-tree
		std::shared_ptr<MiniTreeNode> mLeft;

		/// Right sub-tree
		std::shared_ptr<MiniTreeNode> mRight;

		/// Next MiniTree object
		std::shared_ptr<MiniTreeNode> mNext;
	};
	
	/// Pointer to the head of the linked list of MiniTrees
	std::shared_ptr<MiniTreeNode> mHead;

private:
	/// Pointer to the tail of the linked list of MiniTrees (last node)
	std::shared_ptr<MiniTreeNode> mTail;

public:
	/** Iterator to iterate over the mouse movement records */
	class Iter
	{
	public:
		/** Constructor
		 * \param history The CPointHistory object we are iterating over
		 * \param node The starting node for the iterator */
		Iter(CPointHistory *history, std::shared_ptr<MiniTreeNode> node) :
			mHistory(history), mNode(node) {};

		/** Test for end of the iterator
		 * \param other The object on the right of the != operator
		 * \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			return mNode != other.mNode;
		}

		/** Get value at current position
		 * \returns Value at mPos in the collection */
		Gdiplus::Point operator *() const { return mNode->Get(); }

		/** Increment the iterator
		 * \returns Reference to this iterator */
		const Iter& operator++();

	private:
		CPointHistory *mHistory;   ///< City we are iterating over
		std::shared_ptr<MiniTreeNode> mNode;       ///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
	 * \returns Iter object at position 0 */
	Iter begin() 
	{
		if (mHead != nullptr && mHead->GetLeft() != nullptr)
		{
			return Iter(this, mHead->GetLeft());
		}
		
		return Iter(this, mHead);
	}

	/** Get an iterator for the end of the collection
	 * \returns Iter object at position past the end */
	Iter end() { return Iter(this, nullptr); }
};


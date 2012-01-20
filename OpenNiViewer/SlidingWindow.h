#ifndef DEF_H_SLIDING_WINDOW_
#define DEF_H_SLIDING_WINDOW_

#include <deque>

class SlidingWindow
{
private:
	int windowSize_;
	std::deque<double> memory_;
	double updatedMean_;

public:
	SlidingWindow(int windowSize) : windowSize_(windowSize) {}

	void push(double value) {
		const unsigned int memSize = memory_.size();
		if (memSize == windowSize_)
			memory_.pop_front();
		memory_.push_back(value);
		// Mean update
		updatedMean_ = 0;
		for (unsigned int i = 0; i < memSize; ++i)
			updatedMean_ += memory_[i];
		updatedMean_ /= memSize;
	}

	double mean() { return updatedMean_; }
};

#endif //DEF_H_SLIDING_WINDOW_
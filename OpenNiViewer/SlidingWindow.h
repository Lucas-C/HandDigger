#ifndef DEF_H_SLIDING_WINDOW_
#define DEF_H_SLIDING_WINDOW_

#include <deque>

class SlidingWindowMean
{
private:
	int windowSize_;
	double updatedMean_;
	std::deque<double> memory_;

public:
	SlidingWindowMean(int windowSize) : windowSize_(windowSize), updatedMean_(0), memory_() {}

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

class SlidingWindowExp
{
private:
	double mean_;
	int nbValues_;
	double alpha_;

public:
	SlidingWindowExp(double alpha) : mean_(0), nbValues_(0), alpha_(alpha) {}

	void push(double value) {
		mean_ = (1 - alpha_) * mean_ + alpha_ * value;
	}

	double mean() { return mean_; }
};

#ifdef USE_SLIDING_WINDOW_EXP
typedef SlidingWindowMean SlidingWindow;
#else
typedef SlidingWindowExp SlidingWindow;
#endif


#endif //DEF_H_SLIDING_WINDOW_
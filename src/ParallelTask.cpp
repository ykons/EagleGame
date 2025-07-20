#include <SFML/System/Time.hpp>

#include <ParallelTask.hpp>

ParallelTask::ParallelTask()
	: mThread(&ParallelTask::runTask, this), mFinished(false)
{
}

void ParallelTask::execute()
{
	mFinished = false;
	mElapsedTime.restart();
	mThread.detach();
}

bool ParallelTask::isFinished()
{
	std::lock_guard<std::mutex> lock(mMutex);
	return mFinished;
}

float ParallelTask::getCompletion()
{
	std::lock_guard<std::mutex> lock(mMutex);

	// 100% at 10 seconds of elapsed time
	return mElapsedTime.getElapsedTime().asSeconds() / 2.f;
}

void ParallelTask::runTask()
{
	// Dummy task - stall 10 seconds
	bool ended = false;
	while (!ended)
	{
		std::lock_guard<std::mutex> lock(mMutex); // Protect the clock
		if (mElapsedTime.getElapsedTime().asSeconds() >= 2.f)
			ended = true;
	}

	{ // mFinished may be accessed from multiple threads, protect it
		std::lock_guard<std::mutex> lock(mMutex);
		mFinished = true;
	}
}
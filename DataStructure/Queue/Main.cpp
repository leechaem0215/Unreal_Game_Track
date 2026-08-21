#include "Queue.h"

int main()
{
	// 큐의 크기
	const int count = 5;

	Queue<int, count> queue;

	for (int ix = 0; ix < count + 1; ++ix)
	{
		queue.Enqueue(ix +1 );
	}

}
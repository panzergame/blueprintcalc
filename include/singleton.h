#pragma once

template <class T>
class Singleton
{
public:
	static T *singleton;

	template <class ... A>
	static void initSingleton(A ... args)
	{
		singleton = new T(args ...);
	}
};

template <class T>
T *Singleton<T>::singleton;

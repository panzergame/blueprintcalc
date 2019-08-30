#pragma once

template <class T>
class Singleton
{
public:
	static T singleton;
};

template <class T>
T Singleton<T>::singleton;

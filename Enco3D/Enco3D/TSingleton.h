#ifndef _ENCO3D_TSINGLETON_H_
#define _ENCO3D_TSINGLETON_H_

#include <memory>

template <typename T>
class TSingleton
{
public:
	inline static T *getInstance()
	{
		static std::unique_ptr<T> instance(nullptr);
		if (instance.get() == nullptr)
			instance = std::unique_ptr<T>(new T);
		return instance.get();
	}
};

#endif
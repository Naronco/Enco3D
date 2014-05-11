#ifndef _ENCO3D_TSINGLETON_H_
#define _ENCO3D_TSINGLETON_H_

template <typename T>
class TSingleton
{
public:
	inline static T *GetInstance()
	{
		static T instance;
		return &instance;
	}
};

#endif
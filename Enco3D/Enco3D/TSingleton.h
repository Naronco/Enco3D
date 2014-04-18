#ifndef _ENCO3D_TSINGLETON_H_
#define _ENCO3D_TSINGLETON_H_

template <typename T>
class TSingleton
{
private:
	static T *s_instance;

public:
	inline static T *GetInstance()
	{
		return s_instance == nullptr ? (s_instance = new T) : s_instance;
	}
};

template <typename T> T *TSingleton<T>::s_instance = nullptr;

#endif
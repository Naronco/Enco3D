#ifndef _ENCO3D_VECTOR3_H_
#define _ENCO3D_VECTOR3_H_

#include "Vector2.h"

namespace Enco3D
{
	namespace Core
	{
		template <typename T> struct Vector3
		{
			union
			{
				struct
				{
					T x, y, z;
				};

				T xyz[3];
			};

			inline Vector3(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) {  }
			inline Vector3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {  }

			inline Vector3<T> &clear() { x = y = z = 0; return *this; }
			inline Vector3<T> &set(T _x, T _y, T _z) { x = _x; y = _y; z = _z; return *this; }
			inline Vector3<T> &set(const Vector3<T> &v) { x = v.x; y = v.y; z = v.z; return *this; }

			template <typename S> inline bool operator == (const Vector3<S> &v) const { return x == v.x && y == v.y && z == v.z; }
			template <typename S> inline bool operator != (const Vector3<S> &v) const { return x != v.x || y != v.y || z != v.z; }

			inline Vector3<T> operator - () const { return Vector3<T>(-x, -y, -z); }

			template <typename S> inline Vector3<T> operator + (const Vector3<S> &v) const { return Vector3<T>(x + v.x, y + v.y, z + v.z); }
			template <typename S> inline Vector3<T> operator - (const Vector3<S> &v) const { return Vector3<T>(x - v.x, y - v.y, z - v.z); }
			template <typename S> inline Vector3<T> operator * (S val) const { return Vector3<T>(x * val, y * val, z * val); }
			template <typename S> inline Vector3<T> operator / (S val) const { T ival = (T)(1.0 / val); return Vector3<T>(x * ival, y * ival, z * ival); }

			template <typename S> inline Vector3<T> &operator += (const Vector3<S> &v) { return set(x + v.x, y + v.y, z + v.z); }
			template <typename S> inline Vector3<T> &operator -= (const Vector3<S> &v) { return set(x - v.x, y - v.y, z - v.z); }
			template <typename S> inline Vector3<T> &operator *= (S val) { return set(x * val, y * val, z * val); }
			template <typename S> inline Vector3<T> &operator /= (S val) { T ival = (T)(1.0 / val); return set(x * ival, y * ival, z * ival); }

			inline T getSquaredLength() const { return x * x + y * y + z * z; }
			inline T getLength() const { return (T)sqrt(x * x + y * y + z * z); }

			template <typename S> inline T getSquaredDistance(const Vector3<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); T zd = (T)(v.z - z); return xd * xd + yd * yd + zd * zd; }
			template <typename S> inline T getDistance(const Vector3<S> &v) { T xd = (T)(v.x - x); T yd = (T)(v.y - y); T zd = (T)(v.z - z); (T)sqrt(xd * xd + yd * yd + zd * zd); }

			inline Vector3<T> &normalize() { return (*this * (T)(1.0 / getLength())); }

			template <typename S> inline T dot(const Vector3<S> &v) { return x * v.x + y * v.y + z * v.z; }
			template <typename S> inline Vector3<T> &cross(const Vector3<S> &v) { return set(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

			inline Vector3<T> &rotate(const Vector3<T> &axis, T angle)
			{
				T s = (T)(sin(angle));
				T c = (T)(cos(angle));
				return set(cross(axis * s) + (*this * c) + (axis * (dot(axis * (1 - c)))));
			}
		};

		template <typename T, typename S> inline Vector3<T> operator * (S val, const Vector3<T> &v) { return Vector3<T>(v.x * val, v.y * val, v.z * val); }

		typedef Vector3<float> Vector3f;
		typedef Vector3<double> Vector3d;

		namespace Vector3Template
		{
			static const Vector3f Zero(0, 0, 0);
			static const Vector3f One(1, 1, 1);
			static const Vector3f Up(0, 1, 0);
			static const Vector3f Down(0, -1, 0);
			static const Vector3f Left(-1, 0, 0);
			static const Vector3f Right(1, 0, 0);
			static const Vector3f Forward(0, 0, 1);
			static const Vector3f Backward(0, 0, -1);
		}

#pragma region Colors
		namespace Color3Template
		{
			static const Vector3f White(1, 1, 1);
			static const Vector3f Black(0, 0, 0);
			static const Vector3f AliceBlue(0.9411765f, 0.972549f, 1);
			static const Vector3f AntiqueWhite(0.9803922f, 0.9215686f, 0.8431373f);
			static const Vector3f Aqua(0, 1, 1);
			static const Vector3f Aquamarine(0.4980392f, 1, 0.8313726f);
			static const Vector3f Azure(0.9411765f, 1, 1);
			static const Vector3f Beige(0.9607843f, 0.9607843f, 0.8627451f);
			static const Vector3f Bisque(1, 0.8941177f, 0.7686275f);
			static const Vector3f BlanchedAlmond(1, 0.9215686f, 0.8039216f);
			static const Vector3f Blue(0, 0, 1);
			static const Vector3f BlueViolet(0.5411765f, 0.1686275f, 0.8862745f);
			static const Vector3f Brown(0.6470588f, 0.1647059f, 0.1647059f);
			static const Vector3f BurlyWood(0.8705882f, 0.7215686f, 0.5294118f);
			static const Vector3f CadetBlue(0.372549f, 0.6196079f, 0.627451f);
			static const Vector3f Chartreuse(0.4980392f, 1, 0);
			static const Vector3f Chocolate(0.8235294f, 0.4117647f, 0.1176471f);
			static const Vector3f Coral(1, 0.4980392f, 0.3137255f);
			static const Vector3f CornflowerBlue(0.3921569f, 0.5843138f, 0.9294118f);
			static const Vector3f Cornsilk(1, 0.972549f, 0.8627451f);
			static const Vector3f Crimson(0.8627451f, 0.07843138f, 0.2352941f);
			static const Vector3f Cyan(0, 1, 1);
			static const Vector3f DarkBlue(0, 0, 0.5450981f);
			static const Vector3f DarkCyan(0, 0.5450981f, 0.5450981f);
			static const Vector3f DarkGoldenRod(0.7215686f, 0.5254902f, 0.04313726f);
			static const Vector3f DarkGray(0.6627451f, 0.6627451f, 0.6627451f);
			static const Vector3f DarkGreen(0, 0.3921569f, 0);
			static const Vector3f DarkKhaki(0.7411765f, 0.7176471f, 0.4196078f);
			static const Vector3f DarkMagenta(0.5450981f, 0, 0.5450981f);
			static const Vector3f DarkOliveGreen(0.3333333f, 0.4196078f, 0.1843137f);
			static const Vector3f DarkOrange(1, 0.5490196f, 0);
			static const Vector3f DarkOrchid(0.6f, 0.1960784f, 0.8f);
			static const Vector3f DarkRed(0.5450981f, 0, 0);
			static const Vector3f DarkSalmon(0.9137255f, 0.5882353f, 0.4784314f);
			static const Vector3f DarkSeaGreen(0.5607843f, 0.7372549f, 0.5607843f);
			static const Vector3f DarkSlateBlue(0.282353f, 0.2392157f, 0.5450981f);
			static const Vector3f DarkSlateGray(0.1843137f, 0.3098039f, 0.3098039f);
			static const Vector3f DarkTurquoise(0, 0.8078431f, 0.8196079f);
			static const Vector3f DarkViolet(0.5803922f, 0, 0.827451f);
			static const Vector3f DeepPink(1, 0.07843138f, 0.5764706f);
			static const Vector3f DeepSkyBlue(0, 0.7490196f, 1);
			static const Vector3f DimGray(0.4117647f, 0.4117647f, 0.4117647f);
			static const Vector3f DodgerBlue(0.1176471f, 0.5647059f, 1);
			static const Vector3f FireBrick(0.6980392f, 0.1333333f, 0.1333333f);
			static const Vector3f FloralWhite(1, 0.9803922f, 0.9411765f);
			static const Vector3f ForestGreen(0.1333333f, 0.5450981f, 0.1333333f);
			static const Vector3f Fuchsia(1, 0, 1);
			static const Vector3f Gainsboro(0.8627451f, 0.8627451f, 0.8627451f);
			static const Vector3f GhostWhite(0.972549f, 0.972549f, 1);
			static const Vector3f Gold(1, 0.8431373f, 0);
			static const Vector3f GoldenRod(0.854902f, 0.6470588f, 0.1254902f);
			static const Vector3f Gray(0.5019608f, 0.5019608f, 0.5019608f);
			static const Vector3f Green(0, 0.5019608f, 0);
			static const Vector3f GreenYellow(0.6784314f, 1, 0.1843137f);
			static const Vector3f HoneyDew(0.9411765f, 1, 0.9411765f);
			static const Vector3f HotPink(1, 0.4117647f, 0.7058824f);
			static const Vector3f IndianRed(0.8039216f, 0.3607843f, 0.3607843f);
			static const Vector3f Indigo(0.2941177f, 0, 0.509804f);
			static const Vector3f Ivory(1, 1, 0.9411765f);
			static const Vector3f Khaki(0.9411765f, 0.9019608f, 0.5490196f);
			static const Vector3f Lavender(0.9019608f, 0.9019608f, 0.9803922f);
			static const Vector3f LavenderBlush(1, 0.9411765f, 0.9607843f);
			static const Vector3f LawnGreen(0.4862745f, 0.9882353f, 0);
			static const Vector3f LemonChiffon(1, 0.9803922f, 0.8039216f);
			static const Vector3f LightBlue(0.6784314f, 0.8470588f, 0.9019608f);
			static const Vector3f LightCoral(0.9411765f, 0.5019608f, 0.5019608f);
			static const Vector3f LightCyan(0.8784314f, 1, 1);
			static const Vector3f LightGoldenRodYellow(0.9803922f, 0.9803922f, 0.8235294f);
			static const Vector3f LightGray(0.827451f, 0.827451f, 0.827451f);
			static const Vector3f LightGreen(0.5647059f, 0.9333333f, 0.5647059f);
			static const Vector3f LightPink(1, 0.7137255f, 0.7568628f);
			static const Vector3f LightSalmon(1, 0.627451f, 0.4784314f);
			static const Vector3f LightSeaGreen(0.1254902f, 0.6980392f, 0.6666667f);
			static const Vector3f LightSkyBlue(0.5294118f, 0.8078431f, 0.9803922f);
			static const Vector3f LightSlateGray(0.4666667f, 0.5333334f, 0.6f);
			static const Vector3f LightSteelBlue(0.6901961f, 0.7686275f, 0.8705882f);
			static const Vector3f LightYellow(1, 1, 0.8784314f);
			static const Vector3f Lime(0, 1, 0);
			static const Vector3f LimeGreen(0.1960784f, 0.8039216f, 0.1960784f);
			static const Vector3f Linen(0.9803922f, 0.9411765f, 0.9019608f);
			static const Vector3f Magenta(1, 0, 1);
			static const Vector3f Maroon(0.5019608f, 0, 0);
			static const Vector3f MediumAquaMarine(0.4f, 0.8039216f, 0.6666667f);
			static const Vector3f MediumBlue(0, 0, 0.8039216f);
			static const Vector3f MediumOrchid(0.7294118f, 0.3333333f, 0.827451f);
			static const Vector3f MediumPurple(0.5764706f, 0.4392157f, 0.8588235f);
			static const Vector3f MediumSeaGreen(0.2352941f, 0.7019608f, 0.4431373f);
			static const Vector3f MediumSlateBlue(0.4823529f, 0.4078431f, 0.9333333f);
			static const Vector3f MediumSpringGreen(0, 0.9803922f, 0.6039216f);
			static const Vector3f MediumTurquoise(0.282353f, 0.8196079f, 0.8f);
			static const Vector3f MediumVioletRed(0.7803922f, 0.08235294f, 0.5215687f);
			static const Vector3f MidnightBlue(0.09803922f, 0.09803922f, 0.4392157f);
			static const Vector3f MintCream(0.9607843f, 1, 0.9803922f);
			static const Vector3f MistyRose(1, 0.8941177f, 0.8823529f);
			static const Vector3f Moccasin(1, 0.8941177f, 0.7098039f);
			static const Vector3f NavajoWhite(1, 0.8705882f, 0.6784314f);
			static const Vector3f Navy(0, 0, 0.5019608f);
			static const Vector3f OldLace(0.9921569f, 0.9607843f, 0.9019608f);
			static const Vector3f Olive(0.5019608f, 0.5019608f, 0);
			static const Vector3f OliveDrab(0.4196078f, 0.5568628f, 0.1372549f);
			static const Vector3f Orange(1, 0.6470588f, 0);
			static const Vector3f OrangeRed(1, 0.2705882f, 0);
			static const Vector3f Orchid(0.854902f, 0.4392157f, 0.8392157f);
			static const Vector3f PaleGoldenRod(0.9333333f, 0.9098039f, 0.6666667f);
			static const Vector3f PaleGreen(0.5960785f, 0.9843137f, 0.5960785f);
			static const Vector3f PaleTurquoise(0.6862745f, 0.9333333f, 0.9333333f);
			static const Vector3f PaleVioletRed(0.8588235f, 0.4392157f, 0.5764706f);
			static const Vector3f PapayaWhip(1, 0.9372549f, 0.8352941f);
			static const Vector3f PeachPuff(1, 0.854902f, 0.7254902f);
			static const Vector3f Peru(0.8039216f, 0.5215687f, 0.2470588f);
			static const Vector3f Pink(1, 0.7529412f, 0.7960784f);
			static const Vector3f Plum(0.8666667f, 0.627451f, 0.8666667f);
			static const Vector3f PowderBlue(0.6901961f, 0.8784314f, 0.9019608f);
			static const Vector3f Purple(0.5019608f, 0, 0.5019608f);
			static const Vector3f Red(1, 0, 0);
			static const Vector3f RosyBrown(0.7372549f, 0.5607843f, 0.5607843f);
			static const Vector3f RoyalBlue(0.254902f, 0.4117647f, 0.8823529f);
			static const Vector3f SaddleBrown(0.5450981f, 0.2705882f, 0.07450981f);
			static const Vector3f Salmon(0.9803922f, 0.5019608f, 0.4470588f);
			static const Vector3f SandyBrown(0.9568627f, 0.6431373f, 0.3764706f);
			static const Vector3f SeaGreen(0.1803922f, 0.5450981f, 0.3411765f);
			static const Vector3f SeaShell(1, 0.9607843f, 0.9333333f);
			static const Vector3f Sienna(0.627451f, 0.3215686f, 0.1764706f);
			static const Vector3f Silver(0.7529412f, 0.7529412f, 0.7529412f);
			static const Vector3f SkyBlue(0.5294118f, 0.8078431f, 0.9215686f);
			static const Vector3f SlateBlue(0.4156863f, 0.3529412f, 0.8039216f);
			static const Vector3f SlateGray(0.4392157f, 0.5019608f, 0.5647059f);
			static const Vector3f Snow(1, 0.9803922f, 0.9803922f);
			static const Vector3f SpringGreen(0, 1, 0.4980392f);
			static const Vector3f SteelBlue(0.2745098f, 0.509804f, 0.7058824f);
			static const Vector3f Tan(0.8235294f, 0.7058824f, 0.5490196f);
			static const Vector3f Teal(0, 0.5019608f, 0.5019608f);
			static const Vector3f Thistle(0.8470588f, 0.7490196f, 0.8470588f);
			static const Vector3f Tomato(1, 0.3882353f, 0.2784314f);
			static const Vector3f Turquoise(0.2509804f, 0.8784314f, 0.8156863f);
			static const Vector3f Violet(0.9333333f, 0.509804f, 0.9333333f);
			static const Vector3f Wheat(0.9607843f, 0.8705882f, 0.7019608f);
			static const Vector3f WhiteSmoke(0.9607843f, 0.9607843f, 0.9607843f);
			static const Vector3f Yellow(1, 1, 0);
			static const Vector3f YellowGreen(0.6039216f, 0.8039216f, 0.1960784f);
		}
#pragma endregion
	}
}

#endif
#ifndef __ENCO3D_ISCENENODE_H_INCLUDED__
#define __ENCO3D_ISCENENODE_H_INCLUDED__

#include "IGraphicsDevice.h"
#include "IPhysicsDevice.h"
#include "CTransform.h"

namespace enco
{
	namespace core
	{
		///////////////////////////////////////////////////////
		// MATERIAL ///////////////////////////////////////////
		///////////////////////////////////////////////////////
		enum EMaterialFlags
		{
			eMATERIALFLAG_LIGHTING,
			eMATERIALFLAG_NORMALMAPPING,

			// Autocount -> number of material flags
			__materialflagcount,
		};

		enum EMaterialTextures
		{
			eMATERIALTEXTURE_DIFFUSE,
			eMATERIALTEXTURE_NORMAL,

			// Autocount -> number of material textures
			__materialtexturecount
		};

		enum EMaterialColors
		{
			eMATERIALCOLOR_DIFFUSE,

			// Autocount -> number of material colors
			__materialcolorcount
		};

		enum EMaterialFloats
		{
			eMATERIALFLOAT_SPECULARINTENSITY,
			eMATERIALFLOAT_SPECULAREXPONENT,

			// Autocouunt -> number of material floats
			__materialfloatcount
		};
		
		///////////////////////////////////////////////////////
		// PHYSICS ////////////////////////////////////////////
		///////////////////////////////////////////////////////
		enum EPhysicsFlags
		{
			ePHYSICSFLAG_USERIGIDBODY,
			ePHYSICSFLAG_RIGIDBODYROTATION,

			// Autocount -> number of physics flags
			__physicsflagcount
		};

		enum EPhysicsFloats
		{
			ePHYSICSFLOAT_MASS,
			ePHYSICSFLOAT_RESTITUTION,
			ePHYSICSFLOAT_FRICTION,
			ePHYSICSFLOAT_LINEARDAMPING,
			ePHYSICSFLOAT_ANGULARDAMPING,

			// Autocount -> number of physics flags
			__physicsfloatcount
		};

		class ISceneNode
		{
		protected:
			IGraphicsDevice *m_graphicsDevice;

			CTransform<float32> *m_transform;

			bool m_materialFlags[__materialflagcount];
			ITexture2D *m_materialTextures[__materialtexturecount];
			Color4f32 m_materialColors[__materialcolorcount];
			float32 m_materialFloats[__materialfloatcount];

			bool m_physicsFlags[__physicsflagcount];
			float32 m_physicsFloats[__physicsfloatcount];
			IShape *m_physicsShape;
			
			inline void clearMaterialFlags() { __FILLARRAY(m_materialFlags, __materialflagcount, false); }
			inline void clearMaterialTextures() { __FILLARRAY(m_materialTextures, __materialtexturecount, 0); }
			inline void clearMaterialColors() { __FILLARRAY(m_materialColors, __materialcolorcount, Color4f32(1, 1, 1, 1)); }
			inline void clearMaterialFloats() { __FILLARRAY(m_materialFloats, __materialfloatcount, 0.0f); }

			inline void clearPhysicsFlags() { __FILLARRAY(m_physicsFlags, __physicsflagcount, false); }
			inline void clearPhysicsFloats() { __FILLARRAY(m_physicsFloats, __physicsfloatcount, 0); }

			inline void releaseMaterialTextures() { for (sint32 i = 0; i < __materialtexturecount; i++) m_graphicsDevice->releaseTexture2D(m_materialTextures[i]); }

		public:
			virtual void create(IGraphicsDevice *graphicsDevice) = 0;
			virtual void release() = 0;

			virtual void render() = 0;

			inline void setMaterialFlag(sint32 materialFlag, bool enabled) { m_materialFlags[materialFlag] = enabled; }
			inline void setMaterialTexture(sint32 materialTexture, const char *filename, sint32 filter = eTEXTUREFILTER_NEAREST, sint32 wrap = eTEXTUREWRAP_REPEAT) { m_materialTextures[materialTexture] = m_graphicsDevice->buildTexture2D(filename, filter, wrap); }
			inline void setMaterialColor(sint32 materialColor, const Color4f32 &color) { m_materialColors[materialColor] = color; }
			inline void setMaterialFloat(sint32 materialFloat, float32 value) { m_materialFloats[materialFloat] = value; }

			inline void setPhysicsFlag(sint32 physicsFlag, bool enabled) { m_physicsFlags[physicsFlag] = enabled; }
			inline void setPhysicsFloat(sint32 physicsFloat, float32 value) { m_physicsFloats[physicsFloat] = value; }
			inline void setPhysicsShape(IShape *shape) { m_physicsShape = shape; }

			inline CTransform<float32> *getTransform() const { return m_transform; }

			inline bool isMaterialFlagEnabled(sint32 materialFlag) const { return m_materialFlags[materialFlag]; }
			inline ITexture2D *getMaterialTexture(sint32 materialTexture) const { return m_materialTextures[materialTexture]; }
			inline Color4f32 getMaterialColor(sint32 materialColor) const { return m_materialColors[materialColor]; }
			inline float32 getMaterialFloat(sint32 materialFloat) const { return m_materialFloats[materialFloat]; }

			inline bool isPhysicsFlagEnabled(sint32 physicsFlag) const { return m_physicsFlags[physicsFlag]; }
			inline float32 getPhysicsFloat(sint32 physicsFloat) const { return m_physicsFloats[physicsFloat]; }
			inline IShape *getPhysicsShape() const { return m_physicsShape; }

			inline void buildRigidBodyData(RigidBodyData *out) {
				out->shape = m_physicsShape;
				out->mass = m_physicsFloats[ePHYSICSFLOAT_MASS];
				out->restitution = m_physicsFloats[ePHYSICSFLOAT_RESTITUTION];
				out->friction = m_physicsFloats[ePHYSICSFLOAT_FRICTION];
				out->linearDamping = m_physicsFloats[ePHYSICSFLOAT_LINEARDAMPING];
				out->angularDamping = m_physicsFloats[ePHYSICSFLOAT_ANGULARDAMPING];
				out->rotationEnabled = m_physicsFlags[ePHYSICSFLAG_RIGIDBODYROTATION];
			}
		};
	}
}

#endif
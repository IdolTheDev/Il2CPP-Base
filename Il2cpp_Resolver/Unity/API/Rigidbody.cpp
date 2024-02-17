#include "../../Includes.hpp"

namespace Unity
{
	SRigidbodyFunctions RigidbodyFunctions;

	namespace RigidBody
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_RIGIDBODY_CLASS);

			RigidbodyFunctions.m_pGetDetectCollisions	= IL2CPP::ResolveCall(UNITY_RIGIDBODY_GETDETECTCOLLISIONS);
			RigidbodyFunctions.m_pGetVelocity			= IL2CPP::ResolveCall(UNITY_RIGIDBODY_GETVELOCITY);
			RigidbodyFunctions.m_pGetFreezeRotation		= IL2CPP::ResolveCall(UNITY_RIGIDBODY_GETFREEZEROTATION);
			RigidbodyFunctions.m_pGetIsKinematic		= IL2CPP::ResolveCall(UNITY_RIGIDBODY_GETISKINEMATIC);
			RigidbodyFunctions.m_pSetFreezeRotation		= IL2CPP::ResolveCall(UNITY_RIGIDBODY_SETFREEZEROTATION);
			RigidbodyFunctions.m_pSetDetectCollisions	= IL2CPP::ResolveCall(UNITY_RIGIDBODY_SETDETECTCOLLISIONS);
			RigidbodyFunctions.m_pSetVelocity			= IL2CPP::ResolveCall(UNITY_RIGIDBODY_SETVELOCITY);
			RigidbodyFunctions.m_pSetIsKinematic		= IL2CPP::ResolveCall(UNITY_RIGIDBODY_SETISKINEMATIC);

		}
	}
}
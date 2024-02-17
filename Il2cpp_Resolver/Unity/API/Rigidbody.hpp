#pragma once

namespace Unity
{
	struct SRigidbodyFunctions
	{
		void* m_pGetDetectCollisions = nullptr;
		void* m_pGetVelocity = nullptr;
		void* m_pGetFreezeRotation = nullptr;
		void* m_pGetIsKinematic = nullptr;
		void* m_pSetDetectCollisions = nullptr;
		void* m_pSetVelocity = nullptr;
		void* m_pSetFreezeRotation = nullptr;
		void* m_pSetIsKinematic = nullptr;
	};
	extern SRigidbodyFunctions RigidbodyFunctions;

	class CRigidbody : public IL2CPP::CClass
	{
	public:
		bool GetDetectCollisions()
		{
			return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(void*)>(RigidbodyFunctions.m_pGetDetectCollisions)(this);
		}

		void SetDetectCollisions(bool m_bDetect)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, bool)>(RigidbodyFunctions.m_pSetDetectCollisions)(this, m_bDetect);
		}

		Vector3 GetVelocity()
		{
			Vector3 vRet;
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&)>(RigidbodyFunctions.m_pGetVelocity)(this, vRet);
			return vRet;
		}

		void SetVelocity(Vector3 m_vVector)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3)>(RigidbodyFunctions.m_pSetVelocity)(this, m_vVector);
		}

		bool GetFreezeRotation()
		{
			return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(void*)>(RigidbodyFunctions.m_pGetFreezeRotation)(this);
		}

		void SetFreezeRotation(bool m_bFreezeRotation)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, bool)>(RigidbodyFunctions.m_pSetFreezeRotation)(this, m_bFreezeRotation);
		}

		bool GetIsKinematic()
		{
			return reinterpret_cast<bool(UNITY_CALLING_CONVENTION)(void*)>(RigidbodyFunctions.m_pGetIsKinematic)(this);
		}

		void SetIsKinematic(bool m_bIsKinematic)
		{
			reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, bool)>(RigidbodyFunctions.m_pSetIsKinematic)(this, m_bIsKinematic);
		}
	};

	namespace RigidBody
	{
		void Initialize();
	}
}
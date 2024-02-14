#include "../../Includes.hpp"

namespace Unity
{
	SGameObjectFunctions GameObjectFunctions;

	namespace GameObject
	{
		void Initialize()
		{
			IL2CPP::SystemTypeCache::Initializer::Add(UNITY_GAMEOBJECT_CLASS);

			GameObjectFunctions.m_pAddComponent				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_ADDCOMPONENT);
			GameObjectFunctions.m_pCreatePrimitive			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_CREATEPRIMITIVE);
			GameObjectFunctions.m_pFind						= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_FIND);
			GameObjectFunctions.m_pFindGameObjectsWithTag	= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_FINDGAMEOBJECTWITHTAG);
			GameObjectFunctions.m_pGetComponent				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENT);
			GameObjectFunctions.m_pGetComponents			= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETCOMPONENTS);
			GameObjectFunctions.m_pGetActive				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETACTIVE);
			GameObjectFunctions.m_pGetLayer					= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETLAYER);
			GameObjectFunctions.m_pGetTransform				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_GETTRANSFORM);
			GameObjectFunctions.m_pSetActive				= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_SETACTIVE);
			GameObjectFunctions.m_pSetLayer					= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_SETLAYER);
			GameObjectFunctions.m_pSetTag					= IL2CPP::ResolveCall(UNITY_GAMEOBJECT_SETTAG);
		}

		CGameObject* CreatePrimitive(m_ePrimitiveType m_eType)
		{
			return reinterpret_cast<CGameObject*(UNITY_CALLING_CONVENTION)(m_ePrimitiveType)>(GameObjectFunctions.m_pCreatePrimitive)(m_eType);
		}


		/// <summary>
		/// Finds a CGameObject* that matches the name you provided.
		/// Normally you would need to add "(Clone)" at the back of the name, but with this change it adds "(Clone)" automatically.
		/// </summary>
		/// <param name="m_pName"></param>
		/// <returns></returns>
		CGameObject* Find(const char* m_pName)
		{
			// Finds the GameObject we are looking for without the "(Clone)" part.
			auto CGameObjectFound = reinterpret_cast<CGameObject * (UNITY_CALLING_CONVENTION)(System_String*)>(GameObjectFunctions.m_pFind)(IL2CPP::String::New(m_pName));

			// Checks if the GameObject found is a nullptr, if it is, that means the GameObject was NOT found and we will then add the "(Clone)" part in the next search.
			if (CGameObjectFound == nullptr) {

				// Variable to store the "m_pName"
				std::string cloneText = m_pName;

				// We add the ("Clone") to the end of the "m_pName".
				cloneText += "(Clone)";

				// We return as a CGameObject* using the "cloneText" name.
				return reinterpret_cast<CGameObject * (UNITY_CALLING_CONVENTION)(System_String*)>(GameObjectFunctions.m_pFind)(IL2CPP::String::New(cloneText.c_str()));
			}

			// We found the GameObject without the "(Clone)", so we will return it now.
			return reinterpret_cast<CGameObject * (UNITY_CALLING_CONVENTION)(System_String*)>(GameObjectFunctions.m_pFind)(IL2CPP::String::New(m_pName));
		}
		
		il2cppArray<CGameObject*>* FindWithTag(const char* m_pTag)
		{
			return reinterpret_cast<il2cppArray<CGameObject*>*(UNITY_CALLING_CONVENTION)(void*)>(GameObjectFunctions.m_pFindGameObjectsWithTag)(IL2CPP::String::New(m_pTag));
		}
	}
}

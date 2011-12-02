//#pragma once
//#include <Box2D\Box2D.h>
//#include <GameObj.h>

//
//class MyContactListener : public b2ContactListener{
//
//	void MyContactListener::BeginContact(b2Contact* contact) {
//  
//		//check if fixture A was a GameObj
//		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//		if ( bodyUserData )
//			static_cast<GameObj*>( bodyUserData )->addContact();
////			bodyUserData->addContact();
//  
//		//check if fixture B was a GameObj
//		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//		if ( bodyUserData )
//			static_cast<GameObj*>( bodyUserData )->addContact();
//  
//	}
//  
//	void MyContactListener::EndContact(b2Contact* contact) {
//  
//		//check if fixture A was a GameObj
//		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//		if ( bodyUserData )
//		static_cast<GameObj*>( bodyUserData )->subContact();
//  
//		//check if fixture B was a GameObj
//		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//		if ( bodyUserData )
//		static_cast<GameObj*>( bodyUserData )->subContact();
//  
//	}
//};
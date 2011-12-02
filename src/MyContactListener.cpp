//#include "MyContactListener.h"


//MyContactListener::MyContactListener(void)
//{
//}
//
//
//MyContactListener::~MyContactListener(void)
//{
//}

//
//void MyContactListener::BeginContact(b2Contact* contact) {
//  
//	//check if fixture A was a GameObj
//	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//	if ( bodyUserData )
////		static_cast<GameObj*>( bodyUserData )->addContact();
//		bodyUserData->addContact();
//  
//	//check if fixture B was a GameObj
//	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//	if ( bodyUserData )
//		static_cast<GameObj*>( bodyUserData )->addContact();
//  
//}
//  
//void MyContactListener::EndContact(b2Contact* contact) {
//  
//    //check if fixture A was a GameObj
//    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//    if ( bodyUserData )
//    static_cast<GameObj*>( bodyUserData )->subContact();
//  
//    //check if fixture B was a GameObj
//    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//    if ( bodyUserData )
//    static_cast<GameObj*>( bodyUserData )->subContact();
//  
//}
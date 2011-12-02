#pragma once
#include <vector>

class GameObjectFactory
{
public:
//	GameObjectFactory(void);
	GameObjectFactory* GameObjectFactory::getInstance() {
		if(inst == NULL) {
			static GameObjectFactory self;
			inst = &self;
		}
		return inst;
	}

private:
	GameObjectFactory();
	GameObjectFactory(const GameObjectFactory& copy);			// not implemented
    GameObjectFactory& operator=(GameObjectFactory const& copy); // Not Implemented
	~GameObjectFactory(void);
	static GameObjectFactory* inst;

};

//GameObjectFactory* GameObjectFactory::getInstance() {
//	if(inst == 0) {
//		static GameObjectFactory self;
//		inst = &self;
//	}
//	return inst;
//}


//
//class S
//{
//    public:
//        static S& getInstance()
//        {
//            static S    instance;
//            return instance;
//        }
//    private:
//        S() {}
//        S(S const&);              // Don't Implement.
//        void operator=(S const&); // Don't implement
// };
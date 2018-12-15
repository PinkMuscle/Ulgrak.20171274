//#ifndef PlayState_h
//#define PlayState_h
//#include "GameState.h"
//#include <vector>
//#include <array>
//#include <memory>
//
//class ProjectileManager;
//
//class PlayState : public GameState
//{
//public:
//    ~PlayState() {}
//    static PlayState* Instance()
//    {
//        if (pInstance == nullptr)
//        {
//            pInstance = new PlayState();
//        }
//        return pInstance;
//    }
//    virtual void Update();
//    virtual void Render();
//    virtual bool OnEnter();
//    virtual bool OnExit();
//    void CheckCollision();
//    void Refresh();
//    virtual std::string GetStateID() const { return playID; }
//
//private:
//    PlayState() {}
//    static PlayState* pInstance;
//    static const std::string playID;
//    ProjectileManager* projectiles;
//
//    unsigned int nextSpawn;
//    unsigned int spawnDelay;
//
//    std::array<std::unique_ptr<GameObject>, 2> backgrounds;
//    std::unique_ptr<GameObject> player;
//    std::vector<std::unique_ptr<GameObject>> enemies;
//    std::vector<std::unique_ptr<GameObject>> animals;
//    std::vector<std::unique_ptr<GameObject>> missiles;
//    std::vector<std::unique_ptr<GameObject>> effects;
//    std::vector<std::unique_ptr<GameObject>> ui;
//};
//
//#endif
#include "ModelRepository.h"

std::shared_ptr<ModelRepository> ModelRepository::repositoryInstance(nullptr);

ModelRepository* ModelRepository::getModelRepository()
{
    //singleton pattern, if timerInstance does not exist create one and return pointer to timerInstance
  //otherwise only return pointer
    if (!repositoryInstance) {
        repositoryInstance.reset(new ModelRepository());
    }
    return repositoryInstance.get();
	return nullptr;
}

std::shared_ptr<Model> ModelRepository::getModel(int id)
{
    return ModelRepository::getModelRepository()->_getModel(id);
}

ModelRepository::ModelRepository() {
    //constructor initializes all models
    models[FAIRY_ID] = std::make_shared<FairyModel>(FairyModel());
    models[SHELF_GROUND_ID] = std::make_shared<AssimpModel>(AssimpModel(SHELF_GROUND_ID));
    models[SHELF_LBORDER_ID] = std::make_shared<AssimpModel>(AssimpModel(SHELF_LBORDER_ID));
    models[SHELF_RBORDER_ID] = std::make_shared<AssimpModel>(AssimpModel(SHELF_RBORDER_ID));
    models[LINVISIBLE_WALL_ID] = std::make_shared<AssimpModel>(AssimpModel(LINVISIBLE_WALL_ID));
    models[RINVISIBLE_WALL_ID] = std::make_shared<AssimpModel>(AssimpModel(RINVISIBLE_WALL_ID));
    models[RUPEE_GREEN_ID] = std::make_shared<AssimpModel>(AssimpModel(RUPEE_GREEN_ID, true));
    models[RUPEE_RED_ID] = std::make_shared<AssimpModel>(AssimpModel(RUPEE_RED_ID, true));
    models[RUPEE_BLUE_ID] = std::make_shared<AssimpModel>(AssimpModel(RUPEE_BLUE_ID, true));
    models[RUPEE_YELLOW_ID] = std::make_shared<AssimpModel>(AssimpModel(RUPEE_YELLOW_ID, true));
    models[RUPEE_PURPLE_ID] = std::make_shared<AssimpModel>(AssimpModel(RUPEE_PURPLE_ID, true));
    models[SPIKEBALL_ID] = std::make_shared<AssimpModel>(AssimpModel(SPIKEBALL_ID, true));
    models[POWER1_ID] = std::make_shared<AssimpModel>(AssimpModel(POWER1_ID, true));
    models[POWER2_ID] = std::make_shared<AssimpModel>(AssimpModel(POWER2_ID, true));
    models[POWER3_ID] = std::make_shared<AssimpModel>(AssimpModel(POWER3_ID, true));
    models[SWORD_POWERUP_ID] = std::make_shared<AssimpModel>(AssimpModel(SWORD_POWERUP_ID, true));
    models[SWORD_PROJECTILE_ID] = std::make_shared<AssimpModel>(AssimpModel(SWORD_PROJECTILE_ID, false));
    models[HEART_ID] = std::make_shared<AssimpModel>(AssimpModel(HEART_ID, true));
    models[ZELDALOGO_ID] = std::make_shared<AssimpModel>(AssimpModel(ZELDALOGO_ID, true));
    models[CROSS_ID] = std::make_shared<AssimpModel>(AssimpModel(CROSS_ID, true));
    models[WHITE_RECTAGLE_ID] = std::make_shared<AssimpModel>(AssimpModel(WHITE_RECTAGLE_ID, false));
    models[RED_RECTANGLE_ID] = std::make_shared<AssimpModel>(AssimpModel(RED_RECTANGLE_ID, false));
    models[GAME_MENU] = std::make_shared<AssimpModel>(AssimpModel(GAME_MENU, false));
    models[START_BUTTON] = std::make_shared<AssimpModel>(AssimpModel(START_BUTTON, false)); 
}

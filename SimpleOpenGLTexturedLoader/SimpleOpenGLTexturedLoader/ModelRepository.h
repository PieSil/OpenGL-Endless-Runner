#pragma once
#include <memory>
#include <map>
#include "Model.h"
#include "AssimpModel.h"
#include "FairyModel.h"
#include "Const.h"

class ModelRepository
{
public:

	~ModelRepository() {}; //dest

	static ModelRepository* getModelRepository();
	static std::shared_ptr<Model> getModel(int id);
	void animateModels() {
		for ( auto i = models.begin(); i != models.end(); i++)
		{
			(*i).second->animate();
		}
	}

	void resetAllAnimations() {
		for (auto i = models.begin(); i != models.end(); i++)
		{
			(*i).second->resetAnimation();
		}
	}
private:

	explicit ModelRepository(); //private constructor, enables Singleton pattern
	std::shared_ptr<Model> _getModel(int id) {
		return models[id];
	};
	static std::shared_ptr<ModelRepository> repositoryInstance;
	std::map<int, std::shared_ptr<Model>> models;
};


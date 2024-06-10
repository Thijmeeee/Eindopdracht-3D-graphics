#pragma once

#include <memory>
#include <unordered_map>

#include "components/ModelComponent.h"

class ScoreManager {
private:
	std::unordered_map<int, std::shared_ptr<ModelComponent>> numbersModels;

public:
	ScoreManager() {
        for (int i = 0; i < 10; ++i) {
            std::string filePath = "./assets/numbers/" + std::to_string(i) + ".obj";
            auto numberModel = std::make_shared<ModelComponent>(filePath);
            numberModel->loadModel();
            numbersModels[i] = numberModel;
        }
	}

    std::shared_ptr<ModelComponent> getNumberModel(int number) {
        if (numbersModels.find(number) != numbersModels.end()) {
            return numbersModels[number];
        }
        return nullptr;
    }

};

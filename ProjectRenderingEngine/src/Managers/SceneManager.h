#pragma once

#include <vector>
#include <string>
#include "LightingInformation.h"

class Scene;

class SceneManager {
public:
	static SceneManager* GetInstance() {
		if (m_Instance) {
			return m_Instance;
		}
		m_Instance = new SceneManager();
		return m_Instance;
	}

	~SceneManager() = default;

	inline Scene* GetCurrentScene() { return *m_SceneIterator; }
	inline Scene* GetNextScene() {
		std::advance(m_SceneIterator, 1);
		if (m_SceneIterator == m_Scenes.end()) {
			m_SceneIterator = m_Scenes.begin();
		}
		return *m_SceneIterator;
	}
	inline std::vector<Scene*> GetAllScenes() { return m_Scenes; }

private:
	static SceneManager* m_Instance;
	SceneManager();

	std::vector<Scene*> m_Scenes;
	std::vector<Scene*>::iterator m_SceneIterator;

	void LoadIceScene();
	void LoadOceanScene();
	void LoadSunsetScene();
};
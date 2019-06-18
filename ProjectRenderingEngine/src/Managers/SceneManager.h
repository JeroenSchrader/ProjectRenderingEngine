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

private:
	static SceneManager* m_Instance;
	SceneManager();

	std::vector<Scene*> m_Scenes;
	std::vector<Scene*>::iterator m_SceneIterator;

	std::string m_CurrentShader;
	const std::string m_MirrorShader = "MirrorShader.glsl";

	void LoadIceScene();
	void LoadOceanScene();
	void LoadSunsetScene();
};
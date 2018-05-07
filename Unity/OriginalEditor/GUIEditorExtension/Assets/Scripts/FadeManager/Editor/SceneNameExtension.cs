#if UNITY_EDITOR

using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CustomPropertyDrawer(typeof(SceneNameAttribute))]
public class SceneNameExtension : PropertyDrawer 
{
	private int index_ = 0;
	private List<int> sceneNumbers_ = new List<int>();
	private List<string> sceneNames_ = new List<string>();

	// 省略化
	private SceneNameAttribute attributeName
	{
		get
		{
			return (SceneNameAttribute)attribute;
		}
	}

	public override void OnGUI(Rect rect, SerializedProperty property, GUIContent content)
	{
		content.text = "SceneName";

		ScenesSearch();
		int[] sceneNumbers = sceneNumbers_.ToArray();
		string[] sceneNames = sceneNames_.ToArray();

		ApplyLastSetting(sceneNames, property.stringValue);

		attributeName.sceneIndex_ = EditorGUI.IntPopup(rect, content.text, attributeName.sceneIndex_, sceneNames, sceneNumbers);
		property.stringValue = sceneNames[attributeName.sceneIndex_];
	}

	private void ScenesSearch()
	{
		foreach (EditorBuildSettingsScene child in EditorBuildSettings.scenes)
		{
			string path = child.path.Replace("Assets/", "").Replace(".unity", "");

			sceneNumbers_.Add(index_);
			sceneNames_.Add(path);
			index_++;
		}
		index_ = 0;
	}

	private void ApplyLastSetting(string[] scenes, string lastScene)
	{
		if (!IsLastSetting(lastScene)) return;

		attributeName.sceneIndex_ = LastSceneIndex(scenes, lastScene);
	}

	private bool IsLastSetting(string lastScene)
	{
		return !string.IsNullOrEmpty(lastScene);
	}

	private int LastSceneIndex(string[] scenes, string lastScene)
	{
		int sceneIndex = 0;
		bool sceneDetection = false;
		foreach (string sceneName in scenes)
		{
			if (sceneName == lastScene)
			{
				sceneDetection = true;
				break;
			}
			sceneIndex++;
		}
		return sceneDetection ? sceneIndex : 0;
	}
}

#endif
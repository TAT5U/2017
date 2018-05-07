using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerNameManager : MonoBehaviour 
{
	private string objectName;
	private string charaString_;
	private List<GameObject> name_ = new List<GameObject>();
	private int count_ = 0;
	private bool isFlash = false;
	private bool isDecision = false;

	[SerializeField]
	private NameSceneManager nameManager_;

	void Start()
	{
		objectName = gameObject.name;
		objectName = objectName.Replace("Name", "");

		foreach (Transform nameChild in transform)
		{
			name_.Add(nameChild.gameObject);
		}
	}

	void Update()
	{
		if (!isFlash)
		{
			if (count_ > 0)
			{
				name_[count_ - 1].GetComponent<FlashScript>().StopFlash();
			}
			name_[count_].GetComponent<FlashScript>().FlashStart(name_[count_].gameObject);
			isFlash = true;
		}

	}

	public void SetCharaName(string nameKey)
	{
		if (nameKey == "" || isDecision) return;

		name_[count_].GetComponentInChildren<Text>().text = nameKey;
		if (count_ < name_.Count - 1)
		{
			count_++;
			isFlash = false;
		}
	}

	public void DeleteCharaString()
	{
		name_[count_].GetComponentInChildren<Text>().text = "";
		name_[count_].GetComponent<FlashScript>().StopFlash(true);
		if (count_ > 0)
		{
			count_--;
		}
		isFlash = false;
	}

	public void PlayerNameWrite()
	{
		int nameCount = 0;

		while (nameCount < name_.Count)
		{
			charaString_ += name_[nameCount].GetComponentInChildren<Text>().text;

			name_[nameCount].GetComponent<Image>().color =
				new Color(name_[nameCount].GetComponent<Image>().color.r, name_[nameCount].GetComponent<Image>().color.g, name_[nameCount].GetComponent<Image>().color.b, 0.0f);
			nameCount++;
		}

		nameManager_.PlayerNameWrite(int.Parse(objectName.Replace("Player", "")) - 1, charaString_);

		isFlash = true;
		isDecision = true;

		// Debug
		print("名前を決定しました");
		print("名前 : " + nameManager_.PlayerNameLoad()[int.Parse(objectName.Replace("Player", "")) - 1]);
	}
}

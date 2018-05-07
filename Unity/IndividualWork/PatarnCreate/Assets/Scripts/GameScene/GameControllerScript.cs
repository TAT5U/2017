using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameControllerScript : MonoBehaviour 
{
	public string level;

	bool isFlg = false;

	private SelectLevelScript select;

	void Start()
	{
		select = gameObject.AddComponent<SelectLevelScript>();
	}

	// Update is called once per frame
	void Update () 
	{
		if (Application.platform == RuntimePlatform.IPhonePlayer)
		{
			if (Input.GetTouch(0).phase == TouchPhase.Began)
			{
				if (!isFlg)
				{
					isFlg = true;
					select.SetLevel(level);
				}
			}
		}
		else
		{
			if (Input.GetKey("down"))
			{
				if (!isFlg)
				{
					isFlg = true;
					select.SetLevel(level);
				}
			}
		}
	}
}

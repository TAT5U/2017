using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickManager : MonoBehaviour 
{
	private int sceneManageCount_ = 0;

	public bool IsClickOK()
	{
		if (sceneManageCount_ > 0) return false;

		sceneManageCount_++;
		return true;
	}

	public void CountInitialize()
	{
		print("Initialize");
		sceneManageCount_ = 0;
	}
}

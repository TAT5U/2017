using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class APILevelManager : MonoBehaviour 
{
	protected virtual void APIJudge()
	{
		AndroidJavaClass judgeClass = new AndroidJavaClass("android.os.Build$VERSION");
		int apiLevel = judgeClass.GetStatic<int>("SDK_INT");
		if (apiLevel >= 24)
		{
			gameObject.SetActive(false);
		}
	}
}

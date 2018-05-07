using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeInScript : MonoBehaviour 
{
	private Color fadeInColor;
	public float fadeInSpeed;

	private bool fadeFlg;
	//private List<GameObject> objectName;
	private Text objectName;

	// Use this for initialization
	//public void FadeStart (List<GameObject> dispObject) 
	//{
	//	objectName = new List<GameObject>();
	//	objectName = dispObject;
	//	fadeFlg = false;
	//	fadeInColor = new Color(1.0f, 1.0f, 1.0f, 0.0f);
	//	objectName[0].GetComponent<Image>().color = fadeInColor;
	//	StartCoroutine("FadeInScene");
	//}

	public void FadeStart(Text dispObject)
	{
		//objectName = new List<Text>();
		objectName = dispObject;
		fadeFlg = false;
		fadeInColor = new Color(1.0f, 1.0f, 1.0f, 0.0f);
		objectName.GetComponent<Text>().color = fadeInColor;
		//objectName[0].GetComponent<Image>().color = fadeInColor;
		StartCoroutine("FadeInScene");
	}

	// 関数に永久ループをいれるとフリーズするのでコルーチン使用
	//IEnumerator FadeInScene()
	//{
	//	while (true)
	//	{
	//		foreach (GameObject obj in objectName)
	//		{
	//			obj.GetComponent<Image>().color = fadeInColor;
	//		}
	//		fadeInColor.a += fadeInSpeed;
	//		if (fadeInColor.a >= 1.0f)
	//		{
	//			fadeFlg = true;
	//			StopCoroutine("FadeInScene");
	//		}
	//		yield return null;
	//	}
	//}

	IEnumerator FadeInScene()
	{
		while (true)
		{
			//foreach (Text obj in objectName)
			//{
				objectName.GetComponent<Text>().color = fadeInColor;
			//}
			fadeInColor.a += fadeInSpeed;
			if (fadeInColor.a >= 1.0f)
			{
				fadeFlg = true;
				StopCoroutine("FadeInScene");
			}
			yield return null;
		}
	}

	public bool FadeJudge()
	{
		return fadeFlg;
	}
}

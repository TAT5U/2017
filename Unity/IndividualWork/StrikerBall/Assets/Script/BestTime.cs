using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BestTime : MonoBehaviour {

	// Use this for initialization
	void Start () 
	{
		if (Mathf.FloorToInt(PlayerPrefs.GetFloat("BestTime")) < 999)
		{
			GetComponent<Text>().text = "最短時間  " + Mathf.FloorToInt(PlayerPrefs.GetFloat("BestTime")).ToString() + "秒";
		}
		else
		{
			GetComponent<Text>().text = "最短時間  " + "未測定";
		}
	}
}

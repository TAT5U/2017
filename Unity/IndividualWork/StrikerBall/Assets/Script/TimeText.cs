using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TimeText : MonoBehaviour 
{
	public TimeManager time_;
	
	// Update is called once per frame
	void Update () 
	{
		GetComponent<Text>().text = "経過時間 : " + Mathf.FloorToInt(time_.GetTime()).ToString() + "秒";
	}
}

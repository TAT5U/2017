using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Result : MonoBehaviour {

	// Use this for initialization
	void Start () 
	{
		GetComponent<Text>().text = "経過時間  " + Mathf.FloorToInt(PlayerPrefs.GetFloat("Time")).ToString() + "秒";
	}
}

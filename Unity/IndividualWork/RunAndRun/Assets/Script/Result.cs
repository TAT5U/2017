using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Result : MonoBehaviour 
{
	void Awake()
	{
		GetComponent<Text>().text += PlayerPrefs.GetInt("Score").ToString() + "m";
		PlayerPrefs.DeleteAll();
	}
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConfigScript : MonoBehaviour 
{
	private const string speaker = "Speaker";
	private const string vibration = "Vibration";
	private string backName;

	private bool getFlg;
	public bool reBGMFlg = false;

	public void SetInitialize()
	{
		if (!PlayerPrefs.HasKey(speaker))
		{
			SetSpeaker(true);
		}
		if (!PlayerPrefs.HasKey(vibration))
		{
			SetVibration(true);
		}

		if (!PlayerPrefs.HasKey(backName))
		{
			SetBackName("");
		}
	}
	
	// Update is called once per frame
	void Update () 
	{
	}
	public void SetSpeaker(bool value)
	{
		PlayerPrefs.SetInt(speaker, value ? 1 : 0);
	}
	public void SetVibration(bool value)
	{
		PlayerPrefs.SetInt(vibration, value ? 1 : 0);
	}

	public void SetBackName(string value)
	{
		PlayerPrefs.SetString(backName, value);
	}


	public bool GetSpeaker()
	{
		return getFlg = PlayerPrefs.GetInt(speaker) == 1;
	}
	public bool GetVibration()
	{
		return getFlg = PlayerPrefs.GetInt(vibration) == 1;
	}

	public string GetBackName()
	{
		return PlayerPrefs.GetString(backName);
	}




	public void DeleteBackResultFlg()
	{
		PlayerPrefs.DeleteKey(backName);
	}
	// Not root
	public void DeleteData()
	{
		PlayerPrefs.DeleteAll();
	}
}
